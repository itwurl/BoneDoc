#include "BoneDocServer.h"
#include "Study.h"

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        // start http-server, analysis will be triggered by client requests
        // '/data' must be found within application folder
        BoneDocServer server(argv[0]);
        server.Start();
    }
    else if (argc == 4)
    {
        // create a study
        Study study(argv[1], argv[2], argv[3]);
        
        // start an analysis
        study.Start("Thesis");
    }
    else
    {
        cout << "Usage (server):\t./BoneDoc" << endl;
        cout << "Usage (command line):\t./BoneDoc [mesh (*.stl *.vtk)] [landmarks (*.csv)] [config (*.txt)]" << endl;
        return -1;
    }

    return 0;
}
