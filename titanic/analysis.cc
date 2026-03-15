#include "analysis.h"
#include "condition.h"
#include <iostream>
#include <random>
#include <limits>

using namespace std;

vector<Passenger> Analyzer::makeBootstrapSample(const vector<Passenger>& passengers) {
    vector<Passenger> sample;
    sample.reserve(passengers.size());

    static mt19937 rng(42);
    uniform_int_distribution<int> dist(0, passengers.size() - 1);

    // Sample with replacement
    for (size_t i = 0; i < passengers.size(); i++) {
        sample.push_back(passengers[dist(rng)]);
    }
    return sample;
}

void Analyzer::runAnalysis(const vector<Passenger>& passengers) {
    
    // Tries various combination of conditions.
    // -1 means "do not filter on this feature."
    const int BOOTSTRAP_ITERATIONS = 20000;

    for (int gender = -1; gender <= 1; gender++) {
        for (int pClass = -1; pClass <= 3; pClass++) {
            for (int age = -1; age <= 2; age++) {
                for (int fare = -1; fare <= 2; fare++) {
                    ConditionRes cr = Condition::defineCond(passengers, gender, pClass, age, fare);
                    
                    // Skip weak or tiny conditions before doing heavy work
                    if (cr.matched < 25 || cr.probability < 0.60) {
                        continue;
                }
                    double totalProb = 0.0;
                    double minProb = numeric_limits<double>::max();
                    double maxProb = numeric_limits<double>::lowest();
                    int stableCount = 0;

                    // Heavy computation: repeatedly resample and re-evaluate
                    for (int iter = 0; iter < BOOTSTRAP_ITERATIONS; iter++) {
                        vector<Passenger> samp = makeBootstrapSample(passengers);
                        ConditionRes r = Condition::defineCond(samp, gender, pClass, age, fare);
                        if (r.matched > 0) {
                            totalProb += r.probability;

                            if (r.probability < minProb) {
                                minProb = r.probability;
                            }
                            if (r.probability > maxProb) {
                                maxProb = r.probability;
                            }
                            if (r.probability >= 0.70) {
                                stableCount++;
                            }
                        }/* else {
                            // Branch for rare cases when a resample contains no matches
                            if (minProb > 0.0) {
                                minProb = 0.0;
                            } if (maxProb < 0.0) {
                                maxProb = 0.0;
                            }
                        }  */
                    }

                    double avgProb = totalProb / BOOTSTRAP_ITERATIONS;
                    double stability = static_cast<double>(stableCount) / BOOTSTRAP_ITERATIONS;

                    if (avgProb >= 0.70 && stability >= 0.80) {
                        cout << "Stable condition found:" << endl;
                        cout << "Condition: ";
                        if (gender == 1) {
                            cout << "Gender: Female, ";
                        } else if (gender == 0) {
                            cout << "Gender: Male, ";
                        } if(pClass != -1) {
                            cout << "Class: " << pClass << ", ";
                        }
                        if (age == 0) {
                            cout << "Age: Less than 18, ";
                        } else if (age == 1) {
                            cout << "Age: Between 18 to 40, ";
                        } else if (age == 2) {
                            cout << "Age: 40 or over, ";
                        }
                        if (fare == 0) {
                            cout << "Fare: Under $20 ";
                        } else if(fare == 1) {
                            cout << "Fare: Between $20 to $50 ";
                        } else if (fare == 2) {
                            cout << "Fare: $50 or over ";
                        }

                        cout << endl;
                        cout << "Original matches: " << cr.matched << endl;
                        cout << "Original survival rate: " << cr.probability << endl;
                        cout << "Bootstrap average rate: " << avgProb << endl;
                        cout << "Bootstrap min rate: " << minProb << endl;
                        cout << "Bootstrap max rate: " << maxProb << endl;
                        cout << "Stability (rate >= 0.70): " << stability << endl;
                    }
            }
        }
    }
}
} 
