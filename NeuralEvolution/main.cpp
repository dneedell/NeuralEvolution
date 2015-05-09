//
//  main.cpp
//  NeuralEvolution
//
//  Created by David Robert Needell on 4/20/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#include <iostream>
#include <stdio.h>
#include "neuralEvolAlg.h"

using namespace::std;

//Constant Variables:

const int epochs = 100;

void testing(string trainName, string testname, int epochs, int genNum){
    
    double learnRate;
    double mutProb;
    int pop;
    double crossProb;
    string selection;
    string crossover;
    for (int lr = 0; lr < 2; lr++){
        if(lr == 0){
            learnRate = 0.2;
        }
        else{
            learnRate = 0.3;
        }
                for (int s = 0; s < 3; s++){
                    if(s == 0){
                        selection = "TS";
                    }
                    else if(s == 1){
                        selection = "RS";
                    }
                    else{
                        selection = "BS";
                    }
                    for (int c = 0; c < 2; c++){
                        if(c == 0){
                            crossover = "OPC";
                        }
                        else{
                            crossover = "UC";
                        }
                        for (int cp = 0;  cp < 2; cp++){
                            if(cp == 0){
                                crossProb = 0.5;
                            }
                            else{
                                crossProb = 0.7;
                            }
                            for (int mp = 0; mp < 2; mp++){
                                if(lr == 0){
                                    mutProb = 0.01;
                                }
                                else{
                                    mutProb = 0.1;
                                }
                                    for (int p = 0; p < 2; p++){
                                        if(p == 0){
                                            pop = 4;
                                        }
                                        else{
                                            pop = 8;
                                        }
                                        //run each test 5 times
                                        for(int i = 0; i < 5; i++){
                                            NeuralEvolAlg* alg = new NeuralEvolAlg(trainName, testname, learnRate,
                                                                                   selection, crossover, crossProb,
                                                                                   mutProb, genNum, pop, epochs);
                                            
                                            //start the clock
                                            
                                            clock_t start = clock();
                                            alg->run(); // alg needs to return something for this to work!
                                            
                                            
                                            double time = (clock() - start)/(double)CLOCKS_PER_SEC;
                                            //                                            saveResults(tops[topo], funcs[func], particles[numParticles],
                                            //                                            result, time);
                                            
                                        }
                                        
                                    }
                                }
                            }
                        }
                    }
                }
            }



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
        
        testing(trainName, testname, epochs, genNum);
        
        //New instance of the Neural Evolutionary algorithm
        NeuralEvolAlg* alg = new NeuralEvolAlg(trainName, testname, learnRate,
                                               selection, crossover, crossProb,
                                               mutProb, genNum, pop, epochs);
        
        //Run the algorithm
        alg->run();
        
        cout << "Done!" << endl;
        
    }
}
