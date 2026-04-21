#pragma once
#include <map>
#include <set>
#include <string>
#include <unordered_set>

using namespace std;

struct Edge {
    int to;
    int weight;
    bool isOpen;

    Edge(int to, int weight, bool isClosed);
};

struct Student {
    string name;
    int residence;
    set<string> classes;

    Student(string name, int residence, set<string> classes);
};

class CampusCompass {
private:
    unordered_set<string> valid_classes;
    unordered_map<int, vector<Edge>> graph;
    unordered_map<string, Student> students;

public:
    // Think about what helper functions you will need in the algorithm
    CampusCompass(); // constructor
    bool ParseCSV(const string &edges_filepath, const string &classes_filepath);
    bool insert(string student_name, string student_id, int residence_location_id, set<string> class_codes);
    bool remove(string student_id);
    bool dropClass(string student_id, string class_code);
    bool replaceClass (string student_id, string class_code1, string class_code2);
    bool removeClass(string class_code);
    bool toggleEdgesClosure(int n, vector<int> locations);
    bool checkEdgesStatus(int location_id_X, int location_id_Y);
    bool isConnected(int location_id_1, int location_id_2);
    void printShortestEdges(string student_id);
    void StudentZone(string student_id);
    bool verifySchedule(string student_id);


};
