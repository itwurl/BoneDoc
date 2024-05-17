#ifndef Study_H
#define Study_H

// c++
#include "Femur.h"
#include "Humerus.h"
#include "Tibia.h"

class Study {

private:
    string meshFile;
    string landmarksFile;
    string configFile;
    string anatomy;

public:
    static string getAnatomyFromString(string s);

    Study(string meshFile, string landmarksFile, string configFile);
    ~Study();
    
    void Start(string studyID);

};

#endif
