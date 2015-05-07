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

    this->training = new Problem(trainFile);
    this->tests = new Problem(testFile);
    
    this->learnRate = learnRate;
    this->selection = selection;
    this->crossover = crossover;
    this->crossProb = crossProb;
    this->mutProb = mutProb;
    this->genNum = genNum;
    this->epochs = epochs;
    
    int inputNum = getNumInputNodes();
    
    this->net = new NeuralNet(inputNum, OUTPUTNODES, HIDDENNODES, this->learnRate);
    
}

/**
 *Gets the number of input nodes by figuring out the dimensions of the graymap.
 */

int NeuralEvolAlg::getNumInputNodes(){
    vector<IOPair*> allGrayMaps = this->training->getGrayMaps();
    IOPair* first = allGrayMaps[0];
    vector<vector<int> > grayMap = first->getGrayMap();
    return (int) grayMap.size()* (int) grayMap[0].size();
}



