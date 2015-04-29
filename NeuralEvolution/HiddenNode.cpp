//
//  HiddenNode.cpp
//  NeuralEvolution
//
//  Created by David Robert Needell on 4/20/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#include "HiddenNode.h"

/**
 *When intializing a Hidden Node, give a random edge weight between -1.0 and 1.0.
 *Also, the net is fully connected, so each Hidden Node has an output edge
 *for each Output Node.
 */

HiddenNode::HiddenNode(int outputNum){
    calcAllInitialEdgeWeight(outputNum);
}

/**
 *The number of output edges from a hidden node corresponds to the number of
 *output nodes. Thus, Output Node 0 (in the vector) corresponds to the 0th output
 *edge from each Hidden Node's vector or output edges.
 */

void HiddenNode::calcAllInitialEdgeWeight(int outputNum){
    for (int i = 0; i < outputNum; i++){
        double f = (double)rand() / RAND_MAX;
        double val = MIN + f * (MAX - MIN);
        this->outputEdgeWeights.push_back(val);
    }
    
}


