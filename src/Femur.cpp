#include "Femur.h"

Femur::Femur(const string anatomicalMeshPath,
        const string anatomicalLandmarksPath,
        const string configPath)
{
    this->configPath = configPath;

    // read number of anatomical landmarks (todo: should be used for error handling)
    SetAnatomicalLandmarksSize(configPath, "femur-anatomical-landmarks-size");

    // load anatomical landmarks
    SetAnatomicalLandmarks(anatomicalLandmarksPath);

    // load anatomical mesh
    SetAnatomicalMesh(anatomicalMeshPath);

    // reset antomical parameters
    ResetMeasurements();

    // try to set meta information
    SetMetaInfo(anatomicalMeshPath);
}

void Femur::MapAnatomicalLandmarksToAnatomicalMesh()
{
    // project anatomical landmarks onto anatomical mesh -> technical landmarks
    getClosestPointFromMesh(anatomicalLandmarks.at(0), fovea, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(1), minor_trochanter, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(2), major_trochanter, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(3), linea_intertrochanterica, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(4), intercondylar_notch, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(5), facies_patellaris, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(6), lateral_epicondyle, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(7), medial_epicondyle, anatomicalMesh);
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
    getClosestPointFromMesh(anatomicalLandmarks.at(21), lateral_condyle, anatomicalMesh);
    getClosestPointFromMesh(anatomicalLandmarks.at(22), medial_condyle, anatomicalMesh);
}

void Femur::ResetMeasurements()
{
    // sphere-fit parameters
    rms0 = 99999;
    a0 = b0 = c0 = r0 = distance = 0;

    // anatomical parameters
    bone_length = shaft_length = medial_offset = lateral_offset = ML_width = AP_width = head_radius = inclination = anteversion = 0;
    head[0] = head[1] = head[2] = head[3] = 0;
    center_of_condyles[0] = center_of_condyles[1] = center_of_condyles[2] = 0;
    center_of_condyles[3] = 3;
    distal_shaft_center[0] = distal_shaft_center[1] = distal_shaft_center[2] = 0;
    distal_shaft_center[3] = 3;
    proximal_shaft_center[0] = proximal_shaft_center[1] = proximal_shaft_center[2] = 0;
    proximal_shaft_center[3] = 3;
    neck_isthmus_center[0] = neck_isthmus_center[1] = neck_isthmus_center[2] = 0;
    neck_isthmus_center[3] = 3;
    neck_center[0] = neck_center[1] = neck_center[2] = 0;
    neck_center[3] = 3;
    neck_shaft_interception[0] = neck_shaft_interception[1] = neck_shaft_interception[2] = 0;
    neck_shaft_interception[3] = 1;
    neck_axis[0] = neck_axis[1] = neck_axis[2] = 0;
    bone_length = 0;
    shaft_length = 0;
    medial_offset = 0;
    lateral_offset = 0;
    ML_width = 0;
    AP_width = 0;
    head_radius = 0;
    inclination = 0;
    anteversion = 0;

    // anatomical landmarks size
    anatomicalLandmarksSize = 0;

    // anatomical landmarks
    medial_epicondyle[0] = medial_epicondyle[1] = medial_epicondyle[2] = medial_epicondyle[3] = 0;
    lateral_epicondyle[0] = lateral_epicondyle[1] = lateral_epicondyle[2] = lateral_epicondyle[3] = 0;
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
    medial_condyle[0] = medial_condyle[1] = medial_condyle[2] = medial_condyle[3] = 0;
    lateral_condyle[0] = lateral_condyle[1] = lateral_condyle[2] = lateral_condyle[3] = 0;
    intercondylar_notch[0] = intercondylar_notch[1] = intercondylar_notch[2] = intercondylar_notch[3] = 0;
    fovea[0] = fovea[1] = fovea[2] = fovea[3] = 0;
    minor_trochanter[0] = minor_trochanter[1] = minor_trochanter[2] = minor_trochanter[3] = 0;
    major_trochanter[0] = major_trochanter[1] = major_trochanter[2] = major_trochanter[3] = 0;
    linea_intertrochanterica[0] = linea_intertrochanterica[1] = linea_intertrochanterica[2] = linea_intertrochanterica[3];
    facies_patellaris[0] = facies_patellaris[1] = facies_patellaris[2] = facies_patellaris[3];

    // for each anatomical landmark find the closest point on anatomical mesh
    MapAnatomicalLandmarksToAnatomicalMesh();
}

void Femur::Thesis()
{
    cout << "##################" << endl;
    cout << "# Thesis - Femur #" << endl;
    cout << "##################" << endl;

    // optimize manually found anatomical landmarks 'most_distal_point' and 'most_proximal_point'
    OptimizeProximalAndDistalLandmark();

    // intersect shaft at 75% of bone length an set contour's center of mass to 'proximal_shaft_center'
    SetProximalShaftCenter();

    // intersect shaft at 25% of bone length an set contour's center of mass to 'distal_shaft_center'
    SetDistalShaftCenter();

    // axis to define local coordinate system with
    SetMedialAndLateralAxis();
        
    // define local coordinate system
    SetCoordinateSystem();

    // transform each coordinate to new system

    SetOffsetAndWidth();

    FemoralBoneLength1();

    MedialOffset();

    LateralOffset();

    MLWidth();

    APWidth();

    FemoralHeadCenter1();

    FemoralNeckAxis1();

    //FemoralNeckAxisCorrection1();

    //FemoralNeckAndShaftAxisInterception1();

    //FemoralNeckAxis2();

    FemoralAnteversionAndInclination1();

    FemoralCenterOfCondyles1();

    GuessEthnicGroup();

    cout << "bone length: " << bone_length << "mm" << endl;
    cout << "medial offset: " << medial_offset << "mm" << endl;
    cout << "lateral offset: " << lateral_offset << "mm" << endl;
    cout << "ml width: " << ML_width << "mm" << endl;
    cout << "ap width: " << AP_width << "mm" << endl;
    cout << "head radius: " << head_radius << "mm" << endl;
    cout << "inclination: " << inclination << "°" << endl;
    cout << "anteversion: " << anteversion << "°" << endl;
    cout << "asian: " << asian << "%" << endl;
    cout << "caucasian: " << caucasian << "%" << endl;
}

void Femur::PPFX()
{
    // optimize manual found anatomical landmarks
    OptimizeProximalAndDistalLandmark();

    // intersect shaft at 75% of bone length an set contour's center of mass to 'proximal_shaft_center'
    SetProximalShaftCenter();

    // intersect shaft at 25% of bone length an set contour's center of mass to 'distal_shaft_center'
    SetDistalShaftCenter();

    SetMedialAndLateralAxis();

    // to define local coordinate system from
    SetCoordinateSystem();
    
    FemoralBoneLength1();

    FemoralNeckAxis1();

    //FemoralNeckAxisCorrection1();

    //FemoralNeckAndShaftAxisInterception1();

    //FemoralNeckAxis2();

    FemoralAnteversionAndInclination1();

    FemoralCenterOfCondyles1();

    FemoralShaftLength1();

    FemoralTwist1();
}

void Femur::FemoralBoneLength1()
{
    bone_length = sqrt(pow(distanceToPlane(axis[6], axis[7], axis[8], most_proximal_point[0], most_proximal_point[1], most_proximal_point[2],
            most_distal_point[0], most_distal_point[1], most_distal_point[2]), 2));
}

void Femur::OptimizeProximalAndDistalLandmark()
{
    // temporary axis
    double zx = most_proximal_point[0] - most_distal_point[0];
    double zy = most_proximal_point[1] - most_distal_point[1];
    double zz = most_proximal_point[2] - most_distal_point[2];

    // norm
    double b = sqrt(pow(zx, 2) + pow(zy, 2) + pow(zz, 2));
    zx = zx / b;
    zy = zy / b;
    zz = zz / b;

    double max_z = -9999;
    vtkIdType max_z_i = 0;
    double min_z = 9999;
    vtkIdType min_z_i = 0;

    // take center of polydata as plane center
    double center[3];
    anatomicalMesh->GetCenter(center);

    for (vtkIdType i = 0; i < anatomicalMesh->GetNumberOfPoints(); ++i)
    {
        double tmp[3];
        anatomicalMesh->GetPoint(i, tmp);

        double d = distanceToPlane(zx, zy, zz, tmp[0], tmp[1], tmp[2], center[0], center[1], center[2]); 

        if (d > max_z)
        {
            max_z = d;
            max_z_i = i;
        }

        if (d < min_z) 
        {
            min_z = d;
            min_z_i = i;
        }
    }

    // ### most proximal ###
    anatomicalMesh->GetPoint(max_z_i, most_proximal_point);

    // ### most distal ###
    anatomicalMesh->GetPoint(min_z_i, most_distal_point);
}

void Femur::SetProximalShaftCenter()
{
    double n[3] = {most_proximal_point[0] - most_distal_point[0],
        most_proximal_point[1] - most_distal_point[1],
            most_proximal_point[2] - most_distal_point[2]};

    double p[3] = {most_distal_point[0] + ((most_proximal_point[0] - most_distal_point[0]) * 0.75),
        most_distal_point[1] + ((most_proximal_point[1] - most_distal_point[1]) * 0.75),
            most_distal_point[2] + ((most_proximal_point[2] - most_distal_point[2]) * 0.75)};

    // plane
    vtkSmartPointer<vtkPlane> vtkplane = vtkSmartPointer<vtkPlane>::New();
    vtkplane->SetOrigin(p[0], p[1], p[2]);
    vtkplane->SetNormal(n[0], n[1], n[2]);

    // surface cut with plane
    vtkSmartPointer<vtkCutter> cutEdges = vtkSmartPointer<vtkCutter>::New();
    cutEdges->SetInputData(anatomicalMesh);
    cutEdges->SetCutFunction(vtkplane);

    // generates triangle poly-lines from input polygon
    vtkSmartPointer<vtkStripper> cutStrips = vtkSmartPointer<vtkStripper>::New();
    cutStrips->SetInputConnection(cutEdges->GetOutputPort());
    cutStrips->Update();
    vtkSmartPointer<vtkPolyData> cutPoly = vtkSmartPointer<vtkPolyData>::New();
    cutPoly->SetPoints(cutStrips->GetOutput()->GetPoints());
    cutPoly->SetPolys(cutStrips->GetOutput()->GetLines());

    // crash's may occure if no suitable cut will be found - return then
    if (cutPoly->GetNumberOfPoints() == 0)
        cout << "could not define intersection contour!" << endl;
    else
    {
        // get the cutting-contours center
        cutPoly->GetCenter(proximal_shaft_center);
    }
    
}

void Femur::SetDistalShaftCenter()
{
    double center[3];
    double normal[3];
    double bn;

    center[0] = most_distal_point[0] + ((most_proximal_point[0] - most_distal_point[0]) * 0.25);
    center[1] = most_distal_point[1] + ((most_proximal_point[1] - most_distal_point[1]) * 0.25);
    center[2] = most_distal_point[2] + ((most_proximal_point[2] - most_distal_point[2]) * 0.25);

    bn = sqrt( pow(most_distal_point[0] - most_proximal_point[0], 2) + pow(most_distal_point[1] - most_proximal_point[1], 2) + pow(most_distal_point[2] - most_proximal_point[2], 2) );
    normal[0] = (most_distal_point[0] - most_proximal_point[0]) / bn;
    normal[1] = (most_distal_point[1] - most_proximal_point[1]) / bn;
    normal[2] = (most_distal_point[2] - most_proximal_point[2]) / bn;

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
        cout << "Error - could not define distal shaft center!" << endl;
        return;
    }
    
    // get the cutting-contours center
    cutPoly_dist->GetCenter(distal_shaft_center);
}

void Femur::SetMedialAndLateralAxis()
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

void Femur::SetOffsetAndWidth()
{
    double center[3];
    double normal[3];
    double bn;

    center[0] = most_distal_point[0] + ((most_proximal_point[0] - most_distal_point[0]) * 0.25);
    center[1] = most_distal_point[1] + ((most_proximal_point[1] - most_distal_point[1]) * 0.25);
    center[2] = most_distal_point[2] + ((most_proximal_point[2] - most_distal_point[2]) * 0.25);

    bn = sqrt( pow(most_distal_point[0] - most_proximal_point[0], 2) + pow(most_distal_point[1] - most_proximal_point[1], 2) + pow(most_distal_point[2] - most_proximal_point[2], 2) );
    normal[0] = (most_distal_point[0] - most_proximal_point[0]) / bn;
    normal[1] = (most_distal_point[1] - most_proximal_point[1]) / bn;
    normal[2] = (most_distal_point[2] - most_proximal_point[2]) / bn;

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
        cout << "Error - could not define distal shaft center!" << endl;
        return;
    }
    
    // get the cutting-contours center
    cutPoly_dist->GetCenter(distal_shaft_center);

    // ### OFFSET AND WIDTH ###
    double tmp3[3];
    double plane[9];
    double min = 9999; int mini = 0;

    // most lateral shaft point (p19)
    for (int i=0; i<cutPoly_dist->GetNumberOfPoints(); ++i)
    {
        cutPoly_dist->GetPoint(i, tmp3);

        // plane: n, x, p
        plane[0] = axis[3]; plane[1] = axis[4]; plane[2] = axis[5];
        plane[3] = tmp3[0]; plane[4] = tmp3[1]; plane[5] = tmp3[2];
        plane[6] = distal_shaft_center[0]; plane[7] = distal_shaft_center[1]; plane[8] = distal_shaft_center[2];

        if (distanceToPlane(plane) < min)
        {
            min = distanceToPlane(plane);
            mini = i;
        }

    }

    cutPoly_dist->GetPoint(mini, most_lateral_shaft_point);

    // most medial shaft point (p20)
    double max = -9999; int maxi = 0;
    
    for (int i=0; i<cutPoly_dist->GetNumberOfPoints(); ++i)
    {
        cutPoly_dist->GetPoint(i, tmp3);

        // define plane with mediolateral axis as normal * (-1)
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

    // most posterior shaft point (p21) 
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

    // most anterior shaft point (p22))
    max = 0; maxi = 0;
    
    for (int i = 0; i < cutPoly_dist->GetNumberOfPoints(); ++i)
    {
        cutPoly_dist->GetPoint(i, tmp3);

        // define plane with mediolateral axis as normal * (-1)
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


void Femur::FemoralHeadCenter1()
{
    double sphere[8][3];
    sphere[0][0] = head_fit_point_1[0]; sphere[0][1] = head_fit_point_1[1]; sphere[0][2] = head_fit_point_1[2];
    sphere[1][0] = head_fit_point_2[0]; sphere[1][1] = head_fit_point_2[1]; sphere[1][2] = head_fit_point_2[2];
    sphere[2][0] = head_fit_point_3[0]; sphere[2][1] = head_fit_point_3[1]; sphere[2][2] = head_fit_point_3[2];
    sphere[3][0] = head_fit_point_4[0]; sphere[3][1] = head_fit_point_4[1]; sphere[3][2] = head_fit_point_4[2];
    sphere[4][0] = head_fit_point_5[0]; sphere[4][1] = head_fit_point_5[1]; sphere[4][2] = head_fit_point_5[2];
    sphere[5][0] = head_fit_point_6[0]; sphere[5][1] = head_fit_point_6[1]; sphere[5][2] = head_fit_point_6[2];
    sphere[6][0] = head_fit_point_7[0]; sphere[6][1] = head_fit_point_7[1]; sphere[6][2] = head_fit_point_7[2];
    sphere[7][0] = head_fit_point_8[0]; sphere[7][1] = head_fit_point_8[1]; sphere[7][2] = head_fit_point_8[2];

    double Cx = 0;
    double Cy = 0;
    double Cz = 0;
    double tmp[4];
    tmp[3] = 1;

    for (int i = 0; i < 8; ++i)
    {
        Cx = Cx + sphere[i][0];
        Cy = Cy + sphere[i][1];
        Cz = Cz + sphere[i][2];
    }

    SphereFit(sphere, 8, Cx/8, Cy/8, Cz/8);

    head[0] = a0;
    head[1] = b0;
    head[2] = c0;
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

void Femur::FemoralNeckAxis1()
{

    if ((head[0] == 0) && (head[1] == 0) && (head[2] == 0))
    {
        cout << "head-center not defined!" << endl;
        return;
    }

    // aus den 3 am Hals gesetzten Punkten (p5, p6, p7) wird die Halsebene definiert
    double v1[3];
    v1[0] = most_anterior_neck_point[0] - most_medial_neck_point[0];
    v1[1] = most_anterior_neck_point[1] - most_medial_neck_point[1];
    v1[2] = most_anterior_neck_point[2] - most_medial_neck_point[2];

    double b1 = sqrt(pow(v1[0], 2) + pow(v1[1], 2) + pow(v1[2], 2));

    v1[0] = v1[0] / b1;
    v1[1] = v1[1] / b1;
    v1[2] = v1[2] / b1;

    // vektor2 von medial p30 nach anterior p29, also anterior-medial
    double v2[3];
    v2[0] = most_posterior_neck_point[0] - most_medial_neck_point[0];
    v2[1] = most_posterior_neck_point[1] - most_medial_neck_point[1];
    v2[2] = most_posterior_neck_point[2] - most_medial_neck_point[2];

    double b2 = sqrt(pow(v2[0], 2) + pow(v2[1], 2) + pow(v2[2], 2));

    v2[0] = v2[0] / b2;
    v2[1] = v2[1] / b2;
    v2[2] = v2[2] / b2;

    // neck-axis
    neck_axis[0] = v1[1]*v2[2]-v1[2]*v2[1];
    neck_axis[1] = v1[2]*v2[0]-v1[0]*v2[2];
    neck_axis[2] = v1[0]*v2[1]-v1[1]*v2[0];


    double cut_center[3];
    getCenterOfIntersectionContour(anatomicalMesh, neck_axis[0], neck_axis[1], neck_axis[2],
            (most_anterior_neck_point[0] + most_medial_neck_point[0] + most_posterior_neck_point[0]) / 3,
                    (most_anterior_neck_point[1] + most_medial_neck_point[1] + most_posterior_neck_point[1]) / 3,
                            (most_anterior_neck_point[2] + most_medial_neck_point[2] + most_posterior_neck_point[2]) / 3, cut_center);


    // visualize technical landmark
    neck_isthmus_center[0] = cut_center[0];
    neck_isthmus_center[1] = cut_center[1];
    neck_isthmus_center[2] = cut_center[2];
    neck_isthmus_center[3] = 3;

    // neck axis = neck-isthmus center towards head center
    neck_axis[0] = head[0] - cut_center[0];
    neck_axis[1] = head[1] - cut_center[1];
    neck_axis[2] = head[2] - cut_center[2];

    double b3 = sqrt(pow(neck_axis[0], 2) + pow(neck_axis[1], 2) + pow(neck_axis[2], 2));

    neck_axis[0] = neck_axis[0] / b3;
    neck_axis[1] = neck_axis[1] / b3;
    neck_axis[2] = neck_axis[2] / b3;

}

void Femur::FemoralNeckAxisCorrection1()
{
    if ((neck_isthmus_center[0] == 0) && (neck_isthmus_center[1] == 0) && (neck_isthmus_center[2] == 0))
    {
        cout << "neck-isthmus-center not defined!" << endl;
        return;
    }
    
    if ((head[0] == 0) && (head[1] == 0) && (head[2] == 0))
    {
        cout << "head-center not defined!" << endl;
        return;
    }

    // neck-length
    double neck_length = getDistance(neck_isthmus_center, head);

    // normed axis
    double neck_axis[3];
    neck_axis[0] = (head[0] - neck_isthmus_center[0]) / neck_length;
    neck_axis[1] = (head[1] - neck_isthmus_center[1]) / neck_length;
    neck_axis[2] = (head[2] - neck_isthmus_center[2]) / neck_length;

    // position vector on intersection plane
    double p[3];

    // lambda
    double lambda = 0;

    // centers of neck
    vector<vector<double>> centers;

    // set up sizes +1 for the head
    centers.resize(neck_intersection_size+1);
    
    for (int i = 0; i < neck_intersection_size+1; ++i)
        centers[i].resize(3);

    // loop along tempory neck-axis starting from neck-isthmus
    for (int i = 0; i < neck_intersection_size; ++i)
    {
        lambda = (i * (neck_length / (neck_intersection_size-1)));

        p[0] = neck_isthmus_center[0] + (lambda * neck_axis[0]);
        p[1] = neck_isthmus_center[1] + (lambda * neck_axis[1]);
        p[2] = neck_isthmus_center[2] + (lambda * neck_axis[2]);

        double center[4];
        getCenterOfIntersectionContour(anatomicalMesh, neck_axis, p, center);

        centers[i].at(0) = center[0];
        centers[i].at(1) = center[1];
        centers[i].at(2) = center[2];

        // center of mass
        neck_center[0] += center[0];
        neck_center[1] += center[1];
        neck_center[2] += center[2];
    }

    centers[neck_intersection_size].at(0) = head[0];
    centers[neck_intersection_size].at(1) = head[1];
    centers[neck_intersection_size].at(2) = head[2];

    neck_center[0] /= neck_intersection_size;
    neck_center[1] /= neck_intersection_size;
    neck_center[2] /= neck_intersection_size;

    // write result back to 'neck_axis', orientation of neck-axis may vary
    getLineFit(centers, neck_intersection_size, neck_axis);

    // 2 local vectors and center of mass
    double position_vectors[6];
    position_vectors[0] = neck_center[0] + ((neck_length*4) * neck_axis[0]);
    position_vectors[1] = neck_center[1] + ((neck_length*4) * neck_axis[1]);
    position_vectors[2] = neck_center[2] + ((neck_length*4) * neck_axis[2]);
    position_vectors[3] = neck_center[0] - ((neck_length*4) * neck_axis[0]);
    position_vectors[4] = neck_center[1] - ((neck_length*4) * neck_axis[1]);
    position_vectors[5] = neck_center[2] - ((neck_length*4) * neck_axis[2]);

    // check wheter neck axis is orientated correctly
    // if first vector is closer to center of head neck axis points medial
    // else lateral and has then to be inverted
    if (getDistance(position_vectors[0], position_vectors[1], position_vectors[2], head[0], head[1], head[2]) <
            getDistance(position_vectors[3], position_vectors[4], position_vectors[5], head[0], head[1], head[2]))
    {
        neck_axis[0] = position_vectors[0] - position_vectors[3];
        neck_axis[1] = position_vectors[1] - position_vectors[4];
        neck_axis[2] = position_vectors[2] - position_vectors[5];
        // norm
        double b = sqrt(pow(neck_axis[0], 2) + pow(neck_axis[0], 2) + pow(neck_axis[0], 2));
        neck_axis[0] /= b;
        neck_axis[1] /= b;
        neck_axis[2] /= b;
    }
    else
    {
        neck_axis[0] = position_vectors[3] - position_vectors[0];
        neck_axis[1] = position_vectors[4] - position_vectors[1];
        neck_axis[2] = position_vectors[5] - position_vectors[2];
        // norm
        double b = sqrt(pow(neck_axis[0], 2) + pow(neck_axis[0], 2) + pow(neck_axis[0], 2));
        neck_axis[0] /= b;
        neck_axis[1] /= b;
        neck_axis[2] /= b;
    }

}

void Femur::CoordinateTransformation() {

}

void Femur::FemoralNeckAxis2()
{
    // 'neck_shaft_interception' and 'head' had to be defined
    if (((0 == neck_shaft_interception[0]) && (0 == neck_shaft_interception[1]) && (0 == neck_shaft_interception[2])) ||
            ((0 == head[0]) && (0 == head[1]) && (0 == head[2])))
    {
        cout << "Intersection between neck- and shaft axis or femoral head center was not defined before!" << endl;
        return;
    }

    // length 'head' - 'neck_shaft_interception'
    double b = sqrt(pow((head[0] - neck_shaft_interception[0]), 2) + pow((head[1] - neck_shaft_interception[1]), 2) + pow((head[2] - neck_shaft_interception[2]), 2));

    // redefine femoral neck axis between femoral head and intersection between neck- and shaft axis
    neck_axis[0] = (head[0] - neck_shaft_interception[0]) / b;
    neck_axis[1] = (head[1] - neck_shaft_interception[1]) / b;
    neck_axis[2] = (head[2] - neck_shaft_interception[2]) / b;


    std::cout << neck_isthmus_center[0] << " " << neck_isthmus_center[1] << " " << neck_isthmus_center[2] << std::endl;
    std::cout << neck_axis[0] << " " << neck_axis[1] << " " << neck_axis[2] << std::endl;
    std::cout << neck_shaft_interception[0] << " " << neck_shaft_interception[1] << " " << head[2] << std::endl;

}



void Femur::FemoralShaftLength1()
{
    // distance between 'neck_shaft_interception' and 'center_of_condyles' along z-axis
    shaft_length = sqrt(pow(distanceToPlane(axis[6], axis[7], axis[8], neck_shaft_interception[0], neck_shaft_interception[1], neck_shaft_interception[2],
            center_of_condyles[0], center_of_condyles[1], center_of_condyles[2]), 2));
}

void Femur::MedialOffset()
{
    medial_offset = distanceToPlane(axis[3], axis[4], axis[5], medial_epicondyle[0], medial_epicondyle[1], medial_epicondyle[2], most_medial_shaft_point[0], most_medial_shaft_point[1], most_medial_shaft_point[2]);
}

void Femur::LateralOffset()
{
    lateral_offset = distanceToPlane(axis[3], axis[4], axis[5], most_lateral_shaft_point[0], most_lateral_shaft_point[1], most_lateral_shaft_point[2], lateral_epicondyle[0], lateral_epicondyle[1], lateral_epicondyle[2]);
}

void Femur::MLWidth()
{
    ML_width = distanceToPlane(axis[3], axis[4], axis[5], most_medial_shaft_point[0], most_medial_shaft_point[1], most_medial_shaft_point[2], most_lateral_shaft_point[0], most_lateral_shaft_point[1], most_lateral_shaft_point[2]);
}

void Femur::APWidth()
{
    AP_width = distanceToPlane(axis[0], axis[1], axis[2], most_posterior_shaft_point[0], most_posterior_shaft_point[1], most_posterior_shaft_point[2], most_anterior_shaft_point[0], most_anterior_shaft_point[1], most_anterior_shaft_point[2]);
}

void Femur::FemoralAnteversionAndInclination1()
{
    //#######################
    //### (1) inclination ###
    //#######################

    // project n onto yz plane -> n_yz
    double lambda1 = -((axis[0] * neck_axis[0]) + (axis[1] * neck_axis[1]) + (axis[2] * neck_axis[2]));
    double nx_yz = neck_axis[0] + (lambda1 * axis[0]);
    double ny_yz = neck_axis[1] + (lambda1 * axis[1]);
    double nz_yz = neck_axis[2] + (lambda1 * axis[2]);

    // norm
    double b1 = sqrt(pow(nx_yz, 2) + pow(ny_yz, 2) + pow(nz_yz ,2));
    nx_yz /= b1;
    ny_yz /= b1;
    nz_yz /= b1;

    // inclination is angle with cranio-caudal axis: -1 * Z
    double ZxMinus = -1 * axis[6];
    double ZyMinus = -1 * axis[7];
    double ZzMinus = -1 * axis[8];

    // calculate angle
    double alphaR = acos( ((nx_yz * ZxMinus) + (ny_yz * ZyMinus) + (nz_yz * ZzMinus)) / ( sqrt(pow(ZxMinus, 2) + pow(ZyMinus, 2) + pow(ZzMinus, 2)) * (sqrt(pow(nx_yz, 2) + pow(ny_yz, 2) + pow(nz_yz, 2))) ) );
    inclination = alphaR * (180/PI);

    // ####################################
    // ### (2) anteversion/retroversion ###
    // ####################################

    // project n onto xy plane -> n_yz -> n_xy
    double lambda2 = -((axis[6] * neck_axis[0]) + (axis[7] * neck_axis[1]) + (axis[8] * neck_axis[2]));
    double nx_xy = neck_axis[0] + (lambda2 * axis[6]);
    double ny_xy = neck_axis[1] + (lambda2 * axis[7]);
    double nz_xy = neck_axis[2] + (lambda2 * axis[8]);

    // norm
    double b2 = sqrt(pow(nx_xy, 2) + pow(ny_xy, 2) + pow(nz_xy ,2));
    nx_xy /= b2;
    ny_xy /= b2;
    nz_xy /= b2;

    // length of ml-axis
    double b3 = sqrt(pow((medial_condyle[0] - lateral_condyle[0]), 2) + pow((medial_condyle[1] - lateral_condyle[1]), 2) + pow((medial_condyle[2] - lateral_condyle[2]), 2));

    // define and norm ml axis
    double mlx = (medial_condyle[0] - lateral_condyle[0]) / b3;
    double mly = (medial_condyle[1] - lateral_condyle[1]) / b3;
    double mlz = (medial_condyle[2] - lateral_condyle[2]) / b3;

    // project medio-lateral axis onto xy plane -> ml_xy
    double lambda3 = -((axis[6] * mlx) + (axis[7] * mly) + (axis[8] * mlz));
    double mlx_xy = mlx + (lambda3 * axis[6]);
    double mly_xy = mly + (lambda3 * axis[7]);
    double mlz_xy = mlz + (lambda3 * axis[8]);

    // norm
    double b4 = sqrt(pow(mlx_xy, 2) + pow(mly_xy, 2) + pow(mlz_xy, 2));
    mlx_xy /= b4;
    mly_xy /= b4;
    mlz_xy /= b4;

    // angle between projected ml-axis and medial oriented and projected neck axis
    double betaR = acos( ((nx_xy * mlx_xy) + (ny_xy * mly_xy) + (nz_xy * mlz_xy)) / ( sqrt(pow(mlx_xy, 2) + pow(mly_xy, 2) + pow(mlz_xy, 2)) * (sqrt(pow(nx_xy, 2) + pow(ny_xy, 2) + pow(nz_xy, 2))) ) );

    // check for retroversion - if neck-asis lies behind cornonal plane -> retroversion 
    if (((nx_xy * axis[0]) + (ny_xy * axis[1]) + (nz_xy * axis[2])) < 0)
        anteversion = -betaR * (180 / PI);
    else
        anteversion = betaR * (180 / PI);
}

void Femur::FemoralCenterOfCondyles1()
{
    double lambda = distanceToPlane(axis[6], axis[7], axis[8],
            intercondylar_notch[0], intercondylar_notch[1], intercondylar_notch[2],
                    proximal_shaft_center[0], proximal_shaft_center[1], proximal_shaft_center[2]);

    // projected point on plane
    center_of_condyles[0] = proximal_shaft_center[0] + (lambda * axis[6]);
    center_of_condyles[1] = proximal_shaft_center[1] + (lambda * axis[7]);
    center_of_condyles[2] = proximal_shaft_center[2] + (lambda * axis[8]);
}

void Femur::FemoralNeckAndShaftAxisInterception1()
{
    // x-axis 
    vector<double> x(3);
    x.at(0) = axis[0];
    x.at(1) = axis[1];
    x.at(2) = axis[2];

    vector<double> tmp(3);
    tmp.at(0) = neck_axis[0];
    tmp.at(1) = neck_axis[1];
    tmp.at(2) = neck_axis[2];

    vector<double> xXneck = CrossProduct(tmp, x);

    double lambda;

    // S1: interception between plane with normal 'xXneck', center of head and femoral shaft-axis
    // get lambda
    lambda = (neck_center[0] * xXneck.at(0) + neck_center[1] * xXneck.at(1) + neck_center[2] * xXneck.at(2) - proximal_shaft_center[0] * xXneck.at(0) - 
            proximal_shaft_center[1] * xXneck.at(1) - proximal_shaft_center[2] * xXneck.at(2)) / (xXneck.at(0)*axis[6]+xXneck.at(1)*axis[7]+xXneck.at(2)*axis[8]);

    // get interception
    double intercept1[4];
    intercept1[0] = proximal_shaft_center[0] + (lambda * axis[6]);
    intercept1[1] = proximal_shaft_center[1] + (lambda * axis[7]);
    intercept1[2] = proximal_shaft_center[2] + (lambda * axis[8]);
    intercept1[3] = 1;

    // S2: interception between plane with normal of y-axis, center of proximal cut neck-axis
    // get lambda
    lambda = (proximal_shaft_center[0] * axis[3] + proximal_shaft_center[1] * axis[4] + proximal_shaft_center[2] * axis[5] - neck_center[0] * axis[3] - 
            neck_center[1] * axis[4]-neck_center[2] * axis[5]) / (axis[3] * neck_axis[0] + axis[4] * neck_axis[1] + axis[5] * neck_axis[2]);

    // get interception
    double intercept2[4];
    intercept2[0] = neck_center[0] + (lambda * neck_axis[0]);
    intercept2[1] = neck_center[1] + (lambda * neck_axis[1]);
    intercept2[2] = neck_center[2] + (lambda * neck_axis[2]);
    intercept2[3] = 1;

    // mean of both interception-points get most likely interception between neck and shaft-axis.
    neck_shaft_interception[0] = (intercept1[0] + intercept2[0]) / 2;
    neck_shaft_interception[1] = (intercept1[1] + intercept2[1]) / 2;
    neck_shaft_interception[2] = (intercept1[2] + intercept2[2]) / 2;
    neck_shaft_interception[3] = 1;
}

void Femur::FemoralTwist1()
{
    double intersection[3];
    double twistIntersection[4];

    // create locator
    vtkSmartPointer<vtkOBBTree> tree = vtkSmartPointer<vtkOBBTree>::New();
    tree->SetDataSet(anatomicalMesh);
    tree->BuildLocator();

    // intersection points
    vtkSmartPointer<vtkPoints> intersectPoints = vtkSmartPointer<vtkPoints>::New();

    // intersect the locator
    double lineP0[3];
    double lineP1[3];
    double lambda = 0;
    double cut_center[3];

    for (int i = 0; i < twist_intersections_size; ++i)
    {
        // intersections points starting with i = 0, so subtract -1 from twist_intersections_size for correct number 
        lambda = (i*(shaft_length/(twist_intersections_size-1)));

        getCenterOfIntersectionContour(anatomicalMesh, axis[6], axis[7], axis[8], neck_shaft_interception[0] - (lambda*axis[6]), neck_shaft_interception[1] - (lambda*axis[7]), neck_shaft_interception[2] - (lambda*axis[8]), cut_center);

        lineP0[0] = cut_center[0] + (100*axis[3]);
        lineP0[1] = cut_center[1] + (100*axis[4]);
        lineP0[2] = cut_center[2] + (100*axis[5]);

        lineP1[0] = cut_center[0] - (100*axis[3]);
        lineP1[1] = cut_center[1] - (100*axis[4]);
        lineP1[2] = cut_center[2] - (100*axis[5]);

        tree->IntersectWithLine(lineP0, lineP1, intersectPoints, NULL);

        if (intersectPoints->GetNumberOfPoints() == 0)
        {
            cout << "no intersections found!" << endl;
            return;
        }

        int min_j = 0;
        double dist = 9999;

        for (int j = 0; j < intersectPoints->GetNumberOfPoints(); j++)
        {
            intersectPoints->GetPoint(j, intersection);

            // get distance to lateral epicondyle
            // found intersections distance to plane through lateral epicondyle with vector y (which points lateral)
            if (distanceToPlane(axis[3], axis[4], axis[5], intersection[0], intersection[1], intersection[2], 
                    lateral_epicondyle[0], lateral_epicondyle[1], lateral_epicondyle[2]) < dist)
            {
                dist = distanceToPlane(axis[3], axis[4], axis[5], intersection[0], intersection[1], intersection[2], 
                    lateral_epicondyle[0], lateral_epicondyle[1], lateral_epicondyle[2]);
                min_j = j;
            }

        }

        intersectPoints->GetPoint(min_j, twistIntersection);

        // global
        twist_intersections[0][i] = twistIntersection[0];
        twist_intersections[1][i] = twistIntersection[1];
        twist_intersections[2][i] = twistIntersection[2];

        twistIntersection[3] = 3;
    }

}

void Femur::GuessEthnicGroup()
{
    // set logistic model
    string model = "LogisticModelFemur";

    // load model from config file
    ifstream file(configPath);
        
    if (!file.is_open())
    {
        cout << "Could not load config file!" << endl;
        return;
    }

    string value;
    string row;
    bool found = false;
    vector<float> coefficients;
    size_t pos = 0;
    string delimiter = ",";

    // read all lines
    while (getline(file, row))
    {
        found = false;

        // read every single comma separated value
        while ((pos = row.find(delimiter)) != string::npos)
        {
            value = row.substr(0, pos);
            row.erase(0, pos + delimiter.length());

            // if identifier for model was found in value coefficients follows
            if (value.compare(model) == 0)
                found = true;
            else if (found)
                coefficients.push_back(stof(value.c_str()));
        }
        
        if (found)
        {
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
        (coefficients.at(7) * anteversion) +
        (coefficients.at(8) * gender);

    caucasian = (int)((1 / (1 + exp(-logits))) * 100);
    asian = 100 - caucasian;
}

Femur::~Femur()
{
}