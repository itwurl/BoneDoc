#include "Femur.h"

static const unsigned int nAnatomicalLandmarks = 23;

Femur::Femur(const std::string anatomicalMeshPath, const std::string anatomicalLandmarksPath) {
	// anatomical landmarks
	this->anatomicalLandmarks = LoadAnatomicalLandmarks(anatomicalLandmarksPath);

	if (this->anatomicalLandmarks.size() != nAnatomicalLandmarks) {
		std::cout << "Unexpected number of anatomical landmarks!" << std::endl;
		exit(-1);
	}

	// anatomical mesh
	this->anatomicalMesh = this->LoadAnatomicalMesh(anatomicalMeshPath);

	if ((this->anatomicalMesh == nullptr) || (this->anatomicalMesh->GetNumberOfPoints() <= 0)) {
		std::cout << "Error loading anatomical mesh!" << std::endl;
		exit(-1);
	}

	// antomical parameters must be set to if valid output is required
	ResetMeasurements();

	// meta information
	DefineSideAgeSexFromFileName(anatomicalMeshPath);

	if (side.empty()) {
		std::cout << "Side must be known!" << std::endl;
		return;
	} else
		std::cout << "Found meta information 'side': " << this->side << std::endl;
	if (age != "")
		std::cout << "Found meta information 'age': " << this->age << std::endl;
	if (sex != "")
		std::cout << "Found meta information 'sex': " << this->sex << std::endl;
	std::cout << std::endl;
	
}

void Femur::ResetMeshesAndMeasurements(const std::string file, std::string side) {
	// deletes all saved meshes
	meshes.clear();

	// assign polydata to this class
	this->anatomicalMesh = LoadAnatomicalMesh(file);

	// reset propably already calculated anatomical parameters, technical axis and technical landmarks
	ResetMeasurements();

	// get meta information
	DefineSideAgeSexFromFileName(file);
}

void Femur::MapAnatomicalLandmarksToAnatomicalMesh() {
	
	// project anatomical landmarks onto anatomical mesh -> technical landmarks
	getClosestPointFromMesh(anatomicalLandmarks.at(0), fovea, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(1), minor_trochanter, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(2), major_trochanter, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(3), linea_intertrochanterica, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(4), intercondylar_notch, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(5), facies_patellaris, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(6), lateral_epicondyle, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(7), medial_epicondyle, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(8), most_distal_point, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(9), most_proximal_point, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(10), most_anterior_neck_point, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(11), most_medial_neck_point, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(12), most_posterior_neck_point, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(13), head_fit_point_1, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(14), head_fit_point_2, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(15), head_fit_point_3, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(16), head_fit_point_4, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(17), head_fit_point_5, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(18), head_fit_point_6, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(19), head_fit_point_7, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(20), head_fit_point_8, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(21), lateral_condyle, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(22), medial_condyle, this->anatomicalMesh);
}

void Femur::ResetMeasurements() {
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
	
	// anatomical landmarks
	medial_epicondyle[0] = medial_epicondyle[1] = medial_epicondyle[2] = medial_epicondyle[4] = 0;
	medial_epicondyle[3] = 3;
	lateral_epicondyle[0] = lateral_epicondyle[1] = lateral_epicondyle[2] = lateral_epicondyle[4] = 0;
	lateral_epicondyle[3] = 3;
	most_distal_point[0] = most_distal_point[1] = most_distal_point[2] = most_distal_point[4] = 0;
	most_distal_point[3] = 3;
	most_proximal_point[0] = most_proximal_point[1] = most_proximal_point[2] = most_proximal_point[4] = 0;
	most_proximal_point[3] = 3;
	most_anterior_neck_point[0] = most_anterior_neck_point[1] = most_anterior_neck_point[2] = most_anterior_neck_point[4] = 0;
	most_anterior_neck_point[3] = 3;
	most_medial_neck_point[0] = most_medial_neck_point[1] = most_medial_neck_point[2] = most_medial_neck_point[4] = 0;
	most_medial_neck_point[3] = 3;
	most_posterior_neck_point[0] = most_posterior_neck_point[1] = most_posterior_neck_point[2] = most_posterior_neck_point[4] = 0;
	most_posterior_neck_point[3] = 3;
	head_fit_point_1[0] = head_fit_point_1[1] = head_fit_point_1[2] = head_fit_point_1[4] = 0;
	head_fit_point_1[3] = 3;
	head_fit_point_2[0] = head_fit_point_2[1] = head_fit_point_2[2] = head_fit_point_2[4] = 0;
	head_fit_point_2[3] = 3;
	head_fit_point_3[0] = head_fit_point_3[1] = head_fit_point_3[2] = head_fit_point_3[4] = 0;
	head_fit_point_3[3] = 3;
	head_fit_point_4[0] = head_fit_point_4[1] = head_fit_point_4[2] = head_fit_point_4[4] = 0;
	head_fit_point_4[3] = 3;
	head_fit_point_5[0] = head_fit_point_5[1] = head_fit_point_5[2] = head_fit_point_5[4] = 0;
	head_fit_point_5[3] = 3;
	head_fit_point_6[0] = head_fit_point_6[1] = head_fit_point_6[2] = head_fit_point_6[4] = 0;
	head_fit_point_6[3] = 3;
	head_fit_point_7[0] = head_fit_point_7[1] = head_fit_point_7[2] = head_fit_point_7[4] = 0;
	head_fit_point_7[3] = 3;
	head_fit_point_8[0] = head_fit_point_8[1] = head_fit_point_8[2] = head_fit_point_8[4] = 0;
	head_fit_point_8[3] = 3;
	medial_condyle[0] = medial_condyle[1] = medial_condyle[2] = medial_condyle[4] = 0;
	medial_condyle[3] = 3;
	lateral_condyle[0] = lateral_condyle[1] = lateral_condyle[2] = lateral_condyle[4] = 0;
	lateral_condyle[3] = 3;
	intercondylar_notch[0] = intercondylar_notch[1] = intercondylar_notch[2] = intercondylar_notch[4] = 0;
	intercondylar_notch[3] = 3;
	fovea[0] = fovea[1] = fovea[2] = fovea[4] = 0;
	fovea[3] = 3;
	minor_trochanter[0] = minor_trochanter[1] = minor_trochanter[2] = minor_trochanter[4] = 0;
	minor_trochanter[3] = 3;
	major_trochanter[0] = major_trochanter[1] = major_trochanter[2] = major_trochanter[4] = 0;
	major_trochanter[3] = 3;
	linea_intertrochanterica[0] = linea_intertrochanterica[1] = linea_intertrochanterica[2] = linea_intertrochanterica[4];
	linea_intertrochanterica[3] = 3;
	facies_patellaris[0] = facies_patellaris[1] = facies_patellaris[2] = facies_patellaris[4];
	facies_patellaris[3] = 3;

	
	// for each anatomical landmark find the closest point on anatomical mesh
	MapAnatomicalLandmarksToAnatomicalMesh();
}

void Femur::Thesis() {
	// index for mesh-access
	int meshIndex;

	// ### Epicondyle_Medial ###
	this->anatomicalMesh->GetPoint(medial_epicondyle[4], medial_epicondyle);
	addMesh(vtkSphereSource::New(), medial_epicondyle ); 
	
	// ### Epicondyle_Lateral  ###
	this->anatomicalMesh->GetPoint(lateral_epicondyle[4], lateral_epicondyle);
	lateral_epicondyle[3] = 3; 
	addMesh(vtkSphereSource::New(), lateral_epicondyle ); 

	// ### Most_Distal_Point  ###
	this->anatomicalMesh->GetPoint(most_distal_point[4], most_distal_point);
	most_distal_point[3] = 3; 
	addMesh(vtkSphereSource::New(), most_distal_point ); 

	// ### Most_Proximal_Point  ###
	this->anatomicalMesh->GetPoint(most_proximal_point[4], most_proximal_point);
	most_proximal_point[3] = 3;
	addMesh(vtkSphereSource::New(), most_proximal_point);

	// ### Neck_Anterior  ###
	this->anatomicalMesh->GetPoint(most_anterior_neck_point[4], most_anterior_neck_point);
	most_anterior_neck_point[3] = 3; 
	addMesh(vtkSphereSource::New(), most_anterior_neck_point ); 

	// ### Neck_Medial  ###
	this->anatomicalMesh->GetPoint(most_medial_neck_point[4], most_medial_neck_point);
	most_medial_neck_point[3] = 3; 
	addMesh(vtkSphereSource::New(), most_medial_neck_point ); 

	// ### Neck_Posterior  ###
	this->anatomicalMesh->GetPoint(most_posterior_neck_point[4], most_posterior_neck_point);
	most_posterior_neck_point[3] = 3; 
	addMesh(vtkSphereSource::New(), most_posterior_neck_point ); 

	// ### Head_Fit_1  ###
	this->anatomicalMesh->GetPoint(head_fit_point_1[4], head_fit_point_1);
	head_fit_point_1[3] = 3; 
	addMesh(vtkSphereSource::New(), head_fit_point_1 ); 

	// ### Head_Fit_2  ###
	this->anatomicalMesh->GetPoint(head_fit_point_2[4], head_fit_point_2);
	head_fit_point_2[3] = 3; 
	addMesh(vtkSphereSource::New(), head_fit_point_2 ); 

	// ### Head_Fit_3  ###
	this->anatomicalMesh->GetPoint(head_fit_point_3[4], head_fit_point_3);
	head_fit_point_3[3] = 3; 
	addMesh(vtkSphereSource::New(), head_fit_point_3 ); 

	// ### Head_Fit_4  ###
	this->anatomicalMesh->GetPoint(head_fit_point_4[4], head_fit_point_4);
	head_fit_point_4[3] = 3; 
	addMesh(vtkSphereSource::New(), head_fit_point_4 ); 

	// ### Head_Fit_5  ###
	this->anatomicalMesh->GetPoint(head_fit_point_5[4], head_fit_point_5);
	head_fit_point_5[3] = 3; 
	addMesh(vtkSphereSource::New(), head_fit_point_5 ); 

	// ### Head_Fit_6 ###
	this->anatomicalMesh->GetPoint(head_fit_point_6[4], head_fit_point_6);
	head_fit_point_6[3] = 3; 
	addMesh(vtkSphereSource::New(), head_fit_point_6 ); 

	// ### Head_Fit_7 ###
	this->anatomicalMesh->GetPoint(head_fit_point_7[4], head_fit_point_7);
	head_fit_point_7[3] = 3; 
	addMesh(vtkSphereSource::New(), head_fit_point_7 ); 

	// ### Head_Fit_8 ###
	this->anatomicalMesh->GetPoint(head_fit_point_8[4], head_fit_point_8);
	head_fit_point_8[3] = 3; 
	addMesh(vtkSphereSource::New(), head_fit_point_8 );

	// ### Condyle_Medial ###
	this->anatomicalMesh->GetPoint(medial_condyle[4], medial_condyle);
	medial_condyle[3] = 3; 
	addMesh(vtkSphereSource::New(), medial_condyle );

	// ### Condyle_Lateral ###
	this->anatomicalMesh->GetPoint(lateral_condyle[4], lateral_condyle);
	lateral_condyle[3] = 3;
	addMesh(vtkSphereSource::New(), lateral_condyle );

	// ### Intercondylar_Notch ###
	this->anatomicalMesh->GetPoint(intercondylar_notch[4], intercondylar_notch);
	intercondylar_notch[3] = 3;
	addMesh(vtkSphereSource::New(), intercondylar_notch);

	// optimize manually found anatomical landmarks 'most_distal_point' and 'most_proximal_point'
	OptimizeProximalAndDistalLandmark1();

	// ### CUTTING AT 25- and 75% OF BONE LENGTH ### //
	// ### center-point: 75% of length (proximal) ###
	getCenterOfIntersectionContour(this->anatomicalMesh, most_proximal_point[0] - most_distal_point[0], most_proximal_point[1] - most_distal_point[1],
		most_proximal_point[2] - most_distal_point[2], most_distal_point[0] + ((most_proximal_point[0] - most_distal_point[0]) * 0.75),
			most_distal_point[1] + ((most_proximal_point[1] - most_distal_point[1]) * 0.75), most_distal_point[2] + 
				((most_proximal_point[2] - most_distal_point[2]) * 0.75), proximal_shaft_center);

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
	cutEdges_dist->SetInputData(this->anatomicalMesh);
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
		return;

	// get the cutting-contours center
	cutPoly_dist->GetCenter(distal_shaft_center);

	// ### DEFINE COORDINATE SYSTEM ###
	setCoordinateSystem(medial_condyle[0] - lateral_condyle[0], medial_condyle[1] - lateral_condyle[1], medial_condyle[2] - lateral_condyle[2], 
		proximal_shaft_center[0] - distal_shaft_center[0], proximal_shaft_center[1] - distal_shaft_center[1], proximal_shaft_center[2] - distal_shaft_center[2], this->side);

	// define extended femoral axis to visualize it as a line 
	double position_vectors[6];
	position_vectors[0] = proximal_shaft_center[0] + (proximal_shaft_center[0] - distal_shaft_center[0]);
	position_vectors[1] = proximal_shaft_center[1] + (proximal_shaft_center[1] - distal_shaft_center[1]);
	position_vectors[2] = proximal_shaft_center[2] + (proximal_shaft_center[2] - distal_shaft_center[2]);
	position_vectors[3] = distal_shaft_center[0] - (proximal_shaft_center[0] - distal_shaft_center[0]);
	position_vectors[4] = distal_shaft_center[1] - (proximal_shaft_center[1] - distal_shaft_center[1]);
	position_vectors[5] = distal_shaft_center[2] - (proximal_shaft_center[2] - distal_shaft_center[2]);
	addMesh(vtkLineSource::New(), position_vectors);

	// ### OFFSET AND WIDTH ###
	double tmp3[3];
	double plane[9];
	double min = 9999; int mini = 0;

	// look for most lateral point - p19
	for (int i=0; i<cutPoly_dist->GetNumberOfPoints(); i++) {
		cutPoly_dist->GetPoint(i, tmp3);

		// plane: n, x, p
		plane[0] = axis[3]; plane[1] = axis[4]; plane[2] = axis[5];
		plane[3] = tmp3[0]; plane[4] = tmp3[1]; plane[5] = tmp3[2];
		plane[6] = distal_shaft_center[0]; plane[7] = distal_shaft_center[1]; plane[8] = distal_shaft_center[2];

		if (distanceToPlane(plane) < min) {
			min = distanceToPlane(plane);
			mini = i;
		}
	}

	double fem_p19[4];
	cutPoly_dist->GetPoint(mini, fem_p19);
	fem_p19[3] = 3;
	meshIndex = addMesh(vtkSphereSource::New(), fem_p19);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 0, 1);

	// most medial point - p20
	double max = -9999; int maxi = 0;
	for (int i=0; i<cutPoly_dist->GetNumberOfPoints(); i++ ) {
		cutPoly_dist->GetPoint(i, tmp3);

		// define plane with mediolateral axis as normal * (-1)
		plane[0] = axis[3]; plane[1] = axis[4]; plane[2] = axis[5];
		plane[3] = tmp3[0]; plane[4] = tmp3[1]; plane[5] = tmp3[2];
		plane[6] = distal_shaft_center[0]; plane[7] = distal_shaft_center[1]; plane[8] = distal_shaft_center[2];

		if (distanceToPlane(plane) > max) {
			max = distanceToPlane(plane);
			maxi = i;
		}
	}
	
	double fem_p20[4];
	cutPoly_dist->GetPoint(maxi, fem_p20);
	fem_p20[3] = 3;
	meshIndex = addMesh(vtkSphereSource::New(), fem_p20);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 0, 1);

	// most posterior point - p21
	max = 0; maxi = 0;
	for (int i = 0; i < cutPoly_dist->GetNumberOfPoints(); i++) {
		cutPoly_dist->GetPoint(i, tmp3);

		plane[0] = axis[0]; plane[1] = axis[1]; plane[2] = axis[2];
		plane[3] = tmp3[0]; plane[4] = tmp3[1]; plane[5] = tmp3[2];
		plane[6] = distal_shaft_center[0]; plane[7] = distal_shaft_center[1]; plane[8] = distal_shaft_center[2];

		if (distanceToPlane(plane) > max) {
			max = distanceToPlane(plane);
			maxi = i;
		}
	}

	double fem_p21[4];
	cutPoly_dist->GetPoint(maxi, fem_p21);
	fem_p21[3] = 3;
	meshIndex = addMesh(vtkSphereSource::New(), fem_p21);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 0, 1);

	// most anterior
	max = 0; maxi = 0;
	for (int i = 0; i < cutPoly_dist->GetNumberOfPoints(); i++ ) {
		cutPoly_dist->GetPoint(i, tmp3);

		// define plane with mediolateral axis as normal * (-1)
		plane[0] = -1 * axis[0]; plane[1] = -1 * axis[1]; plane[2] = -1 * axis[2];
		plane[3] = tmp3[0]; plane[4] = tmp3[1]; plane[5] = tmp3[2];
		plane[6] = distal_shaft_center[0]; plane[7] = distal_shaft_center[1]; plane[8] = distal_shaft_center[2];

		if (distanceToPlane(plane) > max) {
			max = distanceToPlane(plane);
			maxi = i;
		}
	}

	double fem_p22[4];
	cutPoly_dist->GetPoint(maxi, fem_p22);
	fem_p22[3] = 3;
	meshIndex = addMesh(vtkSphereSource::New(), fem_p22);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 0, 1);

	// add cut_center_prox as new technical landmark to the scene
	meshIndex = addMesh(vtkSphereSource::New(), proximal_shaft_center);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 0, 1);

	// add cut_center_dist as new technical landmark to the scene
	meshIndex = addMesh(vtkSphereSource::New(), proximal_shaft_center);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 0, 1);

    // ############################################ //
	// ### CALCULATION OF ANATOMICAL PARAMETERS ### //
	// ############################################ //

	FemoralBoneLength1();

	medial_offset = distanceToPlane(axis[3], axis[4], axis[5], medial_epicondyle[0], medial_epicondyle[1], medial_epicondyle[2], fem_p20[0], fem_p20[1], fem_p20[2]);

	lateral_offset = distanceToPlane(axis[3], axis[4], axis[5], fem_p19[0], fem_p19[1], fem_p19[2], lateral_epicondyle[0], lateral_epicondyle[1], lateral_epicondyle[2]);

	ML_width = distanceToPlane(axis[3], axis[4], axis[5], fem_p20[0], fem_p20[1], fem_p20[2], fem_p19[0], fem_p19[1], fem_p19[2]);

	AP_width = distanceToPlane(axis[0], axis[1], axis[2], fem_p21[0], fem_p21[1], fem_p21[2], fem_p22[0], fem_p22[1], fem_p22[2]);

	FemoralHeadCenter1(head_fit_point_1, head_fit_point_2, head_fit_point_3, head_fit_point_4, head_fit_point_5, head_fit_point_6, head_fit_point_7, head_fit_point_8);

	FemoralNeckAxis1();

	FemoralNeckAxisCorrection1();

	FemoralNeckAndShaftAxisInterception1();

	FemoralNeckAxis2();

	FemoralAnteversionAndInclination1(medial_condyle, lateral_condyle);

	FemoralCenterOfCondyles1();
	
	std::cout << "anteversion: " << anteversion << std::endl;
    std::cout << "ap with: " << AP_width << std::endl;
    std::cout << "bone length: " << bone_length << std::endl;
    std::cout << "head radius: " << head_radius << std::endl;
    std::cout << "inclination: " << inclination << std::endl;
    std::cout << "lateral offset: " << lateral_offset << std::endl;
    std::cout << "medial offset: " << medial_offset << std::endl;
    std::cout << "ml with: " << ML_width << std::endl;
	std::cout << std::endl;
}

void Femur::PPFX() {
	// Anhand der gespeicherten Indizes werden die hierzu n�chstliegendsten Punkte auf der aktuellen Oberfl�che gesucht
	// ### fem_Epicondyle_Medial ###
	this->anatomicalMesh->GetPoint(medial_epicondyle[4], medial_epicondyle);
	addMesh(vtkSphereSource::New(), medial_epicondyle);
	
	// ### fem_Epicondyle_Lateral ###
	this->anatomicalMesh->GetPoint(lateral_epicondyle[4], lateral_epicondyle);
	lateral_epicondyle[3] = 3;
	addMesh(vtkSphereSource::New(), lateral_epicondyle);

	// ### fem_Most_Distal_Point ###
	this->anatomicalMesh->GetPoint(most_distal_point[4], most_distal_point);
	most_distal_point[3] = 3;
	addMesh(vtkSphereSource::New(), most_distal_point);

	// ### fem_Most_Proximal_Point ###
	this->anatomicalMesh->GetPoint(most_proximal_point[4], most_proximal_point);
	most_proximal_point[3] = 3;
	addMesh(vtkSphereSource::New(), most_proximal_point);

	// ### fem_Neck_Anterior ###
	this->anatomicalMesh->GetPoint(most_anterior_neck_point[4], most_anterior_neck_point);
	most_anterior_neck_point[3] = 3; 
	addMesh(vtkSphereSource::New(), most_anterior_neck_point ); 

	// ### fem_Neck_Medial ###
	this->anatomicalMesh->GetPoint(most_medial_neck_point[4], most_medial_neck_point);
	most_medial_neck_point[3] = 3; 
	addMesh(vtkSphereSource::New(), most_medial_neck_point ); 

	// ### fem_Neck_Posterior ###
	this->anatomicalMesh->GetPoint(most_posterior_neck_point[4], most_posterior_neck_point);
	most_posterior_neck_point[3] = 3; 
	addMesh(vtkSphereSource::New(), most_posterior_neck_point ); 

	// ### fem_Head_Fit_1 ###
	this->anatomicalMesh->GetPoint(head_fit_point_1[4], head_fit_point_1);
	head_fit_point_1[3] = 3; 
	addMesh(vtkSphereSource::New(), head_fit_point_1 ); 

	// ### fem_Head_Fit_2 ###
	this->anatomicalMesh->GetPoint(head_fit_point_2[4], head_fit_point_2);
	head_fit_point_2[3] = 3; 
	addMesh(vtkSphereSource::New(), head_fit_point_2 ); 

	// ### fem_Head_Fit_3 ###
	this->anatomicalMesh->GetPoint(head_fit_point_3[4], head_fit_point_3);
	head_fit_point_3[3] = 3; 
	addMesh(vtkSphereSource::New(), head_fit_point_3 ); 

	// ### fem_Head_Fit_4 ###
	this->anatomicalMesh->GetPoint(head_fit_point_4[4], head_fit_point_4);
	head_fit_point_4[3] = 3; 
	addMesh(vtkSphereSource::New(), head_fit_point_4 ); 

	// ### fem_Head_Fit_5 ###
	this->anatomicalMesh->GetPoint(head_fit_point_5[4], head_fit_point_5);
	head_fit_point_5[3] = 3; 
	addMesh(vtkSphereSource::New(), head_fit_point_5 ); 

	// ### fem_Head_Fit_6 ###
	this->anatomicalMesh->GetPoint(head_fit_point_6[4], head_fit_point_6);
	head_fit_point_6[3] = 3; 
	addMesh(vtkSphereSource::New(), head_fit_point_6 ); 

	// ### fem_Head_Fit_7 ###
	this->anatomicalMesh->GetPoint(head_fit_point_7[4], head_fit_point_7);
	head_fit_point_7[3] = 3; 
	addMesh(vtkSphereSource::New(), head_fit_point_7 ); 

	// ### fem_Head_Fit_8 ###
	this->anatomicalMesh->GetPoint(head_fit_point_8[4], head_fit_point_8);
	head_fit_point_8[3] = 3; 
	addMesh(vtkSphereSource::New(), head_fit_point_8 );

	// ### fem_Condyle_Medial ###
	this->anatomicalMesh->GetPoint(medial_condyle[4], medial_condyle);
	medial_condyle[3] = 3; 
	addMesh(vtkSphereSource::New(), medial_condyle );

	// ### fem_Condyle_Lateral ###
	this->anatomicalMesh->GetPoint(lateral_condyle[4], lateral_condyle);
	lateral_condyle[3] = 3;
	addMesh(vtkSphereSource::New(), lateral_condyle );

	// ### fem_Intercondylar_Notch ###
	this->anatomicalMesh->GetPoint(intercondylar_notch[4], intercondylar_notch);
	intercondylar_notch[3] = 3;
	addMesh(vtkSphereSource::New(), intercondylar_notch);

	// optimize manual found anatomical landmarks 'fem_p3' and 'fem_p4'
	OptimizeProximalAndDistalLandmark1();

	// ### CUTTING AT 25- and 75% OF BONE LENGTH ### //
	// ### center-point: 75% of length (proximal) ###
	getCenterOfIntersectionContour(this->anatomicalMesh, most_proximal_point[0] - most_distal_point[0], most_proximal_point[1] - most_distal_point[1],
		most_proximal_point[2] - most_distal_point[2], most_distal_point[0] + ((most_proximal_point[0] - most_distal_point[0]) * 0.75),
			most_distal_point[1] + ((most_proximal_point[1] - most_distal_point[1]) * 0.75), most_distal_point[2] + ((most_proximal_point[2] - most_distal_point[2]) * 0.75),
				proximal_shaft_center);


	/// ### center-point: 25% of length ###
	getCenterOfIntersectionContour(this->anatomicalMesh, most_proximal_point[0]- most_distal_point[0], most_proximal_point[1]- most_distal_point[1], 
		most_proximal_point[2]- most_distal_point[2], most_distal_point[0] + ((most_proximal_point[0]- most_distal_point[0]) * 0.25), 
			most_distal_point[1] + ((most_proximal_point[1]- most_distal_point[1]) * 0.25), most_distal_point[2] + ((most_proximal_point[2] - most_distal_point[2]) * 0.25),
				distal_shaft_center);

	// ### DEFINE COORDINATE SYSTEM ###
	setCoordinateSystem(medial_condyle[0]-lateral_condyle[0], medial_condyle[1]-lateral_condyle[1], medial_condyle[2]-lateral_condyle[2], 
		proximal_shaft_center[0] - distal_shaft_center[0], proximal_shaft_center[1] - distal_shaft_center[1], proximal_shaft_center[2] - distal_shaft_center[2], this->side);

	// define extended femoral axis to visualize it as a line 
	double position_vectors[6];
	position_vectors[0] = proximal_shaft_center[0] + (proximal_shaft_center[0] - distal_shaft_center[0]);
	position_vectors[1] = proximal_shaft_center[1] + (proximal_shaft_center[1] - distal_shaft_center[1]);
	position_vectors[2] = proximal_shaft_center[2] + (proximal_shaft_center[2] - distal_shaft_center[2]);
	position_vectors[3] = distal_shaft_center[0] - (proximal_shaft_center[0] - distal_shaft_center[0]);
	position_vectors[4] = distal_shaft_center[1] - (proximal_shaft_center[1] - distal_shaft_center[1]);
	position_vectors[5] = distal_shaft_center[2] - (proximal_shaft_center[2] - distal_shaft_center[2]);
	addMesh(vtkLineSource::New(), position_vectors);

	FemoralBoneLength1();

	FemoralHeadCenter1(head_fit_point_1, head_fit_point_2, head_fit_point_3, head_fit_point_4, head_fit_point_5, head_fit_point_6, head_fit_point_7, head_fit_point_8);

	FemoralNeckAxis1();

	FemoralNeckAxisCorrection1();

	FemoralNeckAndShaftAxisInterception1();
	
	FemoralNeckAxis2();

	FemoralAnteversionAndInclination1(medial_condyle, lateral_condyle);

	FemoralCenterOfCondyles1();

	FemoralShaftLength1();

	FemoralTwist1();
}

void Femur::FemoralBoneLength1()
{
	bone_length = sqrt(pow(distanceToPlane(axis[6], axis[7], axis[8], most_proximal_point[0], most_proximal_point[1], most_proximal_point[2],
		most_distal_point[0], most_distal_point[1], most_distal_point[2]), 2));
}

void Femur::OptimizeProximalAndDistalLandmark1()
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

	for (vtkIdType i = 0; i < anatomicalMesh->GetNumberOfPoints(); i++)
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

	int meshIndex;
	
	// ### most proximal ###
	anatomicalMesh->GetPoint(max_z_i, most_proximal_point);
	most_proximal_point[3] = 3;
	meshIndex = addMesh(vtkSphereSource::New(), most_proximal_point);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 0, 1);
	
	// ### most distal ###
	anatomicalMesh->GetPoint(min_z_i, most_distal_point);
	most_distal_point[3] = 3;
	meshIndex = addMesh(vtkSphereSource::New(), most_distal_point);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 0, 1);
}

void Femur::FemoralShaftLength1() {
	// distance between 'neck_shaft_interception' and 'center_of_condyles' along z-axis
	shaft_length = sqrt(pow(distanceToPlane(axis[6], axis[7], axis[8], neck_shaft_interception[0], neck_shaft_interception[1], neck_shaft_interception[2],
		center_of_condyles[0], center_of_condyles[1], center_of_condyles[2]), 2));
}

void Femur::FemoralHeadCenter1(double p8[3], double p9[3], double p10[3], double p11[3], double p12[3], double p13[3], double p14[3], double p15[3])
{
	double sphere[8][3];
	sphere[0][0] = p8[0]; sphere[0][1] = p8[1]; sphere[0][2] = p8[2];
	sphere[1][0] = p9[0]; sphere[1][1] = p9[1]; sphere[1][2] = p9[2];
	sphere[2][0] = p10[0]; sphere[2][1] = p10[1]; sphere[2][2] = p10[2];
	sphere[3][0] = p11[0]; sphere[3][1] = p11[1]; sphere[3][2] = p11[2];
	sphere[4][0] = p12[0]; sphere[4][1] = p12[1]; sphere[4][2] = p12[2];
	sphere[5][0] = p13[0]; sphere[5][1] = p13[1]; sphere[5][2] = p13[2];
	sphere[6][0] = p14[0]; sphere[6][1] = p14[1]; sphere[6][2] = p14[2];
	sphere[7][0] = p15[0]; sphere[7][1] = p15[1]; sphere[7][2] = p15[2];

	int meshIndex;
	double Cx = 0;
	double Cy = 0;
	double Cz = 0;
	double tmp[4];
	tmp[3] = 1;

	for (int i = 0; i < 8; i++)
	{
		Cx = Cx + sphere[i][0];
		Cy = Cy + sphere[i][1];
		Cz = Cz + sphere[i][2];
		//std::cout << Cx << "\t" << Cy << "\t" << Cz << std::endl;
	}

	//qDebug() << "Init large SphereFit" << Cx/8 << ":" << Cy/8 << ":" << Cz/8 << endl;
	SphereFit(sphere, 8, Cx/8, Cy/8, Cz/8);

	// fitted head center
	head[0] = a0;
	head[1] = b0;
	head[2] = c0;
	head[3] = head_radius = r0;
	// add opaque sphere 
	meshIndex = addMesh(vtkSphereSource::New(), head);
	meshes.at(meshIndex).actor->GetProperty()->SetOpacity(0.5);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(1, 0, 0);

	// and technical landmark
	head[3] = 3;
	meshIndex = addMesh(vtkSphereSource::New(), head);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 0, 1);

	this->rms0 = 99999; 
	this->a0 = 0;
	this->b0 = 0;
	this->c0 = 0;
	this->r0 = 0;
	Cx = 0;
	Cy = 0;
	Cz = 0;
}

void Femur::FemoralNeckAxis1()
{
	if ((this->head[0] == 0) && (this->head[1] == 0) && (this->head[2] == 0))
	{
		std::cout << "head-center not defined!" << std::endl;
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
	int meshIndex = addMesh(vtkSphereSource::New(), neck_isthmus_center);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 0, 1);

	// die richtige Halsachse definieren (Femurkopfzentrum - dieser punkt)
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
	if ((this->neck_isthmus_center[0] == 0) && (this->neck_isthmus_center[1] == 0) && (this->neck_isthmus_center[2] == 0))
	{
		std::cout << "neck-isthmus-center not defined!" << std::endl;
		return;
	}
	if ((this->head[0] == 0) && (this->head[1] == 0) && (this->head[2] == 0))
	{
		std::cout << "head-center not defined!" << std::endl;
		return;
	}

	// neck-length
	double neck_length = getDistance(this->neck_isthmus_center, this->head);

	// normed axis
	double neck_axis[3];
	neck_axis[0] = (this->head[0] - this->neck_isthmus_center[0]) / neck_length;
	neck_axis[1] = (this->head[1] - this->neck_isthmus_center[1]) / neck_length;
	neck_axis[2] = (this->head[2] - this->neck_isthmus_center[2]) / neck_length;

	// position vector on intersection plane
	double p[3];

	// lambda
	double lambda = 0;

	// centers of neck
	std::vector<std::vector<double>> centers;

	// set up sizes +1 for the head
	centers.resize(neck_intersection_size+1);
	for (int i = 0; i < neck_intersection_size+1; ++i)
		centers[i].resize(3);

	// loop along tempory neck-axis starting from neck-isthmus
	for (int i = 0; i < neck_intersection_size; i++)
	{
		lambda = (i * (neck_length / (neck_intersection_size-1)));

		p[0] = this->neck_isthmus_center[0] + (lambda * neck_axis[0]);
		p[1] = this->neck_isthmus_center[1] + (lambda * neck_axis[1]);
		p[2] = this->neck_isthmus_center[2] + (lambda * neck_axis[2]);

		double center[4];
		getCenterOfIntersectionContour(this->anatomicalMesh, neck_axis, p, center);

		// add intersection points as technical landmark
		center[3] = 1;
		int meshindex = addMesh(vtkSphereSource::New(), center);
		meshes.at(meshindex).actor->GetProperty()->SetColor(1, 0, 0);

		centers[i].at(0) = center[0];
		centers[i].at(1) = center[1];
		centers[i].at(2) = center[2];

		// center of mass
		this->neck_center[0] += center[0];
		this->neck_center[1] += center[1];
		this->neck_center[2] += center[2];
	}
	centers[neck_intersection_size].at(0) = this->head[0];
	centers[neck_intersection_size].at(1) = this->head[1];
	centers[neck_intersection_size].at(2) = this->head[2];

	this->neck_center[0] /= neck_intersection_size;
	this->neck_center[1] /= neck_intersection_size;
	this->neck_center[2] /= neck_intersection_size;

	// write result back to 'neck_axis', orientation of neck-axis may vary
	getLineFit(centers, neck_intersection_size, neck_axis);

	// zwei Ortsvektoren aus der Normalen und dem Schwerpunkt ermitteln
	double position_vectors[6];
	position_vectors[0] = this->neck_center[0] + ((neck_length*4) * neck_axis[0]);
	position_vectors[1] = this->neck_center[1] + ((neck_length*4) * neck_axis[1]);
	position_vectors[2] = this->neck_center[2] + ((neck_length*4) * neck_axis[2]);
	position_vectors[3] = this->neck_center[0] - ((neck_length*4) * neck_axis[0]);
	position_vectors[4] = this->neck_center[1] - ((neck_length*4) * neck_axis[1]);
	position_vectors[5] = this->neck_center[2] - ((neck_length*4) * neck_axis[2]);

	//std::cout << "LINEFIT: " << std::endl;
	//std::cout << position_vectors[0] << " " << position_vectors[1] << " " << position_vectors[2] << std::endl;
	//std::cout << position_vectors[3] << " " << position_vectors[4] << " " << position_vectors[5] << std::endl;

	// guessed 'neck_axis' visualisieren
	int meshIndex = addMesh(vtkLineSource::New(), position_vectors);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(1, 0, 0);

	// Zus�tzlich pr�fen, ob die neck_axis in die richtige Richtung zeigt. Falls der 1. Vektor n�her am Kopfzentrum
	// liegt ist die Achse nach medial orientiert, falls nicht ist sie nach lateral orientiert und muss invertiert werden.
	if (getDistance(position_vectors[0], position_vectors[1], position_vectors[2], this->head[0], this->head[1], this->head[2]) <
		getDistance(position_vectors[3], position_vectors[4], position_vectors[5], this->head[0], this->head[1], this->head[2]))
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

void Femur::FemoralNeckAxis2()
{
	// 'neck_shaft_interception' and 'head' had to be defined
	if (((0 == neck_shaft_interception[0]) && (0 == neck_shaft_interception[1]) && (0 == neck_shaft_interception[2])) ||
		((0 == head[0]) && (0 == head[1]) && (0 == head[2])))
	{
		std::cout << "Intersection between neck- and shaft axis or femoral head center was not defined before!" << std::endl;
		return;
	}

	// length 'head' - 'neck_shaft_interception'
	double b = sqrt(pow((head[0] - neck_shaft_interception[0]), 2) + pow((head[1] - neck_shaft_interception[1]), 2) + pow((head[2] - neck_shaft_interception[2]), 2));

	// redefine femoral neck axis between femoral head and intersection between neck- and shaft axis
	neck_axis[0] = (head[0] - neck_shaft_interception[0]) / b;
	neck_axis[1] = (head[1] - neck_shaft_interception[1]) / b;
	neck_axis[2] = (head[2] - neck_shaft_interception[2]) / b;

	// norm

	// visualization of neck axis
	double position_vectors[6];
	position_vectors[0] = (neck_shaft_interception[0]) + ((b*3) * neck_axis[0]);
	position_vectors[1] = (neck_shaft_interception[1]) + ((b*3) * neck_axis[1]);
	position_vectors[2] = (neck_shaft_interception[2]) + ((b*3) * neck_axis[2]);
	position_vectors[3] = (neck_shaft_interception[0]) - ((b*3) * neck_axis[0]);
	position_vectors[4] = (neck_shaft_interception[1]) - ((b*3) * neck_axis[1]);
	position_vectors[5] = (neck_shaft_interception[2]) - ((b*3) * neck_axis[2]);
	addMesh(vtkLineSource::New(), position_vectors);
}

void Femur::FemoralAnteversionAndInclination1(double medial_condyle[3], double lateral_condyle[3])
{
	//######################################
	//### (1) Berechnung der Inklination ###
	//######################################

	// Orthogonale Projektion von n auf die YZ-Becken Ebene (APP, Koronalebene) -> n_yz
	double lambda1 = -((axis[0] * neck_axis[0]) + (axis[1] * neck_axis[1]) + (axis[2] * neck_axis[2]));
	double nx_yz = neck_axis[0] + (lambda1 * axis[0]);
	double ny_yz = neck_axis[1] + (lambda1 * axis[1]);
	double nz_yz = neck_axis[2] + (lambda1 * axis[2]);

	// schnittpunkt vektor normieren
	double b1 = sqrt(pow(nx_yz, 2) + pow(ny_yz, 2) + pow(nz_yz ,2));
	nx_yz /= b1;
	ny_yz /= b1;
	nz_yz /= b1;

	// Inklination wird mit der nach inferior orientierten Achse berechnet, also -1 * Z
	double ZxMinus = -1 * axis[6];
	double ZyMinus = -1 * axis[7];
	double ZzMinus = -1 * axis[8];

	// Winkel zwischen auf app projiziertem n und nach inferior orientierte Z-Achse (axis[6-7])
	// echo "RI: " [expr (($nx_yz*$ZxMinus)+($ny_yz*$ZyMinus)+($nz_yz*$ZzMinus)) / ( sqrt(pow($ZxMinus,2)+pow($ZyMinus,2)+pow($ZzMinus,2)) * (sqrt(pow($nx_yz,2)+pow($ny_yz,2)+pow($nz_yz,2))) )]
	double alphaR = acos( ((nx_yz * ZxMinus) + (ny_yz * ZyMinus) + (nz_yz * ZzMinus)) / ( sqrt(pow(ZxMinus, 2) + pow(ZyMinus, 2) + pow(ZzMinus, 2)) * (sqrt(pow(nx_yz, 2) + pow(ny_yz, 2) + pow(nz_yz, 2))) ) );
	inclination = alphaR * (180/PI);

	// ###################################################
	// ### (2) Berechnung der Anteversion/Retroversion ###
	// ###################################################

	// Orthogonale Projektion der Halsachse 'neck_axis' auf die XY-Ebene (Axialebende) -> n_xy
	double lambda2 = -((axis[6] * neck_axis[0]) + (axis[7] * neck_axis[1]) + (axis[8] * neck_axis[2]));
	double nx_xy = neck_axis[0] + (lambda2 * axis[6]);
	double ny_xy = neck_axis[1] + (lambda2 * axis[7]);
	double nz_xy = neck_axis[2] + (lambda2 * axis[8]);

	// schnittpunkt vektor normieren
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

	// Orthogonale Projektion der mediolateralen Achse auf die XY-Ebene (Axialebende) -> ml_xy
	// negativ scalar product for z-axis and ml-axis (length to be projected)
	double lambda3 = -((axis[6] * mlx) + (axis[7] * mly) + (axis[8] * mlz));
	double mlx_xy = mlx + (lambda3 * axis[6]);
	double mly_xy = mly + (lambda3 * axis[7]);
	double mlz_xy = mlz + (lambda3 * axis[8]);

	// schnittpunkt vektor normieren
	double b4 = sqrt(pow(mlx_xy, 2) + pow(mly_xy, 2) + pow(mlz_xy, 2));
	mlx_xy /= b4;
	mly_xy /= b4;
	mlz_xy /= b4;

	// Winkel zwischen auf die Axialebene projizierter ml-achse 'ml[xyz]_xy' und nach medial orientierter auch auf die Axialebene projizierter hals-achse n[xyz]_xy
	double betaR = acos( ((nx_xy * mlx_xy) + (ny_xy * mly_xy) + (nz_xy * mlz_xy)) / ( sqrt(pow(mlx_xy, 2) + pow(mly_xy, 2) + pow(mlz_xy, 2)) * (sqrt(pow(nx_xy, 2) + pow(ny_xy, 2) + pow(nz_xy, 2))) ) );
	

	// check for retroversion - if neck-asis lies behind cornonal plane -> retroversion 
	if (((nx_xy * axis[0]) + (ny_xy * axis[1]) + (nz_xy * axis[2])) < 0)
	{
		anteversion = -betaR * (180 / PI);
	}
	else
	{
		anteversion = betaR * (180 / PI);
	}

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

	// size of landmark sphere
	center_of_condyles[3] = 3;

	// add knee-center as new technical landmark to the scene
	int meshIndex = addMesh(vtkSphereSource::New(), center_of_condyles);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 0, 1);
}

void Femur::FemoralNeckAndShaftAxisInterception1()
{
	// x-axis 
	std::vector<double> x(3);
	x.at(0) = axis[0];
	x.at(1) = axis[1];
	x.at(2) = axis[2];

	std::vector<double> tmp(3);
	tmp.at(0) = neck_axis[0];
	tmp.at(1) = neck_axis[1];
	tmp.at(2) = neck_axis[2];

	std::vector<double> xXneck = CrossProduct(tmp, x);

	double lambda;
	int meshIndex;

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

	// add neck-shaft-interception as new technical landmark to the scene
	meshIndex = addMesh(vtkSphereSource::New(), neck_shaft_interception);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(1, 0, 1);
}

void Femur::FemoralTwist1()
{
	int meshIndex;
	double intersection[3];
	double twistIntersection[4];

	// Create the locator
	vtkSmartPointer<vtkOBBTree> tree = vtkSmartPointer<vtkOBBTree>::New();
	tree->SetDataSet(this->anatomicalMesh);
	tree->BuildLocator();

	// intersection points
	vtkSmartPointer<vtkPoints> intersectPoints = vtkSmartPointer<vtkPoints>::New();
	
	// Intersect the locator
	double lineP0[3];
	double lineP1[3];
	double lambda = 0;
	double cut_center[3];

	for (int i = 0; i < twist_intersections_size; i++)
	{
		// intersections points starting with i = 0, so subtract -1 from twist_intersections_size for correct number 
		lambda = (i*(shaft_length/(twist_intersections_size-1)));

		getCenterOfIntersectionContour(this->anatomicalMesh, axis[6], axis[7], axis[8], neck_shaft_interception[0] - (lambda*axis[6]), neck_shaft_interception[1] - (lambda*axis[7]), neck_shaft_interception[2] - (lambda*axis[8]), cut_center);

		lineP0[0] = cut_center[0] + (100*axis[3]);
		lineP0[1] = cut_center[1] + (100*axis[4]);
		lineP0[2] = cut_center[2] + (100*axis[5]);

		lineP1[0] = cut_center[0] - (100*axis[3]);
		lineP1[1] = cut_center[1] - (100*axis[4]);
		lineP1[2] = cut_center[2] - (100*axis[5]);

		tree->IntersectWithLine(lineP0, lineP1, intersectPoints, NULL);

		if (intersectPoints->GetNumberOfPoints() == 0)
		{
			std::cout << "no intersections found!" << std::endl;
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

		//std::cout << "twistIntersection" << "\t" << twistIntersection[0] << " " << twistIntersection[1] << " " << twistIntersection[2] << std::endl;

		// add neck-shaft-interception as new technical landmark to the scene
		meshIndex = addMesh(vtkSphereSource::New(), twistIntersection);
		meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 0, 1);

	}

}

Femur::~Femur()
{
}