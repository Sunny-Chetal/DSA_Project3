#pragma once
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <map>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <stack>
#include <queue>
#include <functional>
#include <climits>


using namespace std;

struct Edge {
    int from;
    int to;
    int weight;
    bool isOpen;

    Edge();
    Edge(int from, int to, int weight, bool isClosed);
};

struct Student {
    string name;
    int residence;
    set<string> classes;

    Student(string name, int residence, set<string> classes);
};

class CampusCompass {
private:
    unordered_map<string, pair<int, int>> class_times;
    unordered_map<string, int> valid_classes;
    unordered_map<int, vector<Edge>> graph;
    unordered_map<string, Student> students;

public:
    CampusCompass(); // constructor
    int timeConverter(string time);
    bool ParseCSV(const string &edges_filepath, const string &classes_filepath);
    bool insert(string student_name, string student_id, int residence_location_id, set<string> class_codes);
    bool remove(string student_id);
    bool dropClass(string student_id, string class_code);
    bool replaceClass (string student_id, string class_code1, string class_code2);
    bool removeClass(string class_code);
    bool toggleEdgesClosure(vector<pair<int , int>> locations);
    bool checkEdgeStatus(int location_id_X, int location_id_Y);
    bool isConnected(int location_id_1, int location_id_2);
    void printShortestEdges(string student_id);
    void printStudentZone(string student_id);
    bool verifySchedule(string student_id);
};
