#include "CampusCompass.h"
#include<fstream>
#include<sstream>
#include <iostream>
#include <ostream>
#include <string>

using namespace std;

Edge::Edge(int to, int weight, bool isClosed) {
    this->to = to;
    this->weight = weight;
    this->isOpen = isClosed;
}

Student::Student(string name, int residence, set<string> classes){
    this->name = name;
    this->residence = residence;
    this->classes = classes;
}

CampusCompass::CampusCompass() {
    // initialize your object
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
        Edge edge(location_2, weight, true);
        graph[location_1].push_back(edge);
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
        valid_classes.insert(class_code);
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
    set<string>& classes = it->second.classes;
    if (it == students.end()) {
        cout << "unsuccessful" << endl;
        return false;
    }

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

    for (auto student: students) {
        if (student.second.classes.find(class_code )!= student.second.classes.end()) {
            student.second.classes.erase(class_code);

            //Checks to see if student no longer has classes
            if (student.second.classes.size() == 0) {
                students.erase(student.first);
            }
            count++;
        }
    }

    if (count == 0) {
        cout << "unsuccessful" << endl;
        return false;
    }

    cout << count << endl;
    //Check to see if we need to remove class from valid
    return true;
}

bool CampusCompass::toggleEdgesClosure(int n, vector<int> locations) {
    int count = 0;
    int index = 0;
    int index2 = index + 1;
    while (count < n && index < locations.size()) {
        for (auto edge : graph[locations[index]]) {
            if (edge.to == locations[index2]) {
                edge.isOpen = !edge.isOpen;
                index2 += 2;
                break;
            }
        }
        index += 2;
        count++;
    }
    cout << "successful" << endl;
    return true;
}

bool CampusCompass::checkEdgesStatus(int location_id_X, int location_id_Y) {
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

    cout << "unsuccessful" << endl;
    return false;
}

void CampusCompass::printShortestEdges(string student_id) {

}

void StudentZone(string student_id) {

}

bool verifySchedule(string student_id){
    return true;
}