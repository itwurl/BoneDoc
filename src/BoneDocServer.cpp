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
    try
    {
        for (;;)
        {
            boost::asio::streambuf request;
            boost::asio::read_until(socket, request, "\r\n");

            std::istream request_stream(&request);

            std::string method, target, request_header;
            std::getline(request_stream, method); // "GET /path HTTP/1.1"

            std::cout << "Incoming Request: " << method << std::endl;

            // Variables to store the request headers
            std::string mesh, dataset, anatomy, side, gender, ethnic_group, study, anatomical_landmarks;

            // Read and process request headers
            while (std::getline(request_stream, request_header) && request_header != "\r")
            {
                std::cout << "DEBUG: request_header = '" << request_header << "'" << std::endl;

                if (request_header.compare(0, 7, "Anatomy") == 0)
                    anatomy = request_header.substr(9, request_header.length() - 10);
                else if (request_header.compare(0, 11, "EthnicGroup") == 0)
                    ethnic_group = request_header.substr(13, request_header.length() - 14);
                else if (request_header.compare(0, 6, "Gender") == 0)
                    gender = request_header.substr(8, request_header.length() - 9);
                else if (request_header.compare(0, 4, "Mean") == 0)
                    mesh = request_header.substr(6, request_header.length() - 7);
                else if (request_header.compare(0, 6, "Random") == 0)
                    mesh = request_header.substr(8, request_header.length() - 9);
                else if (request_header.compare(0, 4, "Side") == 0)
                    side = request_header.substr(6, request_header.length() - 7);
                else if (request_header.compare(0, 5, "Study") == 0)
                    study = request_header.substr(7, request_header.length() - 8);
                else if (request_header.compare(0, 7, "Dataset") == 0)
                    dataset = request_header.substr(9, request_header.length() - 10);
                else
                    std::cout << "DEBUG: Unrecognized header: " << request_header << std::endl;
            }

            // Prepare the response
            boost::asio::streambuf response;
            std::ostream response_stream(&response);

            // Basic headers for CORS and content
            response_stream << "HTTP/1.1 200 OK\r\n";
            response_stream << "Content-Type: text/plain\r\n";
            response_stream << "Access-Control-Allow-Origin: *\r\n";
            response_stream << "Connection: keep-alive\r\n";
            response_stream << "Access-Control-Allow-Headers: Dataset,Anatomy,EthnicGroup,Gender,Mean,Random,Side,Study\r\n\r\n";

            // Check if request contains valid anatomy and study data
            if (!anatomy.empty() && study == "Thesis")
            {
                fs::path dataDir = BONEDOC_WORKING_DIR / "data";
                std::cout << "dataDir: " << dataDir << std::endl;

                fs::path anatomicalMeshPath = dataDir / (dataset + ".vtk");
                std::cout << "anatomicalMeshPath: " << anatomicalMeshPath << std::endl;

                fs::path anatomicallandmarksPath = dataDir / (dataset + "-landmarks.csv");
                std::cout << "anatomicallandmarksPath: " << anatomicallandmarksPath << std::endl;

                // Process based on anatomy
                if (anatomy == "Femur")
                {
                    Femur femur(anatomicalMeshPath.string(), anatomicallandmarksPath.string());
                    femur.Thesis();
                    response_stream << "bone length: " << femur.bone_length << " mm\n";
                    response_stream << "medial offset: " << femur.medial_offset << " mm\n";
                    response_stream << "lateral offset: " << femur.lateral_offset << " mm\n";
                    response_stream << "ml width: " << femur.ML_width << "mm" << endl;
                    response_stream << "ap width: " << femur.AP_width << "mm" << endl;
                    response_stream << "head radius: " << femur.head_radius << "mm" << endl;
                    response_stream << "inclination: " << femur.inclination << "°" << endl;
                    response_stream << "anteversion: " << femur.anteversion << "°" << endl;
                    response_stream << "asian: " << femur.asian << "%" << endl;
                    response_stream << "caucasian: " << femur.caucasian << "%" << endl;
                }
                else if (anatomy == "Humerus")
                {
                    Humerus humerus(anatomicalMeshPath.string(), anatomicallandmarksPath.string());
                    humerus.Thesis();
                    response_stream << "bone length: " << humerus.bone_length << " mm\n";
                    response_stream << "medial offset: " << humerus.medial_offset << "mm" << endl;
                    response_stream << "lateral offset: " << humerus.lateral_offset << "mm" << endl;
                    response_stream << "ml width: " << humerus.ML_width << "mm" << endl;
                    response_stream << "ap width: " << humerus.AP_width << "mm" << endl;
                    response_stream << "head radius: " << humerus.head_radius << "mm" << endl;
                    response_stream << "inclination: " << humerus.inclination << "°" << endl;
                    response_stream << "retroversion: " << humerus.retroversion << "°" << endl;
                    response_stream << "asian: " << humerus.asian << "%" << endl;
                    response_stream << "caucasian: " << humerus.caucasian << "%" << endl;
                }
                else if (anatomy == "Tibia")
                {
                    Tibia tibia(anatomicalMeshPath.string(), anatomicallandmarksPath.string());
                    tibia.Thesis();
                    response_stream << "bone length: " << tibia.bone_length << " mm\n";
                    response_stream << "medial offset: " << tibia.medial_offset << "mm" << endl;
                    response_stream << "lateral offset: " << tibia.lateral_offset << "mm" << endl;
                    response_stream << "ml width: " << tibia.ML_width << "mm" << endl;
                    response_stream << "ap width: " << tibia.AP_width << "mm" << endl;
                    response_stream << "torsion: " << tibia.torsion << "°" << endl;
                    response_stream << "asian: " << tibia.asian << "%" << endl;
                    response_stream << "caucasian: " << tibia.caucasian << "%" << endl;
                }
            }

            // Send the response back to the client
            boost::asio::write(socket, response);
            break; // Exit after responding
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << "Exception in session: " << e.what() << std::endl;
    }
}

BoneDocServer::~BoneDocServer() {
    std::cout << "BoneDocServer is shutting down." << std::endl;
}
