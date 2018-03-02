/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "BoneDocServer.h"
#include "Femur.h"


BoneDocServer::BoneDocServer() {

}

void session(boost::asio::ip::tcp::socket socket)
{
    
    try
    {
        for (;;)
        {
            
            // read the request header (until blank line)
            boost::asio::streambuf request;
            boost::asio::read_until(socket, request, "\r\n");

            // put request to input stream
            std::istream request_stream(&request);

            // vars
            std::string request_header = "";
            std::string anatomy = "";
            std::string dataset = "";
            std::string study = "";
            
            // print the request (header), each line is separated by carriage return symbol '\r'.
            std::cout << "Client request:" << "\n";

            while (std::getline(request_stream, request_header) && request_header != "\r")
            {
                std::cout << request_header << "\n";
                if (request_header.compare(0, 7, "Anatomy") == 0)
                    anatomy = request_header.substr(9, request_header.length()-10);
                else if (request_header.compare(0, 7, "Dataset") == 0)
                    dataset = request_header.substr(9, request_header.length()-10);
                else if (request_header.compare(0, 5, "Study") == 0)
                    study = request_header.substr(7, request_header.length()-8);
            }
            std::cout << std::endl;

            // put server's response to output stream
            boost::asio::streambuf response;
            std::ostream response_stream(&response);

            response_stream << "HTTP/1.1 200 OK\r\n";
            response_stream << "Content-Type: text/plain\r\n";
            response_stream << "Access-Control-Allow-Origin: *\r\n";
            response_stream << "Connection: keep alive\r\n";
            response_stream << "Access-Control-Allow-Headers: Anatomy,Dataset,Study\r\n\r\n";
            
            // client message is only considered for analysis if header consists of meta infos
            if ((anatomy != "") && (dataset != "") && (study == "Thesis"))
            {
                std::cout << "Starting study 'Thesis' with:" << "\n";

                std::cout << "anatomy: " << anatomy << std::endl;
                std::cout << "dataset: " << dataset << std::endl;
                std::cout << "study: " << study << std::endl;

                std::cout << "\n";

                // concatenate correct path's (DEBUG: currently 'VTK' and 'FCSV' format required!)
                std::stringstream anatomicalMeshPath;
                anatomicalMeshPath << "Data/" << dataset << ".vtk";

                std::stringstream anatomicallandmarksPath;
                anatomicallandmarksPath << "Data/" << dataset << ".fcsv";

                // DEBUG: recognize anatomy from dataset name
		std::transform(dataset.begin(), dataset.end(), dataset.begin(), ::toupper);
		if (dataset.find("FEMUR") != std::string::npos)
                {
                    Femur femur(anatomicalMeshPath.str(), anatomicallandmarksPath.str());
                    femur.Thesis();

                    response_stream << "anteversion: " << femur.anteversion << std::endl;
                    response_stream << "ap with: " << femur.AP_width << std::endl;
                    response_stream << "bone length: " << femur.bone_length << std::endl;
                    response_stream << "head radius: " << femur.head_radius << std::endl;
                    response_stream << "inclination: " << femur.inclination << std::endl;
                    response_stream << "lateral offset: " << femur.lateral_offset << std::endl;
                    response_stream << "medial offset: " << femur.medial_offset << std::endl;
                    response_stream << "ml with: " << femur.ML_width << std::endl;
                }
                else if (dataset.find("HUMERUS") != std::string::npos)
                {
                    response_stream << "Under construction!" << std::endl;
		}
		else if (dataset.find("TIBIA") != std::string::npos)
                {
                    response_stream << "Under construction!" << std::endl;
                }

            }

            // write to socket
            boost::asio::write(socket, response);
            
            // mit break funktioniert es - Nachricht wird dann gesendet!!!!!!!!!
            break;
        }

    }
    catch (std::exception& e)
    {
      std::cerr << "Exception in thread: " << e.what() << "\n";
    }

}



void BoneDocServer::Start() {

    try {

        boost::asio::io_service io_service;
        boost::asio::ip::tcp::acceptor a(io_service, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), BONEDOC_SERVER_PORT));

        for (;;) {

            //std::cout << "Listening on port " << BONEDOC_SERVER_PORT_STR << " ..." << std::endl << std::endl;
            boost::asio::ip::tcp::socket socket(io_service);
            a.accept(socket);
            //std::cout << "Client " << socket.remote_endpoint().address() << " connected!" << std::endl << std::endl;
            std::thread(session, std::move(socket)).detach();
        }

    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

}

BoneDocServer::~BoneDocServer() {
    
}