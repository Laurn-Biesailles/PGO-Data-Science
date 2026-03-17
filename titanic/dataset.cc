#include "dataset.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <cctype>

using namespace std;

/* Splits a CSV line while reviewing quoted text.
   This is necessary because Titanic names contain commas,
   such as: "Braund, Mr. Owen Harris" 
*/

static vector<string> splitCSVLine(const string& line){

    vector<string> fields;
    string current;
    bool inQuotes = false;

    for (size_t i = 0; i < line.size(); i++) {
        char c = line[i];

        // Toggle quote mode when a double quote is found.
        if (c == '"') {
            inQuotes = !inQuotes;

        }
        // Onky splits commas that are not inside quotes. 
        else if (c == ',' && !inQuotes) {
            fields.push_back(current);
            current.clear();
        } else {
            current += c;
        }
    }
    
    // Add the last field after the loop ends.
    fields.push_back(current);
    return fields;

}



bool Dataset::loadCSVfile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Can't open file: " << filename << endl;
        return false;
    }
    passengers.clear();

    string line;
    getline(file, line);  // Skip the header row

    while(getline(file, line)) {
        
		if (line.empty()){
            continue;
        }
        vector<string> fields = splitCSVLine(line);

        // Skip incomplete or incorrect rows.
        if (fields.size() < 10) {
            continue;
        }

        try {
            
            Passenger p;

            // Extract only the columns needed for analysis
            p.survived = stoi(fields[1]);
            p.pClass   = stoi(fields[2]);
            p.sex = (fields[4] == "male") ? 0 : 1;

            // Missing ages are stored as -1. (This helps to handle null data)
            if(fields[5].empty()){
                p.age = -1.0;
            } else {
                p.age = stod(fields[5]);
            }

            p.sibsp = stoi(fields[6]);
            p.parch = stoi(fields[7]);

            // Missing fares are treated as 0.
            if (fields[9].empty()){
                p.fare = 0.0;
            } else {
                p.fare = stod(fields[9]);
            }

            passengers.push_back(p);

        } catch (...) {
            // If conversion fails, ignore the bad row and continue.
            continue;
        }
    }

    return true;
}

const vector<Passenger>& Dataset::getPassengers() const {
    return passengers;
}
