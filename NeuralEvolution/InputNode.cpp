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
 *The number of output edges from an input node corresponds to the number of
 *hidden nodes. Thus, Hidden Node 0 (in the vector) corresponds to the 0th output
 *edge from each Hidden Node's vector or output edges.
 */

void InputNode::calcAllInitialEdgeWeight(int hiddenNum){
    for (int i = 0; i < hiddenNum; i++){
        double f = (double)rand() / RAND_MAX;
        double val = MIN + f * (MAX - MIN);
        this->hiddenEdgeWeights.push_back(val);
    }
}