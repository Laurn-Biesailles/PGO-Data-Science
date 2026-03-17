# Titanic Survival Pattern Analyzer

## Project Members

##Person 1 (Data Science):  Amir

##Person 2 (The Tester):  Jack

##Person 3 (Instrumenter):  Gurshan

##Person 4 (Pogo Stick):  Justus


## Overview

This project analyzes the Titanic dataset from Kaggle using C++. The program searches for patterns that correlate with passenger survival by evaluating combinations of demographic and ticket-related features.
The program generates a large number of survival conditions and test how reliable those conditions are through repeated bootstrap resampling. This approach allows the program to identify patterns that are not only strong in the original dataset but also stable across randomized samples.
The analysis performs computationally heavy operations involving nested loops and branching logic so that compiler optimization techniques such as O3, LTO, PGO, and GCOV can be evaluated.
Typical runtime is between 30-60 seconds depending on compiler optimizations and system performance.

## Dataset

The dataset used is the Titanic training dataset available on Kaggle.
Each passenger record includes information such as:
- Survival status
+ Passenger class
* Gender
- Age
+ Number of siblings/spouses aboard
* Number of parents/children aboard
- Ticket fare

The program loads the dataset from:

```data/train.csv ```

Only the fields needed for the analysis are parsed and stored.

## Program Structure

The project is divided into multiple source files to maintain modular design.

## Source Files

```main.cc```

The entry point of the program.

### Responsibilities:
- Load the Titanic dataset
- Report number of passengers loaded
- Run the survival analysis

### dataset.h/dataset.cc

Reponsible for loading and parsing the Titanic CSV dataset.

#### Key features:
- Handles CSV fields with quoted text (names contain commas)
+ Converts missing values safely
* Stores passengers in a vector structure


## Passenger structure used in the project:
Passenger 

`survived | pclass | sex | age | sibsp | parch | fare`

## condition.h/condition.cc

Evaluates survival conditions/rules on a dataset.

A condition is defined by factors such as :

- gender
+ passenger class
* age group
- fare group

## Example condition:

```Female AND Class = 1 AND Age >= 40```

The condition scans the dataset and computes:

- number of passengers matching the condition
+ number of survivors
* survival probability

## analysis.h/analysis.cc

Performs the main analysis.

### Steps performed:
1. Generate combinations of rule conditions
2. Evaluate each condition on the original dataset
3. Filter out weak or small condition
4. Perform bootstrap resampling thousands of times
5. Measure stability of each condition across samlpes

### For each condition the program measures:
- original survival rate
* average survival rate across samples
+ minimum survival rate observed
- maximum survival rate observed
* condition stability

A condition is considered stable if it consistently shows strong survival probability across bootstrap samples.

## Computational Design
The analysis intentionally includes:

### Multiple Nested Loops
The program generates rule combinations through nested loops:
gender loop
passenger class loop
age group loop
fare group loop

Inside these loops the program performs repeated bootstrap simulations.

### Multiple Branching Conditions
Branching occurs when applying rule conditions:
```
if gender condition matches
if class condition matches
if age group matches
if fare group matches
```

### Additional branching is used to:
skip weak rules
handle cases where no passengers match
determine whether rules are stable

## Bootstrap Resampling
Bootstrap sampling randomly selects passengers with replacement to generate many synthetic datasets.
Each rule is evaluated repeatedly on these samples.
This process measures how robust a survival pattern is, rather than relying on a single dataset.

## Compilation
The project uses a Makefile to support different compilation modes.

## Default Build
`make`

Produces the executable:

`./titanic`


High Optimization Build

`make opt`


Compiles using:

`-O3`

Link Time Optimization

`make lto`

Compiles using:

`-O3 -flto`

Code Coverage (GCOV)

`make gcov`

Compiles with coverage instrumentation

After running the program, coverage data files will be produced.

Profile Guided Optimization (PGO)

## Generate Profile Data

`make pgo-gen`

`./titanic`

## Use Profile Data

`make pgo-use`

The compiler uses collected profile data to optimize the program.

## Cleaning Build Files

To remove object files, executable, and coverage files:
`make clean`

This removes:
```
*.o
titanic
*.gcda
*.gcno
*.gcov

```


## Example Output
Example rule discovered by the program:
```
Stable condition found:
Condition: Gender: Female, Class: 1, Age: 40 or over

Original matches: 21
Original survival rate: 0.90
Bootstrap average rate: 0.88
Bootstrap min rate: 0.75
Bootstrap max rate: 0.95
Stability: 0.92

```

This indicates that the condition remains strong across many bootstrap samples.


## Finding From the Analysis

Several interesting patterns appear consistently.

### Gender and Survival

Female passengers have significantly higher survival rates than male passengers. This pattern remains stable across bootstrap samples and is consistent with the historical evacuation policy of "women and children first."

### Passenger Class

First and second class passengers have higher survival probabilities than third class passengers.
This likely reflects the location of cabins and access to lifeboats.

### Age Effects

Younger passengers often show slightly higher survival rates, but age alone is not strong predictor compared to gender and class.
Conditions combining age with gender and class tend to perform better.

### Ticket Fare

Passengers with higher ticket fares tend to have better survival outcomes, likely due to correlation with higher passenger class.
However, fare-based rules alone are generally less stable than conditions based on gender and class.

### Condition Stability
Some conditions appear stron on the original dataset but become weaker when evaluated across bootstrap samples.
This demonstrates that certain patterns may arise due to randomness in the dataset rather than representing true relationships.
Bootstrap analysis helps identify reliable patterns rather than coincidental ones.
