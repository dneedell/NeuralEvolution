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

const int OUTPUTNODES = 20;
const int HIDDENNODES = 20;

class NeuralEvolAlg{
public:
    //Constructor function
    NeuralEvolAlg(string newTrainFile, string newTestFile, double learnRate,
                  string selection, string crossover, double crossProb,
                  double mutProb, int genNum, int epochs);
    
    //main method
    vector<double> run();
    
private:
    Problem* training;
    Problem* tests;
    NeuralNet* net;
    
    double learnRate;
    string selection;
    string crossover;
    double crossProb;
    double mutProb;
    int genNum;
    int epochs;
    
    int getNumInputNodes();
    
    double runTraining(vector<IOPair*> problems);
    double runTests();
    
};

#endif /* defined(__NeuralEvolution__NeuralEvolAlg__) */
