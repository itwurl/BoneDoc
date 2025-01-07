#include "BoneDocServer.h"

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
        responseStream << "Connection: keep-alive\r\n";
        //responseStream << "Access-Control-Allow-Headers: Dataset,Anatomy,EthnicGroup,Gender,Mean,Random,Side,Study\r\n\r\n";
        responseStream << "Access-Control-Allow-Origin: *\r\n";
        responseStream << "Access-Control-Allow-Methods: GET, POST, OPTIONS\r\n";
        responseStream << "Access-Control-Allow-Headers: Content-Type, Authorization, Dataset, Anatomy, Side, Gender, EthnicGroup, Study\r\n";
        responseStream << "Access-Control-Max-Age: 86400\r\n";

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
            fs::path dataDir = BONEDOC_WORKING_DIR / "data";
            fs::path anatomicalMeshPath = dataDir / (dataset + ".vtk");
            fs::path anatomicallandmarksPath = dataDir / (dataset + "-landmarks.csv");

            if (anatomy == "Femur") {
                Femur femur(anatomicalMeshPath.string(), anatomicallandmarksPath.string());
                femur.Thesis();
                responseStream << "Bone Length: " << femur.bone_length << " mm\n";
                responseStream << "Medial Offset: " << femur.medial_offset << " mm\n";
                responseStream << "Lateral Offset: " << femur.lateral_offset << " mm\n";
                responseStream << "ML Width: " << femur.ML_width << " mm\n";
                responseStream << "AP Width: " << femur.AP_width << " mm\n";
                responseStream << "Head Radius: " << femur.head_radius << " mm\n";
                responseStream << "Inclination: " << femur.inclination << "°\n";
                responseStream << "Anteversion: " << femur.anteversion << "°\n";
            } else if (anatomy == "Humerus") {
                Humerus humerus(anatomicalMeshPath.string(), anatomicallandmarksPath.string());
                humerus.Thesis();
                responseStream << "Bone Length: " << humerus.bone_length << " mm\n";
                responseStream << "Medial Offset: " << humerus.medial_offset << " mm\n";
                responseStream << "Lateral Offset: " << humerus.lateral_offset << " mm\n";
                responseStream << "ML Width: " << humerus.ML_width << " mm\n";
                responseStream << "AP Width: " << humerus.AP_width << " mm\n";
                responseStream << "Head Radius: " << humerus.head_radius << " mm\n";
                responseStream << "Inclination: " << humerus.inclination << "°\n";
                responseStream << "Retroversion: " << humerus.retroversion << "°\n";
            } else if (anatomy == "Tibia") {
                Tibia tibia(anatomicalMeshPath.string(), anatomicallandmarksPath.string());
                tibia.Thesis();
                responseStream << "Bone Length: " << tibia.bone_length << " mm\n";
                responseStream << "Medial Offset: " << tibia.medial_offset << " mm\n";
                responseStream << "Lateral Offset: " << tibia.lateral_offset << " mm\n";
                responseStream << "ML Width: " << tibia.ML_width << " mm\n";
                responseStream << "AP Width: " << tibia.AP_width << " mm\n";
                responseStream << "Torsion: " << tibia.torsion << "°\n";
            } else {
                responseStream << "Error: Unsupported anatomy type\n";
            }
        } else {
            responseStream << "Error: Invalid request parameters\n";
        }

        // Antwort zurücksenden
        boost::asio::write(socket, boost::asio::buffer(responseStream.str()));
    } catch (const std::exception& e) {
        std::cerr << "Exception in session: " << e.what() << std::endl;
    }
}

BoneDocServer::~BoneDocServer() {
    std::cout << "BoneDocServer is shutting down." << std::endl;
}
