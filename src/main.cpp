#include "BoneDocServer.h"

int main(int argc, char *argv[]) {

//    Femur femur("/home/wurl/Projekte/BoneDoc/Data/FemurLeftFemaleA.vtk",
//                    "/home/wurl/Projekte/BoneDoc/Data/FemurLeftFemaleA.fcsv",
//                        "/home/wurl/Projekte/BoneDoc/config.txt");
//    
//    femur.Thesis();
    
    // server - needs application path
    BoneDocServer server(argv[0]);

    server.Start();

    return 0;
}
