//
//  neuralEvolAlg.h
//  NeuralEvolution
//
//  Created by David Robert Needell on 4/20/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#ifndef __NeuralEvolution__neuralEvolAlg__
#define __NeuralEvolution__neuralEvolAlg__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Problem.h"
#include "IOPair.h"
#include "NeuralNet.h"

using namespace::std;

class neuralEvolAlg{
public:
    //Constructor function
    neuralEvolAlg(string trainFile, string testFile, double learnRate,
                  string selection, string crossover, double crossProb,
                  double mutProb, int genNum);
    
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

#endif /* defined(__NeuralEvolution__neuralEvolAlg__) */
