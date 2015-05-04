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

Problem::Problem(char fileName[]) {
    FILE *file;
    file = std::fopen(fileName, "r");
    char line[512];
    std::fgets(line, 511, file);
    int type;
    sscanf(line, "P%d", &type);
    if (type != 5 && type != 2) {
        printf("ERROR: Only handles pgm files (type P5 or P2)\n");
        fclose(file);
        return;
    }
    /*
     * Get dimensions of pgm
     */
    fgets(line, 511, file);
    int nc;
    int nr;
    sscanf(line, "%d %d", &nc, &nr);
    int grayMap[nr][nc];
    int maxval;
    sscanf(line, "%d", &maxval);
    if (maxval > 255){
        printf("ERROR: Only handles pgm files of 8 bits or less.\n");
        fclose(file);
        return;
    }
    /*
     * Read in pixels to grayMap
     */
    if (type==5){
        for (int i=0; i<nr; i++){
            for (int j=0; j<nc; j++){
                grayMap[i][j]=fgetc(file);
            }
        }
    }
    char intbuf[100];
    if (type == 2){
        for (int i = 0; i < nr; i++) {
            for (int j = 0; j < nc; j++) {
                bool found = false;
                int k = 0;
                while (!found) {
                    char ch = fgetc(file);
                    if (ch >= '0' && ch <= '9') {
                        intbuf[k] = ch;
                    }
                    else if(k != 0) {
                        intbuf[k] = '\0';
                        found = true;
                    }
                }
                grayMap[i][j] = atoi(intbuf);
            }
        }
    }
    fclose(file);
    return;
}