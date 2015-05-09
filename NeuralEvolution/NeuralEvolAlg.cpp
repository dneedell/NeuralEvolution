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
                             double mutProb, int genNum, int pop, int epochs){

    this->training = new Problem(trainFile);
    this->tests = new Problem(testFile);
    
    this->learnRate = learnRate;
    this->selection = selection;
    this->crossover = crossover;
    this->crossProb = crossProb;
    this->mutProb = mutProb;
    this->genNum = genNum;
    this->popSize = pop;
    this->epochs = epochs;
    
    int inputNum = getNumInputNodes();
    this->population = new Population(this->popSize, inputNum, this->learnRate);
}

/**
 *For a given number of epochs, train the neural net with a new, random training
 *problem. After this number of epochs, test the neural net on various random test
 *problems
 */

void NeuralEvolAlg::run(){
    if (EVOLVE){
        for (int g = 0; g < this->genNum; g++){
            vector<NeuralNet*> nets = this->population->getIndividuals();
            
            //Run training and testing
            for (int n = 0; n < nets.size(); n++){
                NeuralNet* net = nets[n];
                runTrainingAndTesting(net);
            }
            
            //Selection
            this->population->selection(this->selection);
            
            //Breeding
            this->population->breed(this->crossover, this->crossProb, this->mutProb);
        }
    }
    //Else do fully connected input to hidden, no evolution
    else {
        NeuralNet* net = new NeuralNet(getNumInputNodes(), OUTPUTNODES, HIDDENNODES, this->learnRate);
        runTrainingAndTesting(net);
    }
}

/**
 *Runs all the training and testing
 */

void NeuralEvolAlg::runTrainingAndTesting(NeuralNet* net){
    //For each epoch, run all examples and store percentage satisfied per epoch
    vector<double> trainPercentages;
    for (int i = 0; i < this->epochs; i++){
        trainPercentages.push_back(runTraining(net));
    }
    
    //Store the testing percentage as fitness for the neural net and in the back of the vector
    double classificationPercent = runTests(net);
    net->setFitness(classificationPercent);
    
    vector<double> testPercentages = net->getTestPercentages();
    testPercentages.push_back(classificationPercent);
    net->setTestPercentages(testPercentages);
}

/**
 *Runs all problems from training set
 */

double NeuralEvolAlg::runTraining(NeuralNet* net){
    //get the correct vector of problems
    vector<IOPair*> problems = this->training->getGrayMaps();
    
    int satisfied = 0;
    int total = 0;
    
    for (IOPair* problem : problems){
        if (net->train(problem)){
            satisfied++;
        }
        total++;
    }
    double percent = (double) satisfied/total;
    
    cout << "Percent of tests satisfied: " << percent << endl;
    
    return percent;
}

/**
 *Runs each example in the vector of tests. Determines if it has been solved and
 *calculates percent of examples satisfied in the entire set.
 */

double NeuralEvolAlg::runTests(NeuralNet* net){
    //get the correct vector of problems
    vector<IOPair*> problems = this->tests->getGrayMaps();

    int satisfied = 0;
    int total = 0;
    
    for (IOPair* test : problems){
        if (net->test(test)){
            satisfied++;
        }
        total++;
    }
    
    double percent = (double) satisfied/total;
    
    cout << "Percent of tests satisfied: " << percent << endl;
    
    return percent;
}

/**
 *Gets the number of input nodes by figuring out the dimensions of the graymap.
 */

int NeuralEvolAlg::getNumInputNodes(){
    vector<IOPair*> allGrayMaps = this->training->getGrayMaps();
    IOPair* first = allGrayMaps[0];

    return first->getRows() * first->getCols();
}



