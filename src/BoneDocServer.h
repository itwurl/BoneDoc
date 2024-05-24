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
namespace ip = boost::asio::ip;

class BoneDocServer {
	
public:

    BoneDocServer(const char* path);
    void Start();

    ~BoneDocServer();
    void session(ip::tcp::socket socket);

private:
    const int BONEDOC_SERVER_PORT = 61180; // Port utilized for the program's service communication
    const fs::path BONEDOC_WORKING_DIR = fs::initial_path<fs::path>(); // Working dir for program
    const fs::path BONEDOC_CONFIGURATION_FILE = BONEDOC_WORKING_DIR / "bonedoc.conf"; // Filename utilized for the program's configuration

};

#endif /* BONEDOCSERVER_H */

