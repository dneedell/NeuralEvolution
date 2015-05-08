//
//  NeuralEvolAlg.cpp
//  NeuralEvolution
//
//  Created by David Robert Needell on 4/20/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#include "NeuralEvolAlg.h"
#include <string>
#include <iostream>
#include <sstream>

/**
 *Constructor for the overarching algorithm. Read in the problem, create the
 *neural net, and set the number of epochs.
 */

NeuralEvolAlg::NeuralEvolAlg(string trainFile, string testFile, double learnRate,
                             string selection, string crossover, double crossProb,
                             double mutProb, int genNum, int epochs){

    this->training = new Problem(trainFile);
    this->tests = new Problem(testFile);
    
    this->learnRate = learnRate;
    this->selection = selection;
    this->crossover = crossover;
    this->crossProb = crossProb;
    this->mutProb = mutProb;
    this->genNum = genNum;
    this->epochs = epochs;
    
    int inputNum = getNumInputNodes();
    
    this->net = new NeuralNet(inputNum, OUTPUTNODES, HIDDENNODES, this->learnRate);
    
}

/**
 *For a given number of epochs, train the neural net with a new, random training
 *problem. After this number of epochs, test the neural net on various random test
 *problems
 */

vector<double> NeuralEvolAlg::run(){
    //get the correct training set from the problem class
    vector<IOPair*> problems;
    problems = this->training->getGrayMaps();
    
    //For each epoch, run all examples and store percentage satisfied per epoch
    vector<double> percentages;
    for (int i = 0; i < this->epochs; i++){
        percentages.push_back(runTraining(problems));
    }
    
    //Store the testing percentage in the back of the vector
    //percentages.push_back(runTests());
    
    return percentages;
}

/**
 *Runs all problems from training set
 */

double NeuralEvolAlg::runTraining(vector<IOPair*> problems){
    int satisfied = 0;
    int total = 0;
    
    for (IOPair* problem : problems){
        if (this->net->train(problem)){
            satisfied++;
        }
        total++;
    }
    double percent = (double) satisfied/total;
    
    cout << "Percent of tests satisfied: " << percent << endl;
    
    return percent;
}

/**
 *Runs each example in the vector of tests. Determines if it has been solved and
 *calculates percent of examples satisfied in the entire set.
 */

double NeuralEvolAlg::runTests(){
    //get the correct vector of problems
    vector<IOPair*> problems = this->training->getGrayMaps();

    int satisfied = 0;
    int total = 0;
    
    for (IOPair* test : problems){
        if (this->net->test(test)){
            satisfied++;
        }
        total++;
    }
    
    double percent = (double) satisfied/total;
    
    cout << "Percent of tests satisfied: " << percent << endl;
    
    return percent;
}

/**
 *Gets the number of input nodes by figuring out the dimensions of the graymap.
 */

int NeuralEvolAlg::getNumInputNodes(){
    vector<IOPair*> allGrayMaps = this->training->getGrayMaps();
    IOPair* first = allGrayMaps[0];

    return first->getRows() * first->getCols();
}



