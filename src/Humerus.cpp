#include "Humerus.h"

Humerus::Humerus(const string anatomicalMeshPath,
        const string anatomicalLandmarksPath)
{

    // anatomical landmarks
    SetAnatomicalLandmarks(anatomicalLandmarksPath);

    // anatomical mesh
    SetAnatomicalMesh(anatomicalMeshPath);

    // reset antomical parameters
    ResetMeasurements();

    // meta information
    SetMetaInfo(anatomicalMeshPath);
}

void Humerus::ResetMeasurements()
{
    bone_length = medial_offset = lateral_offset = ML_width = AP_width = head_fit_x = head_fit_y = head_fit_z = head_radius = inclination = retroversion = 0;

    // initialize corresponding (technical) landmark coordinates and size of sphere for visualizing
    medial_epicondyle[0] = medial_epicondyle[1] = medial_epicondyle[2] = medial_epicondyle[3] = 0;
    lateral_epicondyle[0] = lateral_epicondyle[1] = lateral_epicondyle[2] = lateral_epicondyle[3] = 0;
    minor_tuberculum[0] = minor_tuberculum[1] = minor_tuberculum[2] = minor_tuberculum[3] = 0;
    major_tuberculum[0] = major_tuberculum[1] = major_tuberculum[2] = major_tuberculum[3] = 0;
    superior_fossa_olecrani[0] = superior_fossa_olecrani[1] = superior_fossa_olecrani[2] = superior_fossa_olecrani[3] = 0;
    most_distal_point[0] = most_distal_point[1] = most_distal_point[2] = most_distal_point[3] = 0;
    most_proximal_point[0] = most_proximal_point[1] = most_proximal_point[2] = most_proximal_point[3] = 0;
    most_anterior_neck_point[0] = most_anterior_neck_point[1] = most_anterior_neck_point[2] = most_anterior_neck_point[3] = 0;
    most_medial_neck_point[0] = most_medial_neck_point[1] = most_medial_neck_point[2] = most_medial_neck_point[3] = 0;
    most_posterior_neck_point[0] = most_posterior_neck_point[1] = most_posterior_neck_point[2] = most_posterior_neck_point[3] = 0;
    head_fit_point_1[0] = head_fit_point_1[1] = head_fit_point_1[2] = head_fit_point_1[3] = 0;
    head_fit_point_2[0] = head_fit_point_2[1] = head_fit_point_2[2] = head_fit_point_2[3] = 0;
    head_fit_point_3[0] = head_fit_point_3[1] = head_fit_point_3[2] = head_fit_point_3[3] = 0;
    head_fit_point_4[0] = head_fit_point_4[1] = head_fit_point_4[2] = head_fit_point_4[3] = 0;
    head_fit_point_5[0] = head_fit_point_5[1] = head_fit_point_5[2] = head_fit_point_5[3] = 0;
    head_fit_point_6[0] = head_fit_point_6[1] = head_fit_point_6[2] = head_fit_point_6[3] = 0;
    head_fit_point_7[0] = head_fit_point_7[1] = head_fit_point_7[2] = head_fit_point_7[3] = 0;
    head_fit_point_8[0] = head_fit_point_8[1] = head_fit_point_8[2] = head_fit_point_8[3] = 0;

    MapAnatomicalLandmarksToAnatomicalMesh();
}

void Humerus::MapAnatomicalLandmarksToAnatomicalMesh()
{
    getClosestPointFromMesh(anatomicalLandmarks.at(0), medial_epicondyle, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(1), lateral_epicondyle, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(2), minor_tuberculum, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(3), major_tuberculum, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(4), superior_fossa_olecrani, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(5), medial_fossa_olecrani , anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(6), lateral_fossa_olecrani , anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(7), inferior_fossa_olecrani , anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(8), most_distal_point, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(9), most_proximal_point, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(10), most_anterior_neck_point, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(11), most_medial_neck_point, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(12), most_posterior_neck_point, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(13), head_fit_point_1, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(14), head_fit_point_2, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(15), head_fit_point_3, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(16), head_fit_point_4, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(17), head_fit_point_5, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(18), head_fit_point_6, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(19), head_fit_point_7, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(20), head_fit_point_8, anatomicalMesh);
}

void Humerus::Thesis()
{
    //cout << "####################" << endl;
    //cout << "# Thesis - Humerus #" << endl;
    //cout << "####################" << endl;

    SetProximalShaftCenter();
    
    SetDistalShaftCenter();
    
    SetMedialAndLateralAxis();
    
    SetCoordinateSystem();
    
    SetOffsetAndWidth();

    BoneLength();

    MedialOffset();

    LateralOffset();

    MLWidth();
    
    APWidth();

    HumerusHeadCenter();

    HumerusInclinationAndRetroversion();

    GuessEthnicGroup();

    cout << "\n"
        << "calculated parameters:" << "\n" << "\n"
        << "bone length" << "\t" << bone_length << "mm\n"
        << "med. offset" << "\t" << medial_offset << "mm\n"
        << "lat. offset" << "\t" << lateral_offset << "mm\n"
        << "ml with" << "\t" << ML_width << "mm\n"
        << "ap width" << "\t" << AP_width << "mm\n"
        << "head radius" << "\t" << head_radius << "mm\n"
        << "inclination" << "\t" << inclination << "mm\n"
        << "retroversion" << "\t" << retroversion << "mm\n"
        << "asians" << "\t" << asian << "%\n"
        << "caucasian" << "\t" << caucasian << "%\n\n";

}

void Humerus::SetProximalShaftCenter()
{
    // ### center-point: 80% of length (proximal) ###
    double center[3];
    center[0] = most_distal_point[0] + ((most_proximal_point[0]-most_distal_point[0]) * 0.8);
    center[1] = most_distal_point[1] + ((most_proximal_point[1]-most_distal_point[1]) * 0.8);
    center[2] = most_distal_point[2] + ((most_proximal_point[2]-most_distal_point[2]) * 0.8);

    // normal, defined with 
    double normal[3]; double bn;
    bn = sqrt( pow(most_proximal_point[0]-most_distal_point[0], 2) + pow(most_proximal_point[1]-most_distal_point[1], 2) + pow(most_proximal_point[2]-most_distal_point[2], 2) );
    normal[0] = (most_proximal_point[0]-most_distal_point[0]) / bn;
    normal[1] = (most_proximal_point[1]-most_distal_point[1]) / bn;
    normal[2] = (most_proximal_point[2]-most_distal_point[2]) / bn;

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
    cutStrips_prox->SetInputConnection(cutEdges_prox->GetOutputPort());
    cutStrips_prox->Update();
    vtkSmartPointer<vtkPolyData> cutPoly_prox = vtkSmartPointer<vtkPolyData>::New();
    cutPoly_prox->SetPoints(cutStrips_prox->GetOutput()->GetPoints());
    cutPoly_prox->SetPolys(cutStrips_prox->GetOutput()->GetLines());

    // crash's may occure if no suitable were done - so return then
    if (cutPoly_prox->GetNumberOfPoints() == 0)
    {
        cout << "error cutting proximal part of shaft!" << endl;
        return;
    }

    // get the cutting-contours center
    cutPoly_prox->GetCenter(proximal_shaft_center);
}

void Humerus::SetDistalShaftCenter()
{
    double center[3]; 
    double normal[3];
    double bn;
    
    // ### center-point: 20% of length ###
    center[0] = most_distal_point[0] + ((most_proximal_point[0]-most_distal_point[0]) * 0.2);
    center[1] = most_distal_point[1] + ((most_proximal_point[1]-most_distal_point[1]) * 0.2);
    center[2] = most_distal_point[2] + ((most_proximal_point[2]-most_distal_point[2]) * 0.2);

    bn = sqrt( pow(most_distal_point[0]-most_proximal_point[0], 2) + pow(most_distal_point[1]-most_proximal_point[1], 2) + pow(most_distal_point[2]-most_proximal_point[2], 2) );
    normal[0] = (most_distal_point[0]-most_proximal_point[0]) / bn;
    normal[1] = (most_distal_point[1]-most_proximal_point[1]) / bn;
    normal[2] = (most_distal_point[2]-most_proximal_point[2]) / bn;

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

    // crash's may occure if no suitable were done - so return then
    if (cutPoly_dist->GetNumberOfPoints() == 0)
    {
        cout << "error cutting distal part of shaft!" << endl;
        return;
    }

    // get the cutting-contours center
    cutPoly_dist->GetCenter(distal_shaft_center);
}

void Humerus::SetOffsetAndWidth()
{
    double center[3]; 
    double normal[3];
    double bn;
    
    // ### center-point: 20% of length ###
    center[0] = most_distal_point[0] + ((most_proximal_point[0]-most_distal_point[0]) * 0.2);
    center[1] = most_distal_point[1] + ((most_proximal_point[1]-most_distal_point[1]) * 0.2);
    center[2] = most_distal_point[2] + ((most_proximal_point[2]-most_distal_point[2]) * 0.2);

    bn = sqrt( pow(most_distal_point[0]-most_proximal_point[0], 2) + pow(most_distal_point[1]-most_proximal_point[1], 2) + pow(most_distal_point[2]-most_proximal_point[2], 2) );
    normal[0] = (most_distal_point[0]-most_proximal_point[0]) / bn;
    normal[1] = (most_distal_point[1]-most_proximal_point[1]) / bn;
    normal[2] = (most_distal_point[2]-most_proximal_point[2]) / bn;

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

    // crash's may occure if no suitable were done - so return then
    if (cutPoly_dist->GetNumberOfPoints() == 0)
    {
        cout << "error cutting distal part of shaft!" << endl;
        return;
    }

    // get the cutting-contours center
    cutPoly_dist->GetCenter(distal_shaft_center);

    double plane[9];
    int max = 0;
    int maxi = 0;
    double tmp3[3];

    // look for most medial point
    for (int i=0; i < cutPoly_dist->GetNumberOfPoints(); ++i)
    {
        cutPoly_dist->GetPoint(i, tmp3);

        // plane: n, x, p
        plane[0] = axis[3]; plane[1] = axis[4]; plane[2] = axis[5];
        plane[3] = tmp3[0]; plane[4] = tmp3[1]; plane[5] = tmp3[2];
        plane[6] = distal_shaft_center[0]; plane[7] = distal_shaft_center[1]; plane[8] = distal_shaft_center[2];

        if (distanceToPlane(plane) > max)
        {
            max = distanceToPlane(plane);
            maxi = i;
        }

    }

    cutPoly_dist->GetPoint(maxi, most_medial_shaft_point);

    // most lateral point
    max = 0;
    maxi = 0;
    
    for (int i = 0; i < cutPoly_dist->GetNumberOfPoints(); ++i)
    {
        cutPoly_dist->GetPoint(i, tmp3);

        // define plane with mediolateral axis as normal * (-1)
        plane[0] = -1 * axis[3]; plane[1] = -1 * axis[4]; plane[2] = -1 * axis[5];
        plane[3] = tmp3[0]; plane[4] = tmp3[1]; plane[5] = tmp3[2];
        plane[6] = distal_shaft_center[0]; plane[7] = distal_shaft_center[1]; plane[8] = distal_shaft_center[2];

        if (distanceToPlane(plane) > max)
        {
                max = distanceToPlane(plane);
                maxi = i;
        }

    }
    
    cutPoly_dist->GetPoint(maxi, most_lateral_shaft_point);

    // most posterior point
    max = 0; maxi = 0;
    for (int i = 0; i < cutPoly_dist->GetNumberOfPoints(); ++i)
    {
        cutPoly_dist->GetPoint(i, tmp3);

        plane[0] = axis[0]; plane[1] = axis[1]; plane[2] = axis[2];
        plane[3] = tmp3[0]; plane[4] = tmp3[1]; plane[5] = tmp3[2];
        plane[6] = distal_shaft_center[0]; plane[7] = distal_shaft_center[1]; plane[8] = distal_shaft_center[2];

        if (distanceToPlane(plane) > max)
        {
            max = distanceToPlane(plane);
            maxi = i;
        }

    }

    cutPoly_dist->GetPoint(maxi, most_posterior_shaft_point);

    // most anterior point
    max = 0;
    maxi = 0;
    for (int i = 0; i < cutPoly_dist->GetNumberOfPoints(); ++i)
    {
        cutPoly_dist->GetPoint(i, tmp3);

        // define plane with ventral axis
        plane[0] = -1 * axis[0]; plane[1] = -1 * axis[1]; plane[2] = -1 * axis[2];
        plane[3] = tmp3[0]; plane[4] = tmp3[1]; plane[5] = tmp3[2];
        plane[6] = distal_shaft_center[0]; plane[7] = distal_shaft_center[1]; plane[8] = distal_shaft_center[2];

        if (distanceToPlane(plane) > max)
        {
            max = distanceToPlane(plane);
            maxi = i;
        }

    }

    cutPoly_dist->GetPoint(maxi, most_anterior_shaft_point);    
}

void Humerus::BoneLength()
{
    // bone length:
    bone_length = sqrt(pow(most_proximal_point[0]-most_distal_point[0], 2) + pow(most_proximal_point[1]-most_distal_point[1], 2) + pow(most_proximal_point[2]-most_distal_point[2], 2));
}

void Humerus::MedialOffset()
{
    // medial offset:
    double plane[9];
    
    plane[0] = axis[3]; plane[1] = axis[4]; plane[2] = axis[5];
    plane[3] = medial_epicondyle[0]; plane[4] = medial_epicondyle[1]; plane[5] = medial_epicondyle[2];
    plane[6] = most_medial_shaft_point[0]; plane[7] = most_medial_shaft_point[1]; plane[8] = most_medial_shaft_point[2];
    medial_offset = distanceToPlane(plane);
}
    
void Humerus::LateralOffset()
{
    // lateral offset:
    double plane[9];

    plane[0] = -axis[3]; plane[1] = -axis[4]; plane[2] = -axis[5];
    plane[3] = lateral_epicondyle[0]; plane[4] = lateral_epicondyle[1]; plane[5] = lateral_epicondyle[2];
    plane[6] = most_lateral_shaft_point[0]; plane[7] = most_lateral_shaft_point[1]; plane[8] = most_lateral_shaft_point[2];
    lateral_offset = distanceToPlane(plane);
}
    
void Humerus::MLWidth()
{
    // ml width:
    double plane[9];

    plane[0] = axis[3]; plane[1] = axis[4]; plane[2] = axis[5];
    plane[3] = most_medial_shaft_point[0]; plane[4] = most_medial_shaft_point[1]; plane[5] = most_medial_shaft_point[2];
    plane[6] = most_lateral_shaft_point[0]; plane[7] = most_lateral_shaft_point[1]; plane[8] = most_lateral_shaft_point[2];
    ML_width = distanceToPlane(plane);
}
    
void Humerus::APWidth()
{
    // ap width:
    double plane[9];

    plane[0] = axis[0]; plane[1] = axis[1]; plane[2] = axis[2];
    plane[3] = most_posterior_shaft_point[0]; plane[4] = most_posterior_shaft_point[1]; plane[5] = most_posterior_shaft_point[2];
    plane[6] = most_anterior_shaft_point[0]; plane[7] = most_anterior_shaft_point[1]; plane[8] = most_anterior_shaft_point[2];
    AP_width = distanceToPlane(plane);
}

void Humerus::HumerusHeadCenter()
{
    double Cx = 0;
    double Cy = 0;
    double Cz = 0;
    double head_circle[8][3];

    // define points for head sphere-fit
    head_circle[0][0] = head_fit_point_1[0];
    head_circle[0][1] = head_fit_point_1[1];
    head_circle[0][2] = head_fit_point_1[2];

    head_circle[1][0] = head_fit_point_2[0];
    head_circle[1][1] = head_fit_point_2[1];
    head_circle[1][2] = head_fit_point_2[2];

    head_circle[2][0] = head_fit_point_3[0];
    head_circle[2][1] = head_fit_point_3[1];
    head_circle[2][2] = head_fit_point_3[2];

    head_circle[3][0] = head_fit_point_4[0];
    head_circle[3][1] = head_fit_point_4[1];
    head_circle[3][2] = head_fit_point_4[2];

    head_circle[4][0] = head_fit_point_5[0];
    head_circle[4][1] = head_fit_point_5[1];
    head_circle[4][2] = head_fit_point_5[2];

    head_circle[5][0] = head_fit_point_6[0];
    head_circle[5][1] = head_fit_point_6[1];
    head_circle[5][2] = head_fit_point_6[2];

    head_circle[6][0] = head_fit_point_7[0];
    head_circle[6][1] = head_fit_point_7[1];
    head_circle[6][2] = head_fit_point_7[2];

    head_circle[7][0] = head_fit_point_8[0];
    head_circle[7][1] = head_fit_point_8[1];
    head_circle[7][2] = head_fit_point_8[2];

    // fit of humeral head
    rms0 = 99999; 
    a0 = 0;
    b0 = 0;
    c0 = 0;
    r0 = 0;
    Cx = 0;
    Cy = 0;
    Cz = 0;

    for (int i = 0; i < 8; ++i)
    {
        Cx = Cx + head_circle[i][0];
        Cy = Cy + head_circle[i][1];
        Cz = Cz + head_circle[i][2];
    }

    SphereFit(head_circle, 8, Cx/8, Cy/8, Cz/8);

    head_fit_x = a0;
    head_fit_y = b0;
    head_fit_z = c0;
    head_radius = r0;

    rms0 = 99999; 
    a0 = 0;
    b0 = 0;
    c0 = 0;
    r0 = 0;
    Cx = 0;
    Cy = 0;
    Cz = 0;
}

void Humerus::HumerusInclinationAndRetroversion()
{
    // vector pointing posterior
    vector<double> v1(3);
    v1.at(0) = most_posterior_neck_point[0] - most_medial_neck_point[0];
    v1.at(1) = most_posterior_neck_point[1] - most_medial_neck_point[1];
    v1.at(2) = most_posterior_neck_point[2] - most_medial_neck_point[2];

    // norm
    double b1 = sqrt(pow(v1.at(0), 2) + pow(v1.at(1), 2) + pow(v1.at(2), 2));
    v1.at(0) = v1.at(0) / b1;
    v1.at(1) = v1.at(1) / b1;
    v1.at(2) = v1.at(2) / b1;

    // vector pointing anterior
    vector<double> v2(3);
    v2.at(0) = most_anterior_neck_point[0] - most_medial_neck_point[0];
    v2.at(1) = most_anterior_neck_point[1] - most_medial_neck_point[1];
    v2.at(2) = most_anterior_neck_point[2] - most_medial_neck_point[2];

    // norm
    double b2 = sqrt(pow(v2.at(0), 2) + pow(v2.at(1), 2) + pow(v2.at(2), 2));
    v2.at(0) = v2.at(0) / b2;
    v2.at(1) = v2.at(1) / b2;
    v2.at(2) = v2.at(2) / b2;

    // neck axis is cross product
    vector<double> neck_axis(3);

    // correct orientation for neck axis depends on side
    if (side.compare("RIGHT") == 0)
        neck_axis = CrossProduct(v1, v2);
    else if (side.compare("LEFT") == 0)
        neck_axis = CrossProduct(v2, v1);

    // coronal projected neck axis
    vector<double> neck_axis_ap(3);

    // distance to coronal plane
    double lambda1 = (axis[0] * neck_axis.at(0)) + (axis[1] * neck_axis.at(1)) + (axis[2] * neck_axis.at(2));

    // intersection with coronal plane
    neck_axis_ap.at(0) = neck_axis.at(0) + lambda1 * axis[0];
    neck_axis_ap.at(1) = neck_axis.at(1) + lambda1 * axis[1];
    neck_axis_ap.at(2) = neck_axis.at(2) + lambda1 * axis[2];

    // norm
    b1 = sqrt(pow(neck_axis_ap.at(0), 2) + pow(neck_axis_ap.at(1), 2) + pow(neck_axis_ap.at(2), 2));
    neck_axis_ap.at(0) = neck_axis_ap.at(0) / b1;
    neck_axis_ap.at(1) = neck_axis_ap.at(1) / b1;
    neck_axis_ap.at(2) = neck_axis_ap.at(2) / b1;

    //cout << "Neck-Axis-AP: " << "\t" << neck_axis_ap.at(0) << "\t" << neck_axis_ap.at(1) << "\t" << neck_axis_ap.at(2) << endl;

    // inclination is angle between invertec cranio-caudal axis and coronal projected neck axis
    double param1 = neck_axis_ap.at(0) * (-axis[6]) + neck_axis_ap.at(1) * (-axis[7]) + neck_axis_ap.at(2) * (-axis[8]);
    inclination = acos(param1) * (360 / (2 * PI));

    // axial projected neck axis
    vector<double> neck_axis_kk(3);

    // distance to axial plane
    lambda1 = (axis[6]) * neck_axis.at(0) + (axis[7]) * neck_axis.at(1) + (axis[8]) * neck_axis.at(2);

    // intersection with axial plane
    neck_axis_kk.at(0) = neck_axis.at(0) - lambda1 * (axis[6]);
    neck_axis_kk.at(1) = neck_axis.at(1) - lambda1 * (axis[7]);
    neck_axis_kk.at(2) = neck_axis.at(2) - lambda1 * (axis[8]);

    // norm
    b1 = sqrt(pow(neck_axis_kk.at(0), 2) + pow(neck_axis_kk.at(1), 2) + pow(neck_axis_kk.at(2), 2));
    neck_axis_kk.at(0) = neck_axis_kk.at(0) / b1;
    neck_axis_kk.at(1) = neck_axis_kk.at(1) / b1;
    neck_axis_kk.at(2) = neck_axis_kk.at(2) / b1;

    //cout << "neck_axis: " << "\t" << neck_axis.at(0) << "\t" << neck_axis.at(1) << "\t" << neck_axis.at(2) << endl;
    //cout << "neck_axis_kk: " << "\t" << neck_axis_kk.at(0) << "\t" << neck_axis_kk.at(1) << "\t" << neck_axis_kk.at(2) << endl;

    // epicondyle axis
    epicondyle_axis[0] = medial_epicondyle[0] - lateral_epicondyle[0];
    epicondyle_axis[1] = medial_epicondyle[1] - lateral_epicondyle[1];
    epicondyle_axis[2] = medial_epicondyle[2] - lateral_epicondyle[2];

    // norm
    double b = sqrt(pow(epicondyle_axis[0], 2) + pow(epicondyle_axis[1], 2) + pow(epicondyle_axis[2], 2));
    epicondyle_axis[0] = epicondyle_axis[0] / b;
    epicondyle_axis[1] = epicondyle_axis[1] / b;
    epicondyle_axis[2] = epicondyle_axis[2] / b;

    // axial projected epicondyle axis
    vector<double> epicondyle_axis_kk(3);

    // distance
    double lambda2 = (axis[6]) * epicondyle_axis[0] + (axis[7]) * epicondyle_axis[1] + (axis[8]) * epicondyle_axis[2];

    // intersection
    if (lambda2 < 0) {
        // behind plane
        epicondyle_axis_kk.at(0) = epicondyle_axis[0] + lambda2 * (axis[6]);
        epicondyle_axis_kk.at(1) = epicondyle_axis[1] + lambda2 * (axis[7]);
        epicondyle_axis_kk.at(2) = epicondyle_axis[2] + lambda2 * (axis[8]);
    } else {
        epicondyle_axis_kk.at(0) = epicondyle_axis[0] - lambda2 * (axis[6]);
        epicondyle_axis_kk.at(1) = epicondyle_axis[1] - lambda2 * (axis[7]);
        epicondyle_axis_kk.at(2) = epicondyle_axis[2] - lambda2 * (axis[8]);
    }

    // norm
    b2 = sqrt(pow(epicondyle_axis_kk.at(0), 2) + pow(epicondyle_axis_kk.at(1), 2) + pow(epicondyle_axis_kk.at(2), 2));
    epicondyle_axis_kk.at(0) = epicondyle_axis_kk.at(0) / b2;
    epicondyle_axis_kk.at(1) = epicondyle_axis_kk.at(1) / b2;
    epicondyle_axis_kk.at(2) = epicondyle_axis_kk.at(2) / b2;

    //cout << "epicondyle_axis: " << "\t" << epicondyle_axis[0] << "\t" << epicondyle_axis[1] << "\t" << epicondyle_axis[2] << endl;
    //cout << "epicondyle_axis_kk: " << "\t" << epicondyle_axis_kk.at(0) << "\t" << epicondyle_axis_kk.at(1) << "\t" << epicondyle_axis_kk.at(2) << endl;

    // retroversion is angle between axial projected epicondyle and axial projected neck axis
    double param2 = epicondyle_axis_kk.at(0) * neck_axis_kk.at(0) + epicondyle_axis_kk.at(1) * neck_axis_kk.at(1) + epicondyle_axis_kk.at(2) * neck_axis_kk.at(2);
    retroversion = acos(param2) * (360 / (2 * PI));
}

void Humerus::SetMedialAndLateralAxis()
{
    // define temporarily medio-lateral ...
    axis[0] = medial_epicondyle[0] - lateral_epicondyle[0];
    axis[1] = medial_epicondyle[1] - lateral_epicondyle[1];
    axis[2] = medial_epicondyle[2] - lateral_epicondyle[2];
    
    // ... and cranio-caudal axis
    axis[3] = proximal_shaft_center[0] - distal_shaft_center[0];
    axis[4] = proximal_shaft_center[1] - distal_shaft_center[1];
    axis[5] = proximal_shaft_center[2] - distal_shaft_center[2];
}

void Humerus::GuessEthnicGroup()
{
    // set logistic model
    string model = "LogisticModelHumerus";

    // load model from config file
    ifstream file("bonedoc.conf");
    string value;
    string row;
    bool found = false;
    vector<float> coefficients;
    size_t pos = 0;
    string delimiter = ",";

    while (getline(file, row)) {
        found = false;

        while ((pos = row.find(delimiter)) != string::npos) {
            value = row.substr(0, pos);

            row.erase(0, pos + delimiter.length());

            if (value.compare(model) == 0)
                    found = true;
            else if (found)
                    coefficients.push_back(stof(value.c_str()));
        }
        
        if (found) {
            value = row.substr(pos+1, row.length());
            coefficients.push_back(stof(value.c_str()));
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
        (coefficients.at(5) * head_radius) +
        (coefficients.at(6) * inclination) +
        (coefficients.at(7) * retroversion) +
        (coefficients.at(8) * gender);

    caucasian = (int)((1 / (1 + exp(-logits))) * 100);
    asian = 100 - caucasian;
}

Humerus::~Humerus() {
}
