#ifndef TIBIA_H
#define TIBIA_H

#include "Anatomy.h"

class Tibia : public Anatomy {
private:
    string configPath;

    void ResetMeasurements();

    // anatomical landmarks
    double medial_malleolus[5]; // tib_p1[5];
    double fibular_notch[5]; // tib_p2[5];
    double medial_epicondyle[5]; // tib_p3[5];
    double lateral_epicondyle[5]; // tib_p4[5];
    double tuberositas[5]; // tib_p5[5];
    double most_proximal_point[5]; // tib_p6[5];
    double medial_condyle[5]; // tib_p7[5];
    double lateral_condyle[5];
    
    // technical landmarks
    double proximal_shaft_center[3];
    double distal_shaft_center[3];
    double most_lateral_shaft_point[3]; // most lateral point of shaft-axis
    double most_medial_shaft_point[3]; // most medial point of shaft-axis
    double most_posterior_shaft_point[3]; // most posterior point of shaft-axis
    double most_anterior_shaft_point[3]; // most anterior point of shaft-axis
  
    
    // proximal shaft center [1]
    // intersect shaft at 80% of bone length an set contour's center of mass to 'proximal_shaft_center'
    // no references yet.
    void SetProximalShaftCenter();

    // distal shaft center [1]
    // intersect shaft at 20% of bone length an set contour's center of mass to 'distal_shaft_center'
    // no references yet.
    void SetDistalShaftCenter();
    
    void SetOffsetAndWidth();

    void BoneLength();

    // references: see thesis
    void MedialOffset();
    
    // references: see thesis
    void LateralOffset();
    
    // references: see thesis
    void MLWidth();
    
    // references: see thesis
    void APWidth();
    
    void SetMedialAndLateralAxis();
    
    void TibiaTorsion();

    void MapAnatomicalLandmarksToAnatomicalMesh();

    void GuessEthnicGroup();
        
public:
    Tibia(const string anatomicalMesh,
            const string anatomicalLandmarksPath,
                const string configPath);
    ~Tibia();

    void Thesis();


    double bone_length;
    double medial_offset;
    double lateral_offset;
    double ML_width;
    double AP_width;
    double torsion;
};

#endif // TIBIA_H