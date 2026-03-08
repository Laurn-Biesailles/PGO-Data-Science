#include "condition.h"

using namespace std;


ConditionRes Condition::defineCond(
    const std::vector<Passenger>& passengers, int gender, int pclass, int ageGroup, int fareGroup
) {
    int matched  = 0;
    int survived = 0;
    
    // Check every passenger against the current condition.
    for (const auto& p : passengers) {
        bool cond = true;

        // Apply gender condition if specified.
        if (gender != -1) {
            cond = cond && (p.sex == gender);
        }

        // Apply ticket class condition if specified.
        if (pclass != -1) {
            cond = cond && (p.pClass == pclass);
        }

        // Apply age grouping condition.
        if (ageGroup != -1) {
            if (ageGroup == 0) {
                cond = cond && (p.age < 18);
            } else if (ageGroup == 1) {
                cond = cond && (p.age >= 18 && p.age < 40);
            } else {
                cond = cond && (p.age >= 40);
            }
        }

        // Apply fare grouping condition.
        if (fareGroup != -1) {
            if (fareGroup == 0) {
                cond = cond && (p.fare < 20);
            } else if (fareGroup == 1) {
                cond = cond && (p.fare >= 20 && p.fare < 50);
            } else {
                cond = cond && (p.fare >= 50);
            }
        }
        
        // If passenger satisfies all active conditions, count them.
        if (cond) {
            matched++;
            if (p.survived) {
                survived++;
            }
        }
    }

    ConditionRes cr;
    cr.matched     = matched;
    cr.survived    = survived;
    cr.probability = matched ? (double)survived / matched : 0;

    return cr;
    
}