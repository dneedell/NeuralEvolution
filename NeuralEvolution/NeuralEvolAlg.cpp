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
        NeuralNet* globalBest = new NeuralNet();
        for (int g = 0; g < this->genNum; g++){
            vector<NeuralNet*> nets = this->population->getIndividuals();
            
            runFutures(nets);
            
            //Run training and testing sequentially
//            for (int n = 0; n < nets.size(); n++){
//                NeuralNet* net = nets[n];
//                runTrainingAndTesting(net);
//            }
            
            //printNetPercentages(nets);
            
            //Selection
            this->population->selection(this->selection);
            
            //Breeding
            this->population->breed(this->crossover, this->crossProb, this->mutProb);
            
            NeuralNet* genBest = getBestNetPerGen(nets);
            if (genBest->getFitness() > globalBest->getFitness()){
                globalBest = genBest;
            }
            
            //Write test results per generation to file
            writeToEANNTest(this->learnRate, this->crossProb, this->mutProb, g, genBest);
            writeToEANNTrain(this->learnRate, this->crossProb, this->mutProb, g, genBest);
        }
    }
    //Else do fully connected input to hidden, no evolution
    else {
        NeuralNet* net = new NeuralNet(getNumInputNodes(), OUTPUTNODES, HIDDENNODES, this->learnRate);
        runTrainingAndTesting(net);
        
        vector<NeuralNet*> nets;
        nets.push_back(net);
        //printNetPercentages(nets);
        
        writeToAnnTest(this->epochs, this->learnRate, net);
        writeToANNTrain(this->epochs, this->learnRate, net);
    }
}

/**
 *Runs all the training and testing from futures
 */

vector<NeuralNet*> runTrainingAndTestingFutures(NeuralEvolAlg* alg, vector<NeuralNet*> nets){
    for (int n = 0; n < nets.size(); n++){
        NeuralNet* net = nets[n];
        
        //For each epoch, run all examples and store percentage satisfied per epoch
        vector<double> trainPercentages;
        
        struct timeval start, end;
        gettimeofday(&start, NULL);
        for (int i = 0; i < alg->getEpochs(); i++){
            trainPercentages.push_back(alg->runTraining(net) * 100.0);
        }
        gettimeofday(&end, NULL);
        double time = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
        
        net->setTrainTime(time);
        
        net->setTrainPercentages(trainPercentages);
        
        //Store the testing percentage as fitness for the neural net and in the back of the vector
        gettimeofday(&start, NULL);
        double classificationPercent = alg->runTests(net) * 100.0;
        gettimeofday(&end, NULL);
        time = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
        
        net->setTestTime(time);
        
        net->setFitness(classificationPercent);
        
        net->setTestPercentages(classificationPercent);
    }
    
    return nets;
}

/**
 *Runs all the training and testing from futures
 */

void NeuralEvolAlg::runTrainingAndTesting(NeuralNet* net){
    //For each epoch, run all examples and store percentage satisfied per epoch
    vector<double> trainPercentages;
    
    struct timeval start, end;
    gettimeofday(&start, NULL);
    for (int i = 0; i < this->epochs; i++){
        trainPercentages.push_back(runTraining(net) * 100.0);
    }
    gettimeofday(&end, NULL);
    double time = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
    
    net->setTrainTime(time);
    
    net->setTrainPercentages(trainPercentages);
    
    //Store the testing percentage as fitness for the neural net and in the back of the vector
    gettimeofday(&start, NULL);
    double classificationPercent = runTests(net) * 100;
    time = ((end.tv_sec  - start.tv_sec) * 1000000u + end.tv_usec - start.tv_usec) / 1.e6;
    
    net->setTestTime(time);
    
    net->setFitness(classificationPercent);
    
    net->setTestPercentages(classificationPercent);
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
    
    //cout << "Percent of tests satisfied: " << percent << endl;
    
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
    
    //cout << "Percent of tests satisfied: " << percent << endl;
    
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

/**
 *
 */

void NeuralEvolAlg::runFutures(vector<NeuralNet*> nets){
    //Create futures to run in parallel
    vector<future<vector<NeuralNet*> > > allFutures;
    
    int sector = (int) nets.size()/NUMCORES;
    
    for (int f = 0; f < NUMCORES; f++){
        //If last future, go to the end of the vector
        if (f == NUMCORES-1){
            vector<NeuralNet*> subNets(nets.begin()+(f*sector), nets.end());
            allFutures.push_back(async(runTrainingAndTestingFutures, this, subNets));
        }
        else{
            vector<NeuralNet*> subNets(nets.begin()+(f*sector), nets.begin()+((f+1)*sector));
            allFutures.push_back(async(runTrainingAndTestingFutures, this, subNets));
        }
    }
    
    //Add the updated neural nets back into a vector
    vector<NeuralNet*> allUpdatedNets;
    for (int f = 0; f < NUMCORES; f++){
        vector<NeuralNet*> updatedNets = allFutures[f].get();
        for (NeuralNet* net : updatedNets){
            allUpdatedNets.push_back(net);
        }
    }
    
    //set individuals
    this->population->setIndividuals(allUpdatedNets);
}

/**
 *
 */

void NeuralEvolAlg::printNetPercentages(vector<NeuralNet*> nets){
    for (int n = 0; n < nets.size(); n++){
        NeuralNet* net = nets[n];
        cout << "Neural Net " << n << ": " << endl;
        net->printFinalTrainPercentages();
        net->printTestPercentages();
        
        cout << "" << endl;
    }
}

/**
 *
 */

NeuralNet* NeuralEvolAlg::getBestNetPerGen(vector<NeuralNet*> nets){
    NeuralNet* best = nets[0];
    for (int i = 1; i < nets.size(); i++){
        if (nets[i]->getFitness() > best->getFitness()){
            best = nets[i];
        }
    }
    return best;
}

/**
 *
 */

void NeuralEvolAlg::writeToEANNTest(double learnRate, double crossProb, double mutProb,
                     int genNum, NeuralNet* genBest){
    ofstream csvFile;
    csvFile.open("/Users/sbowman/Desktop/EANN_test.csv", std::ios_base::app);
    
    csvFile << learnRate << "," << crossProb << "," << mutProb << "," << genNum << "," <<
    genBest->getFitness() << "," << genBest->getTestTime() << endl;
    
    csvFile.close();
}

/**
 *
 */

void NeuralEvolAlg::writeToEANNTrain(double learnRate, double crossProb, double mutProb,
                      int genNum, NeuralNet* genBest){
    ofstream csvFile;
    csvFile.open("/Users/sbowman/Desktop/EANN_train.csv", std::ios_base::app);
    
    vector<double> trainResults = genBest->getTrainPercentages();
    for (int i = 0; i < trainResults.size(); i++){
        csvFile << learnRate << "," << crossProb << "," << mutProb << "," << genNum << "," <<
        i << "," << trainResults[i] << "," << genBest->getTrainTime() << endl;
    }
    
    csvFile.close();
}

/**
 *
 */

void NeuralEvolAlg::writeToANNTrain(int totEpocs, double learnRate, NeuralNet* best){
    ofstream csvFile;
    csvFile.open("/Users/sbowman/Desktop/ANN_train.csv", std::ios_base::app);
    
    vector<double> trainResults = best->getTrainPercentages();
    for (int i = 0; i < trainResults.size(); i++){
        csvFile << totEpocs << "," << learnRate << "," << i << "," << trainResults[i] << "," <<
        best->getTrainTime() << endl;
    }
    
    csvFile.close();
}

/**
 *
 */

void NeuralEvolAlg::writeToAnnTest(int totEpocs, double learnRate, NeuralNet* best){
    ofstream csvFile;
    csvFile.open("/Users/sbowman/Desktop/ANN_test.csv", std::ios_base::app);
    
    double testResult = best->getTestPercentages();
    csvFile << totEpocs << "," << learnRate << "," << testResult << "," <<
    best->getTestTime() << endl;
    
    csvFile.close();
}





