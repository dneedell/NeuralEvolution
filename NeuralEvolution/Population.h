//
//  Population.h
//  NeuralEvolution
//
//  Created by Sawyer Bowman on 5/8/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#ifndef __NeuralEvolution__Population__
#define __NeuralEvolution__Population__

#include <stdio.h>
#include <stdio.h>
#include <iostream>
#include <vector>

#include "NeuralNet.h"

const int OUTPUTNODES = 20;
const int HIDDENNODES = 20;

const int M = 2;
const int k = 1;

//Sorts ascending by fitness (lowest to highest)
static bool sortByFitness(NeuralNet* firstIndiv, NeuralNet* secondIndiv) { return firstIndiv->getFitness() < secondIndiv->getFitness(); }
static bool maxByFitness(NeuralNet* firstIndiv, NeuralNet* secondIndiv) { return firstIndiv->getFitness() < secondIndiv->getFitness(); }

class Population {
public:
    Population(int numNets, int inputNum, double learnRate);
    
    //Getter
    vector<NeuralNet*> getIndividuals() { return this->individuals; }
    vector<NeuralNet*> getBreedingPool() { return this->breedingPool; }
    
    void selection(string select);
    void breed(string crossover, double probCrossover, double probMutation);
    
private:
    vector<NeuralNet*> individuals;
    vector<NeuralNet*> breedingPool;
    
    //helper functions for select()
    void tournamentSelect();
    void rankSelect();
    void boltzmannSelect();
    
    NeuralNet* getRandomIndividual();
    
};

#endif /* defined(__NeuralEvolution__Population__) */
