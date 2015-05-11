//
//  Problem.cpp
//  NeuralEvolution
//
//  Created by David Robert Needell on 4/20/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#include "Problem.h"
#include <iostream>
#include <stdio.h>

using namespace std;

/**
 *Initializes a new problem, which is a list of images. Uses a file that dictates
 *which images to read.
 */

Problem::Problem(string fileName) {
    //Try to read in the file containing each image location
    ifstream problemFile(fileName);
    
    //String to hold each line
    string line;
    
    //If file is valid, continue parsing
    if(problemFile.is_open()){
        while(getline(problemFile, line)){
            char imageFile[1024];
            strncpy(imageFile, line.c_str(), sizeof(imageFile));
            imageFile[sizeof(imageFile) - 1] = 0;
            allGrayMaps.push_back(new IOPair(imageFile));
        }
    }
    problemFile.close();
}


