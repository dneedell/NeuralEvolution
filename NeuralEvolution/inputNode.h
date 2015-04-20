//
//  inputNode.h
//  NeuralEvolution
//
//  Created by David Robert Needell on 4/20/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#ifndef __NeuralEvolution__inputNode__
#define __NeuralEvolution__inputNode__

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
    InputNode(int outputNum);
    
    //Getters and Setters
    int getValue() { return this->value; }
    void setValue(int value) { this->value = value; }
    
    //Pos represents a particular output node
    double getEdgeWeightAtPos(int pos) { return this->edgeWeights[pos]; }
    void setEdgeWeightAtPos(int pos, double edgeWeight) { this->edgeWeights[pos] = edgeWeight; }
    
private:
    int value;
    vector<double> edgeWeights;
    
    void calcAllInitialEdgeWeight(int outputNum);
    
};

#endif /* defined(__NeuralEvolution__inputNode__) */
