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
    IOPair(char fileName[]);
    
    //Getters
    vector<vector<int> > getGrayMap() { return this->grayMap; }
    int getActualPersonNum() { return this->actualPersonNum; }
    string getActualPerson() { return this->actualPerson; }
    
private:
    //TODO: consider using a number to represent a person
    int actualPersonNum;
    //TODO: consider dividing the file name into traits (delimiter = _)
    vector<string> traits;
    
    string actualPerson;
    vector<vector<int> > grayMap;
    
    void initGrayMap(int rows, int cols);
    string getNameFromFile(char fileName[]);
    
};


#endif /* defined(__NeuralEvolution__IOPair__) */
