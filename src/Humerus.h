#ifndef HUMERUS_H
#define HUMERUS_H

#include "Anatomy.h"

class Humerus : public Anatomy {
private:
    std::string configPath;

    void ResetMeasurements();

    // anatomical landmarks (x21)
    double medial_epicondyle[4];
    double lateral_epicondyle[4];
    double minor_tuberculum[4];
    double major_tuberculum[4];
    double superior_fossa_olecrani[4];
    double medial_fossa_olecrani[4];
    double lateral_fossa_olecrani[4];
    double inferior_fossa_olecrani[4];
    double most_distal_point[4];
    double most_proximal_point[4];
    double most_anterior_neck_point[4];
    double most_medial_neck_point[4];
    double most_posterior_neck_point[4];
    double head_fit_point_1[4];
    double head_fit_point_2[4];
    double head_fit_point_3[4];
    double head_fit_point_4[4];
    double head_fit_point_5[4];
    double head_fit_point_6[4];
    double head_fit_point_7[4];
    double head_fit_point_8[4];

    // anatomical parameters
    double head_fit_x;
    double head_fit_y;
    double head_fit_z;
    double epicondyle_axis[3];
    double PLAT[3];
    double PMED[3];
    double PP[3];
    double PA[3];

    // technical landmarks
    double proximal_shaft_center[3];
    double distal_shaft_center[3];
    double most_lateral_shaft_point[3]; // most lateral point of shaft-axis
    double most_medial_shaft_point[3]; // most medial point of shaft-axis
    double most_posterior_shaft_point[3]; // most posterior point of shaft-axis
    double most_anterior_shaft_point[3]; // most anterior point of shaft-axis
    
    
    void HumerusHeadCenter(double *p12, double *p13, double *p14, double *p15, double *p16, double *p17, double *p18, double *p19);
    
    // (temporary) medial and lateral axis to define local coordinate from
    void SetMedialAndLateralAxis();
    
    void HumerusInclinationAndRetroversion(double *p9, double *p10, double *p11);

    // find technical landmark (closest point) for each anatomical landmark
    void MapAnatomicalLandmarksToAnatomicalMesh();

    void GuessEthnicGroup();
        
public:
    Humerus(const std::string anatomicalMesh,
            const std::string anatomicalLandmarksPath,
                const std::string configPath);
    ~Humerus();

    // see thesis 'Ethnizitaetsbestimmung mit multivariater Statistik' (Alexander Wurl) for humerus bone
    void Thesis();

    // anatomical parameters
    double bone_length;
    double medial_offset;
    double lateral_offset;
    double ML_width;
    double AP_width;
    double head_radius;
    double inclination;
    double retroversion;
};

#endif // HUMERUS_H