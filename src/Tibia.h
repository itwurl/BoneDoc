#ifndef TIBIA_H
#define TIBIA_H

#include "Anatomy.h"

class Tibia : public Anatomy {
private:
    std::string configPath;

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

    void MapAnatomicalLandmarksToAnatomicalMesh();

    void GuessEthnicGroup();
        
public:
    Tibia(const std::string anatomicalMesh,
            const std::string anatomicalLandmarksPath,
                const std::string configPath);
    ~Tibia();

    void Thesis();

    void TibiaTorsion(const double *p6, const double *p7, const double *p4, const double *p5);

    double bone_length;
    double medial_offset;
    double lateral_offset;
    double ML_width;
    double AP_width;
    double torsion;
};

#endif // TIBIA_H