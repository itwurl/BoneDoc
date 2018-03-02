/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   BoneDocServer.h
 * Author: wurl
 *
 * Created on 19. Januar 2018, 17:57
 */

#ifndef BONEDOCSERVER_H
#define BONEDOCSERVER_H


#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
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
    BoneDocServer();
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

