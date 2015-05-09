//
//  IOPair.h
//  NeuralEvolution
//
//  Created by David Robert Needell on 4/20/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

//Based on image reading code from CMU (listed below)

/*
 ******************************************************************
 * HISTORY
 * 15-Oct-94  Jeff Shufelt (js), Carnegie Mellon University
 *      Prepared for 15-681, Fall 1994.
 *
 ******************************************************************
 */

#ifndef __NeuralEvolution__IOPair__
#define __NeuralEvolution__IOPair__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

#include "Constants.h"

using namespace std;

class IOPair{
public:
    //Constructor function
    IOPair(char fileName[]);
    
    //Getters
    int getActualPersonNum() { return this->actualPersonNum; }
    string getActualPerson() { return this->actualPerson; }
    string getFile() { return this->entireFile; }
    vector<string> getTraits() { return this->traits; }
    
    int getRows() { return this->rows; }
    int getCols() { return this->cols; }
    vector<vector<double> > getGrayMap() { return this->grayMap; }
    
private:
    string entireFile;
    vector<string> traits;
    string actualPerson;
    int actualPersonNum;
    
    int rows;
    int cols;
    vector<vector<double> > grayMap;
    
    void initGrayMap(int rows, int cols);
    string getNameFromFile(char fileName[]);
    void getTraitsFromName();
    void assignNum();
    
};


#endif /* defined(__NeuralEvolution__IOPair__) */
