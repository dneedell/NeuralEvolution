//
//  main.cpp
//  NeuralEvolution
//
//  Created by David Robert Needell on 4/20/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#include <iostream>
#include <stdio.h>

#include "NeuralEvolAlg.h"
#include "Constants.h"

using namespace::std;

//Constant Variables:

int main(int argc, const char * argv[]) {
   
    srand( (int) time( NULL ) );
    
    //Make sure number of command line arguments is correct (print if not)

    if (argc != 10){
        cout << "You've entered an incorrect number of arguments to the program!" << endl;
        cout << "Please enter the following parameters: " << endl;
        cout << "   training file   = the name of the file to train on (string)" << endl;
        cout << "   testing file    = the name of the file to test on (string)" << endl;
        cout << "   learning rate   = the learning rate for Neural Networks (double)" << endl;
        cout << "   selection       = type of selection of breeding pool (string):" << endl;
        cout << "                     ts   = tournament selection" << endl;
        cout << "                     rs   = rank based selection" << endl;
        cout << "                     bs   = Boltzmann selection" << endl;
        cout << "   crossover       = crossover method (string):" << endl;
        cout << "                     1c   = 1-point crossover" << endl;
        cout << "                     uc   = uniform crossover" << endl;
        cout << "   pC              = crossover probability (double)" << endl;
        cout << "   pM              = mutation probability (double)" << endl;
        cout << "   generations     = max number of generations to run (int)" << endl;
        cout << "   population size = number of neural nets (individuals) (int)" << endl;
        //cout << "   epochs          = number of times to train net (int)" << endl;
        exit(0);
        
    }
    
    //If correct number of command line arguments, convert to proper type
    
    else {

        string trainName = argv[1];
        string testname = argv[2];
        double learnRate = stod(argv[3]);
        string selection = argv[4];
        string crossover = argv[5];
        double crossProb = stod(argv[6]);
        double mutProb = stod(argv[7]);
        int genNum = stoi(argv[8]);
        int pop = stoi(argv[9]);
        
        //int epochs = stoi(argv[9]);
        
        //New instance of the Neural Evolutionary algorithm
        NeuralEvolAlg* alg = new NeuralEvolAlg(trainName, testname, learnRate,
                                               selection, crossover, crossProb,
                                               mutProb, genNum, pop, EPOCHS);
        
        //Run the algorithm
        alg->run();
        
        cout << "Done!" << endl;
        
    }
}
