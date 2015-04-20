//
//  outputNode.h
//  NeuralEvolution
//
//  Created by David Robert Needell on 4/20/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#ifndef __NeuralEvolution__outputNode__
#define __NeuralEvolution__outputNode__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class OutputNode {
public:
    //Constructors
    OutputNode();
    OutputNode(double activatedIn);
    
    //Getters and Setters
    int getTarget() { return this->target; }
    void setTarget(int target) { this->target = target; }
    
    int getOutput() { return this->output; }
    void setOutput(int output) { this->output = output; }
    
    double getInValue() { return this->inVal; }
    void setInValue(double inVal) { this->inVal = inVal; }
    
    double getActivatedInValue() { return this->activatedIn; }
    void setActivatedInValue(double activatedIn) { this->activatedIn = activatedIn; }
    
    double getValuePrime() { return this->valuePrime; }
    void setValuePrime(double valuePrime) { this->valuePrime = valuePrime; }
    
    double getError() { return this->error; }
    void setError(double error) { this->error = error; }
    
    double getSquaredError() { return this->squaredError; }
    void setSquaredError(double squaredError) { this->squaredError = squaredError; }
    
    void clearAllProperties();
    void printCharacteristics();
    
private:
    int target;
    int output;
    double inVal;
    double activatedIn;
    double valuePrime;
    double error;
    double squaredError;
};

#endif /* defined(__NeuralEvolution__outputNode__) */
