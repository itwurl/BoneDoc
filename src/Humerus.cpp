#include "Humerus.h"

#include "vtkPlane.h"
#include "vtkCutter.h"
#include "vtkStripper.h"

Humerus::Humerus()
{
	// initialize corresponding (technical) landmark coordinates and size of sphere for visualizing
	hum_p1[0] = hum_p1[1] = hum_p1[2] = hum_p1[4] = 0;
	hum_p1[3] = 3;
	hum_p2[0] = hum_p2[1] = hum_p2[2] = hum_p2[4] = 0;
	hum_p2[3] = 3;
	hum_p3[0] = hum_p3[1] = hum_p3[2] = hum_p3[4] = 0;
	hum_p3[3] = 3;
	hum_p4[0] = hum_p4[1] = hum_p4[2] = hum_p4[4] = 0;
	hum_p4[3] = 3;
	hum_p5[0] = hum_p5[1] = hum_p5[2] = hum_p5[4] = 0;
	hum_p5[3] = 3;
	hum_p6[0] = hum_p6[1] = hum_p6[2] = hum_p6[4] = 0;
	hum_p6[3] = 3;
	hum_p7[0] = hum_p7[1] = hum_p7[2] = hum_p7[4] = 0;
	hum_p7[3] = 3;
	hum_p8[0] = hum_p8[1] = hum_p8[2] = hum_p8[4] = 0;
	hum_p8[3] = 3;
	hum_p9[0] = hum_p9[1] = hum_p9[2] = hum_p9[4] = 0;
	hum_p9[3] = 3;
	hum_p10[0] = hum_p10[1] = hum_p10[2] = hum_p10[4] = 0;
	hum_p10[3] = 3;
	hum_p11[0] = hum_p11[1] = hum_p11[2] = hum_p11[4] = 0;
	hum_p11[3] = 3;
	hum_p12[0] = hum_p12[1] = hum_p12[2] = hum_p12[4] = 0;
	hum_p12[3] = 3;
	hum_p13[0] = hum_p13[1] = hum_p13[2] = hum_p13[4] = 0;
	hum_p13[3] = 3;
	hum_p14[0] = hum_p14[1] = hum_p14[2] = hum_p14[4] = 0;
	hum_p14[3] = 3;
	hum_p15[0] = hum_p15[1] = hum_p15[2] = hum_p15[4] = 0;
	hum_p15[3] = 3;
	hum_p16[0] = hum_p16[1] = hum_p16[2] = hum_p16[4] = 0;
	hum_p16[3] = 3;
	hum_p17[0] = hum_p17[1] = hum_p17[2] = hum_p17[4] = 0;
	hum_p17[3] = 3;
	hum_p18[0] = hum_p17[1] = hum_p17[2] = hum_p17[4] = 0;
	hum_p18[3] = 3;
	hum_p19[0] = hum_p17[1] = hum_p17[2] = hum_p17[4] = 0;
	hum_p19[3] = 3;

	hum_p20[0] = hum_p20[1] = hum_p20[2] = hum_p20[4] = 0;
	hum_p20[3] = 3;
	hum_p21[0] = hum_p21[1] = hum_p21[2] = hum_p21[4] = 0;
	hum_p21[3] = 3;
	hum_p22[0] = hum_p22[1] = hum_p22[2] = hum_p22[4] = 0;
	hum_p22[3] = 3;
	hum_p23[0] = hum_p23[1] = hum_p23[2] = hum_p23[4] = 0;
	hum_p23[3] = 3;
	hum_p24[0] = hum_p24[1] = hum_p24[2] = hum_p24[4] = 0;
	hum_p24[3] = 3;
	hum_p25[0] = hum_p25[1] = hum_p25[2] = hum_p25[4] = 0;
	hum_p25[3] = 3;
	hum_p26[0] = hum_p26[1] = hum_p26[2] = hum_p26[4] = 0;
	hum_p26[3] = 3;
	hum_p27[0] = hum_p27[1] = hum_p27[2] = hum_p27[4] = 0;
	hum_p27[3] = 3;
	hum_p28[0] = hum_p28[1] = hum_p28[2] = hum_p28[4] = 0;
	hum_p28[3] = 3;
	hum_p29[0] = hum_p29[1] = hum_p29[2] = hum_p29[4] = 0;
	hum_p29[3] = 3;
	hum_p30[0] = hum_p30[1] = hum_p30[2] = hum_p30[4] = 0;
	hum_p30[3] = 3;
	hum_p31[0] = hum_p31[1] = hum_p31[2] = hum_p31[4] = 0;
	hum_p31[3] = 3;
	hum_p32[0] = hum_p32[1] = hum_p32[2] = hum_p32[4] = 0;
	hum_p32[3] = 3;
	hum_p33[0] = hum_p33[1] = hum_p33[2] = hum_p33[4] = 0;
	hum_p33[3] = 3;
	hum_p34[0] = hum_p34[1] = hum_p34[2] = hum_p34[4] = 0;
	hum_p34[3] = 3;
	hum_p35[0] = hum_p35[1] = hum_p35[2] = hum_p35[4] = 0;
	hum_p35[3] = 3;

	// metainfos
	side = "";
	sex = "";
}

void Humerus::ResetMeshesAndMeasurements(const std::string file, std::string side)
{
	// deletes all saved meshes
	meshes.clear();

	this->anatomicalMesh = LoadAnatomicalMesh(file);

	// reset measurements
	ResetMeasurements();

	DefineSideAgeSexFromFileName(file);
}

void Humerus::ResetMeasurements()
{
	bone_length = medial_offset = lateral_offset = ML_width = AP_width = H1 = H2 = H3 = H4 = H5 = H6 = V1 = V2 = V3 = medial_fit_x = medial_fit_y = medial_fit_z = medial_radius = lateral_fit_x = lateral_fit_y = lateral_fit_z = lateral_radius = head_fit_x = head_fit_y = head_fit_z = head_radius = inclination = retroversion = 0;
}

void Humerus::ResetAnatomicalLandmarks()
{
	getClosestPointFromMesh(anatomicalLandmarks.at(0), hum_p1, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(1), hum_p2, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(2), hum_p3, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(3), hum_p4, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(4), hum_p5, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(5), hum_p6, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(6), hum_p7, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(7), hum_p8, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(8), hum_p9, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(9), hum_p10, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(10), hum_p11, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(11), hum_p12, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(12), hum_p13, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(13), hum_p14, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(14), hum_p15, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(15), hum_p16, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(16), hum_p17, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(17), hum_p18, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(18), hum_p19, this->anatomicalMesh);

	getClosestPointFromMesh(anatomicalLandmarks.at(19), hum_p20, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(20), hum_p21, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(21), hum_p22, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(22), hum_p23, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(23), hum_p24, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(24), hum_p25, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(25), hum_p26, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(26), hum_p27, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(27), hum_p28, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(28), hum_p29, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(29), hum_p30, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(30), hum_p31, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(31), hum_p32, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(32), hum_p33, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(33), hum_p34, this->anatomicalMesh);
	getClosestPointFromMesh(anatomicalLandmarks.at(34), hum_p35, this->anatomicalMesh);
}

void Humerus::Thesis()
{
	int meshIndex;

	// valid polyData?
	if (meshes.at(0).anatomicalMesh->GetNumberOfPoints() <= 0)
	{
		return;
	}

	// ### medial epicondyle  ###
	meshes.at(0).anatomicalMesh->GetPoint(hum_p1[4], hum_p1);
	addMesh(vtkSphereSource::New(), hum_p1 );

	// ###  lateral epicondyle ###
	meshes.at(0).anatomicalMesh->GetPoint(hum_p2[4], hum_p2);
	addMesh(vtkSphereSource::New(), hum_p2 );

	// ### pnt2 = 9392 #9493 # posterior condyle superior ###
	meshes.at(0).anatomicalMesh->GetPoint(hum_p3[4], hum_p3);
	addMesh(vtkSphereSource::New(), hum_p3 );

	// ### p4 = 7877 # medial fossa 'pass'
	meshes.at(0).anatomicalMesh->GetPoint(hum_p4[4], hum_p4);
	addMesh(vtkSphereSource::New(), hum_p4 );

	// ### p5 = 9305 # lateral fossa 'pass'
	meshes.at(0).anatomicalMesh->GetPoint(hum_p5[4], hum_p5);
	addMesh(vtkSphereSource::New(), hum_p5 );

	// kaudal (unten)
	meshes.at(0).anatomicalMesh->GetPoint(hum_p6[4], hum_p6);
	addMesh(vtkSphereSource::New(), hum_p6 );

	// ### p7 = 7727 # posterior condyle inferior
	meshes.at(0).anatomicalMesh->GetPoint(hum_p7[4], hum_p7);
	addMesh(vtkSphereSource::New(), hum_p7 );

	// ### 1275 ### - kranial (oben)
	meshes.at(0).anatomicalMesh->GetPoint(hum_p8[4], hum_p8);
	addMesh(vtkSphereSource::New(), hum_p8 );

	// ### p9 ###  Anteriorer Periphyeriepunkt am Hals
	meshes.at(0).anatomicalMesh->GetPoint(hum_p9[4], hum_p9);
	addMesh(vtkSphereSource::New(), hum_p9 );

	// ### p10 ### - Medialer Periphyeriepunkt am Hals
	meshes.at(0).anatomicalMesh->GetPoint(hum_p10[4], hum_p10);
	addMesh(vtkSphereSource::New(), hum_p10 );

	// ### p11 ### - Posteriorer Periphyeriepunkt am Hals
	meshes.at(0).anatomicalMesh->GetPoint(hum_p11[4], hum_p11);
	addMesh(vtkSphereSource::New(), hum_p11 );

	// spherefit points
	meshes.at(0).anatomicalMesh->GetPoint(hum_p12[4], hum_p12);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p12 );
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);

	meshes.at(0).anatomicalMesh->GetPoint(hum_p13[4], hum_p13);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p13 );
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);

	meshes.at(0).anatomicalMesh->GetPoint(hum_p14[4], hum_p14);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p14 );
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);
	
	meshes.at(0).anatomicalMesh->GetPoint(hum_p15[4], hum_p15);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p15 );
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);
	
	meshes.at(0).anatomicalMesh->GetPoint(hum_p16[4], hum_p16);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p16 );
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);
	
	meshes.at(0).anatomicalMesh->GetPoint(hum_p17[4], hum_p17);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p17 );
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);
	
	meshes.at(0).anatomicalMesh->GetPoint(hum_p18[4], hum_p18);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p18 );
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);
	
	meshes.at(0).anatomicalMesh->GetPoint(hum_p19[4], hum_p19);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p19 );
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);


	// ### CUTTING AT 20- and 80% OF BONE LENGTH ### //

	// ### center-point: 80% of length (proximal) ###
	double center[3];
	center[0] = hum_p6[0] + ((hum_p8[0]-hum_p6[0]) * 0.8);
	center[1] = hum_p6[1] + ((hum_p8[1]-hum_p6[1]) * 0.8);
	center[2] = hum_p6[2] + ((hum_p8[2]-hum_p6[2]) * 0.8);

	// normal, defined with 
	double normal[3]; double bn;
	bn = sqrt( pow(hum_p8[0]-hum_p6[0], 2) + pow(hum_p8[1]-hum_p6[1], 2) + pow(hum_p8[2]-hum_p6[2], 2) );
	normal[0] = (hum_p8[0]-hum_p6[0]) / bn;
	normal[1] = (hum_p8[1]-hum_p6[1]) / bn;
	normal[2] = (hum_p8[2]-hum_p6[2]) / bn;

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

	// crash's may occure if no suitable were done - so return then
	if (cutPoly_prox->GetNumberOfPoints() == 0)
	{
		return;
	}

	// get the cutting-contours center
	double cut_center_prox[3];
	cutPoly_prox->GetCenter( cut_center_prox );
	
	// ### center-point: 20% of length ###
	center[0] = hum_p6[0] + ((hum_p8[0]-hum_p6[0]) * 0.2);
	center[1] = hum_p6[1] + ((hum_p8[1]-hum_p6[1]) * 0.2);
	center[2] = hum_p6[2] + ((hum_p8[2]-hum_p6[2]) * 0.2);

	bn = sqrt( pow(hum_p6[0]-hum_p8[0], 2) + pow(hum_p6[1]-hum_p8[1], 2) + pow(hum_p6[2]-hum_p8[2], 2) );
	normal[0] = (hum_p6[0]-hum_p8[0]) / bn;
	normal[1] = (hum_p6[1]-hum_p8[1]) / bn;
	normal[2] = (hum_p6[2]-hum_p8[2]) / bn;

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

	// crash's may occure if no suitable were done - so return then
	if (cutPoly_dist->GetNumberOfPoints() == 0)
	{
		return;
	}

	// get the cutting-contours center
	double cut_center_dist[3];
	cutPoly_dist->GetCenter( cut_center_dist );
	

	double tmp6[6];
	// mediolateral and kraniokaudal
	// mediolaterale Achse nach medial orientiert!
	tmp6[0] = hum_p1[0]-hum_p2[0];
	tmp6[1] = hum_p1[1]-hum_p2[1];
	tmp6[2] = hum_p1[2]-hum_p2[2];

	// kraniokaudale Achse nach kranial orientiert
	tmp6[3] = cut_center_prox[0]-cut_center_dist[0];
	tmp6[4] = cut_center_prox[1]-cut_center_dist[1];
	tmp6[5] = cut_center_prox[2]-cut_center_dist[2];

	// ### DEFINE COORDINATE SYSTEM ###
	setCoordinateSystem( tmp6, side );

	double plane[9]; int max = 0; int maxi = 0;
	double tmp3[3];

	// look for most medial point - hum_dist_cut_medial
	for (int i=0; i < cutPoly_dist->GetNumberOfPoints(); ++i)
	{
		cutPoly_dist->GetPoint(i, tmp3);

		// plane: n, x, p
		plane[0] = axis[3]; plane[1] = axis[4]; plane[2] = axis[5];
		plane[3] = tmp3[0]; plane[4] = tmp3[1]; plane[5] = tmp3[2];
		plane[6] = cut_center_dist[0]; plane[7] = cut_center_dist[1]; plane[8] = cut_center_dist[2];

		//qDebug() << "DistanceToPlane: " << distanceToPlane(tmp2) << endl;
		if (distanceToPlane(plane) > max)
		{
			max = distanceToPlane(plane);
			maxi = i;
		}
	}

	double hum_dist_cut_medial[4];
	cutPoly_dist->GetPoint(maxi, hum_dist_cut_medial);

	hum_dist_cut_medial[3] = 3;
	meshIndex = addMesh( vtkSphereSource::New(), hum_dist_cut_medial); // mesh 9
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 0, 1);

	// most lateral point - hum_dist_cut_lateral
	max = 0;
	maxi = 0;
	for (int i = 0; i < cutPoly_dist->GetNumberOfPoints(); i++ )
	{
		cutPoly_dist->GetPoint(i, tmp3);

		// define plane with mediolateral axis as normal * (-1)
		plane[0] = -1 * axis[3]; plane[1] = -1 * axis[4]; plane[2] = -1 * axis[5];
		plane[3] = tmp3[0]; plane[4] = tmp3[1]; plane[5] = tmp3[2];
		plane[6] = cut_center_dist[0]; plane[7] = cut_center_dist[1]; plane[8] = cut_center_dist[2];

		//qDebug() << "DistanceToPlane: " << distanceToPlane(tmp2) << endl;
		if (distanceToPlane(plane) > max)
		{
			max = distanceToPlane(plane);
			maxi = i;
		}
	}
	
	double hum_dist_cut_lateral[4];
	cutPoly_dist->GetPoint(maxi, hum_dist_cut_lateral);

	hum_dist_cut_lateral[3] = 3;
	meshIndex = addMesh( vtkSphereSource::New(), hum_dist_cut_lateral);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 0, 1);

	// most posterior point - hum_dist_cut_posterior
	max = 0; maxi = 0;
	for (int i=0; i<cutPoly_dist->GetNumberOfPoints(); i++ )
	{
		cutPoly_dist->GetPoint(i, tmp3);

		plane[0] = axis[0]; plane[1] = axis[1]; plane[2] = axis[2];
		plane[3] = tmp3[0]; plane[4] = tmp3[1]; plane[5] = tmp3[2];
		plane[6] = cut_center_dist[0]; plane[7] = cut_center_dist[1]; plane[8] = cut_center_dist[2];

		//qDebug() << "DistanceToPlane: " << distanceToPlane(tmp2) << endl;
		if (distanceToPlane(plane) > max)
		{
			max = distanceToPlane(plane);
			maxi = i;
		}
	}
	
	double hum_dist_cut_posterior[4];
	cutPoly_dist->GetPoint(maxi, hum_dist_cut_posterior);
	hum_dist_cut_posterior[3] = 3;
	meshIndex = addMesh( vtkSphereSource::New(), hum_dist_cut_posterior);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 0, 1);

	// most anterior point - hum_dist_cut_anterior
	max = 0;
	maxi = 0;
	for (int i = 0; i < cutPoly_dist->GetNumberOfPoints(); i++ )
	{
		cutPoly_dist->GetPoint(i, tmp3);

		// define plane with ventral axis
		plane[0] = -1 * axis[0]; plane[1] = -1 * axis[1]; plane[2] = -1 * axis[2];
		plane[3] = tmp3[0]; plane[4] = tmp3[1]; plane[5] = tmp3[2];
		plane[6] = cut_center_dist[0]; plane[7] = cut_center_dist[1]; plane[8] = cut_center_dist[2];

		//qDebug() << "DistanceToPlane: " << distanceToPlane(tmp2) << endl;
		if (distanceToPlane(plane) > max)
		{
			max = distanceToPlane(plane);
			maxi = i;
		}
	}
	
	double hum_dist_cut_anterior[4];
	cutPoly_dist->GetPoint(maxi, hum_dist_cut_anterior);
	hum_dist_cut_anterior[3] = 3;
	meshIndex = addMesh( vtkSphereSource::New(), hum_dist_cut_anterior);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 0, 1);

	// bone length:
	bone_length = sqrt( pow(hum_p8[0]-hum_p6[0], 2) + pow(hum_p8[1]-hum_p6[1], 2) + pow(hum_p8[2]-hum_p6[2], 2) );

	// medial offset:
	// plane: n, x, p
	plane[0] = axis[3]; plane[1] = axis[4]; plane[2] = axis[5];
	plane[3] = hum_p1[0]; plane[4] = hum_p1[1]; plane[5] = hum_p1[2];
	plane[6] = hum_dist_cut_medial[0]; plane[7] = hum_dist_cut_medial[1]; plane[8] = hum_dist_cut_medial[2];
	medial_offset = distanceToPlane( plane );

	// lateral offset:
	plane[0] = -axis[3]; plane[1] = -axis[4]; plane[2] = -axis[5];
	plane[3] = hum_p2[0]; plane[4] = hum_p2[1]; plane[5] = hum_p2[2];
	plane[6] = hum_dist_cut_lateral[0]; plane[7] = hum_dist_cut_lateral[1]; plane[8] = hum_dist_cut_lateral[2];
	lateral_offset = distanceToPlane( plane );

	// ml width:
	plane[0] = axis[3]; plane[1] = axis[4]; plane[2] = axis[5];
	plane[3] = hum_dist_cut_medial[0]; plane[4] = hum_dist_cut_medial[1]; plane[5] = hum_dist_cut_medial[2];
	plane[6] = hum_dist_cut_lateral[0]; plane[7] = hum_dist_cut_lateral[1]; plane[8] = hum_dist_cut_lateral[2];
	ML_width = distanceToPlane( plane );

	// ap width:
	plane[0] = axis[0]; plane[1] = axis[1]; plane[2] = axis[2];
	plane[3] = hum_dist_cut_posterior[0]; plane[4] = hum_dist_cut_posterior[1]; plane[5] = hum_dist_cut_posterior[2];
	plane[6] = hum_dist_cut_anterior[0]; plane[7] = hum_dist_cut_anterior[1]; plane[8] = hum_dist_cut_anterior[2];
	AP_width = distanceToPlane( plane );

	// H1 - mediolateral axis, inferior peak of condyle (p6), medial condyle (p1)
	plane[0] = -axis[3]; plane[1] = -axis[4]; plane[2] = -axis[5];
	plane[3] = hum_p6[0]; plane[4] = hum_p6[1]; plane[5] = hum_p6[2];
	plane[6] = hum_p1[0]; plane[7] = hum_p1[1]; plane[8] = hum_p1[2];
	H1 = distanceToPlane( plane );

	// H2 - mediolateral axis, laterale condyle (p2), inferior peak of condyle (p6)
	plane[0] = -axis[3]; plane[1] = -axis[4]; plane[2] = -axis[5];
	plane[3] = hum_p2[0]; plane[4] = hum_p2[1]; plane[5] = hum_p2[2];
	plane[6] = hum_p6[0]; plane[7] = hum_p6[1]; plane[8] = hum_p6[2];
	H2 = distanceToPlane( plane );

	// H3 - mediolateral axis, laterale condyle (p2), medial condyle (p1)
	plane[0] = -axis[3]; plane[1] = -axis[4]; plane[2] = -axis[5];
	plane[3] = hum_p2[0]; plane[4] = hum_p2[1]; plane[5] = hum_p2[2];
	plane[6] = hum_p1[0]; plane[7] = hum_p1[1]; plane[8] = hum_p1[2];
	H3 = distanceToPlane( plane );

	// H4 - mediolateral axis, p5, p4
	plane[0] = -axis[3]; plane[1] = -axis[4]; plane[2] = -axis[5];
	plane[3] = hum_p5[0]; plane[4] = hum_p5[1]; plane[5] = hum_p5[2];
	plane[6] = hum_p4[0]; plane[7] = hum_p4[1]; plane[8] = hum_p4[2];
	H4 = distanceToPlane( plane );

	// H5 - mediolateral axis, p4, p1
	plane[0] = -axis[3]; plane[1] = -axis[4]; plane[2] = -axis[5];
	plane[3] = hum_p4[0]; plane[4] = hum_p4[1]; plane[5] = hum_p4[2];
	plane[6] = hum_p1[0]; plane[7] = hum_p1[1]; plane[8] = hum_p1[2];
	H5 = distanceToPlane( plane );

	// H6 - mediolateral axis, p2, p5
	plane[0] = -axis[3]; plane[1] = -axis[4]; plane[2] = -axis[5];
	plane[3] = hum_p2[0]; plane[4] = hum_p2[1]; plane[5] = hum_p2[2];
	plane[6] = hum_p5[0]; plane[7] = hum_p5[1]; plane[8] = hum_p5[2];
	H6 = distanceToPlane( plane );

	// V1 - z axis, p7, p6
	plane[0] = axis[6]; plane[1] = axis[7]; plane[2] = axis[8];
	plane[3] = hum_p7[0]; plane[4] = hum_p7[1]; plane[5] = hum_p7[2];
	plane[6] = hum_p6[0]; plane[7] = hum_p6[1]; plane[8] = hum_p6[2];
	V1 = distanceToPlane( plane );

	// V2 - z axis, p3, p7
	plane[0] = axis[6]; plane[1] = axis[7]; plane[2] = axis[8];
	plane[3] = hum_p3[0]; plane[4] = hum_p3[1]; plane[5] = hum_p3[2];
	plane[6] = hum_p7[0]; plane[7] = hum_p7[1]; plane[8] = hum_p7[2];
	V2 = distanceToPlane( plane );

	// V3 - z axis, p3, p6
	plane[0] = axis[6]; plane[1] = axis[7]; plane[2] = axis[8];
	plane[3] = hum_p3[0]; plane[4] = hum_p3[1]; plane[5] = hum_p3[2];
	plane[6] = hum_p6[0]; plane[7] = hum_p6[1]; plane[8] = hum_p6[2];
	V3 = distanceToPlane( plane );

	epicondyle_axis[0] = hum_p1[0] - hum_p2[0];
	epicondyle_axis[1] = hum_p1[1] - hum_p2[1];
	epicondyle_axis[2] = hum_p1[2] - hum_p2[2];
	double b = sqrt( pow(epicondyle_axis[0], 2) + pow(epicondyle_axis[1], 2) + pow(epicondyle_axis[2], 2) );
	epicondyle_axis[0] = epicondyle_axis[0] / b;
	epicondyle_axis[1] = epicondyle_axis[1] / b;
	epicondyle_axis[2] = epicondyle_axis[2] / b;

	// spherefit with p12-p19
	HumerusHeadCenter(hum_p12, hum_p13, hum_p14, hum_p15, hum_p16, hum_p17, hum_p18, hum_p19);

	// inclination and retroversion of humerus with p9, p10, p11
	HumerusInclinationAndRetroversion(hum_p9, hum_p10, hum_p11);
}

void Humerus::DistalHumerus()
{
	int meshIndex = 0;

	// valid polyData?
	if (meshes.at(0).anatomicalMesh->GetNumberOfPoints() <= 0)
	{
		return;
	}

	// ### medial epicondyle  ###
	meshes.at(0).anatomicalMesh->GetPoint(hum_p1[4], hum_p1);
	addMesh(vtkSphereSource::New(), hum_p1 );// mesh 4

	// ###  lateral epicondyle ###
	meshes.at(0).anatomicalMesh->GetPoint(hum_p2[4], hum_p2);
	addMesh(vtkSphereSource::New(), hum_p2 );// mesh 3

	// ### pnt2 = 9392 #9493 # posterior condyle superior ###
	meshes.at(0).anatomicalMesh->GetPoint(hum_p3[4], hum_p3);
	addMesh(vtkSphereSource::New(), hum_p3 );// mesh 5

	// ### p4 = 7877 # medial fossa 'pass'
	meshes.at(0).anatomicalMesh->GetPoint(hum_p4[4], hum_p4);
	addMesh(vtkSphereSource::New(), hum_p4 );// mesh 6

	// ### p5 = 9305 # lateral fossa 'pass'
	meshes.at(0).anatomicalMesh->GetPoint(hum_p5[4], hum_p5);
	addMesh(vtkSphereSource::New(), hum_p5 );// mesh 7

	// kaudal (unten)
	meshes.at(0).anatomicalMesh->GetPoint(hum_p6[4], hum_p6);
	addMesh(vtkSphereSource::New(), hum_p6 );// mesh 1

	// ### p7 = 7727 # posterior condyle inferior
	meshes.at(0).anatomicalMesh->GetPoint(hum_p7[4], hum_p7);
	addMesh(vtkSphereSource::New(), hum_p7 );// mesh 8

	// ### 1275 ### - kranial (oben)
	meshes.at(0).anatomicalMesh->GetPoint(hum_p8[4], hum_p8);
	addMesh(vtkSphereSource::New(), hum_p8 );// mesh 2

	// ### p9 ###  Anteriorer Periphyeriepunkt am Hals
	meshes.at(0).anatomicalMesh->GetPoint(hum_p9[4], hum_p9);
	addMesh(vtkSphereSource::New(), hum_p9 );

	// ### p10 ### - Medialer Periphyeriepunkt am Hals
	meshes.at(0).anatomicalMesh->GetPoint(hum_p10[4], hum_p10);
	addMesh(vtkSphereSource::New(), hum_p10 );

	// ### p11 ### - Posteriorer Periphyeriepunkt am Hals
	meshes.at(0).anatomicalMesh->GetPoint(hum_p11[4], hum_p11);
	addMesh(vtkSphereSource::New(), hum_p11 );

	// spherefit points
	meshes.at(0).anatomicalMesh->GetPoint(hum_p12[4], hum_p12);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p12 );
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);

	meshes.at(0).anatomicalMesh->GetPoint(hum_p13[4], hum_p13);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p13 );
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);

	meshes.at(0).anatomicalMesh->GetPoint(hum_p14[4], hum_p14);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p14 );
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);
	
	meshes.at(0).anatomicalMesh->GetPoint(hum_p15[4], hum_p15);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p15 );
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);
	
	meshes.at(0).anatomicalMesh->GetPoint(hum_p16[4], hum_p16);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p16 );
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);
	
	meshes.at(0).anatomicalMesh->GetPoint(hum_p17[4], hum_p17);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p17 );
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);
	
	meshes.at(0).anatomicalMesh->GetPoint(hum_p18[4], hum_p18);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p18 );
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);
	
	meshes.at(0).anatomicalMesh->GetPoint(hum_p19[4], hum_p19);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p19 );
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);

	// medial condyle points for sphere-fit 
	meshes.at(0).anatomicalMesh->GetPoint(hum_p20[4], hum_p20);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p20 );
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);

	meshes.at(0).anatomicalMesh->GetPoint(hum_p21[4], hum_p21);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p21 );
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);

	meshes.at(0).anatomicalMesh->GetPoint(hum_p22[4], hum_p22);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p22 );
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);
	
	meshes.at(0).anatomicalMesh->GetPoint(hum_p23[4], hum_p23);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p23 );
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);
	
	meshes.at(0).anatomicalMesh->GetPoint(hum_p24[4], hum_p24);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p24);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);
	
	meshes.at(0).anatomicalMesh->GetPoint(hum_p25[4], hum_p25);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p25);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);
	
	meshes.at(0).anatomicalMesh->GetPoint(hum_p26[4], hum_p26);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p26);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);
	
	meshes.at(0).anatomicalMesh->GetPoint(hum_p27[4], hum_p27);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p27);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);

	// lateral condyle points for sphere-fit 
	meshes.at(0).anatomicalMesh->GetPoint(hum_p28[4], hum_p28);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p28);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);

	meshes.at(0).anatomicalMesh->GetPoint(hum_p29[4], hum_p29);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p29);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);

	meshes.at(0).anatomicalMesh->GetPoint(hum_p30[4], hum_p30);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p30);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);
	
	meshes.at(0).anatomicalMesh->GetPoint(hum_p31[4], hum_p31);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p31);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);
	
	meshes.at(0).anatomicalMesh->GetPoint(hum_p32[4], hum_p32);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p32);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);
	
	meshes.at(0).anatomicalMesh->GetPoint(hum_p33[4], hum_p33);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p33);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);
	
	meshes.at(0).anatomicalMesh->GetPoint(hum_p34[4], hum_p34);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p34);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);
	
	meshes.at(0).anatomicalMesh->GetPoint(hum_p35[4], hum_p35);
	meshIndex = addMesh(vtkSphereSource::New(), hum_p35);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 1, 0);


	// ### CUTTING AT 20- and 80% OF BONE LENGTH ### //

	// ### center-point: 80% of length (proximal) ###
	double center[3];
	center[0] = hum_p6[0] + ((hum_p8[0]-hum_p6[0]) * 0.8);
	center[1] = hum_p6[1] + ((hum_p8[1]-hum_p6[1]) * 0.8);
	center[2] = hum_p6[2] + ((hum_p8[2]-hum_p6[2]) * 0.8);

	// normal, defined with 
	double normal[3]; double bn;
	bn = sqrt( pow(hum_p8[0]-hum_p6[0], 2) + pow(hum_p8[1]-hum_p6[1], 2) + pow(hum_p8[2]-hum_p6[2], 2) );
	normal[0] = (hum_p8[0]-hum_p6[0]) / bn;
	normal[1] = (hum_p8[1]-hum_p6[1]) / bn;
	normal[2] = (hum_p8[2]-hum_p6[2]) / bn;

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

	// crash's may occure if no suitable were done - so return then
	if (cutPoly_prox->GetNumberOfPoints() == 0)
	{
		return;
	}

	// get the cutting-contours center
	double cut_center_prox[3];
	cutPoly_prox->GetCenter( cut_center_prox );
	
	// ### center-point: 20% of length ###
	center[0] = hum_p6[0] + ((hum_p8[0]-hum_p6[0]) * 0.2);
	center[1] = hum_p6[1] + ((hum_p8[1]-hum_p6[1]) * 0.2);
	center[2] = hum_p6[2] + ((hum_p8[2]-hum_p6[2]) * 0.2);

	bn = sqrt( pow(hum_p6[0]-hum_p8[0], 2) + pow(hum_p6[1]-hum_p8[1], 2) + pow(hum_p6[2]-hum_p8[2], 2) );
	normal[0] = (hum_p6[0]-hum_p8[0]) / bn;
	normal[1] = (hum_p6[1]-hum_p8[1]) / bn;
	normal[2] = (hum_p6[2]-hum_p8[2]) / bn;

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

	// crash's may occure if no suitable were done - so return then
	if (cutPoly_dist->GetNumberOfPoints() == 0)
	{
		return;
	}

	// get the cutting-contours center
	double cut_center_dist[3];
	cutPoly_dist->GetCenter( cut_center_dist );
	

	double tmp6[6];
	// mediolateral and kraniokaudal
	// mediolaterale Achse nach medial orientiert!
	tmp6[0] = hum_p1[0] - hum_p2[0];
	tmp6[1] = hum_p1[1] - hum_p2[1];
	tmp6[2] = hum_p1[2] - hum_p2[2];

	// kraniokaudale Achse nach kranial orientiert
	tmp6[3] = cut_center_prox[0] - cut_center_dist[0];
	tmp6[4] = cut_center_prox[1] - cut_center_dist[1];
	tmp6[5] = cut_center_prox[2] - cut_center_dist[2];

	// ### DEFINE COORDINATE SYSTEM ###
	setCoordinateSystem(tmp6, side);

	double plane[9]; int max = 0; int maxi = 0;
	double tmp3[3];

	// look for most medial point - hum_dist_cut_medial
	for (int i=0; i < cutPoly_dist->GetNumberOfPoints(); ++i)
	{
		cutPoly_dist->GetPoint(i, tmp3);

		// plane: n, x, p
		plane[0] = axis[3]; plane[1] = axis[4]; plane[2] = axis[5];
		plane[3] = tmp3[0]; plane[4] = tmp3[1]; plane[5] = tmp3[2];
		plane[6] = cut_center_dist[0]; plane[7] = cut_center_dist[1]; plane[8] = cut_center_dist[2];

		//qDebug() << "DistanceToPlane: " << distanceToPlane(tmp2) << endl;
		if (distanceToPlane(plane) > max)
		{
			max = distanceToPlane(plane);
			maxi = i;
		}
	}

	double hum_dist_cut_medial[4];
	cutPoly_dist->GetPoint(maxi, hum_dist_cut_medial);

	hum_dist_cut_medial[3] = 3;
	meshIndex = addMesh( vtkSphereSource::New(), hum_dist_cut_medial); // mesh 9
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 0, 1);

	// most lateral point - hum_dist_cut_lateral
	max = 0;
	maxi = 0;
	for (int i = 0; i < cutPoly_dist->GetNumberOfPoints(); i++ )
	{
		cutPoly_dist->GetPoint(i, tmp3);

		// define plane with mediolateral axis as normal * (-1)
		plane[0] = -1 * axis[3]; plane[1] = -1 * axis[4]; plane[2] = -1 * axis[5];
		plane[3] = tmp3[0]; plane[4] = tmp3[1]; plane[5] = tmp3[2];
		plane[6] = cut_center_dist[0]; plane[7] = cut_center_dist[1]; plane[8] = cut_center_dist[2];

		//qDebug() << "DistanceToPlane: " << distanceToPlane(tmp2) << endl;
		if (distanceToPlane(plane) > max)
		{
			max = distanceToPlane(plane);
			maxi = i;
		}
	}
	
	double hum_dist_cut_lateral[4];
	cutPoly_dist->GetPoint(maxi, hum_dist_cut_lateral);

	hum_dist_cut_lateral[3] = 3;
	meshIndex = addMesh( vtkSphereSource::New(), hum_dist_cut_lateral);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 0, 1);

	// most posterior point - hum_dist_cut_posterior
	max = 0; maxi = 0;
	for (int i=0; i<cutPoly_dist->GetNumberOfPoints(); i++ )
	{
		cutPoly_dist->GetPoint(i, tmp3);

		plane[0] = axis[0]; plane[1] = axis[1]; plane[2] = axis[2];
		plane[3] = tmp3[0]; plane[4] = tmp3[1]; plane[5] = tmp3[2];
		plane[6] = cut_center_dist[0]; plane[7] = cut_center_dist[1]; plane[8] = cut_center_dist[2];

		//qDebug() << "DistanceToPlane: " << distanceToPlane(tmp2) << endl;
		if (distanceToPlane(plane) > max)
		{
			max = distanceToPlane(plane);
			maxi = i;
		}
	}
	
	double hum_dist_cut_posterior[4];
	cutPoly_dist->GetPoint(maxi, hum_dist_cut_posterior);
	hum_dist_cut_posterior[3] = 3;
	meshIndex = addMesh( vtkSphereSource::New(), hum_dist_cut_posterior);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 0, 1);

	// most anterior point - hum_dist_cut_anterior
	max = 0;
	maxi = 0;
	for (int i = 0; i < cutPoly_dist->GetNumberOfPoints(); i++ )
	{
		cutPoly_dist->GetPoint(i, tmp3);

		// define plane with ventral axis
		plane[0] = -1 * axis[0]; plane[1] = -1 * axis[1]; plane[2] = -1 * axis[2];
		plane[3] = tmp3[0]; plane[4] = tmp3[1]; plane[5] = tmp3[2];
		plane[6] = cut_center_dist[0]; plane[7] = cut_center_dist[1]; plane[8] = cut_center_dist[2];

		//qDebug() << "DistanceToPlane: " << distanceToPlane(tmp2) << endl;
		if (distanceToPlane(plane) > max)
		{
			max = distanceToPlane(plane);
			maxi = i;
		}
	}
	
	double hum_dist_cut_anterior[4];
	cutPoly_dist->GetPoint(maxi, hum_dist_cut_anterior);
	hum_dist_cut_anterior[3] = 3;
	meshIndex = addMesh( vtkSphereSource::New(), hum_dist_cut_anterior);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(0, 0, 1);

	// ### evaluations ###
	// bone length:
	bone_length = sqrt( pow(hum_p8[0]-hum_p6[0], 2) + pow(hum_p8[1]-hum_p6[1], 2) + pow(hum_p8[2]-hum_p6[2], 2) );


	// medial offset:
	// plane: n, x, p
	plane[0] = axis[3]; plane[1] = axis[4]; plane[2] = axis[5];
	plane[3] = hum_p1[0]; plane[4] = hum_p1[1]; plane[5] = hum_p1[2];
	plane[6] = hum_dist_cut_medial[0]; plane[7] = hum_dist_cut_medial[1]; plane[8] = hum_dist_cut_medial[2];
	medial_offset = distanceToPlane( plane );

	// lateral offset:
	plane[0] = -axis[3]; plane[1] = -axis[4]; plane[2] = -axis[5];
	plane[3] = hum_p2[0]; plane[4] = hum_p2[1]; plane[5] = hum_p2[2];
	plane[6] = hum_dist_cut_lateral[0]; plane[7] = hum_dist_cut_lateral[1]; plane[8] = hum_dist_cut_lateral[2];
	lateral_offset = distanceToPlane( plane );

	// ml width:
	plane[0] = axis[3]; plane[1] = axis[4]; plane[2] = axis[5];
	plane[3] = hum_dist_cut_medial[0]; plane[4] = hum_dist_cut_medial[1]; plane[5] = hum_dist_cut_medial[2];
	plane[6] = hum_dist_cut_lateral[0]; plane[7] = hum_dist_cut_lateral[1]; plane[8] = hum_dist_cut_lateral[2];
	ML_width = distanceToPlane( plane );

	// ap width:
	plane[0] = axis[0]; plane[1] = axis[1]; plane[2] = axis[2];
	plane[3] = hum_dist_cut_posterior[0]; plane[4] = hum_dist_cut_posterior[1]; plane[5] = hum_dist_cut_posterior[2];
	plane[6] = hum_dist_cut_anterior[0]; plane[7] = hum_dist_cut_anterior[1]; plane[8] = hum_dist_cut_anterior[2];
	AP_width = distanceToPlane( plane );

	// H1 - mediolateral axis, inferior peak of condyle (p6), medial condyle (p1)
	plane[0] = -axis[3]; plane[1] = -axis[4]; plane[2] = -axis[5];
	plane[3] = hum_p6[0]; plane[4] = hum_p6[1]; plane[5] = hum_p6[2];
	plane[6] = hum_p1[0]; plane[7] = hum_p1[1]; plane[8] = hum_p1[2];
	H1 = distanceToPlane( plane );

	// H2 - mediolateral axis, laterale condyle (p2), inferior peak of condyle (p6)
	plane[0] = -axis[3]; plane[1] = -axis[4]; plane[2] = -axis[5];
	plane[3] = hum_p2[0]; plane[4] = hum_p2[1]; plane[5] = hum_p2[2];
	plane[6] = hum_p6[0]; plane[7] = hum_p6[1]; plane[8] = hum_p6[2];
	H2 = distanceToPlane( plane );

	// H3 - mediolateral axis, laterale condyle (p2), medial condyle (p1)
	plane[0] = -axis[3]; plane[1] = -axis[4]; plane[2] = -axis[5];
	plane[3] = hum_p2[0]; plane[4] = hum_p2[1]; plane[5] = hum_p2[2];
	plane[6] = hum_p1[0]; plane[7] = hum_p1[1]; plane[8] = hum_p1[2];
	H3 = distanceToPlane( plane );

	// H4 - mediolateral axis, p5, p4
	plane[0] = -axis[3]; plane[1] = -axis[4]; plane[2] = -axis[5];
	plane[3] = hum_p5[0]; plane[4] = hum_p5[1]; plane[5] = hum_p5[2];
	plane[6] = hum_p4[0]; plane[7] = hum_p4[1]; plane[8] = hum_p4[2];
	H4 = distanceToPlane( plane );

	// H5 - mediolateral axis, p4, p1
	plane[0] = -axis[3]; plane[1] = -axis[4]; plane[2] = -axis[5];
	plane[3] = hum_p4[0]; plane[4] = hum_p4[1]; plane[5] = hum_p4[2];
	plane[6] = hum_p1[0]; plane[7] = hum_p1[1]; plane[8] = hum_p1[2];
	H5 = distanceToPlane( plane );

	// H6 - mediolateral axis, p2, p5
	plane[0] = -axis[3]; plane[1] = -axis[4]; plane[2] = -axis[5];
	plane[3] = hum_p2[0]; plane[4] = hum_p2[1]; plane[5] = hum_p2[2];
	plane[6] = hum_p5[0]; plane[7] = hum_p5[1]; plane[8] = hum_p5[2];
	H6 = distanceToPlane( plane );

	// V1 - z axis, p7, p6
	plane[0] = axis[6]; plane[1] = axis[7]; plane[2] = axis[8];
	plane[3] = hum_p7[0]; plane[4] = hum_p7[1]; plane[5] = hum_p7[2];
	plane[6] = hum_p6[0]; plane[7] = hum_p6[1]; plane[8] = hum_p6[2];
	V1 = distanceToPlane( plane );

	// V2 - z axis, p3, p7
	plane[0] = axis[6]; plane[1] = axis[7]; plane[2] = axis[8];
	plane[3] = hum_p3[0]; plane[4] = hum_p3[1]; plane[5] = hum_p3[2];
	plane[6] = hum_p7[0]; plane[7] = hum_p7[1]; plane[8] = hum_p7[2];
	V2 = distanceToPlane( plane );

	// V3 - z axis, p3, p6
	plane[0] = axis[6]; plane[1] = axis[7]; plane[2] = axis[8];
	plane[3] = hum_p3[0]; plane[4] = hum_p3[1]; plane[5] = hum_p3[2];
	plane[6] = hum_p6[0]; plane[7] = hum_p6[1]; plane[8] = hum_p6[2];
	V3 = distanceToPlane( plane );

	epicondyle_axis[0] = hum_p1[0] - hum_p2[0];
	epicondyle_axis[1] = hum_p1[1] - hum_p2[1];
	epicondyle_axis[2] = hum_p1[2] - hum_p2[2];
	double b = sqrt( pow(epicondyle_axis[0],2) + pow(epicondyle_axis[1], 2) + pow(epicondyle_axis[2], 2) );
	epicondyle_axis[0] = epicondyle_axis[0] / b;
	epicondyle_axis[1] = epicondyle_axis[1] / b;
	epicondyle_axis[2] = epicondyle_axis[2] / b;

	// spherefit with p12-p19
	HumerusHeadCenter(hum_p12, hum_p13, hum_p14, hum_p15, hum_p16, hum_p17, hum_p18, hum_p19);

	// spherefit with p20-p27
	HumerusLateralCondyle(hum_p20, hum_p21, hum_p22, hum_p23, hum_p24, hum_p25, hum_p26, hum_p27);

	// spherefit with p28-p35
	HumerusMedialCondyle(hum_p28, hum_p29, hum_p30, hum_p31, hum_p32, hum_p33, hum_p34, hum_p35);
}

void Humerus::HumerusHeadCenter(double* p12, double* p13, double* p14, double* p15, double* p16, double* p17, double* p18, double* p19)
{
	int meshIndex;
	double Cx = 0;
	double Cy = 0;
	double Cz = 0;
	double head_circle[8][3];
	
	// define points for head sphere-fit
	head_circle[0][0] = p12[0];
	head_circle[0][1] = p12[1];
	head_circle[0][2] = p12[2];

	head_circle[1][0] = p13[0];
	head_circle[1][1] = p13[1];
	head_circle[1][2] = p13[2];

	head_circle[2][0] = p14[0];
	head_circle[2][1] = p14[1];
	head_circle[2][2] = p14[2];

	head_circle[3][0] = p15[0];
	head_circle[3][1] = p15[1];
	head_circle[3][2] = p15[2];

	head_circle[4][0] = p16[0];
	head_circle[4][1] = p16[1];
	head_circle[4][2] = p16[2];

	head_circle[5][0] = p17[0];
	head_circle[5][1] = p17[1];
	head_circle[5][2] = p17[2];

	head_circle[6][0] = p18[0];
	head_circle[6][1] = p18[1];
	head_circle[6][2] = p18[2];

	head_circle[7][0] = p19[0];
	head_circle[7][1] = p19[1];
	head_circle[7][2] = p19[2];

	// fit of humeral head
	this->rms0 = 99999; 
	this->a0 = 0;
	this->b0 = 0;
	this->c0 = 0;
	this->r0 = 0;
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

	double c3[4];
	head_fit_x = c3[0] = this->a0;
	head_fit_y = c3[1] = this->b0;
	head_fit_z = c3[2] = this->c0;
	head_radius = c3[3] = this->r0;

	meshIndex = addMesh(vtkSphereSource::New(), c3);
	meshes.at(meshIndex).actor->GetProperty()->SetOpacity(0.5);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(1, 0, 0);

	this->rms0 = 99999; 
	this->a0 = 0;
	this->b0 = 0;
	this->c0 = 0;
	this->r0 = 0;
	Cx = 0;
	Cy = 0;
	Cz = 0;
}

void Humerus::HumerusMedialCondyle(double* p20, double* p21, double* p22, double* p23, double* p24, double* p25, double* p26, double* p27)
{
	int meshIndex;
	double Cx = 0;
	double Cy = 0;
	double Cz = 0;
	double medial_condyle[8][3];
	
	// define points for sphere-fit of medial condyle
	medial_condyle[0][0] = p20[0];
	medial_condyle[0][1] = p20[1];
	medial_condyle[0][2] = p20[2];

	medial_condyle[1][0] = p21[0];
	medial_condyle[1][1] = p21[1];
	medial_condyle[1][2] = p21[2];

	medial_condyle[2][0] = p22[0];
	medial_condyle[2][1] = p22[1];
	medial_condyle[2][2] = p22[2];

	medial_condyle[3][0] = p23[0];
	medial_condyle[3][1] = p23[1];
	medial_condyle[3][2] = p23[2];

	medial_condyle[4][0] = p24[0];
	medial_condyle[4][1] = p24[1];
	medial_condyle[4][2] = p24[2];

	medial_condyle[5][0] = p25[0];
	medial_condyle[5][1] = p25[1];
	medial_condyle[5][2] = p25[2];

	medial_condyle[6][0] = p26[0];
	medial_condyle[6][1] = p26[1];
	medial_condyle[6][2] = p26[2];

	medial_condyle[7][0] = p27[0];
	medial_condyle[7][1] = p27[1];
	medial_condyle[7][2] = p27[2];

	// fit
	this->rms0 = 99999; 
	this->a0 = 0;
	this->b0 = 0;
	this->c0 = 0;
	this->r0 = 0;
	Cx = 0;
	Cy = 0;
	Cz = 0;

	for (int i = 0; i < 8; ++i)
	{
		Cx = Cx + medial_condyle[i][0];
		Cy = Cy + medial_condyle[i][1];
		Cz = Cz + medial_condyle[i][2];
	}

	SphereFit(medial_condyle, 8, Cx/8, Cy/8, Cz/8);

	double c3[4];
	medial_fit_x = c3[0] = this->a0;
	medial_fit_y = c3[1] = this->b0;
	medial_fit_z = c3[2] = this->c0;
	medial_radius = c3[3] = this->r0;

	meshIndex = addMesh(vtkSphereSource::New(), c3);
	meshes.at(meshIndex).actor->GetProperty()->SetOpacity(0.5);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(1, 0, 0);

	this->rms0 = 99999; 
	this->a0 = 0;
	this->b0 = 0;
	this->c0 = 0;
	this->r0 = 0;
	Cx = 0;
	Cy = 0;
	Cz = 0;
}

void Humerus::HumerusLateralCondyle(double* p28, double* p29, double* p30, double* p31, double* p32, double* p33, double* p34, double* p35) 
{
	int meshIndex;
	double Cx = 0;
	double Cy = 0;
	double Cz = 0;
	double lateral_condyle[8][3];
	
	// define points for sphere-fit of medial condyle
	lateral_condyle[0][0] = p28[0];
	lateral_condyle[0][1] = p28[1];
	lateral_condyle[0][2] = p28[2];

	lateral_condyle[1][0] = p29[0];
	lateral_condyle[1][1] = p29[1];
	lateral_condyle[1][2] = p29[2];

	lateral_condyle[2][0] = p30[0];
	lateral_condyle[2][1] = p30[1];
	lateral_condyle[2][2] = p30[2];

	lateral_condyle[3][0] = p31[0];
	lateral_condyle[3][1] = p31[1];
	lateral_condyle[3][2] = p31[2];

	lateral_condyle[4][0] = p32[0];
	lateral_condyle[4][1] = p32[1];
	lateral_condyle[4][2] = p32[2];

	lateral_condyle[5][0] = p33[0];
	lateral_condyle[5][1] = p33[1];
	lateral_condyle[5][2] = p33[2];

	lateral_condyle[6][0] = p34[0];
	lateral_condyle[6][1] = p34[1];
	lateral_condyle[6][2] = p34[2];

	lateral_condyle[7][0] = p35[0];
	lateral_condyle[7][1] = p35[1];
	lateral_condyle[7][2] = p35[2];

	// fit
	this->rms0 = 99999; 
	this->a0 = 0;
	this->b0 = 0;
	this->c0 = 0;
	this->r0 = 0;
	Cx = 0;
	Cy = 0;
	Cz = 0;

	for (int i = 0; i < 8; ++i)
	{
		Cx = Cx + lateral_condyle[i][0];
		Cy = Cy + lateral_condyle[i][1];
		Cz = Cz + lateral_condyle[i][2];
	}

	SphereFit(lateral_condyle, 8, Cx/8, Cy/8, Cz/8);

	double c3[4];
	lateral_fit_x = c3[0] = this->a0;
	lateral_fit_y = c3[1] = this->b0;
	lateral_fit_z = c3[2] = this->c0;
	lateral_radius = c3[3] = this->r0;

	meshIndex = addMesh(vtkSphereSource::New(), c3);
	meshes.at(meshIndex).actor->GetProperty()->SetOpacity(0.5);
	meshes.at(meshIndex).actor->GetProperty()->SetColor(1, 0, 0);

	this->rms0 = 99999; 
	this->a0 = 0;
	this->b0 = 0;
	this->c0 = 0;
	this->r0 = 0;
	Cx = 0;
	Cy = 0;
	Cz = 0;
}

void Humerus::HumerusInclinationAndRetroversion(double* p29, double* p30, double* p31)
{
	// vektor1 von medial p30 nach posterior p31, also posterior-medial
	std::vector<double> v1(3);
	v1.at(0) = p31[0] - p30[0];
	v1.at(1) = p31[1] - p30[1];
	v1.at(2) = p31[2] - p30[2];
	
	double b1 = sqrt( pow( v1.at(0), 2) + pow(v1.at(1), 2) + pow(v1.at(2), 2) );

	v1.at(0) = v1.at(0) / b1;
	v1.at(1) = v1.at(1) / b1;
	v1.at(2) = v1.at(2) / b1;

	// vektor2 von medial p30 nach anterior p29, also anterior-medial
	std::vector<double> v2(3);
	v2.at(0) = p29[0] - p30[0];
	v2.at(1) = p29[1] - p30[1];
	v2.at(2) = p29[2] - p30[2];

	double b2 = sqrt( pow( v2.at(0), 2) + pow(v2.at(1), 2) + pow(v2.at(2), 2) );

	v2.at(0) = v2.at(0) / b2;
	v2.at(1) = v2.at(1) / b2;
	v2.at(2) = v2.at(2) / b2;

	// r als Normalenvektor der Ebene stellt zugleich die Halsachse dar
	std::vector<double> neck_axis(3);
	neck_axis = CrossProduct( v1, v2);
	
	std::vector<double> p(12); // center, normal, point1, point2
	p.at(0) = (p29[0] + p30[0] + p31[0]) / 3; 
	p.at(1) = (p29[1] + p30[1] + p31[1]) / 3;
	p.at(2) = (p29[2] + p30[2] + p31[2]) / 3;
	p.at(3) = neck_axis.at(0); 
	p.at(4) = neck_axis.at(1);
	p.at(5) = neck_axis.at(2);
	p.at(6) = p30[0] + 5 * (p29[0] - p30[0]); 
	p.at(7) = p30[1] + 5 * (p29[1] - p30[1]); 
	p.at(8) = p30[2] + 5 * (p29[2] - p30[2]);
	p.at(9) = p30[0] - 5 * (p31[0] - p30[0]); 
	p.at(10) = p30[1] - 5 * (p31[1] - p30[1]); 
	p.at(11) = p30[2] - 5 * (p31[2] - p30[2]);

	addMesh(vtkPlaneSource::New(), p );

	// neck achse auf die Koronalebene projizieren:
	std::vector<double> neck_axis_ap(3);
	
	// lambda berechnen:
	double lambda1 = axis[0] * neck_axis.at(0) + axis[1] * neck_axis.at(1) + axis[2] * neck_axis.at(2);

	// schnittpunkt auf AP-Ebene (= projizierter Vektor)
	neck_axis_ap.at(0) = neck_axis.at(0) + lambda1 * axis[0];
	neck_axis_ap.at(1) = neck_axis.at(1) + lambda1 * axis[1];
	neck_axis_ap.at(2) = neck_axis.at(2) + lambda1 * axis[2];

	// vektor wieder normieren
	b1 = sqrt( pow(neck_axis_ap.at(0), 2) + pow(neck_axis_ap.at(1), 2) + pow(neck_axis_ap.at(2), 2) );
	neck_axis_ap.at(0) = neck_axis_ap.at(0) / b1;
	neck_axis_ap.at(1) = neck_axis_ap.at(1) / b1;
	neck_axis_ap.at(2) = neck_axis_ap.at(2) / b1;

	//std::cout << "neck_axis: " << "\t" << neck_axis.at(0) << "\t" << neck_axis.at(1) << "\t" << neck_axis.at(2) << std::endl;
	//std::cout << "Neck-Axis-AP: " << "\t" << neck_axis_ap.at(0) << "\t" << neck_axis_ap.at(1) << "\t" << neck_axis_ap.at(2) << std::endl;

	// Winkel zwischen invertierter kranio-kaudale-Achse und neck_axis_ap berechnen
	double param1 = neck_axis_ap.at(0) * (-axis[6]) + neck_axis_ap.at(1) * (-axis[7]) + neck_axis_ap.at(2) * (-axis[8]);

	inclination = acos(param1) * (360/(2*PI));


	// neck achse auf die Axialebene projizieren 
	std::vector<double> neck_axis_kk(3);

	// lambda berechnen:
	lambda1 = (axis[6]) * neck_axis.at(0) + (axis[7]) * neck_axis.at(1) + (axis[8]) * neck_axis.at(2);

	// schnittpunkt auf AP-Ebene (= projizierter Vektor, je nachdem, wie Lambda orientiert ist wird projiziert. hier nach -1):
	neck_axis_kk.at(0) = neck_axis.at(0) - lambda1 * (axis[6]);
	neck_axis_kk.at(1) = neck_axis.at(1) - lambda1 * (axis[7]);
	neck_axis_kk.at(2) = neck_axis.at(2) - lambda1 * (axis[8]);


	// vektor wieder normieren
	b1 = sqrt( pow(neck_axis_kk.at(0), 2) + pow(neck_axis_kk.at(1), 2) + pow(neck_axis_kk.at(2), 2) );
	neck_axis_kk.at(0) = neck_axis_kk.at(0) / b1;
	neck_axis_kk.at(1) = neck_axis_kk.at(1) / b1;
	neck_axis_kk.at(2) = neck_axis_kk.at(2) / b1;

	//std::cout << "neck_axis: " << "\t" << neck_axis.at(0) << "\t" << neck_axis.at(1) << "\t" << neck_axis.at(2) << std::endl;
	//std::cout << "neck_axis_kk: " << "\t" << neck_axis_kk.at(0) << "\t" << neck_axis_kk.at(1) << "\t" << neck_axis_kk.at(2) << std::endl;

	// epicondyle_axis auf die Axialebene projizieren (es wird nach -z projiziert):
	std::vector<double> epicondyle_axis_kk(3);


	// lambda berechnen:
	double lambda2 = (axis[6]) * epicondyle_axis[0] + (axis[7]) * epicondyle_axis[1] + (axis[8]) * epicondyle_axis[2];

	// wenn lambda2 < 0 (hinter der ebene + projektion, sonst - projektion)
	// schnittpunkt auf KK-Ebene (= projizierter Vektor)
	if (lambda2 < 0)
	{
		epicondyle_axis_kk.at(0) = epicondyle_axis[0] + lambda2 * (axis[6]);
		epicondyle_axis_kk.at(1) = epicondyle_axis[1] + lambda2 * (axis[7]);
		epicondyle_axis_kk.at(2) = epicondyle_axis[2] + lambda2 * (axis[8]);
	}
	else
	{
		epicondyle_axis_kk.at(0) = epicondyle_axis[0] - lambda2 * (axis[6]);
		epicondyle_axis_kk.at(1) = epicondyle_axis[1] - lambda2 * (axis[7]);
		epicondyle_axis_kk.at(2) = epicondyle_axis[2] - lambda2 * (axis[8]);
	}

	// vektor wieder normieren
	b2 = sqrt( pow(epicondyle_axis_kk.at(0), 2) + pow(epicondyle_axis_kk.at(1), 2) + pow(epicondyle_axis_kk.at(2), 2) );
	epicondyle_axis_kk.at(0) = epicondyle_axis_kk.at(0) / b2;
	epicondyle_axis_kk.at(1) = epicondyle_axis_kk.at(1) / b2;
	epicondyle_axis_kk.at(2) = epicondyle_axis_kk.at(2) / b2;

	//std::cout << "epicondyle_axis: " << "\t" << epicondyle_axis[0] << "\t" << epicondyle_axis[1] << "\t" << epicondyle_axis[2] << std::endl;
	//std::cout << "epicondyle_axis_kk: " << "\t" << epicondyle_axis_kk.at(0) << "\t" << epicondyle_axis_kk.at(1) << "\t" << epicondyle_axis_kk.at(2) << std::endl;


	// Winkel zwischen epicondyle_axis_kk und neck_axis_kk berechnen
	double param2 = epicondyle_axis_kk.at(0) * neck_axis_kk.at(0) + epicondyle_axis_kk.at(1) * neck_axis_kk.at(1) + epicondyle_axis_kk.at(2) * neck_axis_kk.at(2);
	retroversion = acos(param2) * (360/(2*PI));

}

Humerus::~Humerus()
{
}
