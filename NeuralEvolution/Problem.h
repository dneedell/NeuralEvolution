//
//  Problem.h
//  NeuralEvolution
//
//  Created by David Robert Needell on 4/20/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#ifndef __NeuralEvolution__Problem__
#define __NeuralEvolution__Problem__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "IOPair.h"
#include "Constants.h"

using namespace std;

class Problem{
public:
    //Constructor
    Problem(string fileName);
    
    //Getters
    vector<IOPair*> getGrayMaps() { return this->allGrayMaps; }

    //Setters
    void setGrayMaps(vector<IOPair*> grayMaps) { this->allGrayMaps = grayMaps; }
    
private:
    //Vectors to hold each test/training input/output pairs
    
    //For the images (grayMaps)
    vector<IOPair*> allGrayMaps;
    
    //Helper methods
    IOPair* parseGrayMap(ifstream &problemFile, string line);
};


#endif /* defined(__NeuralEvolution__Problem__) */
