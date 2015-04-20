//
//  neuralNet.cpp
//  NeuralEvolution
//
//  Created by David Robert Needell on 4/20/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#include "neuralNet.h"

using namespace::std;

/**
 *Initialize the neural network with a vector of input nodes and output nodes
 */

neuralNet::neuralNet(int numInNodes, int numOutNodes, int numHiddenNodes, double learnRate){
    
   
//TODO: Creat a new initialization of input nodes as well as hidden nodes.
//    //create a perceptron of empty input nodes with random edge values
//    for (int i = 0; i < numInNodes; i++){
//        this->inputNodes.push_back(new InputNode(numOutNodes));
//    }
    
    //bias node
    this->inputNodes.push_back(new InputNode(numOutNodes));
    
    //create a new vector of output nodes with target values initialized
    for (int i = 0; i < numOutNodes; i++){
        this->outputNodes.push_back(new OutputNode());
    }
    
    //Assign learning rate and activation function from command line args
    this->learnRate = learnRate;
}
