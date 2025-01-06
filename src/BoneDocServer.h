#ifndef BONEDOCSERVER_H
#define BONEDOCSERVER_H

// Boost Libraries
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>

// C++ Standard Libraries
#include <iostream>
#include <cstdlib>
#include <thread>
#include <utility>

// BoneDoc specific includes
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
    const int BONEDOC_SERVER_PORT = 61180;
    const fs::path BONEDOC_WORKING_DIR = fs::initial_path<fs::path>();
    const fs::path BONEDOC_CONFIGURATION_FILE = BONEDOC_WORKING_DIR / "bonedoc.conf";
};

#endif /* BONEDOCSERVER_H */
