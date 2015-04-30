//
//  HiddenNode.h
//  NeuralEvolution
//
//  Created by David Robert Needell on 4/20/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#ifndef __NeuralEvolution__HiddenNode__
#define __NeuralEvolution__HiddenNode__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "InputNode.h"

using namespace std;

class HiddenNode {
public:
    //Constructors
    HiddenNode();
    HiddenNode(int outputNum);
    
    void calcAllInitialEdgeWeight(int outputNum);
    
    //Getters and Setters
    
    int getOutput() { return this->output; }
    void setOutput(int output) { this->output = output; }
    
    double getInValue() { return this->inVal; }
    void setInValue(double inVal) { this->inVal = inVal; }
    
    double getActivatedInValue() { return this->activatedIn; }
    void setActivatedInValue(double activatedIn) { this->activatedIn = activatedIn; }
    
    double getValuePrime() { return this->valuePrime; }
    void setValuePrime(double valuePrime) { this->valuePrime = valuePrime; }
    
    //nodeNum represents a particular output node
    double getOutputEdgeWeightForNode(int nodeNum) { return this->outputEdgeWeights[nodeNum]; }
    void setOutputEdgeWeightForNode(int nodeNum, double edgeWeight) { this->outputEdgeWeights[nodeNum] = edgeWeight; }
        
    void clearAllProperties();
    void printCharacteristics();
    
private:
    vector<double> outputEdgeWeights;
    
    int output;
    double inVal;
    double activatedIn;
    double valuePrime;

};

#endif /* defined(__NeuralEvolution__HiddenNode__) */
