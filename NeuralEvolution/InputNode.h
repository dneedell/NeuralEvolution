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

const double CHANCECONNECT = .1;
const bool FULLCONNECT = false;

class InputNode{
public:
    //Constructor (default and for training/testing)
    InputNode(int hiddenNum);
    InputNode(vector<bool> connections);
    
    //Getters and Setters
    double getValue() { return this->value; }
    void setValue(double value) { this->value = value; }
    
    //nodeNum represents a particular hidden node
    double getHiddenEdgeWeightForNode(int nodeNum) { return this->hiddenEdgeWeights[nodeNum]; }
    void setHiddenEdgeWeightForNode(int nodeNum, double edgeWeight) { this->hiddenEdgeWeights[nodeNum] = edgeWeight; }
    
    vector<bool> getConnections() { return this->connections; }
    
private:
    double value;
    vector<double> hiddenEdgeWeights;
    vector<bool> connections;
    
    void calcAllInitialEdgeWeight(int outputNum);
    void calcInitialEdgeWeightFromConnections(vector<bool> connections);
    double calcEdgeWeight();
    
};

#endif /* defined(__NeuralEvolution__InputNode__) */
