#ifndef Anatomy_H
#define Anatomy_H

#include <vector>
#include <list>
#include <string>

#include "vtkActor.h"
#include "vtkCutter.h"
#include "vtkLineSource.h"
#include "vtkMapper.h"
#include "vtkOBBTree.h"
#include "vtkPolyData.h"
#include "vtkProperty.h"
#include "vtkPlane.h"
#include "vtkPlaneSource.h"
#include "vtkPolyDataMapper.h"
#include "vtkPolyDataReader.h"
#include "vtkPolyDataWriter.h"
#include "vtkSmartPointer.h"
#include "vtkSmoothPolyDataFilter.h"
#include "vtkSphereSource.h"
#include "vtkSTLReader.h"
#include "vtkSTLWriter.h"
#include "vtkStripper.h"

static const float PI = 3.14159265;

class Anatomy
{
protected:

	// data-struct for meshes
	struct mesh
	{
		vtkActor *actor;
		vtkMapper *mapper;
		vtkPolyData *anatomicalMesh;

		// params != var's !
		mesh(vtkPolyData* ppolydata, vtkActor* pactor, vtkPolyDataMapper* pmapper)
		{ 
			anatomicalMesh = ppolydata; actor = pactor; mapper = pmapper;
		};
	};

	// parameters  n, x, p of plane n*(x-p)
	double distanceToPlane(double p[9]);

	// parameters [nx, ny, nz], [x, y, z], [px, py, pz] of plane n*(x-p)
	double distanceToPlane(double nx, double ny, double nz, double x, double y, double z, double px, double py, double pz);

	// Template für Pointer und Pointer
	template <typename M, typename P> int addMesh(M mesh, P p)
	{
		return 0;
	}
	// Spezialisierung für vtkSphereSource und double
	int addMesh(vtkSphereSource* sphere, double* p ) // 2. parameter = center & normal
	{
		vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
		mapper->SetInputConnection(sphere->GetOutputPort());

		vtkActor* actor = vtkActor::New();

		sphere->SetRadius( p[3] );
		sphere->SetPhiResolution( 36 );
		sphere->SetThetaResolution( 36 );
		sphere->SetCenter( p[0], p[1], p[2] );

		actor->SetMapper(mapper);
		actor->GetProperty()->SetColor( 0, 1, 0 );

		mesh m(sphere->GetOutput(), actor, mapper);
		meshes.push_back(m);

		return meshes.size()-1;
	}

	// Template für Pointer und std::vector const
	//template <typename M, typename P> int addMesh(M* mesh, std::vector<P> const &p);

	// Spezialisierung für vtkPlaneSource und double
	int addMesh(vtkPlaneSource* plane, std::vector<double> const &p ) //center, normal, point1, point2 
	{ 
		vtkActor* actor = vtkActor::New();
		vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();

		mapper->SetInputData( plane->GetOutput() );
		actor->SetMapper( mapper );

		plane->SetCenter(p.at(0), p.at(1), p.at(2) );
		plane->SetNormal(p.at(3), p.at(4), p.at(5) );
		plane->Update();

		actor->GetProperty()->SetColor(0.0, 0.0, 1.0);

		mesh m(plane->GetOutput(), actor, mapper);
		meshes.push_back(m);

		return meshes.size()-1;
	}

	// Spezialisierung für vtkSphereSource und double
	int addMesh(vtkSphereSource* sphere, std::vector<double> const &p ) // 2. parameter = center & normal
	{
		vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
		vtkActor* actor = vtkActor::New();
		
		mapper->SetInputConnection(sphere->GetOutputPort());

		sphere->SetRadius( p.at(3) );
		sphere->SetPhiResolution( 36 );
		sphere->SetThetaResolution( 36 );
		sphere->SetCenter( p.at(0), p.at(1), p.at(2) );

		actor->SetMapper(mapper);
		actor->GetProperty()->SetColor( 0, 1, 0 );

		mesh m(sphere->GetOutput(), actor, mapper);
		meshes.push_back(m);

		return meshes.size()-1;
	}

	int addMesh(vtkLineSource* line, double* p ) // 2. parameter = p1 & p2
	{
		line->SetPoint1(p[0], p[1], p[2]);
		line->SetPoint2(p[3], p[4], p[5]);
		line->Update();
		vtkPolyDataMapper* mapper = vtkPolyDataMapper::New();
		mapper->SetInputConnection(line->GetOutputPort());
		vtkActor* actor = vtkActor::New();
		actor->SetMapper(mapper);
		actor->GetProperty()->SetColor( 0, 0, 1 );
		mesh m(line->GetOutput(), actor, mapper);
		meshes.push_back(m);
		return meshes.size()-1;
	}

	// Closest point (in polydata, outgoing from p) found in cp[0..2] and id cp[4] will be written back to 'cp'
	void getClosestPointFromMesh(const std::vector <float> p, double* cp, vtkPolyData* anatomicalMesh);

	// defines coordinate system based on 2 vectors (mediolateral and longitudinal), ml becomes new, lon stayed (order of parameter is important)
	void setCoordinateSystem(double vectors[6], std::string side);

	void setCoordinateSystem(double ml_x, double ml_y, double ml_z, double lon_x, double lon_y, double lon_z, std::string side);

	// normal of plane, point on plane and estimated center of contour found by cuttinng plane and anatomicalMesh, returns 0 if contour could not be defined
	void getCenterOfIntersectionContour(vtkPolyData* polyData, double* n, double* p, double* c);

	// normal of plane, point on plane and estimated center of contour found by cuttinng plane and anatomicalMesh
	void getCenterOfIntersectionContour(vtkPolyData* polyData, double nx, double ny, double nz, double px, double py, double pz, double* c);

	// get most lateral, most medial, most posterior and most anterior point from contour at 'fem_cut_center_dist'
	//void getOffsetAndWidthFromContour(vtkPolyData* polyData, double* fem_cut_center_dist, double* p19, double* p20, double* p21, double* p22);

	// line fit by estimating three main principle components
	void getLineFit(std::vector<std::vector<double>>, int n, double* result);

	// characteristic polynom
	void getCharacteristicalPolynom(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33, double* result);

	// eigenvector (this implementation estimates the one which lowest eigenvalue)
	void getEigenvector(double eigenvalue_x, double eigenvalue_y, double eigenvalue_z, double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33, double* result);

	// axis based on calculated coordinate system
	double axis[9]; 

	double rms0;
	double a0;
	double b0;
	double c0;
	double r0;
	double distance;

	// spherefit as defined in [Philip Schneider and David H Eberly. Geometric tools for computer graphics. Morgan Kaufmann, 2002.]
	void SphereFit(double p[][3], int n, double ai, double bi, double ci);

	// crossproduct as defined in [https://de.wikipedia.org/wiki/Kreuzprodukt]
	template <typename T> std::vector<T> CrossProduct(std::vector<T> const &v1, std::vector<T> const &v2);
	std::vector<double> CrossProduct(std::vector<double> const &v1, std::vector<double> const &v2)
	{
		std::vector<double> r(v1.size());
		r[0] = v1[1] * v2[2] - v1[2] * v2[1];
		r[1] = v1[2] * v2[0] - v1[0] * v2[2];
		r[2] = v1[0] * v2[1] - v1[1] * v2[0];
		return r;
	}


	std::string sex;
	std::string side;
	std::string age;

	// euclidean distance between xa, yb and zc
	double getDistance(double p1x, double p1y, double p1z, double p2x, double p2y, double p2z);
	double getDistance(double p1[3], double p2[3]);

	// anatomical mesh
	vtkPolyData* LoadAnatomicalMesh(const std::string path);
	vtkPolyData* anatomicalMesh;

	// anatomical landmarks
	std::vector<std::vector<float>> LoadAnatomicalLandmarks(const std::string path);
	std::vector<std::vector<float>> anatomicalLandmarks;

	// estimate age, sex and side from file name
	void DefineSideAgeSexFromFileName(const std::string path);


public:
	Anatomy();
	~Anatomy();

	// meshes must be public accessible due to viewer related handling
	std::vector<mesh> meshes;

	void setSide(std::string sideID); // change side 
	void setSex(std::string sexID); // and sex of anatomy

	void smoothAndSaveMesh(std::string file); // mesh smoothing

private:

	// root squared average distance used for sphere-fit
	double RMS(double p[][3], int n, double xm, double ym, double zm, double r);


};

#endif // Anatomy_H


