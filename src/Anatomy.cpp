#include "Anatomy.h"

Anatomy::Anatomy() {
    readVTK = vtkSmartPointer<vtkPolyDataReader>::New();
    readSTL = vtkSmartPointer<vtkSTLReader>::New();
    anatomicalMesh = vtkSmartPointer<vtkPolyData>::New();
}

void Anatomy::getClosestPointFromMesh(const vector<double> p, double* cp, vtkPolyData* polyData) {
    int min_id = 0;
    double min = 9999.99;

    for (int i = 0; i < polyData->GetNumberOfPoints(); i++) {
        double pi[3];
        polyData->GetPoint(i, pi);
        double temp = sqrt( pow(p.at(0)-pi[0], 2) + pow(p.at(1)-pi[1], 2) + pow(p.at(2)-pi[2], 2) );
        
        if (temp < min) {
            min = temp;
            min_id = i;
        }
        
    }

    polyData->GetPoint(min_id, cp);
    cp[4] = min_id;
}

double Anatomy::distanceToPlane(double p[9]) {
    return ((p[0] * p[3]) - (p[0] * p[6])) + ((p[1] * p[4]) - (p[1] * p[7])) + ((p[2] * p[5]) - (p[2] * p[8]));
}

double Anatomy::distanceToPlane(double nx, double ny, double nz, double x, double y, double z, double px, double py, double pz) {
    return ((nx * x) - (nx * px)) + ((ny * y) - (ny * py)) + ((nz * z) - (nz * pz));
}

void Anatomy::SetCoordinateSystem()
{
    if ((side != "RIGHT") && (side != "LEFT"))
    {
        cout << "Unknown side - can not define coordinate system!" << endl;
        return;
    }

    // medio-lateral and cranio-caudal axis 
    double temp[6];
    temp[0] = axis[0];
    temp[1] = axis[1];
    temp[2] = axis[2];
    temp[3] = axis[3];
    temp[4] = axis[4];
    temp[5] = axis[5];
    axis[6] = axis[3];
    axis[7] = axis[4];
    axis[8] = axis[5];

    if (side == "RIGHT")
    {
        // x - medio-lateral axis X cranio-caucal axis (should points anterior)
        axis[0] = (temp[1]*temp[5])-(temp[2]*temp[4]);
        axis[1] = (temp[2]*temp[3])-(temp[0]*temp[5]);
        axis[2] = (temp[0]*temp[4])-(temp[1]*temp[3]);

        // y - mediolateral (ML) axis, Z X AP (should points medial)
        axis[3] = (temp[4]*axis[2])-(temp[5]*axis[1]);
        axis[4] = (temp[5]*axis[0])-(temp[3]*axis[2]);
        axis[5] = (temp[3]*axis[1])-(temp[4]*axis[0]);
    }
    else if (side == "LEFT")
    {
        // x - antero-posterior (AP) axis,Z X Y (should points anterior)
        axis[0] = (temp[4]*temp[2]) - (temp[5]*temp[1]);
        axis[1] = (temp[5]*temp[0]) - (temp[3]*temp[2]);
        axis[2] = (temp[3]*temp[1]) - (temp[4]*temp[0]);

        // y - medio-lateral (ML) axis, AP X Z (should points medial)
        axis[3] = (axis[1]*temp[5]) - (axis[2]*temp[4]);
        axis[4] = (axis[2]*temp[3]) - (axis[0]*temp[5]);
        axis[5] = (axis[0]*temp[4]) - (axis[1]*temp[3]);

    }

    // z - cranio-caudal axis, Z (should points kranial)

    // norm
    double bx = sqrt(pow(axis[0], 2) + pow(axis[1], 2) + pow(axis[2], 2));
    double by = sqrt(pow(axis[3], 2) + pow(axis[4], 2) + pow(axis[5], 2));
    double bz = sqrt(pow(axis[6], 2) + pow(axis[7], 2) + pow(axis[8], 2));

    axis[0] /= bx;
    axis[1] /= bx;
    axis[2] /= bx;

    axis[3] /= by;
    axis[4] /= by;
    axis[5] /= by;

    axis[6] /= bz;
    axis[7] /= bz;
    axis[8] /= bz;

    float b1 = (axis[0]*axis[0])+(axis[1]*axis[1])+(axis[2]*axis[2]);
    float b2 = (axis[3]*axis[3])+(axis[4]*axis[4])+(axis[5]*axis[5]);
    float b3 = (axis[6]*axis[6])+(axis[7]*axis[7])+(axis[8]*axis[8]);
}

void Anatomy::SphereFit(double p[][3], int n, double ai, double bi, double ci) {
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
        rms0 = float( RMS(p, n, Cx+(L*La), Cy+(L*Lb), Cz+(L*Lc), L) );
        SphereFit(p, n, Cx+(L*La), Cy+(L*Lb), Cz+(L*Lc));
    } else {
        a0 = Cx+(L*La);
        b0 = Cy+(L*Lb);
        c0 = Cz+(L*Lc);
        r0 = L;
        distance = L;
    }
    
}

double Anatomy::RMS(double p[][3], int n, double xm, double ym, double zm, double r) {
    double r1 = 0;
    double r2 = 0;
    
    for (int i = 0; i < 8; i++) {
        r1 = sqrt( pow(p[i][0]-xm, 2) + pow(p[i][1]-ym, 2) + pow(p[i][2]-zm, 2) );
        r2 = r2 + pow(r1-r, 2);
    }
    
    double rms = sqrt(r2/n);
    return (float)((int)(rms*10000))/10000;
}

double Anatomy::getDistance(double p1x, double p1y, double p1z, double p2x, double p2y, double p2z) {
    return sqrt( pow(p1x - p2x, 2) + pow(p1y - p2y, 2) + pow(p1z - p2z, 2) );
}

double Anatomy::getDistance(double p1[3], double p2[3]) {
    return sqrt( pow(p1[0] - p2[0], 2) + pow(p1[1] - p2[1], 2) + pow(p1[2] - p2[2], 2) );
}

void Anatomy::getCenterOfIntersectionContour(vtkPolyData* polydata, double* n, double* p, double* c) {
	
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
        cout << "could not define intersection contour!" << endl;
    else {
        // get the cutting-contours center
        cutPoly->GetCenter(c);
    }

}

void Anatomy::getCenterOfIntersectionContour(vtkPolyData* polydata, double nx, double ny, double nz, double px, double py, double pz, double* c) {
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
    if (cutPoly->GetNumberOfPoints() == 0) {
        cout << "could not define intersection contour!" << endl;
        return;
    } else {
        // get the cutting-contours center
        cutPoly->GetCenter(c);
    }
}

void Anatomy::getLineFit(vector<vector<double>> points, int n, double* result) {
    double center[3] = {0, 0, 0};
    
    for (int i = 0; i < n; i++) {
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

    for (int i = 0; i < n; i++) {
        
        // subtract center of mass:
        double x = points[i][0] - center[0];
        double y = points[i][1] - center[1];
        double z = points[i][2] - center[2];

        // Matrix "inertia tensor of centroidal moment"
        Mxx += x * x;
        Myy += y * y;
        Mzz += z * z;
        Mxy += x * y;
        Myz += y * z;
        Mzx += z * x;
    }

    getCharacteristicalPolynom(Mxx, Mxy, Mzx, Mxy, Myy, Myz, Mzx, Myz, Mzz, result);
}

void Anatomy::getCharacteristicalPolynom(double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33, double* result) {
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

void Anatomy::getEigenvector(double eigenvalue1, double eigenvalue2, double eigenvalue3, double a11, double a12, double a13, double a21, double a22, double a23, double a31, double a32, double a33, double* result) {
    double eigenvalue = 0;

    if (eigenvalue1 > eigenvalue2)
        if (eigenvalue1 > eigenvalue3)
            eigenvalue = eigenvalue1;
    
    if (eigenvalue2 > eigenvalue1)
        if (eigenvalue2 > eigenvalue3)
            eigenvalue = eigenvalue2;
    
    if (eigenvalue3 > eigenvalue1)
        if (eigenvalue3 > eigenvalue2)
            eigenvalue = eigenvalue3;

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

    if (b31 != 0) {

        // eliminate b31
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

    if (b21 != 0) {
        // eliminate b21
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
    
    if ( b32 != 0) {
        // eliminate b32
        double mult2 = b22;
        double mult3 = b32;

        b22 = b22* mult3;
        b23 = b23* mult3;

        b32 = b32* mult2;
        b33 = b33* mult2;

        b32 = b32- b22;
        b33 = b33- b23;
    }

    // solution
    result[0] = 0;
    result[1] = 0;
    result[2] = 0;

    // x3 has to be zero = free to select
    result[2] = 1;
    result[1] = -(b23 * result[2] / b22);
    result[0] = ((-b12 * result[1]) / b11) - ((b13 * result[2]) / b11);

    // norm
    double bn = sqrt(result[0] * result[0] + result[1] * result[1] + result[2] * result[2]);
    
    if (bn > 0) {
        result[0] = result[0] / bn;
        result[1] = result[1] / bn;
        result[2] = result[2] / bn;
    }

}

void Anatomy::SetAnatomicalLandmarks(const string path) {
    anatomicalLandmarks.clear();

    // make file ending great (again)
    string tmp = "";
    tmp.resize(path.size());
    transform(path.begin(), path.end(), tmp.begin(), (int (*)(int))toupper);

    // check for supported file type
    if (tmp.substr(tmp.length() - 3, 3) != "CSV") {
        cout << "File format not supported!" << endl;
        exit(-1);
    }

    // load csv from path
    ifstream file(path);

    if (!file.is_open()) {
        cout << "Could not load " << path << "!" << endl;
        return;
    }

    string row;
    size_t pos = 0;
    string delimiter = ",";

    // read all lines
    while (getline(file, row)) {

        // first occurence of delimiter
        pos = row.find(delimiter);

        // erase landmark identifier from row
        row.erase(0, pos + delimiter.length());

        // temporary array for coordinates
        vector<float> values;

        // read every single comma separated value
        while ((pos = row.find(delimiter)) != string::npos) {
            values.push_back(stod(row.substr(0, pos)));
            row.erase(0, pos + delimiter.length());
        }

        // last value
        values.push_back(stod(row.substr(pos+1, row.length())));
        
        // fill 3d float vector element 
        auto it = values.begin();
        anatomicalLandmarks.push_back({ *it, *(++it), *(++it) });
    }

    file.close();
}

void Anatomy::SetAnatomicalLandmarksFromJsonArray(const string json) {
    anatomicalLandmarks.clear();
    vector<double> values;

    for (size_t i = 0; i < json.length() - 1; ++i) {
        i = i + 2;
        size_t pos = i;

        while (json.substr(i, 1) != "]") {
            if (json.substr(i, 1) == ",") {
                std::string segment = json.substr(pos, i - pos);
                std::cout << segment << std::endl; // Sicherer und moderner Ansatz
                values.push_back(stod(segment));
                pos = i + 1;
            }
            i += 1;
        }

        std::string segment = json.substr(pos, i - pos);
        std::cout << segment << std::endl; // Sicherer und moderner Ansatz
        values.push_back(stod(segment));

        auto it = values.begin();
        anatomicalLandmarks.push_back({ *it, *(++it), *(++it) });
    }
}


void Anatomy::SetAnatomicalMesh(const string path) {

    // make file ending great (again)
    string tmp = "";
    tmp.resize(path.size());
    transform(path.begin(), path.end(), tmp.begin(), (int (*)(int))toupper);
    tmp = tmp.substr(tmp.length() - 3, 3);

    // check for supported file type
    if ((tmp != "STL") && (tmp != "VTK")) {
        cout << "File format not supported!" << endl;
        exit(-1);
    }

    if (tmp == "VTK") {
        readVTK->SetFileName(path.c_str());
        readVTK->Update();
        anatomicalMesh = readVTK->GetOutput();
    }
    else if (tmp == "STL") {
        readSTL->SetFileName(path.c_str());
        readSTL->Update();
        anatomicalMesh = readSTL->GetOutput();
    }

    if ((anatomicalMesh == nullptr) || (anatomicalMesh->GetNumberOfPoints() <= 0)) {
        cout << "Could not load " << path << "!" << endl;
        exit(-1);
    }
}


void Anatomy::SetMetaInfo(const string path) {

    // find some meta info's coded in filename
    int pos = path.find_last_of("/");

    string file = path.substr(pos + 1, path.length() - (pos + 1));

    // separator '-' must be found
    pos = file.find("-");

    // if it could not found try to another way
    if (pos <= 0) {

        // make 'file' great again
        transform(file.begin(), file.end(), file.begin(), ::toupper);

        // try to find side ...
        if (file.find("LEFT") != string::npos)
            this->side = "LEFT";
        else if (file.find("RIGHT") != string::npos)
            this->side = "RIGHT";		
        else {
            this->side = "";
            cout << "Meta-info 'side' not found!" << endl;
        }
        
        // ... and gender
        if (file.find("FEMALE") != string::npos)
            this->sex = "FEMALE";
        else if (file.find("MALE") != string::npos)
            this->sex = "MALE";		
        else {
            this->sex = "";
            cout << "Meta-info 'gender' not found!" << endl;
        }
    
        // age ist not important yet
        this->age = "";
        //cout << "Meta-info 'age' not found!" << endl;

        return;
    }

    // set sex found at 4 position after '-' ...
    string sex = file.substr(pos + 4, 1);
    transform(sex.begin(), sex.end(), sex.begin(), ::toupper);

    if (sex.compare("M") == 0) {
        this->sex = "MALE";
    } else if (sex.compare("F") == 0) {
        this->sex = "FEMALE";
    } else {
        this->sex = "";
        cout << "Meta-info 'gender' not found!" << endl;
    }

    // ... and side on first position after '-' ...
    string side = file.substr(pos + 1, 1);
    transform(side.begin(), side.end(), side.begin(), ::toupper);

    if (side.compare("L") == 0) {
        this->side = "LEFT";
    } else if (side.compare("R") == 0) {
        this->side = "RIGHT";
    } else {
        this->side = "";
        cout << "Meta-info 'side' not found!" << endl;
    }
    // ... and age on second position after '-' (two places)
    string age = file.substr(pos + 2, 2);

    if (age != "XX")
        this->age = age;
    else {
        this->age = "";
        cout << "Meta-info 'age' not found!" << endl;
    }
    
}


Anatomy::~Anatomy() {}