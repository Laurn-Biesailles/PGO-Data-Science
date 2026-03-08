#ifndef CONDITION_H
#define CONDITION_H

#include "dataset.h"


// Stores the result of testing one condition against the dataset.
struct ConditionRes {
    int matched;    // Number of passengers matching the condition
    int survived;   // Number of matched passengers who survived
    double probability; // Survival rate among matched passengers
};

// Evaluates condition combination on the dataset.
class Condition {
    public:
        // Tests one condition made from gender, class, age group, and fare group.
        static ConditionRes defineCond(
            const std::vector<Passenger>& passengers,
            int gender,
            int pClass,
            int ageGroup,
            int fareGroup
        );
};

#endif