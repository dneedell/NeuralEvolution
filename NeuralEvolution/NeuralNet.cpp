//
//  NeuralNet.cpp
//  NeuralEvolution
//
//  Created by David Robert Needell on 4/20/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#include "NeuralNet.h"

using namespace::std;

/**
 *
 */

NeuralNet::NeuralNet(){
    this->fitness = 0;
}

/**
 *Initialize the neural network with a vector of input nodes and output nodes
 */

NeuralNet::NeuralNet(int numInNodes, int numOutNodes, int numHiddenNodes, double learnRate){
    //create a new vector of empty input nodes with random edge values
    for (int i = 0; i < numInNodes; i++){
        this->inputNodes.push_back(new InputNode(numHiddenNodes));
    }
    
    //bias node
    this->inputNodes.push_back(new InputNode(numHiddenNodes));
    
    //create a new vector of hidden nodes
    for (int i = 0; i < numHiddenNodes; i++){
        this->hiddenNodes.push_back(new HiddenNode(numOutNodes));
    }
    
    //create a new vector of output nodes with target values initialized
    for (int i = 0; i < numOutNodes; i++){
        this->outputNodes.push_back(new OutputNode());
    }
    
    //Assign learning rate and activation function from command line args
    this->learnRate = learnRate;
}

/**
 *
 */

NeuralNet::NeuralNet(vector<InputNode*> inputNodes, int numOutNodes, int numHiddenNodes,
                     double learnRate){
    this->inputNodes = inputNodes;
    
    //bias node
    this->inputNodes.push_back(new InputNode(numHiddenNodes));
    
    //create a new vector of hidden nodes
    for (int i = 0; i < numHiddenNodes; i++){
        this->hiddenNodes.push_back(new HiddenNode(numOutNodes));
    }
    
    //create a new vector of output nodes with target values initialized
    for (int i = 0; i < numOutNodes; i++){
        this->outputNodes.push_back(new OutputNode());
    }
    
    //Assign learning rate and activation function from command line args
    this->learnRate = learnRate;
}

/**
 *Train the neural network!
 */

bool NeuralNet::train(IOPair* input){
    //Reset output nodes
    resetOutputAndHidden(input);
    
    //Perform initialization of input nodes and calculation of in for matrix
    grayMapSetInput(input);
    
    setBiasNode();
    
    //Activate in values for each hidden node
    activateAllHidden();
    
    //Find the "best" output node
    OutputNode* best = findBestOutput();
    //best->printCharacteristics();
    
    //backprop from output to hidden weights
    updateHiddenWeights();
    
    //backprop from hidden to input weights
    updateInputWeights();

    //test if output matches target output
    if (best->getOutput() == best->getTarget()){
        return true;
    }
    return false;
}

/**
 *Perform the tests!
 */

bool NeuralNet::test(IOPair* input){
    //Reset output nodes
    resetOutputAndHidden(input);
    
    //Perform initialization of input nodes and calculation of in for matrix
    grayMapSetInput(input);
    
    setBiasNode();
    
    //Activate in values for each hidden node
    activateAllHidden();
    
    //Find output node with best activated value
    OutputNode* best = findBestOutput();
    //best->printCharacteristics();
    
    if (best->getOutput() == best->getTarget()){
        return true;
    }
    return false;
}



/**
 *Updates the edge weights from the Hidden Nodes to the Output Nodes
 */

void NeuralNet::updateHiddenWeights(){
    /*
     *Update edge weights based on current weight, alpha, input value, error,
     *and squared error
     */
    for (HiddenNode* hidden : this->hiddenNodes){
        double curVal = hidden->getActivatedInValue();
        for (int i = 0; i < this->outputNodes.size(); i++){
            OutputNode* output = this->outputNodes[i];
            
            double curEdge = hidden->getOutputEdgeWeightForNode(i);
            double err = output->getError();
            //double squaredErr = output->getSquaredError();
            double valPrime = output->getValuePrime();
            
            hidden->setOutputEdgeWeightForNode(i, curEdge+(this->learnRate*curVal*err*valPrime));
        }
    }
}

/**
 *Updates the edge weights from the Input Nodes to the Hidden Nodes
 */

void NeuralNet::updateInputWeights(){
    /*
     *Update edge weights based on current weight, alpha, input value, error,
     *and squared error
     */
    for (int k = 0; k < this->inputNodes.size(); k++){
        InputNode* input = this->inputNodes[k];
        double curVal = input->getValue();
        
        for (int j = 0; j < this->hiddenNodes.size(); j++){
            //only update weights if there is a connection
            if (input->getConnections()[j]){
                HiddenNode* hidden = this->hiddenNodes[j];
                double curHiddenWeight = input->getHiddenEdgeWeightForNode(j);
                double hiddenPrime = hidden->getValuePrime();
                
                double sum = 0;
                for (int i = 0; i < this->outputNodes.size(); i++){
                    OutputNode* output = this->outputNodes[i];
                    
                    double curOutWeight = hidden->getOutputEdgeWeightForNode(i);
                    double err = output->getError();
                    double valOutPrime = output->getValuePrime();
                    
                    sum += curOutWeight*err*valOutPrime;
                }
                sum *= hiddenPrime;
                input->setHiddenEdgeWeightForNode(j, curHiddenWeight+(this->learnRate*curVal*sum));
            }
        }
    }
}

/**
 *Sets the input nodes from graymap, also computes each input node's
 *contribution to the in sum per hidden node
 */

void NeuralNet::grayMapSetInput(IOPair* input){
    vector<vector<double>> map = input->getGrayMap();
    for (int i = 0; i < input->getRows(); i++){
        for (int j = 0; j < input->getCols(); j++){
            setAndCalc((i*(int)map.size())+j, map[i][j]);
        }
    }
}

/**
 *Sets the value and calculates the contribution of the input node to the in
 *of an output node
 */

void NeuralNet::setAndCalc(int index, double value){
    InputNode* curInput = this->inputNodes[index];
    curInput->setValue(value);
    
    //calc contribution to each output node from this input node
    calcInputNodeContribution(curInput);
}

/**
 *For each input node, calculate the contribution it makes to each hidden node's
 *value. It achieves this by getting the value * weight for the input node, which
 *effectively calculates the sum.
 */

void NeuralNet::calcInputNodeContribution(InputNode* input){
    for (int i = 0; i < this->hiddenNodes.size(); i++){
        //only calculate if there is a connection
        if (input->getConnections()[i]){
            HiddenNode* hidden = this->hiddenNodes[i];
            
            //Get value of input node and edge that goes to current output node
            double curVal = input->getValue();

            double curEdge = input->getHiddenEdgeWeightForNode(i);
            
            //Add the curVal*curEdge to existing value of output node
            double newInVal = hidden->getInValue() + curVal * curEdge;
            hidden->setInValue(newInVal);
        }
    }
}

/**
 *Sets the bias node
 */

void NeuralNet::setBiasNode(){
    //set bias node (last in inputnodes vector) to 1
    this->inputNodes[this->inputNodes.size()-1]->setValue(1.0);
    calcInputNodeContribution(this->inputNodes[this->inputNodes.size()-1]);
}

/**
 *For each hidden node, set its activated in to sigmoid function of in value
 */

void NeuralNet::activateAllHidden(){
    for (HiddenNode* node : this->hiddenNodes){
        activateHiddenNodeIn(node);
    }
}

/**
 *Sets the activated in value for the hidden node to the sigmoid function of the 
 *in value
 */

void NeuralNet::activateHiddenNodeIn(HiddenNode* hidden){
    hidden->setActivatedInValue(sigmoidFunction(hidden->getInValue()));
    hidden->setValuePrime(sigmoidPrime(hidden->getInValue()));
}

/**
 *For each output node, calculate the in value and the activated in value and the
 *sigmoid prime value from hidden nodes. Compare activated in values to find the
 *"best" output node (the guessed output by the net)
 */

OutputNode* NeuralNet::findBestOutput(){
    int count = 0;
    OutputNode* best = new OutputNode();
    
    for (int i = 0; i < this->outputNodes.size(); i++){
        OutputNode* output = this->outputNodes[i];
        
        double sum = 0;
        for (int j = 0; j < this->hiddenNodes.size(); j++){
            HiddenNode* hidden = this->hiddenNodes[j];
            sum += hidden->getActivatedInValue()*hidden->getOutputEdgeWeightForNode(i);
        }
        output->setInValue(sum);
        output->setActivatedInValue(sigmoidFunction(sum));
        output->setValuePrime(sigmoidPrime(sum));
        output->setOutput(count);
        
        if (output->getActivatedInValue() > best->getActivatedInValue()){
            best = output;
        }
        
        double error = calcError(output, count, (int) this->outputNodes.size());
        output->setError(error);
        output->setSquaredError(calcSquaredError(error));
        
        count++;
    }
    
    return best;
}


/**
 *Applies the sigmoid activation function to the sum of all inputs (val*edgeweight)
 *to a particular output node
 */

double NeuralNet::sigmoidFunction(double val){
    return 1.0/(1.0+pow(e, (-1.0*val)+.5));
    //return (1.0 / (1.0 + exp(-val)));
    //return 1.0/(1.0+pow(e, (-1.0*val)));
}

/**
 *Calculates sigmoid derivative
 */

double NeuralNet::sigmoidPrime(double val){
    //return (1.64872*pow(e, val))/(pow(1.64872+pow(e,val), 2));
    return pow(e, val)/(pow(pow(e, val) + 1.0, 2));
}

/**
 *Calculate the error by subtracting the calculate output from the target output
 */

double NeuralNet::calcError(OutputNode* output, int nodeNum, int size){
    //if desired number equals correct node in output node vector, 1-activatedVal
    if (nodeNum == output->getTarget()){
        return 1.0-output->getActivatedInValue();
    }
    else {
        return 0.0-output->getActivatedInValue();
    }
    
    return 0;
    
}

/**
 *Calculate the squared error
 */

double NeuralNet::calcSquaredError(double error){
    return .5*pow(error, 2);
}

/**
 *Resets the vector of output nodes and sets the target according to problem passed
 *in
 */

void NeuralNet::resetOutputAndHidden(IOPair* input){
    //reset all output nodes
    for (OutputNode* output : this->outputNodes){
        output->clearAllProperties();
        output->setTarget(input->getActualPersonNum());
    }
    for (HiddenNode* hidden : this->hiddenNodes){
        hidden->clearAllProperties();
    }
}

/**
 *
 */

vector<NeuralNet*> NeuralNet::breed(NeuralNet* parent2, string cross, double crossProb, double mutProb){
    vector<bool> newSequence;
    vector<bool> newSequence2;
    vector<InputNode*> newInputs1;
    vector<InputNode*> newInputs2;
    
    vector<NeuralNet*> siblings;
    
    double crossoverProb = (double)rand()/RAND_MAX;
    if (crossProb > crossoverProb){
        //Breed two nodes' connections, create resulting input node from connections
        vector<InputNode*> parent2InputNodes = parent2->getInputNodes();
        //exclude the bias node (will set later)
        for (int i = 0; i < this->inputNodes.size()-1; i++){
            vector<bool> parent1Connections = this->inputNodes[i]->getConnections();
            vector<bool> parent2Connections = parent2InputNodes[i]->getConnections();
            vector<vector<bool> > sequences = crossover(parent1Connections, parent2Connections, cross);
            
            //perform mutation
            newSequence = mutate(sequences[0], mutProb);
            newSequence2 = mutate(sequences[1], mutProb);
            newInputs1.push_back(new InputNode(newSequence));
            newInputs2.push_back(new InputNode(newSequence2));
        }
    }
    else {
        newInputs1 = this->inputNodes;
        newInputs2 = parent2->getInputNodes();
    }
    
    siblings.push_back(new NeuralNet(newInputs1, (int) this->outputNodes.size(),
                                      (int) this->hiddenNodes.size(), this->learnRate));
    
    siblings.push_back(new NeuralNet(newInputs2, (int) this->outputNodes.size(),
                                     (int) this->hiddenNodes.size(), this->learnRate));
    return siblings;
}

/**
 *This method strictly performs the crossover portion of breeding. It creates
 *one new genetic sequence, either by crossing on a single point or by randomly
 *selecting genes from each parent sequence.
 */

vector<vector<bool> > NeuralNet::crossover(vector<bool> firstSequence, vector<bool> secondSequence,
                                  string method){
    vector<vector<bool> > bothSequences;
    vector<bool> newSequence;
    vector<bool> newSequence2;
    if (method == "1c"){
        int index = rand() % firstSequence.size();
        newSequence.insert(newSequence.end(), firstSequence.begin(), firstSequence.begin()+index);
        newSequence.insert(newSequence.end(), secondSequence.begin()+index, secondSequence.end());
        
        newSequence2.insert(newSequence2.end(), secondSequence.begin(), secondSequence.begin()+index);
        newSequence2.insert(newSequence2.end(), firstSequence.begin()+index, firstSequence.end());
    }
    else {
        int count = 0;
        while (newSequence.size() != firstSequence.size()){
            int randomBit = rand() % 2;
            if (randomBit == 0){
                newSequence.push_back(firstSequence[count]);
                newSequence2.push_back(secondSequence[count]);
                count++;
            }
            else {
                newSequence.push_back(secondSequence[count]);
                newSequence2.push_back(firstSequence[count]);
                count++;
            }
        }
    }
    
    bothSequences.push_back(newSequence);
    bothSequences.push_back(newSequence2);
    
    return bothSequences;
}

/**
 *This method strictly performs the mutation portion of the breeding. With some
 *probability, the gene in the child sequence will be flipped (ex. true to false).
 */

vector<bool> NeuralNet::mutate(vector<bool> newSequence, double mutProb){
    for (int i = 0; i < newSequence.size(); i++){
        double randomProb = (double)rand()/RAND_MAX;
        if (mutProb > randomProb){
            if (newSequence[i] == true){
                newSequence[i] = false;
            }
            else {
                newSequence[i] = true;
            }
        }
    }
    return newSequence;
}

/**
 *
 */

void NeuralNet::printTestPercentages(){
    cout << "Tests satisfied: " << this->testPercentages << endl;
}

/**
 *
 */

void NeuralNet::printFinalTrainPercentages(){
    for (int i = 0; i < (int) this->trainPercentages.size(); i++){
        cout << "Last round of training satisfied: " << this->trainPercentages[EPOCHS-1] << endl;
    }
}



