#include "dataset.h"
#include "analysis.h"
#include <iostream>

using namespace std;

int main() {
    Dataset dataset;

    // Load Titanic training data from the data folder.
    if (!dataset.loadCSVfile("data/train.csv")) {
        cout << "Failed to load dataset" << endl;
        return 1;
    }
    
    // Print how many passengers were succesfully loaded.
    cout << "Passengers loaded: " << dataset.getPassengers().size() << endl;
    
    // Run the full survival pattern analysis.
    Analyzer::runAnalysis(dataset.getPassengers());

    return 0;
}