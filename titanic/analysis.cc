#include "analysis.h"
#include "condition.h"
#include <iostream>

using namespace std;

void Analyzer::runAnalysis(const vector<Passenger>& passengers) {
    
    // Tries various combination of conditions.
    // -1 means "do not filter on this feature."
    for (int gender = -1; gender <= 1; gender++) {
        for (int pClass = -1; pClass <= 3; pClass++) {
            for (int age = -1; age <= 2; age++) {
                for (int fare = -1; fare <= 2; fare++) {
                    ConditionRes cr = Condition::defineCond(passengers, gender, pClass, age, fare);
                    
                    // Print only interesting rules: enough matching passengers and strong survival rate.
                    if (cr.matched >= 20 && cr.probability >= 0.70) {
                        cout << "Condition: ";
                        if (gender == 1) {
                            cout << "Gender: Female, ";
                        }
                        if (gender == 0) {
                            cout << "Gender: Male, ";
                        }
                        if (pClass != -1) {
                            cout << "Class: " << pClass << ", ";
                        }
                        if (age == 0) {
                            cout << "Age: Less than 18, ";
                        }
                        if (age == 1) {
                            cout << "Age: Between 18 to 40, ";
                        }
                        if (age == 2) {
                            cout << "Age: 40 or over, ";
                        }
                        if (fare == 0) {
                            cout << "Fare: Under 20, ";
                        }
                        if (fare == 1) {
                            cout << "Fare: Between 20 to 50, ";
                        }
                        if (fare == 2) {
                            cout << "Fare: 50 or over, ";
                        }
                        
                        cout << "\nMatches: Passenger ID: " << cr.matched << ", Survival Rate: " << cr.probability << endl;
                    }
                }
            }
        }
    }
} 