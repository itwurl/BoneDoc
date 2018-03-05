#ifndef Anatomy_H
#define Anatomy_H

// c++
#include <vector>
#include <list>
#include <string>

// vtk
#include "vtkCutter.h"
#include "vtkOBBTree.h"
#include "vtkPolyData.h"
#include "vtkProperty.h"
#include "vtkPlane.h"
#include "vtkPolyDataReader.h"
#include "vtkPolyDataWriter.h"
#include "vtkSmartPointer.h"
#include "vtkSTLReader.h"
#include "vtkSTLWriter.h"
#include "vtkStripper.h"

static const float PI = 3.14159265;

class Anatomy {
protected:

    // parameters  n, x, p of plane n*(x-p)
    double distanceToPlane(double p[9]);

    // parameters [nx, ny, nz], [x, y, z], [px, py, pz] of plane n*(x-p)
    double distanceToPlane(double nx, double ny, double nz, double x, double y, double z, double px, double py, double pz);

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
    std::vector<double> CrossProduct(std::vector<double> const &v1, std::vector<double> const &v2) {
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

    // polydata-reader
    vtkSmartPointer<vtkPolyDataReader> readVTK; // = vtkSmartPointer<vtkPolyDataReader>::New();
    vtkSmartPointer<vtkSTLReader> readSTL;// = vtkSmartPointer<vtkSTLReader>::New();

    // anatomical mesh
    void SetAnatomicalMesh(const std::string path);
    vtkSmartPointer<vtkPolyData> anatomicalMesh;

    // anatomical landmarks size
    unsigned int anatomicalLandmarksSize;
    
    // anatomical landmarks
    void SetAnatomicalLandmarks(const std::string path);
    std::vector<std::vector<float>> anatomicalLandmarks;

    // estimate age, sex and side from file name
    void SetMetaInfo(const std::string path);

    void SetAnatomicalLandmarksSize(std::string configPath, std::string identifier);

public:
    Anatomy();
    ~Anatomy();
    
    // guessed probability for ethnic groups
    int asian;
    int caucasian;
    
private:

    // root squared average distance used for sphere-fit
    double RMS(double p[][3], int n, double xm, double ym, double zm, double r);

};

#endif // Anatomy_H


