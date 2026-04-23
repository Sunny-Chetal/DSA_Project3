#include <iostream>
#include <sstream>
#include <iomanip>
#include <regex>
#include "CampusCompass.h"

using namespace std;

bool ufidCheck(string ufid) {
    bool notNum = false;
    for(int k = 0; k < (int)ufid.length(); k++) {
        if (!isdigit(ufid[k])) {
            notNum = true;
        }
    }
    if ((int)ufid.length() != 8) {
        cout << "unsuccessful" << endl;
        return false;
    }
    if (notNum) {
        cout << "unsuccessful" << endl;
        return false;
    }
    return true;
}


int main(){
    int n;
    // initialize your main project object
    CampusCompass compass;

    // ingest CSV data
    compass.ParseCSV("data/edges.csv", "data/classes.csv");
    cin >> n;
    cin.ignore(1000, '\n');
    for(int i = 0; i < n; i++) {
        string line;
        getline(cin, line);

        stringstream ss(line);
        string command;
        ss >> command;

        if(command == "insert") {
            string name;
            string ufid;
            int location_id;
            int N;
            ss >> quoted(name);
            ss >> ufid;
            ss >> location_id;
            if (ss.fail()) {
                cout << "unsuccessful" << endl;
                continue;
            }
            ss >> N;
            set<string> classes;
            for (int j = 0; j < N; j++) {
                string class_name;
                ss >> class_name;
                classes.insert(class_name);
            }

            //Check Name
            regex obj("^[a-zA-Z\\s]+$");
            if (!regex_match(name, obj)) {
                cout << "unsuccessful" << endl;
                continue;
            }

            //Check UFID
            bool wrongUFID = ufidCheck(ufid);
            if (wrongUFID == false) {
                continue;
            }

            //Check Classes
            regex obj2("^[A-Z]{3}[0-9]{4}$");
            bool wrongClassName = false;
            for (auto class_names: classes) {
                if (!regex_match(class_names, obj2)) {
                    wrongClassName = true;
                    break;
                }
            }
            if (wrongClassName == true) {
                cout << "unsuccessful" << endl;
                continue;
            }
            if (classes.size() != N || N > 6 || N < 1) {
                cout << "unsuccessful" << endl;
                continue;
            }

            compass.insert(name, ufid, location_id, classes);
        }

        else if(command == "remove") {
            string ufid;

            //Check UFID
            if (!(ss >> ufid)) {
                cout << "unsuccessful" << endl;
                continue;
            }
            bool wrongUFID = ufidCheck(ufid);
            if (wrongUFID == false) {
                continue;
            }

            compass.remove(ufid);
        }

        else if(command == "dropClass") {
            string ufid;
            string class_code;

            //Check UFID
            if (!(ss >> ufid)) {
                cout << "unsuccessful" << endl;
                continue;
            }
            bool wrongUFID = ufidCheck(ufid);
            if (wrongUFID == false) {
                continue;
            }

            //Check Class Code
            ss >> class_code;

            regex obj("^[A-Z]{3}[0-9]{4}$");

            if (!regex_match(class_code, obj)) {
                cout << "unsuccessful" << endl;
                continue;
            }

            compass.dropClass(ufid, class_code);
        }

        else if(command == "replaceClass") {
            string ufid;
            string class_code1, class_code2;

            //Check UFID
            if (!(ss >> ufid)) {
                cout << "unsuccessful" << endl;
                continue;
            }
            bool wrongUFID = ufidCheck(ufid);
            if (wrongUFID == false) {
                continue;
            }

            //Check Class Codes
            ss >> class_code1;
            ss >> class_code2;

            regex obj("^[A-Z]{3}[0-9]{4}$");

            if (!regex_match(class_code1, obj) || !regex_match(class_code2, obj)) {
                cout << "unsuccessful" << endl;
                continue;
            }

            compass.replaceClass(ufid, class_code1, class_code2);
        }

        else if(command == "removeClass") {
            string class_code;

            //Check Class Code
            ss >> class_code;

            regex obj("^[A-Z]{3}[0-9]{4}$");

            if (!regex_match(class_code, obj)) {
                cout << "unsuccessful" << endl;
                continue;
            }

            compass.removeClass(class_code);
        }

        else if(command == "toggleEdgesClosure") {
            int N;

            ss >> N;
            vector<pair<int,int>> locations;
            bool wrongLocationID = false;
            for (int j = 0; j < (N); j++) {
                int location, location2;
                ss >> location >> location2;
                if (ss.fail()) {
                    wrongLocationID = true;
                    break;
                }
                locations.push_back({location, location2});
                locations.push_back({location2, location});
            }

            //Check Locations
            if (wrongLocationID == true) {
                cout << "unsuccessful" << endl;
                continue;
            }
            if (locations.size() != (N * 2) || N < 1) {
                cout << "unsuccessful" << endl;
                continue;
            }

            compass.toggleEdgesClosure(locations);
        }

        else if(command == "checkEdgeStatus") {
;           int location1, location2;

            //Check Locations
            ss >> location1 >> location2;
            if (ss.fail()) {
                cout << "unsuccessful" << endl;
                continue;
            }

            compass.checkEdgeStatus(location1, location2);
        }

        else if(command == "isConnected") {
            int location1, location2;

            //Check Locations
            ss >> location1 >> location2;
            if (ss.fail()) {
                cout << "unsuccessful" << endl;
                continue;
            }

            compass.isConnected(location1, location2);
        }

        else if(command == "printShortestEdges") {
;           string ufid;

            //Check UFID
            if (!(ss >> ufid)) {
                cout << "unsuccessful" << endl;
                continue;
            }
            bool wrongUFID = ufidCheck(ufid);
            if (wrongUFID == false) {
                continue;
            }

            compass.printShortestEdges(ufid);
        }

        else if(command == "printStudentZone") {
   ;        string ufid;

            //Check UFID
            if (!(ss >> ufid)) {
                cout << "unsuccessful" << endl;
                continue;
            }
            bool wrongUFID = ufidCheck(ufid);
            if (wrongUFID == false) {
                continue;
            }

            compass.printStudentZone(ufid);
        }

        else if(command == "verifySchedule") {
            string ufid;

            //Check UFID
            if (!(ss >> ufid)) {
                cout << "unsuccessful" << endl;
                continue;
            }
            bool wrongUFID = ufidCheck(ufid);
            if (wrongUFID == false) {
                continue;
            }

            compass.verifySchedule(ufid);
        }

        else {
            cout << "unsuccessful" << endl;
        }
    }
    return 0;
}
