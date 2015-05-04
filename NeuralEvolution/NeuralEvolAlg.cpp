//
//  NeuralEvolAlg.cpp
//  NeuralEvolution
//
//  Created by David Robert Needell on 4/20/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#include "NeuralEvolAlg.h"
#include <string>
#include <iostream>
#include <sstream>

/**
 *Constructor for the overarching algorithm. Read in the problem, create the
 *neural net, and set the number of epochs.
 */

NeuralEvolAlg::NeuralEvolAlg(string trainFile, string testFile, double learnRate,
                             string selection, string crossover, double crossProb,
                             double mutProb, int genNum, int epochs){
    
    unsigned long long int size1 = trainFile.size();
    char newTrainFile[size1];
    for (int i = 0; i <= size1; i++) {
        newTrainFile[i]=trainFile[i];
    }
    
    unsigned long long int size2 = testFile.size();
    char newTestFile[size2];
    for (int i = 0; i <= size2; i++) {
        newTestFile[i]=testFile[i];
    }

    this->training = new Problem(newTrainFile);
    this->tests = new Problem(newTestFile);
    
    
    //this->net = new neuralNet(problemSize, outputNum, learnRate);
    this->epochs = epochs;
    
}