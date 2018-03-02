#ifndef HUMERUS_H
#define HUMERUS_H

#include "Anatomy.h"

class Humerus : public Anatomy
{
private:
	void ResetMeasurements();
public:
	Humerus();
	~Humerus();

	void ResetMeshesAndMeasurements(const std::string file, std::string side);

	void HumerusHeadCenter(double *p12, double *p13, double *p14, double *p15, double *p16, double *p17, double *p18, double *p19);
	void HumerusMedialCondyle(double* p20, double* p21, double* p22, double* p23, double* p24, double* p25, double* p26, double* p27);
	void HumerusLateralCondyle(double* p28, double* p29, double* p30, double* p31, double* p32, double* p33, double* p34, double* p35);

	void HumerusInclinationAndRetroversion(double *p9, double *p10, double *p11);

	// Scene für die Humerusstudie
	void ResetAnatomicalLandmarks();

	// see thesis 'Ethnizitaetsbestimmung mit multivariater Statistik' (Alexander Wurl) for humerus bone
	void Thesis();

	// study of distal humerus (John Meek, Beat Schmutz, Alexander Wurl)
	void DistalHumerus();

	double hum_p1[5];
	double hum_p2[5];
	double hum_p3[5];
	double hum_p4[5];
	double hum_p5[5];
	double hum_p6[5];
	double hum_p7[5];
	double hum_p8[5];
	double hum_p9[5];
	double hum_p10[5];
	double hum_p11[5];
	double hum_p12[5];
	double hum_p13[5];
	double hum_p14[5];
	double hum_p15[5];
	double hum_p16[5];
	double hum_p17[5];
	double hum_p18[5];
	double hum_p19[5];

	double hum_p20[5];
	double hum_p21[5];
	double hum_p22[5];
	double hum_p23[5];
	double hum_p24[5];
	double hum_p25[5];
	double hum_p26[5];
	double hum_p27[5];

	double hum_p28[5];
	double hum_p29[5];
	double hum_p30[5];
	double hum_p31[5];
	double hum_p32[5];
	double hum_p33[5];
	double hum_p34[5];
	double hum_p35[5];


	double epicondyle_axis[3];

	double PLAT[3];
	double PMED[3];
	double PP[3];
	double PA[3];

	double bone_length;
	double medial_offset;
	double lateral_offset;
	double ML_width;
	double AP_width;
	double H1, H2, H3, H4, H5, H6;
	double V1, V2, V3;
	double medial_fit_x;
	double medial_fit_y;
	double medial_fit_z;
	double medial_radius;
	double lateral_fit_x;
	double lateral_fit_y;
	double lateral_fit_z;
	double lateral_radius;
	double head_fit_x;
	double head_fit_y;
	double head_fit_z;
	double head_radius;
	double inclination;
	double retroversion;
};

#endif // HUMERUS_H