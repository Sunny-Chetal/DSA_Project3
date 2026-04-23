#include "CampusCompass.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <ostream>
#include <string>

using namespace std;

Edge::Edge(int from, int to, int weight, bool isOpen) {
    this->from = from;
    this->to = to;
    this->weight = weight;
    this->isOpen = isOpen;
}

Student::Student(string name, int residence, set<string> classes){
    this->name = name;
    this->residence = residence;
    this->classes = classes;
}

CampusCompass::CampusCompass() {
    // initialize your object
}

int CampusCompass::timeConverter(string time) {
    //Separate minutes and hours
    stringstream ss(time);
    string hours_s, minutes_s;
    getline(ss, hours_s, ':');
    getline(ss, minutes_s);

    int hours = stoi(hours_s);
    int minutes = stoi(minutes_s);

    //Turn into total minutes from 12:00AM
    hours *= 60;
    int total = hours + minutes;
    return total;
}

bool CampusCompass::ParseCSV(const string &edges_filepath, const string &classes_filepath) {
    ifstream file(edges_filepath);
    if (!file.is_open()) {
        cerr << "Error: Could not open file. " << endl;
        return false;
    }
    string line;
    getline(file, line);
    while (getline(file, line)) {
        stringstream ss(line);
        string token;
        getline(ss, token, ',');
        int location_1 = stoi(token);
        getline(ss, token, ',');
        int location_2 = stoi(token);
        getline(ss, token, ',');
        string name_1 = token;
        getline(ss, token, ',');
        string name_2 = token;
        getline(ss, token, ',');
        int weight = stoi(token);
        Edge edge(location_1, location_2, weight, true);
        Edge edge2(location_2, location_1, weight, true);
        graph[location_1].push_back(edge);
        graph[location_2].push_back(edge2);

    }

    ifstream file2(classes_filepath);
    if (!file2.is_open()) {
        cerr << "Error: Could not open file. " << endl;
        return false;
    }
    string line2;
    getline(file2, line2);
    while (getline(file2, line2)) {
        stringstream ss(line2);
        string token;
        getline(ss, token, ',');
        string class_code = token;
        getline(ss, token, ',');
        int locationid = stoi(token);
        getline(ss, token, ',');
        string start_time = token;
        getline(ss, token, ',');
        string end_time = token;
        valid_classes.insert({class_code, locationid});
        int start = timeConverter(start_time);
        int end = timeConverter(end_time);
        class_times.insert({class_code, {start, end}});
    }
    return true;
}


bool CampusCompass::insert(string student_name, string student_id, int residence_location_id, set<string> class_codes) {
    //Most input checks in main
    //Checks if student is already in container
    if (students.find(student_id) != students.end()) {
        cout << "unsuccessful" << endl;
        return false;
    }
    Student student(student_name, residence_location_id, class_codes);
    students.insert({student_id, student});
    cout << "successful" << endl;
    return true;
}

bool CampusCompass::remove(string student_id) {
    //Checks if student isn't in the container
    if (students.find(student_id) == students.end()) {
        cout << "unsuccessful" << endl;
        return false;
    }
    students.erase(student_id);
    cout << "successful" << endl;
    return true;
}

bool CampusCompass::dropClass(string student_id, string class_code) {
    //Checks if student exists
    auto it = students.find(student_id);
    if (it == students.end()) {
        cout << "unsuccessful" << endl;
        return false;
    }
    set<string>& classes = it->second.classes;

    //Checks if class exists
    if (find(classes.begin(), classes.end(), class_code) == classes.end()) {
        cout << "unsuccessful" << endl;
        return false;
    }

    classes.erase(class_code);
    //Checks if student no longer has classes
    if (classes.size() == 0) {
        students.erase(student_id);
    }
    cout << "successful" << endl;
    return true;
}

bool CampusCompass::replaceClass(string student_id, string class_code1, string class_code2) {
    //Checks if student exists
    auto it = students.find(student_id);
    set<string>& classes = it->second.classes;
    if (it == students.end()) {
        cout << "unsuccessful" << endl;
        return false;
    }

    //Checks if class1 not in schedule
    if (find(classes.begin(), classes.end(), class_code1) == classes.end()) {
        cout << "unsuccessful" << endl;
        return false;
    }

    //Checks if class2 already in schedule
    if (find(classes.begin(), classes.end(), class_code2) != classes.end()) {
        cout << "unsuccessful" << endl;
        return false;
    }

    //Checks if class2 exists
    if (valid_classes.find(class_code2) == valid_classes.end()) {
        cout << "unsuccessful" << endl;
        return false;
    }

    classes.erase(class_code1);
    classes.insert(class_code2);
    cout << "successful" << endl;
    return true;
}

bool CampusCompass::removeClass(string class_code) {
    //Checks if class exists
    if (valid_classes.find(class_code) == valid_classes.end()) {
        cout << "unsuccessful" << endl;
        return false;
    }
    int count = 0;
    vector<string> toRemove;

    for (auto& student: students) {
        if (student.second.classes.find(class_code )!= student.second.classes.end()) {
            student.second.classes.erase(class_code);

            //Checks to see if student no longer has classes
            if (student.second.classes.size() == 0) {
                toRemove.push_back(student.first);
            }
            count++;
        }
    }

    for (const string& student : toRemove) {
        students.erase(student);
    }

    if (count == 0) {
        cout << "unsuccessful" << endl;
        return false;
    }

    cout << count << endl;
    return true;
}

bool CampusCompass::toggleEdgesClosure(vector<pair<int , int>> locations) {
    //unordered_map<int, vector<Edge>> graph;


    for (auto location : locations) {
        for (auto& edge: graph[location.first]) {
            if (location.second == edge.to) {
                edge.isOpen = !edge.isOpen;
                break;
            }
        }
    }
    cout << "successful" << endl;
    return true;
}

bool CampusCompass::checkEdgeStatus(int location_id_X, int location_id_Y) {
    for (auto edge : graph[location_id_X]) {
        if (edge.to == location_id_Y) {
            if (edge.isOpen == true) {
                cout << "open" << endl;
                return true;
            }
            if (edge.isOpen == false) {
                cout << "closed" << endl;
                return false;
            }
            break;
        }
    }
    cout << "DNE" << endl;
    return false;
}

bool CampusCompass::isConnected(int location_id_1, int location_id_2) {
    //Adapted from lecture slides
    set<int> visited;
    stack<int> s;
    visited.insert(location_id_1);
    s.push(location_id_1);
    while (!s.empty()) {
        int u = s.top();
        s.pop();
        for (auto edge : graph[u]) {
            if (edge.isOpen) {
                if (edge.to == location_id_2) {
                    cout << "successful" << endl;
                    return true;
                }
                if (visited.find(edge.to) == visited.end()) {
                    visited.insert(edge.to);
                    s.push(edge.to);
                }
            }
        }
    }

    cout << "unsuccessful" << endl;
    return false;
}

void CampusCompass::printShortestEdges(string student_id) {
    //Checks that student exists
    if (students.find(student_id) == students.end()) {
        cout << "unsuccessful" << endl;
        return;
    }

    //Adapted from lecture slides && GeeksForGeeks

    //Dijkstra's Algorithm
    unordered_map<int, int> distance;
    unordered_map<int, int> parent;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    int start = students.at(student_id).residence;
    distance[start] = 0;
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto edge = pq.top();
        pq.pop();
        int u = edge.second;
        int d = edge.first;

        if (d > distance[u]) {
            continue;
        }

        for (auto location : graph[u]) {
            if (location.isOpen){
                int v = location.to;
                int w = location.weight;

                if (!distance.count(v) || distance[u] + w < distance[v]) {
                    distance[v] = distance[u] + w;
                    parent[v] = u;
                    pq.emplace(distance[v], v);
                }
            }
        }
    }

    //To make sure unreachable classes also got initialized
    map<string, int> locations;
    for (auto classes: students.at(student_id).classes) {
        int location = valid_classes.at(classes);
        if (distance.count(location)) {
            locations[classes] = distance[location];
        }
        else {
            locations[classes] = -1;
        }

    }

    cout << "Time For Shortest Edges: " << students.at(student_id).name << endl;
    for (auto class_distance: locations) {
        cout << class_distance.first << ": " << class_distance.second << endl;
    }

}

void CampusCompass::printStudentZone(string student_id) {
    //Checks that student exists
    if (students.find(student_id) == students.end()) {
        cout << "unsuccessful" << endl;
        return;
    }

    //Adapted from lecture slides && GeeksForGeeks

    //Dijkstra's Algorithm
    unordered_map<int, int> distance;
    unordered_map<int, int> parent;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    int start = students.at(student_id).residence;
    distance[start] = 0;
    pq.emplace(0, start);

    while (!pq.empty()) {
        auto edge = pq.top();
        pq.pop();
        int u = edge.second;
        int d = edge.first;

        if (d > distance[u]) {
            continue;
        }

        for (auto location : graph[u]) {
            if (location.isOpen){
                int v = location.to;
                int w = location.weight;

                if (!distance.count(v) || distance[u] + w < distance[v]) {
                    distance[v] = distance[u] + w;
                    parent[v] = u;
                    pq.emplace(distance[v], v);
                }
            }
        }
    }


    //Subgraph
    unordered_set<int> subgraph;
    subgraph.insert(students.at(student_id).residence);
    for (auto classes: students.at(student_id).classes) {
        int location = valid_classes.at(classes);
        if (distance.count(location)) {
            while (location != start) {
                subgraph.insert(location);
                location = parent[location];
            }
        }
    }


    //MST
    int mstTotal = 0;
    unordered_set<int> visited;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> priority;

    priority.push({0, students.at(student_id).residence});

    while (!priority.empty() && visited.size() < subgraph.size()) {
        auto top = priority.top();
        int weight = top.first;
        int u = top.second;
        priority.pop();

        if (visited.count(u)) {
            continue;
        }

        visited.insert(u);
        mstTotal += weight;

        for (auto& edge : graph[u]) {
            if (edge.isOpen && subgraph.count(edge.to) && !visited.count(edge.to)) {
                priority.push({edge.weight, edge.to});
            }
        }
    }
    cout << "Student Zone Cost For " << students.at(student_id).name << ": " << mstTotal << endl;
}

bool CampusCompass::verifySchedule(string student_id) {
    if (students.at(student_id).classes.size() == 1) {
        cout << "unsuccessful" << endl;
        return false;
    }

    //To get the classes in order of start time
    vector<pair<int, string>> classOrdered;
    for (auto studentClasses: students.at(student_id).classes) {
        classOrdered.push_back({class_times[studentClasses].first, studentClasses});
    }
    sort(classOrdered.begin(), classOrdered.end(), [](pair<int, string> a, pair<int, string> b) {
      return a.first < b.first;
    });

    //To create the path needed to be taken
    vector<int> scheduleOrder;
    for (auto place: classOrdered) {
        scheduleOrder.push_back(valid_classes[place.second]);
    }

    cout << "Schedule Check for " << students.at(student_id).name << ":" << endl;

    for (int i = 0; i < scheduleOrder.size() - 1; i++) {
        int start = scheduleOrder[i];
        int end = scheduleOrder[i + 1];
        int gapTime = 0;

        //Calculate amount of time alloted between places
        string startName = classOrdered[i].second;
        string endName = classOrdered[i + 1].second;
        int gapStart = class_times[startName].second;
        int gapEnd = class_times[endName].first;
        gapTime = gapEnd - gapStart;

        //Dijkstra's Algorithm
        unordered_map<int, int> distance;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

        distance[start] = 0;
        pq.emplace(0, start);

        while (!pq.empty()) {
            auto edge = pq.top();
            pq.pop();
            int u = edge.second;
            int d = edge.first;

            if (d > distance[u]) {
                continue;
            }
            if (u == end) {
                break;
            }

            for (auto location : graph[u]) {
                if (location.isOpen){
                    int v = location.to;
                    int w = location.weight;

                    if (!distance.count(v) || distance[u] + w < distance[v]) {
                        distance[v] = distance[u] + w;
                        pq.emplace(distance[v], v);
                    }
                }
            }
        }

        if (distance.count(end) && (gapTime >= distance[end])) {
            cout << classOrdered[i].second << " - " << classOrdered[i + 1].second << ": successful" << endl;
        }
        else {
            cout << classOrdered[i].second << " - " << classOrdered[i + 1].second << ": unsuccessful" << endl;
        }
    }
    return true;
}

