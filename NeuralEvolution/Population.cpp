//
//  Population.cpp
//  NeuralEvolution
//
//  Created by Sawyer Bowman on 5/8/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#include "Population.h"

/**
 *Constructor for a population. Initializes a vector of neural nets.
 */

Population::Population(int numNets, int inputNum, double learnRate){
    for (int i = 0; i < numNets; i++){
        this->individuals.push_back(new NeuralNet(inputNum, OUTPUTNODES, HIDDENNODES,
                                                  learnRate));
    }
}

/**
 *This method takes in the selection method passed as a command line parameter
 *and decides which selection to do.
 */

void Population::selection(string select){
    if (select == "rs"){
        rankSelect();
    }
    else if (select == "ts"){
        tournamentSelect();
    }
    else if (select == "bs"){
        boltzmannSelect();
    }
}

/**
 *This method ranks the individuals in the population and then selects
 *them for breeding with a particular probability.
 */

void Population::rankSelect(){
    //Sort the individuals by fitness
    sort(this->individuals.begin(), this->individuals.end(), sortByFitness);
    
    //empty breeding pool
    this->breedingPool.clear();
    
    //Calculate sum of series for probability calculation later
    double seriesSum = (this->individuals.size() * (this->individuals.size()+1))/2;
    
    //While breeding pool not full, add new individual
    while (this->breedingPool.size() != this->individuals.size()){
        
        //Used to select a new individual
        double randomProb = (double)rand()/RAND_MAX;
        double count = 0;
        
        //Sum up the probabilities while iterating
        for (int i = 0; i < this->individuals.size(); i++){
            count += (i+1)/seriesSum;
            if (count > randomProb){
                this->breedingPool.push_back(this->individuals[i]);
                //restart the for loop and continue until breedingPool is full
                break;
            }
        }
    }
}

/**
 *While there are individuals remaining, this method takes M individuals
 *and places them into a tournament. Then, the k best individuals are
 *chosen from this tournament and added to the breeding pool.
 */

void Population::tournamentSelect(){
    vector<NeuralNet*> individualPool = this->individuals;
    
    //empty breeding pool
    this->breedingPool.clear();
    
    //need to draw M from vector, select k from M, place k in pool
    while (this->breedingPool.size() != this->individuals.size()){
        vector<NeuralNet*> tournamentParticipants;
        
        //Fill the tournament with candidates until M is reached, delete candidates from overall pool
        int drawCount = 0;
        while (drawCount < M){
            int randIndex = rand() % this->individuals.size();
            tournamentParticipants.push_back(this->individuals[randIndex]);
            drawCount++;
        }
        
        //Find the best k individuals, place them in the breeding pool, delete from tournament
        int poolCount = 0;
        while (poolCount < k && this->breedingPool.size() != this->individuals.size()){
            NeuralNet* champion = *max_element(tournamentParticipants.begin(), tournamentParticipants.end(), maxByFitness);
            this->breedingPool.push_back(champion);
            poolCount++;
        }
    }
}

/**
 *A very similar method to rankSelect, but uses e^fitness instead of rank
 *to calculate probability of being selected.
 */

void Population::boltzmannSelect(){
    //Sort the individuals by fitness
    sort(this->individuals.begin(), this->individuals.end(), sortByFitness);
    
    //empty breeding pool
    this->breedingPool.clear();
    
    //Calculate sum of series for probability calculation later
    double seriesSum;
    for (int i = 0; i < this->individuals.size(); i++){
        seriesSum += exp(this->individuals[i]->getFitness());
    }
    
    //While breeding pool not full, add new individual
    while (this->breedingPool.size() != this->individuals.size()){
        
        //Used to select a new individual
        double randomProb = (double)rand()/RAND_MAX;
        double count = 0;
        
        //Sum up the probabilities while iterating
        for (int i = 0; i < this->individuals.size(); i++){
            count += exp(this->individuals[i]->getFitness())/seriesSum;
            if (count > randomProb){
                this->breedingPool.push_back(this->individuals[i]);
                //restart the for loop and continue until breedingPool is full
                break;
            }
        }
    }
}

/**
 *This method chooses two random individuals from the breeding pool, and creates
 *new individuals to replace them in the next generation. It calls upon crossover
 *and mutation to potentially change the gene sequence of the offspring.
 */

void Population::breed(string crossover, double probCrossover, double probMutation){
    vector<NeuralNet*> newGeneration;
    
    //fill up newGeneration until it reaches the set population size
    while(newGeneration.size() != this->individuals.size()){
        //get two random individuals
        NeuralNet* momeo = getRandomIndividual();
        NeuralNet* pappy = getRandomIndividual();
        
        //breed the 2 individuals together to create 2 children
        vector<NeuralNet*> siblings = momeo->breed(pappy, crossover, probCrossover, probMutation);
        
        newGeneration.push_back(siblings[0]);
        newGeneration.push_back(siblings[1]);
    }
    
    this->individuals = newGeneration;
}

/**
 *This method is responsible for getting an individual from the breeding pool
 *and returning it. It also deletes this individual from the breeding pool.
 */

NeuralNet* Population::getRandomIndividual(){
    int randomIndex = rand() % this->breedingPool.size();
    NeuralNet* randomIndiv = this->breedingPool[randomIndex];
    this->breedingPool.erase(this->breedingPool.begin() + randomIndex);
    return randomIndiv;
}



