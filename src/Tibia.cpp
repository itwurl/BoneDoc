#include "Tibia.h"

Tibia::Tibia(const std::string anatomicalMeshPath,
                const std::string anatomicalLandmarksPath,
                    const std::string configPath)
{
    this->configPath = configPath;
    
    // read number of anatomical landmarks
    SetAnatomicalLandmarksSize(configPath, "tibia-anatomical-landmarks-size");
    
    // load and set anatomical landmarks
    SetAnatomicalLandmarks(anatomicalLandmarksPath);

    // load and set anatomical mesh
    SetAnatomicalMesh(anatomicalMeshPath);

    // antomical parameters must be set to if valid output is required
    ResetMeasurements();

    // load and set meta information
    SetMetaInfo(anatomicalMeshPath);
}

void Tibia::ResetMeasurements()
{
    bone_length = medial_offset = lateral_offset = ML_width = AP_width = torsion = 0;

    // initialize corresponding (technical) landmark coordinates and size of sphere for visualizing
    medial_malleolus[0] = medial_malleolus[1] = medial_malleolus[2] = medial_malleolus[3] = 0;
    fibular_notch[0] = fibular_notch[1] = fibular_notch[2] = fibular_notch[3] = 0;
    medial_epicondyle[0] = medial_epicondyle[1] = medial_epicondyle[2] = medial_epicondyle[3] = 0;
    lateral_epicondyle[0] = lateral_epicondyle[1] = lateral_epicondyle[2] = lateral_epicondyle[3] = 0;
    tuberositas[0] = tuberositas[1] = tuberositas[2] = tuberositas[3] = 0;
    most_proximal_point[0] = most_proximal_point[1] = most_proximal_point[2] = most_proximal_point[3] = 0;
    medial_condyle[0] = medial_condyle[1] = medial_condyle[2] = medial_condyle[3] = 0;
    lateral_condyle[0] = lateral_condyle[1] = lateral_condyle[2] = lateral_condyle[3] = 0;

    MapAnatomicalLandmarksToAnatomicalMesh();
}

void Tibia::MapAnatomicalLandmarksToAnatomicalMesh()
{
    getClosestPointFromMesh(anatomicalLandmarks.at(0), medial_malleolus, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(1), fibular_notch, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(2), medial_epicondyle, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(3), lateral_epicondyle, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(4), tuberositas, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(5), most_proximal_point, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(6), medial_condyle, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(7), lateral_condyle, anatomicalMesh);
}

void Tibia::Thesis()
{
    std::cout << "##################" << std::endl;
    std::cout << "# Thesis - Tibia #" << std::endl;
    std::cout << "##################" << std::endl;

    // to be calculated in global system
    SetProximalShaftCenter();
    SetDistalShaftCenter();

    SetMedialAndLateralAxis();
    SetCoordinateSystem();
    
    // local system required
    SetOffsetAndWidth();

    // ################################# //
    // ### CALCULATION OF PARAMETERS ### //
    // ################################# //

    BoneLength();

    MedialOffset();
    LateralOffset();
    MLWidth();
    APWidth();

    TibiaTorsion();

    GuessEthnicGroup();

    std::cout << "ap width: " << AP_width << "mm" << std::endl;
    std::cout << "bone length: " << bone_length << "mm" << std::endl;
    std::cout << "lateral offset: " << lateral_offset << "mm" << std::endl;
    std::cout << "medial offset: " << medial_offset << "mm" << std::endl;
    std::cout << "ml width: " << ML_width << "mm" << std::endl;
    std::cout << "torsion: " << torsion << "°" << std::endl;
    std::cout << "asian: " << asian << "%" << std::endl;
    std::cout << "caucasian: " << caucasian << "%" << std::endl;
}

// no references yet.
void Tibia::SetProximalShaftCenter()
{
    // ### center-point: 80% of length (proximal) ###
    double center[3];
    center[0] = medial_malleolus[0] + ((most_proximal_point[0]-medial_malleolus[0]) * 0.8);
    center[1] = medial_malleolus[1] + ((most_proximal_point[1]-medial_malleolus[1]) * 0.8);
    center[2] = medial_malleolus[2] + ((most_proximal_point[2]-medial_malleolus[2]) * 0.8);

    // normal, defined with 
    double normal[3]; double bn;
    bn = sqrt(pow(most_proximal_point[0]-medial_malleolus[0], 2) + pow(most_proximal_point[1]-medial_malleolus[1], 2) + pow(most_proximal_point[2]-medial_malleolus[2], 2) );
    normal[0] = (most_proximal_point[0]-medial_malleolus[0]) / bn;
    normal[1] = (most_proximal_point[1]-medial_malleolus[1]) / bn;
    normal[2] = (most_proximal_point[2]-medial_malleolus[2]) / bn;

    // plane
    vtkSmartPointer<vtkPlane> vtkplane_prox = vtkSmartPointer<vtkPlane>::New();
    vtkplane_prox->SetOrigin(center[0], center[1], center[2]);
    vtkplane_prox->SetNormal(normal[0], normal[1], normal[2]);

    // surface cut with plane
    vtkSmartPointer<vtkCutter> cutEdges_prox = vtkSmartPointer<vtkCutter>::New();
    cutEdges_prox->SetInputData(anatomicalMesh);
    cutEdges_prox->SetCutFunction(vtkplane_prox);

    // generates triangle poly-lines from input polygon
    vtkSmartPointer<vtkStripper> cutStrips_prox = vtkSmartPointer<vtkStripper>::New();
    cutStrips_prox->SetInputConnection( cutEdges_prox->GetOutputPort() );
    cutStrips_prox->Update();
    vtkSmartPointer<vtkPolyData> cutPoly_prox = vtkSmartPointer<vtkPolyData>::New();
    cutPoly_prox->SetPoints( cutStrips_prox->GetOutput()->GetPoints());
    cutPoly_prox->SetPolys( cutStrips_prox->GetOutput()->GetLines());

    cutPoly_prox->GetCenter(proximal_shaft_center);

    // crash's may occure if no suitable cut were done - so return then
    if (cutPoly_prox->GetNumberOfPoints() == 0)
    {
        std::cout << "error cutting proximal part of shaft!" << std::endl;
        return;
    }
}

void Tibia::SetDistalShaftCenter()
{
    double center[3];
    double normal[3];
    double bn;
    
    // ### center-point: 20% of length ###
    center[0] = medial_malleolus[0] + ((most_proximal_point[0] - medial_malleolus[0]) * 0.2);
    center[1] = medial_malleolus[1] + ((most_proximal_point[1] - medial_malleolus[1]) * 0.2);
    center[2] = medial_malleolus[2] + ((most_proximal_point[2] - medial_malleolus[2]) * 0.2);

    bn = sqrt(pow(most_proximal_point[0] - medial_malleolus[0], 2) + pow(most_proximal_point[1]-medial_malleolus[1], 2) + pow(most_proximal_point[2]-medial_malleolus[2], 2) );
    normal[0] = (most_proximal_point[0] - medial_malleolus[0]) / bn;
    normal[1] = (most_proximal_point[1] - medial_malleolus[1]) / bn;
    normal[2] = (most_proximal_point[2] - medial_malleolus[2]) / bn;

    // plane
    vtkSmartPointer<vtkPlane> vtkplane_dist = vtkSmartPointer<vtkPlane>::New();
    vtkplane_dist->SetOrigin(center[0], center[1], center[2]);
    vtkplane_dist->SetNormal(normal[0], normal[1], normal[2]);

    // surface cut with plane
    vtkSmartPointer<vtkCutter> cutEdges_dist = vtkSmartPointer<vtkCutter>::New();
    cutEdges_dist->SetInputData(anatomicalMesh);
    cutEdges_dist->SetCutFunction(vtkplane_dist);

    // generates triangle poly-lines from input polygon
    vtkSmartPointer<vtkStripper> cutStrips_dist = vtkSmartPointer<vtkStripper>::New();
    cutStrips_dist->SetInputConnection(cutEdges_dist->GetOutputPort());
    cutStrips_dist->Update();
    vtkSmartPointer<vtkPolyData> cutPoly_dist = vtkSmartPointer<vtkPolyData>::New();
    cutPoly_dist->SetPoints(cutStrips_dist->GetOutput()->GetPoints());
    cutPoly_dist->SetPolys(cutStrips_dist->GetOutput()->GetLines());

    // crash's may occure if no suitable cut were done - so return then
    if (cutPoly_dist->GetNumberOfPoints() == 0)
    {
        std::cout << "error cutting distal part of shaft!" << std::endl;
        return;
    }

    cutPoly_dist->GetCenter(distal_shaft_center);
}

void Tibia::SetMedialAndLateralAxis()
{
    // define temporarily medio-lateral ...
    axis[0] = medial_condyle[0] - lateral_condyle[0];
    axis[1] = medial_condyle[1] - lateral_condyle[1];
    axis[2] = medial_condyle[2] - lateral_condyle[2];
    
    // ... and cranio-caudal axis
    axis[3] = proximal_shaft_center[0] - distal_shaft_center[0];
    axis[4] = proximal_shaft_center[1] - distal_shaft_center[1];
    axis[5] = proximal_shaft_center[2] - distal_shaft_center[2];
}

void Tibia::SetOffsetAndWidth()
{
    // ### center-point: 80% of length (proximal) ###
    double center[3];
    center[0] = medial_malleolus[0] + ((most_proximal_point[0]-medial_malleolus[0]) * 0.8);
    center[1] = medial_malleolus[1] + ((most_proximal_point[1]-medial_malleolus[1]) * 0.8);
    center[2] = medial_malleolus[2] + ((most_proximal_point[2]-medial_malleolus[2]) * 0.8);

    // normal, defined with 
    double normal[3]; double bn;
    bn = sqrt( pow(most_proximal_point[0]-medial_malleolus[0], 2) + pow(most_proximal_point[1]-medial_malleolus[1], 2) + pow(most_proximal_point[2]-medial_malleolus[2], 2) );
    normal[0] = (most_proximal_point[0]-medial_malleolus[0]) / bn;
    normal[1] = (most_proximal_point[1]-medial_malleolus[1]) / bn;
    normal[2] = (most_proximal_point[2]-medial_malleolus[2]) / bn;

    // plane
    vtkSmartPointer<vtkPlane> vtkplane_prox = vtkSmartPointer<vtkPlane>::New();
    vtkplane_prox->SetOrigin(center[0], center[1], center[2]);
    vtkplane_prox->SetNormal(normal[0], normal[1], normal[2]);

    // surface cut with plane
    vtkSmartPointer<vtkCutter> cutEdges_prox = vtkSmartPointer<vtkCutter>::New();
    cutEdges_prox->SetInputData(anatomicalMesh);
    cutEdges_prox->SetCutFunction(vtkplane_prox);

    // generates triangle poly-lines from input polygon
    vtkSmartPointer<vtkStripper> cutStrips_prox = vtkSmartPointer<vtkStripper>::New();
    cutStrips_prox->SetInputConnection( cutEdges_prox->GetOutputPort() );
    cutStrips_prox->Update();
    vtkSmartPointer<vtkPolyData> cutPoly_prox = vtkSmartPointer<vtkPolyData>::New();
    cutPoly_prox->SetPoints( cutStrips_prox->GetOutput()->GetPoints());
    cutPoly_prox->SetPolys( cutStrips_prox->GetOutput()->GetLines());

    cutPoly_prox->GetCenter(proximal_shaft_center);

    
   // ### OFFSET AN WIDTH ###
    double tmp3[3];
    double plane[9];
    double min = 9999; int mini = 0;
    
    // look for most lateral point - p8
    for (int i=0; i < cutPoly_prox->GetNumberOfPoints(); ++i) {
        cutPoly_prox->GetPoint(i, tmp3);

        // plane: n, x, p
        plane[0] = axis[3]; plane[1] = axis[4]; plane[2] = axis[5];
        plane[3] = tmp3[0]; plane[4] = tmp3[1]; plane[5] = tmp3[2];
        plane[6] = proximal_shaft_center[0]; plane[7] = proximal_shaft_center[1]; plane[8] = proximal_shaft_center[2];

        if (distanceToPlane(plane) < min) {
            min = distanceToPlane(plane);
            mini = i;
        }

    }

    cutPoly_prox->GetPoint(mini, most_lateral_shaft_point);

    // most medial point - p9
    double max = -9999; int maxi = 0;
    
    for (int i=0; i<cutPoly_prox->GetNumberOfPoints(); ++i ) {
        cutPoly_prox->GetPoint(i, tmp3);

        // define plane with mediolateral axis as normal * (-1)
        plane[0] = axis[3]; plane[1] = axis[4]; plane[2] = axis[5];
        plane[3] = tmp3[0]; plane[4] = tmp3[1]; plane[5] = tmp3[2];
        plane[6] = proximal_shaft_center[0]; plane[7] = proximal_shaft_center[1]; plane[8] = proximal_shaft_center[2];

        if (distanceToPlane(plane) > max) {
            max = distanceToPlane(plane);
            maxi = i;
        }

    }

    cutPoly_prox->GetPoint(maxi, most_medial_shaft_point);

    // most posterior point - p10
    max = 0; maxi = 0;
    
    for (int i = 0; i < cutPoly_prox->GetNumberOfPoints(); ++i) {
        cutPoly_prox->GetPoint(i, tmp3);

        plane[0] = axis[0]; plane[1] = axis[1]; plane[2] = axis[2];
        plane[3] = tmp3[0]; plane[4] = tmp3[1]; plane[5] = tmp3[2];
        plane[6] = proximal_shaft_center[0]; plane[7] = proximal_shaft_center[1]; plane[8] = proximal_shaft_center[2];

        if (distanceToPlane(plane) > max) {
            max = distanceToPlane(plane);
            maxi = i;
        }

    }

    cutPoly_prox->GetPoint(maxi, most_posterior_shaft_point);

    // most anterior p11
    max = 0; maxi = 0;
    
    for (int i = 0; i < cutPoly_prox->GetNumberOfPoints(); ++i)
    {
        cutPoly_prox->GetPoint(i, tmp3);

        // define plane with mediolateral axis as normal * (-1)
        plane[0] = -1 * axis[0]; plane[1] = -1 * axis[1]; plane[2] = -1 * axis[2];
        plane[3] = tmp3[0]; plane[4] = tmp3[1]; plane[5] = tmp3[2];
        plane[6] = proximal_shaft_center[0]; plane[7] = proximal_shaft_center[1]; plane[8] = proximal_shaft_center[2];

        if (distanceToPlane(plane) > max) {
            max = distanceToPlane(plane);
            maxi = i;
        }

    }

    cutPoly_prox->GetPoint(maxi, most_anterior_shaft_point);
}

void Tibia::BoneLength()
{
    bone_length = sqrt(pow(most_proximal_point[0] - medial_malleolus[0], 2) + pow(most_proximal_point[1] - medial_malleolus[1], 2) + pow(most_proximal_point[2] - medial_malleolus[2], 2) );
}

void Tibia::MedialOffset()
{
    // medial offset:
    double plane[9];
    
    plane[0] = axis[3]; plane[1] = axis[4]; plane[2] = axis[5];
    plane[3] = medial_epicondyle[0]; plane[4] = medial_epicondyle[1]; plane[5] = medial_epicondyle[2];
    plane[6] = most_medial_shaft_point[0]; plane[7] = most_medial_shaft_point[1]; plane[8] = most_medial_shaft_point[2];
    medial_offset = distanceToPlane( plane );
}

void Tibia::LateralOffset()
{
    // lateral offset:
    double plane[9];

    plane[0] = axis[3]; plane[1] = axis[4]; plane[2] = axis[5];
    plane[3] = most_lateral_shaft_point[0]; plane[4] = most_lateral_shaft_point[1]; plane[5] = most_lateral_shaft_point[2];
    plane[6] = lateral_epicondyle[0]; plane[7] = lateral_epicondyle[1]; plane[8] = lateral_epicondyle[2];
    lateral_offset = distanceToPlane( plane );

}

void Tibia::MLWidth()
{
    // ml width:
    double plane[9];

    plane[0] = axis[3]; plane[1] = axis[4]; plane[2] = axis[5];
    plane[3] = most_medial_shaft_point[0]; plane[4] = most_medial_shaft_point[1]; plane[5] = most_medial_shaft_point[2];
    plane[6] = most_lateral_shaft_point[0]; plane[7] = most_lateral_shaft_point[1]; plane[8] = most_lateral_shaft_point[2];
    ML_width = distanceToPlane( plane );

}

void Tibia::APWidth()
{
    // ap width:
    double plane[9];

    plane[0] = axis[0]; plane[1] = axis[1]; plane[2] = axis[2];
    plane[3] = most_posterior_shaft_point[0]; plane[4] = most_posterior_shaft_point[1]; plane[5] = most_posterior_shaft_point[2];
    plane[6] = most_anterior_shaft_point[0]; plane[7] = most_anterior_shaft_point[1]; plane[8] = most_anterior_shaft_point[2];
    AP_width = distanceToPlane(plane);
}

void Tibia::TibiaTorsion()
{
    // malleolus axis
    std::vector<double> malleolus_axis(3);

    // malleolus
    malleolus_axis.at(0) = medial_malleolus[0] - fibular_notch[0];
    malleolus_axis.at(1) = medial_malleolus[1] - fibular_notch[1];
    malleolus_axis.at(2) = medial_malleolus[2] - fibular_notch[2];

    double b3 = sqrt(pow(malleolus_axis.at(0), 2) + pow(malleolus_axis.at(1), 2) + pow(malleolus_axis.at(2), 2));

    malleolus_axis.at(0) = malleolus_axis.at(0) / b3;
    malleolus_axis.at(1) = malleolus_axis.at(1) / b3;
    malleolus_axis.at(2) = malleolus_axis.at(2) / b3;

    // lambda
    double lambda1 = (axis[6]) * malleolus_axis.at(0) + (axis[7]) * malleolus_axis.at(1) + (axis[8]) * malleolus_axis.at(2);

    // project neck axis onot axial plane
    std::vector<double> malleolus_axis_kk(3);

    // if lambda1 < 0 (behind plane + projection, else - projection)
    malleolus_axis_kk.at(0) = malleolus_axis.at(0) - lambda1 * (axis[6]);
    malleolus_axis_kk.at(1) = malleolus_axis.at(1) - lambda1 * (axis[7]);
    malleolus_axis_kk.at(2) = malleolus_axis.at(2) - lambda1 * (axis[8]);

    // norm
    double b1 = sqrt(pow(malleolus_axis_kk.at(0), 2) + pow(malleolus_axis_kk.at(1), 2) + pow(malleolus_axis_kk.at(2), 2) );
    malleolus_axis_kk.at(0) = malleolus_axis_kk.at(0) / b1;
    malleolus_axis_kk.at(1) = malleolus_axis_kk.at(1) / b1;
    malleolus_axis_kk.at(2) = malleolus_axis_kk.at(2) / b1;
    std::vector<double> tib_epicondyle_axis(3);
    tib_epicondyle_axis.at(0) = medial_condyle[0] - lateral_condyle[0];
    tib_epicondyle_axis.at(1) = medial_condyle[1] - lateral_condyle[1];
    tib_epicondyle_axis.at(2) = medial_condyle[2] - lateral_condyle[2];

    double b = sqrt( pow(tib_epicondyle_axis.at(0),2) + pow(tib_epicondyle_axis.at(1), 2) + pow(tib_epicondyle_axis.at(2), 2) );
    tib_epicondyle_axis.at(0) = tib_epicondyle_axis.at(0) / b;
    tib_epicondyle_axis.at(1) = tib_epicondyle_axis.at(1) / b;
    tib_epicondyle_axis.at(2) = tib_epicondyle_axis.at(2) / b;

    // project epicondyle axis onto axial plane
    std::vector<double> tib_epicondyle_axis_kk(3);

    // lambda:
    double lambda2 = (axis[6]) * tib_epicondyle_axis.at(0) + (axis[7]) * tib_epicondyle_axis.at(1) + (axis[8]) * tib_epicondyle_axis.at(2);

    // if lambda2 < 0 (behind plane + projection, else - projection)
    tib_epicondyle_axis_kk.at(0) = tib_epicondyle_axis.at(0) - lambda2 * (axis[6]);
    tib_epicondyle_axis_kk.at(1) = tib_epicondyle_axis.at(1) - lambda2 * (axis[7]);
    tib_epicondyle_axis_kk.at(2) = tib_epicondyle_axis.at(2) - lambda2 * (axis[8]);

    // norm
    double b2 = sqrt(pow(tib_epicondyle_axis_kk.at(0), 2) + pow(tib_epicondyle_axis_kk.at(1), 2) + pow(tib_epicondyle_axis_kk.at(2), 2) );
    tib_epicondyle_axis_kk.at(0) = tib_epicondyle_axis_kk.at(0) / b2;
    tib_epicondyle_axis_kk.at(1) = tib_epicondyle_axis_kk.at(1) / b2;
    tib_epicondyle_axis_kk.at(2) = tib_epicondyle_axis_kk.at(2) / b2;

    // angle between projected epicondyle axis and projected malleolus axis
    double param2 = tib_epicondyle_axis_kk.at(0) * malleolus_axis_kk.at(0) + tib_epicondyle_axis_kk.at(1) * malleolus_axis_kk.at(1) + tib_epicondyle_axis_kk.at(2) * malleolus_axis_kk.at(2);
    torsion = acos(param2) * (360/(2*PI));
}

void Tibia::GuessEthnicGroup()
{
    // set current model
    std::string model = "LogisticModelTibia";

    // load model from config file
    std::ifstream file(configPath);
    std::string value;
    std::string row;
    bool found = false;
    std::vector<float> coefficients;
    size_t pos = 0;
    std::string delimiter = ",";

    while (getline(file, row)) {
        found = false;

        while ((pos = row.find(delimiter)) != std::string::npos) {
                value = row.substr(0, pos);

                row.erase(0, pos + delimiter.length());

                if (value.compare(model) == 0)
                    found = true;
                else if (found)
                    coefficients.push_back(std::stof(value.c_str()));
        }
        
        if (found) {
            value = row.substr(pos+1, row.length());
            //std::cout << "value: " << value << std::endl;
            coefficients.push_back(std::stof(value.c_str()));
        }
        
    }

    file.close();

    int gender = 0;
    if (sex == "FEMALE")
        gender = 0;
    else if (sex == "MALE")
        gender = 1;

    float logits = 
        (coefficients.at(0) * bone_length) +
        (coefficients.at(1) * medial_offset) + 
        (coefficients.at(2) * lateral_offset) +
        (coefficients.at(3) * ML_width) +
        (coefficients.at(4) * AP_width) +
        (coefficients.at(5) * torsion) +
        (coefficients.at(6) * gender);
		
    caucasian = (int)((1 / (1 + exp(-logits))) * 100);
    asian = 100 - caucasian;
}

Tibia::~Tibia() {
}
