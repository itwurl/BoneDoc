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

class BoneDocServer {
	
	//static void session(boost::asio::ip::tcp::socket sock);


public:

	//const std::string BONEDOC_CONFIG_FILE = "/home/pi/Projects/BoneDoc/config.txt";

    BoneDocServer(const char* path);
    void Start();

    ~BoneDocServer();

private:

    const int BONEDOC_SERVER_PORT = 16118;
    const char* BONEDOC_SERVER_PORT_STR = "16118";

    std::string anatomy = "";
    std::string dataset = "";
    std::string study = "";
	

};

#endif /* BONEDOCSERVER_H */

