// BoneDoc
#include "Study.h"

Study::Study(std::string meshFile, std::string landmarksFile, std::string configFile) {

    // use first parameter to parse anatomy string from
    anatomy = getAnatomyFromString(meshFile);
    this->meshFile = meshFile;
    this->landmarksFile = landmarksFile;
    this->configFile = configFile;

}

void Study::Start(std::string studyID) {

    if (anatomy.compare("FEMUR") == 0)
    {
         // check meta info and create subclassed anatomy 'femur'
         Femur femur(meshFile, landmarksFile, configFile);

         // start study 'thesis'
         femur.Thesis();
    }
    else if (anatomy.compare("HUMERUS") == 0)
    {
         // check meta info and create subclassed anatomy
         Humerus humerus(meshFile, landmarksFile, configFile);

         // start study 'thesis'
         humerus.Thesis();
    } 
    else if (anatomy.compare("TIBIA") == 0)
    {
         // check meta info and create subclassed anatomy
         Tibia tibia(meshFile, landmarksFile, configFile);

         // start study 'thesis'
         tibia.Thesis();
    }
    else
    {
         std::cout << "No valid anatomy found!" << std::endl;
    }
    
}

// try to get anatomical identifier from file (femur, humerus, tibia)
std::string Study::getAnatomyFromString(std::string s) {

    // string s might be a file path - try to cut starting from last '/'
    int pos = s.find_last_of("/");

    if (pos != std::string::npos)
        s = s.substr(pos + 1, s.length() - (pos + 1));

    std::string ret = "";
    
    // make 'file' great again
    std::transform(s.begin(), s.end(), s.begin(), ::toupper);

    // try to find side ...
    if ( (s.find("FEMUR") != std::string::npos) || (s.compare(0, 3, "FEM") == 0) )
        ret = "FEMUR";
    else if ( (s.find("HUMERUS") != std::string::npos) || (s.compare(0, 3, "HUM") == 0) )
        ret = "HUMERUS";
    else if ( (s.find("TIBIA") != std::string::npos) || (s.compare(0, 3, "TIB") == 0) )
        ret = "TIBIA";
    else
        ret = "";
    
    return ret;
}

Study::~Study() {
    
}

