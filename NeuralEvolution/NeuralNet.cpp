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
 *Initialize the neural network with a vector of input nodes and output nodes
 */

NeuralNet::NeuralNet(int numInNodes, int numOutNodes, int numHiddenNodes, double learnRate){
    //create a new vector of empty input nodes with random edge values
    for (int i = 0; i < numInNodes; i++){
        this->inputNodes.push_back(new InputNode(numHiddenNodes));
    }
    
    //bias node
    this->inputNodes.push_back(new InputNode(numOutNodes));
    
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
    resetOutputSetTarget(input);
    
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
    int count = 0;
    for (InputNode* input : this->inputNodes){
        double curVal = input->getValue();
        double curEdge = input->getHiddenEdgeWeightForNode(count);
        
        double sum = 0;
        for (int i = 0; i < this->outputNodes.size(); i++){
            OutputNode* output = this->outputNodes[i];
            HiddenNode* hidden = this->hiddenNodes[i];
            
            double curEdgeWeight = input->getHiddenEdgeWeightForNode(i);
            double err = output->getError();
            double valOutPrime = output->getValuePrime();
            double valHidPrime = hidden->getValuePrime();
            
            sum += curEdgeWeight*err*valOutPrime*valHidPrime;
        }
        input->setHiddenEdgeWeightForNode(count, curEdge+(this->learnRate*curVal*sum));
        count++;
    }
}

/**
 *Sets the input nodes from graymap, also computes each input node's
 *contribution to the in sum per hidden node
 */

void NeuralNet::grayMapSetInput(IOPair* input){
    vector<vector<int>> map = input->getGrayMap();
    for (int i = 0; i < map[0].size(); i++){
        for (int j = 0; j < map.size(); j++){
            setAndCalc((i*(int)map.size())+j, map[i][j]);
        }
    }
}

/**
 *Sets the value and calculates the contribution of the input node to the in
 *of an output node
 */

void NeuralNet::setAndCalc(int index, int value){
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
        HiddenNode* hidden = this->hiddenNodes[i];
        
        //Get value of input node and edge that goes to current output node
        double curVal = input->getValue();

        double curEdge = input->getHiddenEdgeWeightForNode(i);
        
        //Add the curVal*curEdge to existing value of output node
        double newInVal = hidden->getInValue() + curVal * curEdge;
        hidden->setInValue(newInVal);
    }
}

/**
 *Sets the bias node
 */

void NeuralNet::setBiasNode(){
    //set bias node (last in inputnodes vector) to 1
    this->inputNodes[this->inputNodes.size()-1]->setValue(1);
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
    
    for (OutputNode* output : this->outputNodes){
        double sum = 0;
        for (HiddenNode* hidden : this->hiddenNodes){
            sum += hidden->getActivatedInValue();
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
    //cout << 1.0/(1.0+pow(e, (-1.0*val)+.5)) << endl;
    return 1.0/(1.0+pow(e, (-1.0*val)+.5));
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

void NeuralNet::resetOutputSetTarget(IOPair* input){
    //reset all output nodes
    for (OutputNode* output : this->outputNodes){
        output->clearAllProperties();
        //output->setTarget(input->getActualDigit());
    }
}
