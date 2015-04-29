//
//  InputNode.h
//  NeuralEvolution
//
//  Created by David Robert Needell on 4/20/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#ifndef __NeuralEvolution__InputNode__
#define __NeuralEvolution__InputNode__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

const double MAX = .15;
const double MIN = -.15;

class InputNode{
public:
    //Constructor (default and for training/testing)
    InputNode(int hiddenNum);
    
    //Getters and Setters
    int getValue() { return this->value; }
    void setValue(int value) { this->value = value; }
    
    //nodeNum represents a particular hidden node
    double getHiddenEdgeWeightForNode(int nodeNum) { return this->hiddenEdgeWeights[nodeNum]; }
    void setHiddenEdgeWeightForNode(int nodeNum, double edgeWeight) { this->hiddenEdgeWeights[nodeNum] = edgeWeight; }
    
private:
    int value;
    vector<double> hiddenEdgeWeights;
    
    void calcAllInitialEdgeWeight(int outputNum);
    
};

#endif /* defined(__NeuralEvolution__InputNode__) */
