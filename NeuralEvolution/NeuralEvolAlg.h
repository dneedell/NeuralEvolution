//
//  NeuralEvolAlg.h
//  NeuralEvolution
//
//  Created by David Robert Needell on 4/20/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#ifndef __NeuralEvolution__NeuralEvolAlg__
#define __NeuralEvolution__NeuralEvolAlg__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <future>
#include <chrono>
#include <ctime>
#include <time.h>
#include <sys/time.h>

#include "Problem.h"
#include "IOPair.h"
#include "NeuralNet.h"
#include "Population.h"
#include "Constants.h"

using namespace::std;

class NeuralEvolAlg{
public:
    //Constructor function
    NeuralEvolAlg(string newTrainFile, string newTestFile, double learnRate,
                  string selection, string crossover, double crossProb,
                  double mutProb, int genNum, int pop, int epochs);
    
    //main method
    void run();
    
    double runTraining(NeuralNet* net);
    double runTests(NeuralNet* net);
    
    //Getter
    int getEpochs() { return this->epochs; }
    
private:
    Problem* training;
    Problem* tests;
    
    double learnRate;
    string selection;
    string crossover;
    double crossProb;
    double mutProb;
    int genNum;
    int popSize;
    int epochs;
    
    Population* population;
    
    int getNumInputNodes();
    
    void runTrainingAndTesting(NeuralNet* net);
    void runFutures(vector<NeuralNet*> nets);
    
    void printNetPercentages(vector<NeuralNet*> nets);
    
    NeuralNet* getBestNetPerGen(vector<NeuralNet*> nets);
    
    void writeToEANNTest(double learnRate, double crossProb, double mutProb,
                         int genNum, NeuralNet* genBest);
    
    void writeToEANNTrain(double learnRate, double crossProb, double mutProb,
                          int genNum, NeuralNet* genBest);
    
    void writeToANNTrain(int totEpocs, double learnRate, NeuralNet* best);
    void writeToAnnTest(int totalEpocs, double learnRate, NeuralNet* best);
    
};

#endif /* defined(__NeuralEvolution__NeuralEvolAlg__) */
