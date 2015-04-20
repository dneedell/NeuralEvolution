//
//  neuralEvolAlg.cpp
//  NeuralEvolution
//
//  Created by David Robert Needell on 4/20/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#include "neuralEvolAlg.h"

/**
 *Constructor for the overarching algorithm. Read in the problem, create the
 *neural net, and set the number of epochs.
 */

neuralEvolAlg::neuralEvolAlg(string trainFile, string testFile, double learnRate,
                             string selection, string crossover, double crossProb,
                             double mutProb, int genNum, int epochs){

    this->training = new Problem(trainFile);
    this->tests = new Problem(testFile);
    
    //TODO: find out information on size of problems to be testing in order to
    //      set the problem size to initialize an instance of the neuralNet type
    //      also, we need to determine how we want to represent the output.  Do
    //      we want to represent it as 10 nodes of probablities: .1, .2, ..., 1
    //      giving the probability of a face being in a photo?
    
    //this->net = new neuralNet(problemSize, outputNum, learnRate);
    this->epochs = epochs;
    
}