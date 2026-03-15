#include "dataset.h"
#include "analysis.h"
#include <iostream>

using namespace std;

int main() {
    Dataset dataset;
	string user_dataset = "";
	getline(cin, user_dataset);

    // Load Titanic training data from the data folder.
    if (!dataset.loadCSVfile(user_dataset)) {
        cout << "Failed to load dataset" << endl;
        return 1;
    }
    
    // Print how many passengers were succesfully loaded.
    cout << "Passengers loaded: " << dataset.getPassengers().size() << endl;   
    // Run the full survival pattern analysis.
    Analyzer::runAnalysis(dataset.getPassengers());
	
	/*
    // Load testing data1 from the data folder.
    if (!dataset.loadCSVfile("data/dataset1.csv")) {
        cout << "Failed to load dataset" << endl;
        return 1;
    }
  
    // Print how many passengers were succesfully loaded.
    cout << "Dataset1: " << dataset.getPassengers().size() << endl;   
    // Run the full survival pattern analysis.
    Analyzer::runAnalysis(dataset.getPassengers());

	
    // Load Titanic training data from the data folder.
    if (!dataset.loadCSVfile("data/dataset2.csv")) {
        cout << "Failed to load dataset" << endl;
        return 1;
    }
    
    // Print how many passengers were succesfully loaded.
    cout << "Dataset2: " << dataset.getPassengers().size() << endl;   
    // Run the full survival pattern analysis.
    Analyzer::runAnalysis(dataset.getPassengers());

    // Load Titanic training data from the data folder.
    if (!dataset.loadCSVfile("data/dataset3.csv")) {
        cout << "Failed to load dataset" << endl;
        return 1;
    }
    
    // Print how many passengers were succesfully loaded.
    cout << "Dataset3: " << dataset.getPassengers().size() << endl;   
    // Run the full survival pattern analysis.
    Analyzer::runAnalysis(dataset.getPassengers());

    // Load Titanic training data from the data folder.
    if (!dataset.loadCSVfile("data/dataset4.csv")) {
        cout << "Failed to load dataset" << endl;
        return 1;
    }
    
    // Print how many passengers were succesfully loaded.
    cout << "Dataset4: " << dataset.getPassengers().size() << endl;   
    // Run the full survival pattern analysis.
    Analyzer::runAnalysis(dataset.getPassengers());
*/
    return 0;
}
