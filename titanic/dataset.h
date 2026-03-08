#ifndef DATASET_H
#define DATASET_H

#include <vector>
#include <string>

// Stores the fields from the dataset that will be used for analysis.
struct Passenger {
    int survived; // 1 if survived, 0 if not
    int pClass;   // Ticket class: 1, 2, or 3
    int sex;      // 0 = male, 1 = female
    double age;   // Passenger age (double used to handle the age since there is decimal values for age in dataset.), -1 if missing
    int sibsp;    // Number of siblings/spouses aboard
    int parch;    // Number of parents/children aboard
    double fare;  // Ticket fare
};

// Handles loading and storing passenger data.
class Dataset {
    public:
        //Reads the CSV file and fills the passenger vector.
        bool loadCSVfile(const std::string& fileName);

        // Returns all loaded passengers.
        const std::vector<Passenger>& getPassengers() const;
    
    private:
        std::vector<Passenger> passengers;

};


#endif