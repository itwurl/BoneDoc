#include "Anatomy.h"




Anatomy::Anatomy() {}

void Anatomy::getClosestPointFromMesh(const std::vector<float> p, double* cp, vtkPolyData* polyData)
{
	int min_id = 0;
	double min = 9999.99;

	for (int i = 0; i < polyData->GetNumberOfPoints(); i++)
	{
		double pi[3];
		polyData->GetPoint(i, pi);

		double temp = sqrt( pow(p.at(0)-pi[0], 2) + pow(p.at(1)-pi[1], 2) + pow(p.at(2)-pi[2], 2) );
		if (temp < min)
		{
			min = temp;
			min_id = i;
		}

	}

	polyData->GetPoint(min_id, cp);
	cp[4] = min_id;
}

double Anatomy::distanceToPlane(double p[9])
{
	return ((p[0]*p[3]) - (p[0]*p[6])) + ((p[1]*p[4]) - (p[1]*p[7])) + ((p[2]*p[5]) - (p[2]*p[8]));
}

double Anatomy::distanceToPlane(double nx, double ny, double nz, double x, double y, double z, double px, double py, double pz)
{
	return ((nx*x) - (nx*px)) + ((ny*y) - (ny*py)) + ((nz*z) - (nz*pz));
}

void Anatomy::setCoordinateSystem(double vectors[6], std::string side) {

	if ((side != "RIGHT") && (side != "LEFT")) {
		std::cout << "Unknown side - can not define coordinate system!" << std::endl;
		return;
	}

	// norm vectors
	double bx = sqrt( pow(vectors[0], 2) + pow(vectors[1], 2) + pow(vectors[2], 2) );
	double by = sqrt( pow(vectors[3], 2) + pow(vectors[4], 2) + pow(vectors[5], 2) );

	vectors[0] = vectors[0] / bx;
	vectors[1] = vectors[1] / bx;
	vectors[2] = vectors[2] / bx;
	
	vectors[3] = vectors[3] / by;
	vectors[4] = vectors[4] / by;
	vectors[5] = vectors[5] / by;

	if (side == "RIGHT") {
		// x - medio-lateral axis X longitudinal axis (should points anterior)
		axis[0] = (vectors[1]*vectors[5])-(vectors[2]*vectors[4]);
		axis[1] = (vectors[2]*vectors[3])-(vectors[0]*vectors[5]);
		axis[2] = (vectors[0]*vectors[4])-(vectors[1]*vectors[3]);

		// y - mediolateral (ML) axis, vectorsZ X AP (should points medial)
		axis[3] = (vectors[4]*axis[2])-(vectors[5]*axis[1]);
		axis[4] = (vectors[5]*axis[0])-(vectors[3]*axis[2]);
		axis[5] = (vectors[3]*axis[1])-(vectors[4]*axis[0]);
	}
	else if (side == "LEFT") {
		// x - anteroposterior (AP) axis, vectorsZ X vectorsY (should points anterior)
		axis[0] = (vectors[4]*vectors[2])-(vectors[5]*vectors[1]);
		axis[1] = (vectors[5]*vectors[0])-(vectors[3]*vectors[2]);
		axis[2] = (vectors[3]*vectors[1])-(vectors[4]*vectors[0]);

		// y - mediolateral (ML) axis, AP X vectorsZ (should points medial)
		axis[3] = (axis[1]*vectors[5])-(axis[2]*vectors[4]);
		axis[4] = (axis[2]*vectors[3])-(axis[0]*vectors[5]);
		axis[5] = (axis[0]*vectors[4])-(axis[1]*vectors[3]);
	}

	// z - longitudinal axis, vectorsZ (should points kranial)
	axis[6] = vectors[3];
	axis[7] = vectors[4];
	axis[8] = vectors[5];

	std::cout << "Local coordinate system for " << side << " side:" << std::endl;
	std::cout << "X: " << axis[0] << " "<< axis[1] << " " << axis[2] << std::endl;
	std::cout << "Y: " << axis[3] << " "<< axis[4] << " " << axis[5] << std::endl;
	std::cout << "Z: " << axis[6] << " "<< axis[7] << " " << axis[8] << std::endl << std::endl;
}

void Anatomy::setCoordinateSystem(double ml_x, double ml_y, double ml_z, double lon_x, double lon_y, double lon_z, std::string side)
{
	if ((side != "RIGHT") && (side != "LEFT"))
	{
		std::cout << "Unknown side - can not define coordinate system!" << std::endl;
		return;
	}

	// norm vectors
	double bx = sqrt( pow(ml_x, 2) + pow(ml_y, 2) + pow(ml_z, 2) );
	double by = sqrt( pow(lon_x, 2) + pow(lon_y, 2) + pow(lon_z, 2) );

	ml_x = ml_x / bx;
	ml_y = ml_y / bx;
	ml_z = ml_z / bx;
	
	lon_x = lon_x / by;
	lon_y = lon_y / by;
	lon_z = lon_z / by;

	if (side == "RIGHT")
	{
		// x - medio-lateral axis X longitudinal axis (should points anterior)
		axis[0] = (ml_y*lon_z)-(ml_z*lon_y);
		axis[1] = (ml_z*lon_x)-(ml_x*lon_z);
		axis[2] = (ml_x*lon_y)-(ml_y*lon_x);

		// y - mediolateral (ML) axis, vectorsZ X AP (should points medial)
		axis[3] = (lon_y*axis[2])-(lon_z*axis[1]);
		axis[4] = (lon_z*axis[0])-(lon_x*axis[2]);
		axis[5] = (lon_x*axis[1])-(lon_y*axis[0]);
	}
	else if (side == "LEFT")
	{
		// x - anteroposterior (AP) axis, vectorsZ X vectorsY (should points anterior)
		axis[0] = (lon_y*ml_z)-(lon_z*ml_y);
		axis[1] = (lon_z*ml_x)-(lon_x*ml_z);
		axis[2] = (lon_x*ml_y)-(lon_y*ml_x);

		// y - mediolateral (ML) axis, AP X vectorsZ (should points medial)
		axis[3] = (axis[1]*lon_z)-(axis[2]*lon_y);
		axis[4] = (axis[2]*lon_x)-(axis[0]*lon_z);
		axis[5] = (axis[0]*lon_y)-(axis[1]*lon_x);
	}

	// z - longitudinal axis, vectorsZ (should points kranial)
	axis[6] = lon_x;
	axis[7] = lon_y;
	axis[8] = lon_z;

	std::cout << "local coordinate system for " << side << " side:" << std::endl;
	std::cout << "X: " << axis[0] << " "<< axis[1] << " " << axis[2] << std::endl;
	std::cout << "Y: " << axis[3] << " "<< axis[4] << " " << axis[5] << std::endl;
	std::cout << "Z: " << axis[6] << " "<< axis[7] << " " << axis[8] << std::endl << std::endl;
}

void Anatomy::SphereFit(double p[][3], int n, double ai, double bi, double ci)
{
	// print("init ...")
	double L = 0;
	double Li = 0;
	double La = 0;
	double Lb = 0;
	double Lc = 0;
	double Cx = 0;
	double Cy = 0;
	double Cz = 0;

	for (int l=0; l < n; l++) {
		Cx = Cx + p[l][0] / n;
		Cy = Cy + p[l][1] / n;
		Cz = Cz + p[l][2] / n;
		Li = getDistance( p[l][0], p[l][1], p[l][2], ai, bi, ci );
		L = L + Li;
		La = La + ((ai-p[l][0])/Li);
		Lb = Lb + ((bi-p[l][1])/Li);
		Lc = Lc + ((ci-p[l][2])/Li);
	}

	L = L/n;
	La = La/n;
	Lb = Lb/n;
	Lc = Lc/n;

	if ( rms0 > float( RMS(p, n, Cx+(L*La), Cy+(L*Lb), Cz+(L*Lc), L) ) ) {
		//qDebug() << "old rms: " << rms0 << endl;

		rms0 = float( RMS(p, n, Cx+(L*La), Cy+(L*Lb), Cz+(L*Lc), L) );
		//qDebug() << "new rms: " << rms0 << endl;

		//qDebug() << "Center/Radius: " << Cx+(L*La) << ":" << Cy+(L*Lb) << ":" << Cz+(L*Lc) << ":" << L << endl;
		//qDebug() << "---" << endl;

		SphereFit(p, n, Cx+(L*La), Cy+(L*Lb), Cz+(L*Lc));
	} else {
		//qDebug() << Cx+(L*La) << ":" << Cy+(L*Lb) << ":" << Cz+(L*Lc) << ":" << L << endl;
		//qDebug() << "best sphere-fit done ..." << endl;
		//qDebug() << "---" << endl;
	
		a0 = Cx+(L*La);
		b0 = Cy+(L*Lb);
		c0 = Cz+(L*Lc);
		r0 = L;
		distance = L;

	}
}

double Anatomy::RMS(double p[][3], int n, double xm, double ym, double zm, double r)
{
	double r1 = 0;
	double r2 = 0;
	for (int i = 0; i < 8; i++) {
		r1 = sqrt( pow(p[i][0]-xm, 2) + pow(p[i][1]-ym, 2) + pow(p[i][2]-zm, 2) );
		r2 = r2 + pow(r1-r, 2);
	}
	//rms = "%.2f" % math.ceil( (math.sqrt(r2/n) * 100) / 100)
	double rms = sqrt(r2/n);
	return (float)((int)(rms*10000))/10000;
}

double Anatomy::getDistance(double p1x, double p1y, double p1z, double p2x, double p2y, double p2z)
{
	return sqrt( pow(p1x - p2x, 2) + pow(p1y - p2y, 2) + pow(p1z - p2z, 2) );
}

double Anatomy::getDistance(double p1[3], double p2[3])
{
	return sqrt( pow(p1[0]-p2[0], 2) + pow(p1[1]-p2[1], 2) + pow(p1[2]-p2[2], 2) );
}

void Anatomy::getCenterOfIntersectionContour(vtkPolyData* polydata, double* n, double* p, double* c)
{
	// set result to 0
	c[0] = c[1] = c[2] = 0;

	// plane
	vtkSmartPointer<vtkPlane> vtkplane = vtkSmartPointer<vtkPlane>::New();
	vtkplane->SetOrigin(p[0], p[1], p[2]);
	vtkplane->SetNormal(n[0], n[1], n[2]);

	// surface cut with plane
	vtkSmartPointer<vtkCutter> cutEdges = vtkSmartPointer<vtkCutter>::New();
	cutEdges->SetInputData(polydata);
	cutEdges->SetCutFunction(vtkplane);

	// generates triangle poly-lines from input polygon
	vtkSmartPointer<vtkStripper> cutStrips = vtkSmartPointer<vtkStripper>::New();
	cutStrips->SetInputConnection(cutEdges->GetOutputPort());
	cutStrips->Update();
	vtkSmartPointer<vtkPolyData> cutPoly = vtkSmartPointer<vtkPolyData>::New();
	cutPoly->SetPoints(cutStrips->GetOutput()->GetPoints());
	cutPoly->SetPolys(cutStrips->GetOutput()->GetLines());

	// crash's may occure if no suitable cut were done - return then
	if (cutPoly->GetNumberOfPoints() == 0)
	{
		std::cout << "could not define intersection contour!" << std::endl;
	}
	else
	{
		// get the cutting-contours center
		cutPoly->GetCenter(c);
	}

}

void Anatomy::getCenterOfIntersectionContour(vtkPolyData* polydata, double nx, double ny, double nz, double px, double py, double pz, double* c)
{
	c[0] = c[1] = c[2] = 0;
	// plane
	vtkSmartPointer<vtkPlane> vtkplane = vtkSmartPointer<vtkPlane>::New();
	vtkplane->SetOrigin(px, py, pz);
	vtkplane->SetNormal(nx, ny, nz);

	// surface cut with plane
	vtkSmartPointer<vtkCutter> cutEdges = vtkSmartPointer<vtkCutter>::New();
	cutEdges->SetInputData(polydata);
	cutEdges->SetCutFunction(vtkplane);

	// generates triangle poly-lines from input polygon
	vtkSmartPointer<vtkStripper> cutStrips = vtkSmartPointer<vtkStripper>::New();
	cutStrips->SetInputConnection(cutEdges->GetOutputPort());
	cutStrips->Update();
	vtkSmartPointer<vtkPolyData> cutPoly = vtkSmartPointer<vtkPolyData>::New();
	cutPoly->SetPoints(cutStrips->GetOutput()->GetPoints());
	cutPoly->SetPolys(cutStrips->GetOutput()->GetLines());

	// crash's may occure if no suitable cut were done - return then
	if (cutPoly->GetNumberOfPoints() == 0)
	{
		std::cout << "could not define intersection contour!" << std::endl;
		return;
	}
	else
	{
		// get the cutting-contours center
		cutPoly->GetCenter(c);
	}
}

void Anatomy::getLineFit(std::vector<std::vector<double>> points, int n, double* result)
{
	double center[3] = {0, 0, 0};
	for (int i = 0; i < n; i++)
	{
		center[0] += points[i].at(0);
		center[1] += points[i].at(1);
		center[2] += points[i].at(2);
	}
	center[0] /= n;
	center[1] /= n;
	center[2] /= n;

    double Mxx = 0;
    double Myy = 0;
    double Mzz = 0;
    double Mxy = 0;
    double Myz = 0;
    double Mzx = 0;

    for (int i = 0; i < n; i++)
	{
        // von aktuellem Punkt den Schwerpunkt subtrahieren:
        double x = points[i][0] - center[0];
		double y = points[i][1] - center[1];
		double z = points[i][2] - center[2];

	    // Matrix "inertia tensor of centroidal moment" definieren
        Mxx += x * x;
        Myy += y * y;
        Mzz += z * z;
        Mxy += x * y;
        Myz += y * z;
        Mzx += z * x;
    }

    getCharacteristicalPolynom(Mxx, Mxy, Mzx, Mxy, Myy, Myz, Mzx, Myz, Mzz, result);
}

void Anatomy::getCharacteristicalPolynom(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33, double* result)
{
    double a = 1;
    double b = -1 * (a11 + a22 + a33);
    double c = (a22 * a33 - a23 * a32) + (a11 * a33 - a13 * a31) + (a11 * a22 - a12 * a21);
    double d = -1 * ((a11 * a22 * a33) + (a12 * a23 * a31) + (a13 * a21 * a32) - (a13 * a22 * a31) - (a12 * a21 * a33) - (a11 * a23 * a32));

    double p = (3 * a * c - (b * b)) / (3 * (a * a));
    double q = (2 * (b * b * b)) / (27 * (a * a * a)) - ((b * c) / (3 * (a * a))) + (d / a);

    double dis = ((q / 2) * (q / 2)) + ((p / 3) * (p / 3) * (p / 3));

    double y2 = -sqrt(-1.33333333 * p) * cos(0.33333333 * acos((-q / 2) * sqrt(-27 / (p * p * p)))+(PI / 3)); 
    double y1 = sqrt(-1.33333333 * p) * cos(0.33333333 * acos(-q / 2 * sqrt(-27 / (p * p * p))));
    double y3 = -sqrt(-1.33333333 * p) * cos(0.33333333 * acos(-q / 2 * sqrt(-27 / (p * p * p))) - PI / 3); 

    double eigenvalue2 = y2 - b / (3 * a);
    double eigenvalue1 = y1 - b / (3 * a);
    double eigenvalue3 = y3 - b / (3 * a);

    getEigenvector(eigenvalue1, eigenvalue2, eigenvalue3, a11, a12, a13, a21, a22, a23, a31, a32, a33, result);
}

void Anatomy::getEigenvector(double eigenvalue1, double eigenvalue2, double eigenvalue3, double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33, double* result)
{
	int min = 0;
	double eigenvalue = 0;

    if (eigenvalue1 > eigenvalue2)
	{
        if (eigenvalue1 > eigenvalue3)
		{
            eigenvalue = eigenvalue1;
        }
    }
    if (eigenvalue2 > eigenvalue1)
	{
        if (eigenvalue2 > eigenvalue3)
		{
             eigenvalue = eigenvalue2;
        }
    }
    if (eigenvalue3 > eigenvalue1)
	{
        if (eigenvalue3 > eigenvalue2)
		{
            eigenvalue = eigenvalue3;
        }
    }

	// von der Hauptdiagonale den gr�ssten Eigenwert abziehen und neue b-Matrix erstellen
	double b11 = a11 - eigenvalue;
	double b12 = a12;
	double b13 = a13;
	double b21 = a21;
	double b22 = a22 - eigenvalue;
	double b23 = a23;
	double b31 = a31;
	double b32 = a32;
	double b33 = a33 - eigenvalue;

	if (b31 != 0)
	{
		// Elimination von b31
		double mult2 = b21;
		double mult3 = b31;

		b21 = b21* mult3;
		b22 = b22* mult3;
		b23 = b23* mult3;

		b31 = b31* mult2;
		b32 = b32* mult2;
		b33 = b33* mult2;

		b31 = b31- b21;
		b32 = b32- b22;
		b33 = b33- b23;
	}

	if (b21 != 0)
	{
		// Elimination von b21
		double mult1 = b11;
		double mult2 = b21;

		b11 = b11* mult2;
		b12 = b12* mult2;
		b13 = b13* mult2;

		b21 = b21* mult1;
		b22 = b22* mult1;
		b23 = b23* mult1;

		b21 = b21- b11;
		b22 = b22- b12;
		b23 = b23- b13;
	}
	if ( b32 != 0)
	{
		// Elimination von b32
		double mult2 = b22;
		double mult3 = b32;

		b22 = b22* mult3;
		b23 = b23* mult3;

		b32 = b32* mult2;
		b33 = b33* mult2;

		b32 = b32- b22;
		b33 = b33- b23;
	}

	// heuristik zur Festellung des L�sungsvektors
	
	result[0] = 0;
	result[1] = 0;
	result[2] = 0;

	// x3 muss 0, damit freiw�hlbar, sein !
	result[2] = 1;
	result[1] = -(b23 * result[2] / b22);
	result[0] = ((-b12 * result[1]) / b11) - ((b13 * result[2]) / b11);

	// NORMIEREN!!!!!!!!
	double bn = sqrt(result[0] * result[0] + result[1] * result[1] + result[2] * result[2]);
	if (bn > 0)
	{
		result[0] = result[0] / bn;
		result[1] = result[1] / bn;
		result[2] = result[2] / bn;
	}

}

void Anatomy::setSide(std::string sideID)
{
	// transform tu upper case
	std::transform(sideID.begin(), sideID.end(), sideID.begin(), ::toupper);

	if ((sideID == "L") || (sideID == "LEFT"))
	{
		side = "LEFT";
	}
	else if ((sideID == "R") || (sideID == "RIGHT"))
	{
		side = "RIGHT";
	}
	else 
	{
		side = "";
		std::cout << "could not define side!" << std::endl;
	}
}

void Anatomy::setSex(std::string sexID)
{
	// transform tu upper case
	std::transform(sexID.begin(), sexID.end(), sexID.begin(), ::toupper);

	if ((sexID == "M") || (sexID == "MALE"))
	{
		sex = "MALE";
	}
	else if ((sexID == "F") || (sexID == "FEMALE"))
	{
		sex = "FEMALE";
	}
	else 
	{
		sex = "";
		std::cout << "could not define sex!" << std::endl;
	}
}

void Anatomy::smoothAndSaveMesh(std::string file)
{
	vtkSmartPointer<vtkPolyDataReader> reader = vtkSmartPointer<vtkPolyDataReader>::New();
	vtkSmartPointer<vtkPolyDataWriter> writer = vtkSmartPointer<vtkPolyDataWriter>::New();
	vtkSmartPointer<vtkSTLWriter> stlWriter = vtkSmartPointer<vtkSTLWriter>::New();
	vtkSmartPointer<vtkSmoothPolyDataFilter> smoothed = vtkSmartPointer<vtkSmoothPolyDataFilter>::New();

	// load (only vtk yet)
	reader->SetFileName(file.c_str());
	reader->Update();

	// laplace smoothing with predefined parameters
	smoothed->SetInputData(reader->GetOutput());
	smoothed->SetNumberOfIterations( 2 );              // default-parameters: 20|0.1 seem to be good defaults
	smoothed->SetRelaxationFactor( 0.6 );
	smoothed->Update();

	writer->SetFileName(file.c_str());
	writer->SetInputData( smoothed->GetOutput() );
	writer->SetFileTypeToASCII();
	writer->Write();

	// update anatomicalMesh
	meshes.clear();
	this->anatomicalMesh = LoadAnatomicalMesh(file.c_str());

}

std::vector<std::vector<float>> Anatomy::LoadAnatomicalLandmarks(const std::string path) {
	std::vector<std::vector<float>> ret;

        // 
        if (path.length() < 4)
            return ret;
        
	// make file ending great (again)
	std::string tmp = "";
	tmp.resize(path.size());
	std::transform(path.begin(), path.end(), tmp.begin(), toupper);

	// check for supported file type
	if (tmp.substr(tmp.length() - 4, 4) != "FCSV") {
		std::cout << "File format not supported!" << std::endl;
		return ret;
	}

	ifstream inStream;
	inStream.open(path);

	unsigned int n = 0;
	std::string name = "";
	std::string line = "";

	if (inStream.is_open()) {
		while (getline(inStream, line)) {

			// name for dataset
			if (line.compare(0, 9, "# name = ") == 0)
				name = line.substr(9, line.length() - 10);


			// catch number of points
			if (line.compare(0, 14, "# numPoints = ") == 0)
				n = stoi(line.substr(14, line.length() - 15));
			
			// catch the landmark-coordinates
			if (!(name.empty()) && (line.compare(0, name.length(), name) == 0)) {

				int pos1 = 0;
				int pos2 = 1;

				std::list<float> tmp;

				// do not consider last occurence of ","
				for (size_t i = 0; i < line.size() - 2; i++) {

					if (line.compare(i, 1, ",") == 0) {
						if (pos2 <= pos1) {
							pos2 = i;
							tmp.push_back(std::stod(line.substr(pos1 + 1, pos2 - pos1 - 1)));
							pos1 = pos2;
						}
						else
							pos1 = i;
					}

				}

				// fill 3d float vector element 
				auto it = tmp.begin();
				ret.push_back({ *it, *(++it), *(++it) });

			}

		}

		inStream.close();

	}
	else
		std::cout << "Could not read file: " + path << std::endl;

	return ret;
}

vtkPolyData* Anatomy::LoadAnatomicalMesh(const std::string path) {

	// make file ending great (again)
	std::string tmp = "";
	tmp.resize(path.size());
	std::transform(path.begin(), path.end(), tmp.begin(), toupper);
	tmp = tmp.substr(tmp.length() - 3, 3);

	// check for supported file type
	if ((tmp != "STL") && (tmp != "VTK")) {
		std::cout << "File format not supported!" << std::endl;
		return nullptr;
	}

	vtkSmartPointer<vtkPolyData> ret = vtkSmartPointer<vtkPolyData>::New();
	
	vtkSmartPointer<vtkPolyDataReader> readVTK = vtkSmartPointer<vtkPolyDataReader>::New();
	vtkSmartPointer<vtkSTLReader> readSTL = vtkSmartPointer<vtkSTLReader>::New();

	if (tmp == "VTK") {
		readVTK->SetFileName(path.c_str());
		readVTK->Update();
		ret = readVTK->GetOutput();
	}
	else if (tmp == "STL") {
		readSTL->SetFileName(path.c_str());
		readSTL->Update();
		ret = readSTL->GetOutput();
	}

	// VTK-BUG! strange bug occures if using smart pointer for vtkActor (anatomicalMesh can not be loaded somehow)
	vtkActor* actor = vtkActor::New();

	//vtkPolyDataMapper*mapper = vtkPolyDataMapper::New();
	//vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
	vtkSmartPointer<vtkPolyDataMapper> mapper = vtkSmartPointer<vtkPolyDataMapper>::New();

	mapper->SetInputData(ret);
	actor->SetMapper(mapper);
	actor->GetProperty()->SetOpacity(1);

	mesh m(ret, actor, mapper);
	meshes.push_back(m);

	return ret;
}

void Anatomy::DefineSideAgeSexFromFileName(const std::string path) {

	// Ausgabe und Anzeige aller ermittelten Parameter
	// hierbei ist die Anatomie und NUR der ermittelte Dateiname ben�tigt.
	int pos = path.find_last_of("/");
	
	std::string file = path.substr(pos + 1, path.length() - (pos + 1));

	// separator '-' must be found
	pos = file.find("-");
	
	if (pos <= 0) {
		
		// make 'file' great again
		std::transform(file.begin(), file.end(), file.begin(), ::toupper);

		// try another approach to find at least 'side':
		if (file.find("LEFT") != std::string::npos)
			this->side = "LEFT";
		else if (file.find("RIGHT") != std::string::npos)
			this->side = "RIGHT";		
		else
			this->side = "";

		this->sex = "";
		this->age = "";
		return;
	}
	
	// set sex found at 4 position after '-'
	std::string sex = file.substr(pos + 4, 1);
	std::transform(sex.begin(), sex.end(), sex.begin(), ::toupper);

	if (sex.compare("M") == 0) {
		this->sex = "MALE";
	} else if (sex.compare("F") == 0) {
		this->sex = "FEMALE";
	} else
		this->sex = "";

	// and side on first position after '-'
	std::string side = file.substr(pos + 1, 1);
	std::transform(side.begin(), side.end(), side.begin(), ::toupper);
	
	if (side.compare("L") == 0) {
		this->side = "LEFT";
	} else if (side.compare("R") == 0) {
		this->side = "RIGHT";
	} else
		this->side = "";

	// and age on second position after '-' (two places)
	std::string age = file.substr(pos + 2, 2);

	if (age != "XX")
		this->age = age;
	else
		this->age = "";
}

Anatomy::~Anatomy() {}