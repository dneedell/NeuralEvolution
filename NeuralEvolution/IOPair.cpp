//
//  IOPair.cpp
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

#include "IOPair.h"

/**
 *Constructor for N x N GrayMap
 */

IOPair::IOPair(char fileName[]){
    FILE *file;
    file = std::fopen(fileName, "r");
    char line[512], intbuf[100], ch;
    int type, nc, nr, maxval, i, j, k, found;
    
    if ((file = fopen(fileName, "r")) == NULL) {
        printf("IMGOPEN: Couldn't open '%s'\n", fileName);
        return;
    }
    
    //Set name, get traits of picture, assign number
    this->entireFile = getNameFromFile(fileName);
    getTraitsFromName();
    assignNum();

    //Scan pnm type information, expecting P5
    std::fgets(line, 511, file);
    sscanf(line, "P%d", &type);
    if (type != 5 && type != 2) {
        printf("ERROR: Only handles pgm files (type P5 or P2)\n");
        fclose(file);
        return;
    }
    
    //Get dimensions of pgm
    fgets(line, 511, file);
    sscanf(line, "%d %d", &nc, &nr);
    this->rows = nr;
    this->cols = nc;
    sscanf(line, "%d", &maxval);
    if (maxval > 255){
        printf("ERROR: Only handles pgm files of 8 bits or less.\n");
        fclose(file);
        return;
    }
    
    
    //Get maxval
    fgets(line, 511, file);
    sscanf(line, "%d", &maxval);
    if (maxval > 255) {
        printf("IMGOPEN: Only handles pgm files of 8 bits or less\n");
        fclose(file);
        return;
    }
    
    //Initialize GrayMap according to dimensions (all 0)
    initGrayMap(nr, nc);

    
    //Read in pixels to grayMap
    if (type==5){
        for (int i=0; i<nr; i++){
            for (int j=0; j<nc; j++){
                this->grayMap[i][j] = fgetc(file);
            }
        }
    }
    else if (type == 2) {
        for (i = 0; i < nr; i++) {
            for (j = 0; j < nc; j++) {
                
                k = 0;  found = 0;
                while (!found) {
                    ch = (char) fgetc(file);
                    if (ch >= '0' && ch <= '9') {
                        intbuf[k] = ch;  k++;
                    } else {
                        if (k != 0) {
                            intbuf[k] = '\0';
                            found = 1;
                        }
                    }
                }
                this->grayMap[i][j] = atoi(intbuf);
            }
        }
    }
    fclose(file);
}

/**
 *Allocate memory in the vector of vectors
 */

void IOPair::initGrayMap(int rows, int cols){
    for (int i = 0; i < rows; i++){
        vector<int> row (cols, 0);
        this->grayMap.push_back(row);
    }
}

/**
 *Extracts the name from the filename
 */

string IOPair::getNameFromFile(char fileName[]){
    //convert to string
    string file(fileName);
    string partTest;

    int len, dex;
    
    len = (int) file.length();
    dex = len - 1;
    while (dex > -1) {
        if (fileName[dex] == '/') {
            break;
        } else {
            dex--;
        }
    }
    dex++;
    partTest = file.substr(dex);
    len = (int) partTest.length();
    
    
    
    return partTest;
}

/**
 *Divides the file name into a vector of traits (delimiter = _)
 */

void IOPair::getTraitsFromName(){
    string name = this->entireFile;
    int start = 0;
    int end = -1;
    for (int i = 0; i < name.length(); i++){
        if (name[i] == '_'){
            end = i;
            this->traits.push_back(name.substr(start, end-start));
            start = end+1;
        }
    }
}

/**
 *Assign a number (the target) to the problem by matching the name (alphabetically)
 */

void IOPair::assignNum(){
    cout << sizeof(names) / sizeof(string) << endl;
    for (int i = 0; i < sizeof(names) / sizeof(string); i++){
        if (names[i] == this->traits[0]){
            this->actualPersonNum = i;
            break;
        }
    }
}






