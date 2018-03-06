#ifndef Study_H
#define Study_H

// c++
#include "Femur.h"
#include "Humerus.h"
#include "Tibia.h"

class Study {

private:
    std::string meshFile;
    std::string landmarksFile;
    std::string configFile;
    std::string anatomy;

public:
    static std::string getAnatomyFromString(std::string s);

    Study(std::string meshFile, std::string landmarksFile, std::string configFile);
    ~Study();
    
    void Start(std::string studyID);

};

#endif
