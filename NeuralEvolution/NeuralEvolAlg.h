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
#include "Population.h"

using namespace::std;

const bool EVOLVE = true;

class NeuralEvolAlg{
public:
    //Constructor function
    NeuralEvolAlg(string newTrainFile, string newTestFile, double learnRate,
                  string selection, string crossover, double crossProb,
                  double mutProb, int genNum, int pop, int epochs);
    
    //main method
    void run();
    
private:
    Problem* training;
    Problem* tests;
    
    double learnRate;
    string selection;
    string crossover;
    double crossProb;
    double mutProb;
    int genNum;
    int popSize;
    int epochs;
    
    Population* population;
    
    int getNumInputNodes();
    
    void runTrainingAndTesting(NeuralNet* net);
    
    double runTraining(NeuralNet* net);
    double runTests(NeuralNet* net);
    
};

#endif /* defined(__NeuralEvolution__NeuralEvolAlg__) */
