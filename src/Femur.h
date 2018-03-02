#ifndef FEMUR_H
#define FEMUR_H

#include "Anatomy.h"

class Femur : public Anatomy
{
private:
	
	// based on manually found most proximal/distal anatomical landmarks an axis is build and then used to redefine both landmarks as technical landmarks [1]
	// no references yet.
	void OptimizeProximalAndDistalLandmark1();

	// center of condyles [1]: as suggested by Kenny Koah, Jessica Galie for perioprosthetic study (PPFX)  
	void FemoralCenterOfCondyles1();

	// femoral bone-length was the distance (along predefined z-axis) between the most proximal point of the femoral head and the most distal point of the condyle usually the medial condyle [1]
	// references:
	// Yuki Yoshioka, David Siu, and TD Cooke. The anatomy and functional axes of the femur. J Bone Joint Surg Am, 69(6):873-880, 1987.
	void FemoralBoneLength1();

	// fem_neck_shaft_interception <-> center of condyles [1]: as suggested by Kenny Koah, Jessica Galie for perioprosthetic study (PPFX)
	void FemoralShaftLength1();

	// fitting a sphere to the spherical part of the femoral head [1]: no references yet.
	void FemoralHeadCenter1(double p8[3], double p9[3], double p10[3], double p11[3], double p12[3], double p13[3], double p14[3], double p15[3]);

	// #########################################################################################################################################################
	// FemoralAnteversionAndInclination [1]: femoral anteversion/retroversion and inclination
	// #########################################################################################################################################################
	// anteversion: Reto Sutter, Tobias J Dietrich, Patrick O Zingg, and Christian WA Pfirrmann. Femoral antetorsion:
	//				comparing asymptomatic volunteers and patients with femoroacetabular impingement. Radiology, 263(2):475{483, 2012.
	// explanation: The line of reference in the proximal femur was defined as the line connecting the femoral head center and the center of the femoral neck at
	//				its narrowest point. The line of reference in the distal femur was defined as the line connecting the dorsal border of the two femoral
	//				condyles. The femoral antetorsion angle was then calculated between the proximal and distal reference line.
	// inclination: KS Leung, P Procter, B Robioneck, and K Behrens. Geometric mismatch of the gamma nail to the chinese femur.
	//				Clinical orthopaedics and related research, 323:42-48, 1996.
 	void FemoralAnteversionAndInclination1(double medial_condyle[3], double lateral_condyle[3]);

	// #########################################################################################################################################################
	// FemoralAnteversion [2]: femoral anteversion/retroversion
	// #########################################################################################################################################################
	// references:	Yoshioka, Yuki, David Siu, and T. D. Cooke. "The anatomy and functional axes of the femur." J Bone Joint Surg Am 69.6 (1987): 873-880.
	// summary:		" ... we defined anteversion of the neck somewhat differently than most other authors have We referenced the degree of anteversion to the
	//				transverse functional axis (the Z axis in Fig. 2-B) rather than to the tangent line of the posterior condylar surfaces."


	// find interception between neck-axis and femoral shaft-axis [1]: no references yet.
	void FemoralNeckAndShaftAxisInterception1();

	// center of mass from femoral shaft contour starting at center of condyles up to intersection of neck and shaft-axis [1]: as suggested by Kenny Koah, Jessica Galie for perioprosthetic study (PPFX)
	void FemoralTwist1();

	// #########################################################################################################################################################
	// FemoralNeckAxis1 [1]: axis between guessed neck-isthmus and femoral head center, pointing to the femoral head center
	// #########################################################################################################################################################
	// no references yet!
	// summary:		simple approach to estimate neck axis as vector between head-center and center of mass from intersection-plane through neck-isthmus, defined
	//				by three anatomical landmarks which were have to been put manually on the outer surface of the femoral neck where neck-isthmus is guessed.
	void FemoralNeckAxis1();

	// #########################################################################################################################################################
	// FemoralNeckAxisCorrection [1]: Neck-axis as line-fit/optimized femoral neck axis based on guessed neck-isthmus and femoral head center 
	// #########################################################################################################################################################
	// no references yet!
	// explanation:	fitting a line through head-center and center of massed defined by 'fem_neck_intersection_size' times intersections along temporay neck axis
	//				between head-center and guessed neck-isthmus. New femoral neck axis is then given by vector of fitted line (which may not pass guessed neck-
	//				isthmus or femoral head center). Beside anatomical variations in theory thinking of femoral head as a sphere and neck as a zylinder this
	//				axis must pass real femoral head center and neck-isthmus!
	void FemoralNeckAxisCorrection1();

	// #########################################################################################################################################################
	// FemoralNeckAxis2 [2]: axis between intersection of neck- and shaft axis and femoral head center, pointing to the femoral head center
	//						 in theory line through head-center and narrowest point of neck ist same as line through head-center and neck1/shaft-interserction.
	// #########################################################################################################################################################
	// no references yet! 
	// summary:		Based on 'FemoralNeckAxis1' and 'FemoralNeckAxisCorrection1'. Intersection of neck- and shaft axis has to be found before. Then neck axis
	//				will be defined between this intersection of neck- and shaft axis and the femoral head center, pointing medial to the femoral head center.
	void FemoralNeckAxis2();

	// reset all calculated parameters
	void ResetMeasurements();

public:
	Femur(const std::string anatomicalMesh, const std::string anatomicalLandmarksPath);
	~Femur();

	// anatomical landmarks
	double fovea[5]; // #1
	double minor_trochanter[5]; // #2
	double major_trochanter[5]; // #3 
	double linea_intertrochanterica[5]; // #4 
	double intercondylar_notch[5]; // #5 
	double facies_patellaris[5]; // #6 
	double lateral_epicondyle[5]; // #7 
	double medial_epicondyle[5]; // #8 
	double most_distal_point[5]; // #9 
	double most_proximal_point[5]; // #10 
	double most_anterior_neck_point[5]; // #11 
	double most_medial_neck_point[5]; // #12 
	double most_posterior_neck_point[5]; // #13 
	double head_fit_point_1[5]; // #14 
	double head_fit_point_2[5]; // #15 
	double head_fit_point_3[5]; // #16 
	double head_fit_point_4[5]; // #17 
	double head_fit_point_5[5]; // #18 
	double head_fit_point_6[5]; // #19 
	double head_fit_point_7[5]; // #20 
	double head_fit_point_8[5]; // #21 
	double lateral_condyle[5]; // #22
	double medial_condyle [5]; // #23 
	
	// technical landmarks
	double most_lateral_shaft_point[4]; // most lateral point of shaft-axis
	double most_medial_shaft_point[4]; // most medial point of shaft-axis
	double most_posterior_shaft_point[4]; // most posterior point of shaft-axis
	double most_anterior_shaft_point[4]; // most anterior point of shaft-axis
	double center_of_condyles[4];
	double proximal_shaft_center[4];
	double distal_shaft_center[4];
	double neck_isthmus_center[4]; // center of intersection plane defined by 3 anatomical landmarks
	double neck_center[4]; // center of mass from cutted intersection center points along (uncorrected) neck axis
	double neck_shaft_interception[4];

	// init
	void ResetMeshesAndMeasurements(const std::string file, std::string side);

	// reset all anatomical landmarks and measurements
	void MapAnatomicalLandmarksToAnatomicalMesh();

	// see thesis 'Ethnizitaetsbestimmung mit multivariater Statistik' (Alexander Wurl) for femur bone
	void Thesis();

	// perioprosthetic femoral study (Jessica Galie, ...) for femur bone
	void PPFX();

	// anatomical parameters
	double neck_axis[3];
	double bone_length;
	double shaft_length;
	double medial_offset;
	double lateral_offset;
	double ML_width;
	double AP_width;
	double head[4];
	double head_radius;
	double inclination;
	double anteversion;

	static const int twist_intersections_size = 25;
	static const int neck_intersection_size = 10;

	double twist_intersections[3][twist_intersections_size];

};


#endif // FEMUR_H
