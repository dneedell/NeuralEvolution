//
//  OutputNode.cpp
//  NeuralEvolution
//
//  Created by David Robert Needell on 4/20/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#include "OutputNode.h"

/**
 *Constructor creates an empty output node
 */

OutputNode::OutputNode(){
    this->target = 0;
    this->output = 0;
    this->inVal = 0;
    this->activatedIn = 0;
    this->error = 0;
    this->squaredError = 0;
}

/**
 *Overridden constructor
 */

OutputNode::OutputNode(double activatedIn){
    this->target = 0;
    this->output = 0;
    this->inVal = 0;
    this->activatedIn = activatedIn;
    this->error = 0;
    this->squaredError = 0;
}

/**
 *Refreshed an output node after a round of training.
 */

void OutputNode::clearAllProperties(){
    this->target = 0;
    this->output = 0;
    this->inVal = 0;
    this->activatedIn = 0;
    this->valuePrime = 0;
    this->error = 0;
    this->squaredError = 0;
}

/**
 *Prints the characteristics of an outputnode. Used for debugging.
 */

void OutputNode::printCharacteristics(){
    cout << "In Value: " << this->inVal << endl;
    cout << "Target Value: " << this->target << endl;
    cout << "Output Value: " << this->output << endl;
    cout << "Activated In: " << this->activatedIn << endl;
    cout << "Error: " << this->error << endl;
    cout << "" << endl;
    //cout << "Squared Error: " << this->squaredError << endl;
}
