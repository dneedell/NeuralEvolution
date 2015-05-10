//
//  Constants.h
//  NeuralEvolution
//
//  Created by Sawyer Bowman on 5/9/15.
//  Copyright (c) 2015 David Robert Needell. All rights reserved.
//

#ifndef __NeuralEvolution__Constants__
#define __NeuralEvolution__Constants__

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

const int EPOCHS = 50;
const bool EVOLVE = false;
//const bool EVOLVE = true;
const int NUMCORES = 4;
const int OUTPUTNODES = 20;
const int HIDDENNODES = 20;

const int M = 2;
const int k = 1;

const double MAX = .15;
const double MIN = -.15;

const double CHANCECONNECT = .1;
const double e = exp(1.0);

//From the dataset obtained from CMU
const string names[] = {"an2i", "at33", "boland", "bpm", "ch4f", "cheyer", "choon",
    "danieln", "glickman", "karyadi", "kawamura", "kk49",
    "megak", "mitchell", "night", "phoebe", "saavik", "steffi",
    "sz24", "tammo"};



#endif /* defined(__NeuralEvolution__Constants__) */
