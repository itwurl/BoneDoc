#ifndef BONEDOCSERVER_H
#define BONEDOCSERVER_H

// boost
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>

// c++
#include <iostream>
#include <cstdlib>
#include <thread>
#include <utility>

// BoneDoc
#include "Femur.h"
#include "Humerus.h"
#include "Tibia.h"

namespace fs = boost::filesystem;

class BoneDocServer {
	
public:

    BoneDocServer(const char* path);
    void Start();

    ~BoneDocServer();

private:

    const int BONEDOC_SERVER_PORT = 61180;
    const char* BONEDOC_SERVER_PORT_STR = "61180";
    const fs::path BONEDOC_WORKING_DIR = fs::initial_path<fs::path>();
    const fs::path BONEDOC_CONFIGURATION_FILE = BONEDOC_WORKING_DIR / "bonedoc.conf";

};

#endif /* BONEDOCSERVER_H */

