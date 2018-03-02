#ifndef TIBIA_H
#define TIBIA_H

#include "Anatomy.h"

class Tibia : public Anatomy
{
private:
	void ResetMeasurements();

public:
	Tibia();
	~Tibia();

	void ResetMeshesAndMeasurements(const std::string file, std::string side);

	void ResetAnatomicalLandmarks();
	
	void Thesis();
	
	void TibiaStudy1Angles(const double *p6, const double *p7, const double *p4, const double *p5);

	double tib_bone_length;
	double tib_medial_offset;
	double tib_lateral_offset;
	double tib_ML_width;
	double tib_AP_width;
	double tib_torsion;

	double tib_p1[5];
	double tib_p2[5];
	double tib_p3[5];
	double tib_p4[5];
	double tib_p5[5];
	double tib_p6[5];
	double tib_p7[5];
};

#endif // TIBIA_H