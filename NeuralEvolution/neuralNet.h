//
//  neuralNet.h
//  NeuralEvolution
//
//  Created by David Robert Needell on 4/20/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#ifndef __NeuralEvolution__neuralNet__
#define __NeuralEvolution__neuralNet__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

#include "InputNode.h"
#include "OutputNode.h"
#include "IOPair.h"
#include "Problem.h"

using namespace::std;

const double e = exp(1.0);

class neuralNet {
public:
    //Constructor
    neuralNet(int numInNodes, int numOutNodes, int numHiddenNodes, double learnRate);
    
    bool train(IOPair* train);
    bool test(IOPair* test);
    
private:
    vector<InputNode*> inputNodes;
    vector<OutputNode*> outputNodes;
    double learnRate;
    int activeFunc;
    
    void resetOutputSetTarget(IOPair* input);
    void bitMapSetInput(IOPair* input);
    void matrixSetInput(IOPair* input);
    void setBiasNode();
    void setAndCalc(int index, int value);
    void calcInputNodeContribution(InputNode* input);
    OutputNode* findBest();
    void updateWeights();
    
    double calcError(OutputNode* output, int nodeNum, int size);
    double calcSquaredError(double error);
    
    double sigmoidPrime(double val);
    double sigmoidFunction(double val);
    
};


#endif /* defined(__NeuralEvolution__neuralNet__) */
