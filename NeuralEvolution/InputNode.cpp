//
//  InputNode.cpp
//  NeuralEvolution
//
//  Created by David Robert Needell on 4/20/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#include "InputNode.h"

/**
 *When intializing an Input Node, give a random edge weight between -1.0 and 1.0.
 *Also, the perceptron is fully connected, so each Input Node has an output edge
 *for each Hidden Node.
 */

InputNode::InputNode(int hiddenNum){
    calcAllInitialEdgeWeight(hiddenNum);
}

/**
 *Creates a new input node with a given vector of connections
 */

InputNode::InputNode(vector<bool> connections){
    calcInitialEdgeWeightFromConnections(connections);
}

/**
 *The number of output edges from an input node corresponds to the number of
 *hidden nodes. Thus, Hidden Node 0 (in the vector) corresponds to the 0th output
 *edge from each Hidden Node's vector or output edges.
 */

void InputNode::calcAllInitialEdgeWeight(int hiddenNum){
    for (int i = 0; i < hiddenNum; i++){
        if (!EVOLVE){
            this->hiddenEdgeWeights.push_back(calcEdgeWeight());
            this->connections.push_back(true);
        }
        else {
            double chance = (double)rand() / RAND_MAX;
            if (chance < CHANCECONNECT){
                this->hiddenEdgeWeights.push_back(calcEdgeWeight());
                this->connections.push_back(true);
            }
            else{
                this->hiddenEdgeWeights.push_back(0);
                this->connections.push_back(false);
            }
        }
    }
}

/**
 *Calculate edge weights for neural net based on a vector of given connections
 */

void InputNode::calcInitialEdgeWeightFromConnections(vector<bool> connections){
    for (int i = 0; i < connections.size(); i++){
        if (connections[i]){
            this->hiddenEdgeWeights.push_back(calcEdgeWeight());
            this->connections.push_back(true);
        }
        else {
            this->hiddenEdgeWeights.push_back(0);
            this->connections.push_back(false);
        }
    }
}

/**
 *Calculates the edge weight upon initialization (random)
 */

double InputNode::calcEdgeWeight(){
    double f = (double)rand() / RAND_MAX;
    return MIN + f * (MAX - MIN);
}




