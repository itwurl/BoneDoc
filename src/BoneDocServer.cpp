#include "BoneDocServer.h"
#include <iostream>
#include <cmath> // Für std::round

// Funktion zum Runden auf eine bestimmte Dezimalstelle
double roundToDecimalPlaces(double value, int decimalPlaces) {
    double factor = std::pow(10.0, decimalPlaces);
    return std::round(value * factor) / factor;
}

// Funktion zur Ermittlung des Verzeichnisses des Binarys
fs::path getExecutablePath() {
    return fs::initial_path<fs::path>();
}

BoneDocServer::BoneDocServer(const char* path)
{
    std::cout << "BONEDOC_WORKING_DIR: " << BONEDOC_WORKING_DIR << std::endl;
    std::cout << "BONEDOC_CONFIGURATION_FILE: " << BONEDOC_CONFIGURATION_FILE << std::endl;
}

void BoneDocServer::Start()
{
    std::cout << "BoneDocServer started. Listening on port " << BONEDOC_SERVER_PORT << " ..." << std::endl;

    try
    {
        boost::asio::io_service io_service;
        ip::tcp::acceptor acceptor(io_service, ip::tcp::endpoint(ip::tcp::v4(), BONEDOC_SERVER_PORT));

        for (;;)
        {
            ip::tcp::socket socket(io_service);
            acceptor.accept(socket);
            std::thread(&BoneDocServer::session, this, std::move(socket)).detach();
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    std::cout << "Server closed." << std::endl;
}


void BoneDocServer::session(ip::tcp::socket socket)
{
    try {
        boost::asio::streambuf requestBuffer;
        boost::asio::read_until(socket, requestBuffer, "\r\n");

        std::istream requestStream(&requestBuffer);
        std::ostringstream responseStream;

        responseStream << "HTTP/1.1 200 OK\r\n";
        responseStream << "Content-Type: text/plain\r\n";
        responseStream << "Access-Control-Allow-Origin: *\r\n";
        responseStream << "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n";
        responseStream << "Access-Control-Allow-Headers: Content-Type, Authorization, Dataset, Anatomy, Side, Gender, EthnicGroup, Study\r\n";
        responseStream << "Access-Control-Max-Age: 86400\r\n";
        responseStream << "\r\n";

        std::string header;
        std::map<std::string, std::string> headers;

        // Header lesen und aufteilen
        while (std::getline(requestStream, header) && header != "\r") {
            auto delimiterPos = header.find(":");
            if (delimiterPos != std::string::npos) {
                std::string key = header.substr(0, delimiterPos);
                std::string value = header.substr(delimiterPos + 2); // ": " überspringen
                value.erase(value.find_last_not_of("\r\n") + 1);     // Entferne "\r\n"
                headers[key] = value;
            }
        }

        // Header-Daten abrufen
        std::string anatomy = headers["Anatomy"];
        std::string study = headers["Study"];
        std::string dataset = headers["Dataset"];

        if (!anatomy.empty() && study == "Thesis") {
            fs::path dataDir = BONEDOC_WORKING_DIR / "Data";
            fs::path anatomicalMeshPath = dataDir / (dataset + ".vtk");
            fs::path anatomicallandmarksPath = dataDir / (dataset + "-landmarks.csv");

            if (anatomy == "Femur") {
                Femur femur(anatomicalMeshPath.string(), anatomicallandmarksPath.string());
                femur.Thesis();
                responseStream << "Bone Length: " << roundToDecimalPlaces(femur.bone_length, 1) << " mm\n";
                responseStream << "Medial Offset: " << roundToDecimalPlaces(femur.medial_offset, 1) << " mm\n";
                responseStream << "Lateral Offset: " << roundToDecimalPlaces(femur.lateral_offset, 1) << " mm\n";
                responseStream << "ML Width: " << roundToDecimalPlaces(femur.ML_width, 1) << " mm\n";
                responseStream << "AP Width: " << roundToDecimalPlaces(femur.AP_width, 1) << " mm\n";
                responseStream << "Head Radius: " << roundToDecimalPlaces(femur.head_radius, 1) << " mm\n";
                responseStream << "Inclination: " << roundToDecimalPlaces(femur.inclination, 1) << "°\n";
                responseStream << "Anteversion: " << roundToDecimalPlaces(femur.anteversion, 1) << "°\n";
            } else if (anatomy == "Humerus") {
                Humerus humerus(anatomicalMeshPath.string(), anatomicallandmarksPath.string());
                humerus.Thesis();
                responseStream << "Bone Length: " << roundToDecimalPlaces(humerus.bone_length, 1) << " mm\n";
                responseStream << "Medial Offset: " << roundToDecimalPlaces(humerus.medial_offset, 1) << " mm\n";
                responseStream << "Lateral Offset: " << roundToDecimalPlaces(humerus.lateral_offset, 1) << " mm\n";
                responseStream << "ML Width: " << roundToDecimalPlaces(humerus.ML_width, 1) << " mm\n";
                responseStream << "AP Width: " << roundToDecimalPlaces(humerus.AP_width, 1) << " mm\n";
                responseStream << "Head Radius: " << roundToDecimalPlaces(humerus.head_radius, 1) << " mm\n";
                responseStream << "Inclination: " << roundToDecimalPlaces(humerus.inclination, 1) << "°\n";
                responseStream << "Retroversion: " << roundToDecimalPlaces(humerus.retroversion, 1) << "°\n";
            } else if (anatomy == "Tibia") {
                Tibia tibia(anatomicalMeshPath.string(), anatomicallandmarksPath.string());
                tibia.Thesis();
                responseStream << "Bone Length: " << roundToDecimalPlaces(tibia.bone_length, 1)  << " mm\n";
                responseStream << "Medial Offset: " << roundToDecimalPlaces(tibia.medial_offset, 1)  << " mm\n";
                responseStream << "Lateral Offset: " << roundToDecimalPlaces(tibia.lateral_offset, 1)  << " mm\n";
                responseStream << "ML Width: " << roundToDecimalPlaces(tibia.ML_width, 1)  << " mm\n";
                responseStream << "AP Width: " << roundToDecimalPlaces(tibia.AP_width, 1)  << " mm\n";
                responseStream << "Torsion: " << roundToDecimalPlaces(tibia.torsion, 1)  << "°\n";
            } else {
                responseStream << "Error: Unsupported anatomy type\n";
            }
        } else {
            responseStream << "Error: Invalid request parameters\n";
        }

        // Antwort zurücksenden
        boost::asio::write(socket, boost::asio::buffer(responseStream.str()));
        // Schließen der Sendepipeline
        socket.shutdown(boost::asio::socket_base::shutdown_send);

    } catch (const std::exception& e) {
        std::cerr << "Exception in session: " << e.what() << std::endl;
    }
}

BoneDocServer::~BoneDocServer() {
    std::cout << "BoneDocServer is shutting down." << std::endl;
}
