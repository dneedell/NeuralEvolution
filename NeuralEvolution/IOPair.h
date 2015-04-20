//
//  IOPair.h
//  NeuralEvolution
//
//  Created by David Robert Needell on 4/20/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#ifndef __NeuralEvolution__IOPair__
#define __NeuralEvolution__IOPair__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

class IOPair{
public:
    //Constructor function
    IOPair(vector<vector<int> > grayMap, int digit);
    
    //Getters
    vector<vector<int> > getGrayMap() { return this->grayMap; }
    int getActualDigit() { return this->actualDigit; }
    
private:
    int actualDigit;
    vector<vector<int> > grayMap;
    
};


#endif /* defined(__NeuralEvolution__IOPair__) */
