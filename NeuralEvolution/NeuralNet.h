//
//  NeuralNet.h
//  NeuralEvolution
//
//  Created by David Robert Needell on 4/20/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#ifndef __NeuralEvolution__NeuralNet__
#define __NeuralEvolution__NeuralNet__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

#include "InputNode.h"
#include "OutputNode.h"
#include "HiddenNode.h"

#include "IOPair.h"
#include "Problem.h"

using namespace::std;

const double e = exp(1.0);

class NeuralNet {
public:
    //Constructor
    NeuralNet(int numInNodes, int numOutNodes, int numHiddenNodes, double learnRate);
    NeuralNet(vector<InputNode*> inputNodes, int numOutNodes, int numHiddenNodes,
                       double learnRate);
    
    bool train(IOPair* train);
    bool test(IOPair* test);
    
    vector<NeuralNet*> breed(NeuralNet* indiv, string cross, double crossProb, double mutProb);
    
    //Getters
    double getFitness() { return this->fitness; }
    void setFitness(double fitness) { this->fitness = fitness; }
    
    void setTrainPercentages(vector<double> trainPercentages) { this->allTrainPercentages.push_back(trainPercentages); }
    
    vector<double> getTestPercentages() { return this->testPercentages; }
    void setTestPercentages(vector<double> testPercentages) { this->testPercentages = testPercentages; }
    
    vector<InputNode*> getInputNodes() { return this->inputNodes; }
    
private:
    vector<InputNode*> inputNodes;
    vector<HiddenNode*> hiddenNodes;
    vector<OutputNode*> outputNodes;
    
    double learnRate;
    int activeFunc;
    
    double fitness;
    vector<vector<double> > allTrainPercentages;
    vector<double> testPercentages;
    
    void resetOutputAndHidden(IOPair* input);
    
    void grayMapSetInput(IOPair* input);
    void setBiasNode();
    void setAndCalc(int index, double value);
    void calcInputNodeContribution(InputNode* input);
    
    void activateAllHidden();
    void activateHiddenNodeIn(HiddenNode* hidden);
    
    OutputNode* findBestOutput();
    double findBestHidden();

    void updateInputWeights();
    void updateHiddenWeights();
    
    double calcError(OutputNode* output, int nodeNum, int size);
    double calcHiddenError(HiddenNode* hidden, int nodeNum, int size);
    double calcSquaredError(double error);
    
    double sigmoidPrime(double val);
    double sigmoidFunction(double val);
    
    vector<vector<bool> > crossover(vector<bool> firstSequence, vector<bool> secondSequence, string method);
    vector<bool> mutate(vector<bool> newSequence, double mutProb);
};


#endif /* defined(__NeuralEvolution__NeuralNet__) */
