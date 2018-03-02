#include "Tibia.h"

#include "vtkPlane.h"
#include "vtkCutter.h"
#include "vtkStripper.h"

Tibia::Tibia()
{
	// initialize corresponding (technical) landmark coordinates and size of sphere for visualizing
	tib_p1[0] = tib_p1[1] = tib_p1[2] = tib_p1[4] = 0;
	tib_p1[3] = 3;
	tib_p2[0] = tib_p2[1] = tib_p2[2] = tib_p2[4] = 0;
	tib_p2[3] = 3;
	tib_p3[0] = tib_p3[1] = tib_p3[2] = tib_p3[4] = 0;
	tib_p3[3] = 3;
	tib_p4[0] = tib_p4[1] = tib_p4[2] = tib_p4[4] = 0;
	tib_p4[3] = 3;
	tib_p5[0] = tib_p5[1] = tib_p5[2] = tib_p5[4] = 0;
	tib_p5[3] = 3;
	tib_p6[0] = tib_p6[1] = tib_p6[2] = tib_p6[4] = 0;
	tib_p6[3] = 3;
	tib_p7[0] = tib_p7[1] = tib_p7[2] = tib_p7[4] = 0;
	tib_p7[3] = 3;

	// metainfos
	side = "";
	sex = "";
}

void Tibia::ResetMeasurements()
{
	tib_bone_length = tib_medial_offset = tib_lateral_offset = tib_ML_width = tib_AP_width = tib_torsion = 0;

}

void Tibia::ResetMeshesAndMeasurements(const std::string file, std::string side)
{
	// deletes all saved meshes
	meshes.clear();

	this->anatomicalMesh = LoadAnatomicalMesh(file);

	// reset measurements
	ResetMeasurements();

	DefineSideAgeSexFromFileName(file);
}

void Tibia::ResetAnatomicalLandmarks()
{
	getClosestPointFromMesh(anatomicalLandmarks.at(0), tib_p1, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(1), tib_p2, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(2), tib_p3, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(3), tib_p4, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(4), tib_p5, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(5), tib_p6, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(6), tib_p7, this->anatomicalMesh);
}

void Tibia::Thesis()
{
	int meshIndex;

	// indizes should be within valid ranges
	// debug:
	// index 0 is almost impossible, if not considered following code leads to buggy behaviour (landmarks with id = 0 is shown altough no landmarks was placed) 
	if ( (tib_p1[4] <= 0) || (tib_p1[4] >= meshes.at(0).anatomicalMesh->GetNumberOfPoints()) )
	{
		return;
	}

	// ### tib_Epicondyle_Medial ###
	meshes.at(0).anatomicalMesh->GetPoint(tib_p1[4], tib_p1);
	addMesh(vtkSphereSource::New(), tib_p1 );// mesh 1

	// ### tib_Epicondyle_Lateral ###
	meshes.at(0).anatomicalMesh->GetPoint(tib_p2[4] , tib_p2);
	meshIndex = addMesh(vtkSphereSource::New(), tib_p2 );// mesh 1

	// ### tib_Most_Proximal_Point ###
	meshes.at(0).anatomicalMesh->GetPoint(tib_p3[4], tib_p3);
	addMesh(vtkSphereSource::New(), tib_p3 );// mesh 1

	// ### tib_Malleolus_Medial ###
	meshes.at(0).anatomicalMesh->GetPoint(tib_p4[4], tib_p4);
	addMesh(vtkSphereSource::New(), tib_p4 );// mesh 1

	// ### tib_Malleolus_Lateral ###
	meshes.at(0).anatomicalMesh->GetPoint(tib_p5[4], tib_p5);
	addMesh(vtkSphereSource::New(), tib_p5 );// mesh 1

	// ### tib_Condyle_Medial ###
	meshes.at(0).anatomicalMesh->GetPoint(tib_p6[4], tib_p6);
	addMesh(vtkSphereSource::New(), tib_p6 );

	// ### tib_Condyle_Lateral ###
	meshes.at(0).anatomicalMesh->GetPoint(tib_p7[4], tib_p7);
	addMesh(vtkSphereSource::New(), tib_p7 );


	// ### center-point: 80% of length (proximal) ###
	double center[3];
	center[0] = tib_p4[0] + ((tib_p3[0]-tib_p4[0]) * 0.8);
	center[1] = tib_p4[1] + ((tib_p3[1]-tib_p4[1]) * 0.8);
	center[2] = tib_p4[2] + ((tib_p3[2]-tib_p4[2]) * 0.8);

	// normal, defined with 
	double normal[3]; double bn;
	bn = sqrt( pow(tib_p3[0]-tib_p4[0], 2) + pow(tib_p3[1]-tib_p4[1], 2) + pow(tib_p3[2]-tib_p4[2], 2) );
	normal[0] = (tib_p3[0]-tib_p4[0]) / bn;
	normal[1] = (tib_p3[1]-tib_p4[1]) / bn;
	normal[2] = (tib_p3[2]-tib_p4[2]) / bn;

	// plane
	vtkSmartPointer<vtkPlane> vtkplane_prox = vtkSmartPointer<vtkPlane>::New();
	vtkplane_prox->SetOrigin(center[0], center[1], center[2] );
	vtkplane_prox->SetNormal(normal[0], normal[1], normal[2] );
	// surface cut with plane
	vtkSmartPointer<vtkCutter> cutEdges_prox = vtkSmartPointer<vtkCutter>::New();
	cutEdges_prox->SetInputData( meshes.at(0).anatomicalMesh);
	cutEdges_prox->SetCutFunction( vtkplane_prox );
	// generates triangle poly-lines from input polygon
	vtkSmartPointer<vtkStripper> cutStrips_prox = vtkSmartPointer<vtkStripper>::New();
	cutStrips_prox->SetInputConnection( cutEdges_prox->GetOutputPort() );
	cutStrips_prox->Update();
	vtkSmartPointer<vtkPolyData> cutPoly_prox = vtkSmartPointer<vtkPolyData>::New();
	cutPoly_prox->SetPoints( cutStrips_prox->GetOutput()->GetPoints() );
	cutPoly_prox->SetPolys( cutStrips_prox->GetOutput()->GetLines() );
	// get the cutting-contours center
	double cut_center_prox[3];
	cutPoly_prox->GetCenter( cut_center_prox );

	// crash's may occure if no suitable cut were done - so return then
	if (cutPoly_prox->GetNumberOfPoints() == 0)
	{
		return;
	}

	// ### center-point: 20% of length ###
	center[0] = tib_p4[0] + ((tib_p3[0]-tib_p4[0]) * 0.2);
	center[1] = tib_p4[1] + ((tib_p3[1]-tib_p4[1]) * 0.2);
	center[2] = tib_p4[2] + ((tib_p3[2]-tib_p4[2]) * 0.2);

	bn = sqrt( pow(tib_p3[0]-tib_p4[0], 2) + pow(tib_p3[1]-tib_p4[1], 2) + pow(tib_p3[2]-tib_p4[2], 2) );
	normal[0] = (tib_p3[0]-tib_p4[0]) / bn;
	normal[1] = (tib_p3[1]-tib_p4[1]) / bn;
	normal[2] = (tib_p3[2]-tib_p4[2]) / bn;

	// plane
	vtkSmartPointer<vtkPlane> vtkplane_dist = vtkSmartPointer<vtkPlane>::New();
	vtkplane_dist->SetOrigin(center[0], center[1], center[2] );
	vtkplane_dist->SetNormal(normal[0], normal[1], normal[2] );
	// surface cut with plane
	vtkSmartPointer<vtkCutter> cutEdges_dist = vtkSmartPointer<vtkCutter>::New();
	cutEdges_dist->SetInputData( meshes.at(0).anatomicalMesh);
	cutEdges_dist->SetCutFunction( vtkplane_dist );
	// generates triangle poly-lines from input polygon
	vtkSmartPointer<vtkStripper> cutStrips_dist = vtkSmartPointer<vtkStripper>::New();
	cutStrips_dist->SetInputConnection( cutEdges_dist->GetOutputPort() );
	cutStrips_dist->Update();
	vtkSmartPointer<vtkPolyData> cutPoly_dist = vtkSmartPointer<vtkPolyData>::New();
	cutPoly_dist->SetPoints( cutStrips_dist->GetOutput()->GetPoints() );
	cutPoly_dist->SetPolys( cutStrips_dist->GetOutput()->GetLines() );

	// crash's may occure if no suitable cut were done - so return then
	if (cutPoly_dist->GetNumberOfPoints() == 0)
	{
		return;
	}

	// get the cutting-contours center
	double cut_center_dist[3];
	cutPoly_dist->GetCenter(cut_center_dist);
	

	double tmp6[6];
	// mediolateral and kraniokaudal
	tmp6[0] = tib_p6[0]-tib_p7[0];
	tmp6[1] = tib_p6[1]-tib_p7[1];
	tmp6[2] = tib_p6[2]-tib_p7[2];

	tmp6[3] = cut_center_prox[0]-cut_center_dist[0];
	tmp6[4] = cut_center_prox[1]-cut_center_dist[1];
	tmp6[5] = cut_center_prox[2]-cut_center_dist[2];

	// ### DEFINE COORDINATE SYSTEM ###
	setCoordinateSystem(tmp6, side);

	// ### OFFSET AN WIDTH ###

	double tmp3[3];
	double plane[9];
	double min = 9999; int mini = 0;
	// look for most lateral point - p8
	for (int i=0; i < cutPoly_prox->GetNumberOfPoints(); i++)
	{
		cutPoly_prox->GetPoint(i, tmp3);

		// plane: n, x, p
		plane[0] = axis[3]; plane[1] = axis[4]; plane[2] = axis[5];
		plane[3] = tmp3[0]; plane[4] = tmp3[1]; plane[5] = tmp3[2];
		plane[6] = cut_center_prox[0]; plane[7] = cut_center_prox[1]; plane[8] = cut_center_prox[2];

		if (distanceToPlane(plane) < min)
		{
			//std::cout << "i: " << i << "\t" << mini << "\t" << "min: " << min << "\t" << "DistanceToPlane: " << distanceToPlane(plane) << "\t" << tmp3[0] << "\t" << tmp3[1] << "\t" << tmp3[2] << std::endl;

			min = distanceToPlane(plane);
			mini = i;

		}
	}

	double p8[4];
	cutPoly_prox->GetPoint(mini, p8);
	p8[3] = 3;
	meshIndex = addMesh( vtkSphereSource::New(), p8); // 
	meshes.at(meshIndex).actor->GetProperty()->SetColor(1, 1, 0);

	// most medial point - p9
	double max = -9999; int maxi = 0;
	for (int i=0; i<cutPoly_prox->GetNumberOfPoints(); i++ )
	{
		cutPoly_prox->GetPoint(i, tmp3);

		// define plane with mediolateral axis as normal * (-1)
		plane[0] = axis[3]; plane[1] = axis[4]; plane[2] = axis[5];
		plane[3] = tmp3[0]; plane[4] = tmp3[1]; plane[5] = tmp3[2];
		plane[6] = cut_center_prox[0]; plane[7] = cut_center_prox[1]; plane[8] = cut_center_prox[2];

		// qDebug() << "DistanceToPlane: " << distanceToPlane(plane) << endl;
		if (distanceToPlane(plane) > max)
		{
			max = distanceToPlane(plane);
			maxi = i;
		}
	}
	
	double p9[4];
	cutPoly_prox->GetPoint(maxi, p9);
	p9[3] = 3;
	meshIndex = addMesh( vtkSphereSource::New(), p9);  
	meshes.at(meshIndex).actor->GetProperty()->SetColor(1, 0, 1);

	// most posterior point - p10
	max = 0; maxi = 0;
	for ( int i=0; i<cutPoly_prox->GetNumberOfPoints(); i++ )
	{
		cutPoly_prox->GetPoint(i, tmp3);

		plane[0] = axis[0]; plane[1] = axis[1]; plane[2] = axis[2];
		plane[3] = tmp3[0]; plane[4] = tmp3[1]; plane[5] = tmp3[2];
		plane[6] = cut_center_prox[0]; plane[7] = cut_center_prox[1]; plane[8] = cut_center_prox[2];

		//qDebug() << "DistanceToPlane: " << distanceToPlane(tmp2) << endl;
		if ( distanceToPlane(plane) > max )
		{
			max = distanceToPlane(plane);
			maxi = i;
		}
	}
	
	double p10[4];
	cutPoly_prox->GetPoint(maxi, p10);
	p10[3] = 3;
	meshIndex = addMesh( vtkSphereSource::New(), p10);  
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 0, 1);

	// most anterior p11
	max = 0; maxi = 0;
	for (int i=0; i<cutPoly_prox->GetNumberOfPoints(); i++ )
	{
		cutPoly_prox->GetPoint(i, tmp3);

		// define plane with mediolateral axis as normal * (-1)
		plane[0] = -1 * axis[0]; plane[1] = -1 * axis[1]; plane[2] = -1 * axis[2];
		plane[3] = tmp3[0]; plane[4] = tmp3[1]; plane[5] = tmp3[2];
		plane[6] = cut_center_prox[0]; plane[7] = cut_center_prox[1]; plane[8] = cut_center_prox[2];

		//qDebug() << "DistanceToPlane: " << distanceToPlane(tmp2) << endl;
		if (distanceToPlane(plane) > max)
		{
			max = distanceToPlane(plane);
			maxi = i;
		}
	}
	
	double p11[4];
	cutPoly_prox->GetPoint(maxi, p11);
	p11[3] = 3;
	meshIndex = addMesh( vtkSphereSource::New(), p11);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 0, 1);


    // ################################# //
	// ### CALCULATION OF PARAMETERS ### //
	// ################################# //

	tib_bone_length = sqrt( pow(tib_p3[0]-tib_p4[0], 2) + pow(tib_p3[1]-tib_p4[1], 2) + pow(tib_p3[2]-tib_p4[2], 2) );

	// medial offset:
	// plane: n, x, p
	plane[0] = axis[3]; plane[1] = axis[4]; plane[2] = axis[5];
	plane[3] = tib_p1[0]; plane[4] = tib_p1[1]; plane[5] = tib_p1[2];
	plane[6] = p9[0]; plane[7] = p9[1]; plane[8] = p9[2];
	tib_medial_offset = distanceToPlane( plane );

	// lateral offset:
	plane[0] = axis[3]; plane[1] = axis[4]; plane[2] = axis[5];
	plane[3] = p8[0]; plane[4] = p8[1]; plane[5] = p8[2];
	plane[6] = tib_p2[0]; plane[7] = tib_p2[1]; plane[8] = tib_p2[2];
	tib_lateral_offset = distanceToPlane( plane );

	// ml width:
	plane[0] = axis[3]; plane[1] = axis[4]; plane[2] = axis[5];
	plane[3] = p9[0]; plane[4] = p9[1]; plane[5] = p9[2];
	plane[6] = p8[0]; plane[7] = p8[1]; plane[8] = p8[2];
	tib_ML_width = distanceToPlane( plane );

	// ap width:
	plane[0] = axis[0]; plane[1] = axis[1]; plane[2] = axis[2];
	plane[3] = p10[0]; plane[4] = p10[1]; plane[5] = p10[2];
	plane[6] = p11[0]; plane[7] = p11[1]; plane[8] = p11[2];
	tib_AP_width = distanceToPlane( plane );

	TibiaStudy1Angles(tib_p6, tib_p7, tib_p4, tib_p5);
}

void Tibia::TibiaStudy1Angles(const double *p6, const double *p7, const double *p4, const double *p5)
{

	// malleolus achse
	std::vector<double> malleolus_axis(3);

	// definieren (malleolus)
	malleolus_axis.at(0) = p4[0] - p5[0];
	malleolus_axis.at(1) = p4[1] - p5[1];
	malleolus_axis.at(2) = p4[2] - p5[2];

	double b3 = sqrt( pow( malleolus_axis.at(0), 2) + pow(malleolus_axis.at(1), 2) + pow(malleolus_axis.at(2), 2) );

	malleolus_axis.at(0) = malleolus_axis.at(0) / b3;
	malleolus_axis.at(1) = malleolus_axis.at(1) / b3;
	malleolus_axis.at(2) = malleolus_axis.at(2) / b3;

	// lambda berechnen:
	double lambda1 = (axis[6]) * malleolus_axis.at(0) + (axis[7]) * malleolus_axis.at(1) + (axis[8]) * malleolus_axis.at(2);
	
	// neck achse auf die Axialebene projizieren 
	std::vector<double> malleolus_axis_kk(3);

	// wenn lambda1 < 0 (hinter der ebene + projektion, sonst - projektion)
	// schnittpunkt auf KK-Ebene (= projizierter Vektor)
	malleolus_axis_kk.at(0) = malleolus_axis.at(0) - lambda1 * (axis[6]);
	malleolus_axis_kk.at(1) = malleolus_axis.at(1) - lambda1 * (axis[7]);
	malleolus_axis_kk.at(2) = malleolus_axis.at(2) - lambda1 * (axis[8]);


	// vektor wieder normieren
	double b1 = sqrt( pow(malleolus_axis_kk.at(0), 2) + pow(malleolus_axis_kk.at(1), 2) + pow(malleolus_axis_kk.at(2), 2) );
	malleolus_axis_kk.at(0) = malleolus_axis_kk.at(0) / b1;
	malleolus_axis_kk.at(1) = malleolus_axis_kk.at(1) / b1;
	malleolus_axis_kk.at(2) = malleolus_axis_kk.at(2) / b1;

	//std::cout << "malleolus_axis: " << "\t" << malleolus_axis.at(0) << "\t" << malleolus_axis.at(1) << "\t" << malleolus_axis.at(2) << std::endl;
	//std::cout << "malleolus_axis_kk: " << "\t" << malleolus_axis_kk.at(0) << "\t" << malleolus_axis_kk.at(1) << "\t" << malleolus_axis_kk.at(2) << std::endl;

	std::vector<double> tib_epicondyle_axis(3);
	tib_epicondyle_axis.at(0) = p6[0] - p7[0];
	tib_epicondyle_axis.at(1) = p6[1] - p7[1];
	tib_epicondyle_axis.at(2) = p6[2] - p7[2];

	double b = sqrt( pow(tib_epicondyle_axis.at(0),2) + pow(tib_epicondyle_axis.at(1), 2) + pow(tib_epicondyle_axis.at(2), 2) );
	tib_epicondyle_axis.at(0) = tib_epicondyle_axis.at(0) / b;
	tib_epicondyle_axis.at(1) = tib_epicondyle_axis.at(1) / b;
	tib_epicondyle_axis.at(2) = tib_epicondyle_axis.at(2) / b;

	// epicondyle_axis auf die Axialebene projizieren (es wird nach -z projiziert):
	std::vector<double> tib_epicondyle_axis_kk(3);

	// lambda berechnen:
	double lambda2 = (axis[6]) * tib_epicondyle_axis.at(0) + (axis[7]) * tib_epicondyle_axis.at(1) + (axis[8]) * tib_epicondyle_axis.at(2);

	// wenn lambda2 < 0 (hinter der ebene + projektion, sonst - projektion)
	// schnittpunkt auf KK-Ebene (= projizierter Vektor)
	tib_epicondyle_axis_kk.at(0) = tib_epicondyle_axis.at(0) - lambda2 * (axis[6]);
	tib_epicondyle_axis_kk.at(1) = tib_epicondyle_axis.at(1) - lambda2 * (axis[7]);
	tib_epicondyle_axis_kk.at(2) = tib_epicondyle_axis.at(2) - lambda2 * (axis[8]);

	// vektor wieder normieren
	double b2 = sqrt( pow(tib_epicondyle_axis_kk.at(0), 2) + pow(tib_epicondyle_axis_kk.at(1), 2) + pow(tib_epicondyle_axis_kk.at(2), 2) );
	tib_epicondyle_axis_kk.at(0) = tib_epicondyle_axis_kk.at(0) / b2;
	tib_epicondyle_axis_kk.at(1) = tib_epicondyle_axis_kk.at(1) / b2;
	tib_epicondyle_axis_kk.at(2) = tib_epicondyle_axis_kk.at(2) / b2;

	//std::cout << "tib_epicondyle_axis: " << "\t" << tib_epicondyle_axis.at(0) << "\t" << tib_epicondyle_axis.at(1) << "\t" << tib_epicondyle_axis.at(2) << std::endl;
	//std::cout << "tib_epicondyle_axis_kk: " << "\t" << tib_epicondyle_axis_kk.at(0) << "\t" << tib_epicondyle_axis_kk.at(1) << "\t" << tib_epicondyle_axis_kk.at(2) << std::endl;

	// Winkel zwischen epicondyle_axis_kk und fem_neck_axis_kk berechnen
	double param2 = tib_epicondyle_axis_kk.at(0) * malleolus_axis_kk.at(0) + tib_epicondyle_axis_kk.at(1) * malleolus_axis_kk.at(1) + tib_epicondyle_axis_kk.at(2) * malleolus_axis_kk.at(2);
	tib_torsion = acos(param2) * (360/(2*PI));
}

Tibia::~Tibia()
{
}
