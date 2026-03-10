#ifndef ANALYSIS_H
#define ANALYSIS_H

#include "dataset.h"
#include <vector>

// Runs the full Titanic analysis by testing various condition combinations.
class Analyzer {
    public:
        static void runAnalysis(const std::vector<Passenger>& passengers);
    private:
        static std::vector<Passenger> makeBootstrapSample(const std::vector<Passenger>& passengers);
};

#endif
