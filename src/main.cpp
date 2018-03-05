#include "BoneDocServer.h"

int main(int argc, char *argv[]) {

    // anatomical mesh file, anatomical landmarks file, config file
    if (argc == 4) {
        std::cout << "under construction ..." << std::endl;
        
        // check meta info and create subclassed anatomy
        //Femur femur(argv[1], argv[2], argv[3]);
        
        // start analysis
        //femur.Thesis();
    } else if (argc == 1) {

        // start http-server in application path
        // analysis will be triggered by http request's
        BoneDocServer server(argv[0]);
        server.Start();   
    } else {
        std::cout << "Usage: [anatomical mesh file (vtk)] "
                "[anatomical landmarks file (fcsv)] "
                    "[config file]" << std::endl;
        return -1;
    }

    return 0;
}
