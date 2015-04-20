//
//  IOPair.cpp
//  NeuralEvolution
//
//  Created by David Robert Needell on 4/20/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#include "IOPair.h"

/**
 *Constructor for N x N GrayMap
 */

IOPair::IOPair(vector<vector<int> > grayMap, int digit){
    this->grayMap = grayMap;
    this->actualDigit = digit;
}
