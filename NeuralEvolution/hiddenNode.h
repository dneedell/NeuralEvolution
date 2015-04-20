//
//  hiddenNode.h
//  NeuralEvolution
//
//  Created by David Robert Needell on 4/20/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#ifndef __NeuralEvolution__hiddenNode__
#define __NeuralEvolution__hiddenNode__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class hiddenNode {
public:
    //Constructors
    hiddenNode();
    hiddenNode(double activatedIn);
    
    //Getters and Setters
    
    int getOutput() { return this->output; }
    void setOutput(int output) { this->output = output; }
    
    double getInValue() { return this->inVal; }
    void setInValue(double inVal) { this->inVal = inVal; }
    
    double getActivatedInValue() { return this->activatedIn; }
    void setActivatedInValue(double activatedIn) { this->activatedIn = activatedIn; }
    
    double getValuePrime() { return this->valuePrime; }
    void setValuePrime(double valuePrime) { this->valuePrime = valuePrime; }
    
    void clearAllProperties();
    void printCharacteristics();
    
private:
    int output;
    double inVal;
    double activatedIn;
    double valuePrime;
};

#endif /* defined(__NeuralEvolution__hiddenNode__) */
