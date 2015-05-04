//
//  NeuralEvolAlg.h
//  NeuralEvolution
//
//  Created by David Robert Needell on 4/20/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#ifndef __NeuralEvolution__NeuralEvolAlg__
#define __NeuralEvolution__NeuralEvolAlg__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Problem.h"
#include "IOPair.h"
#include "NeuralNet.h"

using namespace::std;

class NeuralEvolAlg{
public:
    //Constructor function
    NeuralEvolAlg(string newTrainFile, string newTestFile, double learnRate,
                  string selection, string crossover, double crossProb,
                  double mutProb, int genNum, int epochs);
    
    //main method
    void run();
    
private:
    Problem* training;
    Problem* tests;
    NeuralNet* net;
    int epochs;
    int problemType;
    
    IOPair* getRandomTrainingProblem();
    double runTraining(vector<IOPair*> problems);
    double runTests();
    
};

#endif /* defined(__NeuralEvolution__NeuralEvolAlg__) */
