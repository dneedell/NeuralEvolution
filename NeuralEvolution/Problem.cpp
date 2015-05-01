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

Problem::Problem(string fileName) {
    // file in this code corresponds to pgm in the lab code
    ifstream file;
    file.open(fileName);
    string line;
    fgets(line, 511, file);
    int type;
    sscanf(line, "P%d", &type);
    if (type != 5 && type != 2) {
        printf("Only handles pgm files (type P5 or P2)\n");
        file.close();
        return;
    }
    /*
     * Get dimensions of pgm
     */
    fgets(line, 511, file);
    int nc;
    int nr;
    sscanf(line, "%d %d", &nc, &nr);
}