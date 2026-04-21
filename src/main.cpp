#include <iostream>
#include <sstream>
#include <iomanip>
#include "CampusCompass.h"

using namespace std;


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
            //Make sure you add all the input checking for insert here
            string name;
            string ufid;
            int location_id;
            int N;
            ss >> quoted(name);
            ss >> ufid;
            ss >> location_id;
            ss >> N;
            set<string> classes;
            for (int j = 0; j < N; j++) {
                string class_name;
                ss >> class_name;
                classes.insert(class_name);
            }
            compass.insert(ufid, name, location_id, classes);
        }

        else if(command == "remove") {
            string ufid;
            if (!(ss >> ufid)) {
                cout << "unsuccessful" << endl;
                continue;
            }
            bool notNum = false;
            for(int k = 0; k < (int)ufid.length(); k++) {
                if (!isdigit(ufid[k])) {
                    notNum = true;
                }
            }
            if ((int)ufid.length() != 8) {
                cout << "unsuccessful" << endl;
                continue;
            }
            if (notNum) {
                cout << "unsuccessful" << endl;
            }
            else {;
                compass.remove(ufid);
            }

        }

        else if(command == "dropClass") {
            //Check if everything is valid
            string ufid;
            string class_code;
            if (!(ss >> ufid)) {
                cout << "unsuccessful" << endl;
                continue;
            }
            bool notNum = false;
            for(int k = 0; k < (int)ufid.length(); k++) {
                if (!isdigit(ufid[k])) {
                    notNum = true;
                }
            }
            if ((int)ufid.length() != 8) {
                cout << "unsuccessful" << endl;
                continue;
            }
            if (notNum) {
                cout << "unsuccessful" << endl;
            }
            ss >> class_code;
            compass.dropClass(ufid, class_code);

        }
        else if(command == "replaceClass") {

        }
        else if(command == "removeClass") {

        }
        else if(command == "toggleEdgesClosure") {

        }
        else if(command == "checkEdgesStatus") {
;
        }
        else if(command == "isConnected") {
;
        }
        else if(command == "printShortestEdges") {
;
        }
        else if(command == "StudentZone") {
   ;
        }
        else if(command == "verifySchedule") {

        }
        else {
            cout << "unsuccessful" << endl;
        }
    }
    return 0;
}
