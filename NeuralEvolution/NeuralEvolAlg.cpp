//
//  NeuralEvolAlg.cpp
//  NeuralEvolution
//
//  Created by David Robert Needell on 4/20/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#include "NeuralEvolAlg.h"

/**
 *Constructor for the overarching algorithm. Read in the problem, create the
 *neural net, and set the number of epochs.
 */

NeuralEvolAlg::NeuralEvolAlg(string trainFile, string testFile, double learnRate,
                             string selection, string crossover, double crossProb,
                             double mutProb, int genNum, int epochs){

    this->training = new Problem(trainFile);
    this->tests = new Problem(testFile);
    
    
    //this->net = new neuralNet(problemSize, outputNum, learnRate);
    this->epochs = epochs;
    
}