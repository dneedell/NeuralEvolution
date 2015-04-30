//
//  NeuralNet.h
//  NeuralEvolution
//
//  Created by David Robert Needell on 4/20/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#ifndef __NeuralEvolution__NeuralNet__
#define __NeuralEvolution__NeuralNet__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

#include "InputNode.h"
#include "OutputNode.h"
#include "HiddenNode.h"

#include "IOPair.h"
#include "Problem.h"

using namespace::std;

const double e = exp(1.0);

class NeuralNet {
public:
    //Constructor
    NeuralNet(int numInNodes, int numOutNodes, int numHiddenNodes, double learnRate);
    
    bool train(IOPair* train);
    bool test(IOPair* test);
    
private:
    vector<InputNode*> inputNodes;
    vector<HiddenNode*> hiddenNodes;
    vector<OutputNode*> outputNodes;
    
    double learnRate;
    int activeFunc;
    
    void resetOutputSetTarget(IOPair* input);
    void grayMapSetInput(IOPair* input);
    void setBiasNode();
    void setAndCalc(int index, int value);
    void calcInputNodeContribution(InputNode* input);
    
    void activateAllHidden();
    void activateHiddenNodeIn(HiddenNode* hidden);
    
    OutputNode* findBestOutput();
    double findBestHidden();

    void updateInputWeights();
    void updateHiddenWeights();
    
    double calcError(OutputNode* output, int nodeNum, int size);
    double calcHiddenError(HiddenNode* hidden, int nodeNum, int size);
    double calcSquaredError(double error);
    
    double sigmoidPrime(double val);
    double sigmoidFunction(double val);
    
};


#endif /* defined(__NeuralEvolution__NeuralNet__) */
