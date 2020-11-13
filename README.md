# BoneDoc

BoneDoc is a c++ command line tool for 3d shape analysis of human bones. Abstract concept in code faciliates protoyping for anatomical studies of various kinds.

## Prototypes:

* Thesis - logistic model based prediction of ethnic group for femur, humerus and tibia bone

For visual use BoneDoc and prototypes are integrated into 3D-Unity frontend 'BoneHost' which can be found [here](http://www.bonehost.net).

## Installation

BoneDoc needs to be compiled from sources using typical [CMake](https://cmake.org/) workflow considering dependencies [VTK](http://www.vtk.org) and [Boost](http://www.boost.org). Moreve only linux (debian) is supported yet.

## Quickstart

Starting BoneDoc from command line requires three input files (mesh, landmarks, config). For quick testing files in '/data' folder might be used.

```
>bin/BoneDoc data/FemurLeftFemaleA.vtk data/FemurLeftFemaleA-landmarks.csv bin/bonehost.conf
>
>407.208 24.6018 18.6065 29.7854 27.1256 21.382 130.959 17.3214 92 8
>
```

Calculated and returned results for femur bone covers bone length [mm], medial offset [mm], lateral offset [mm], ml width [mm], ap width [mm], head radius [mm], inclination [°], anteversion [°], probability for asian bone [%] and probability for caucasian bone [%].


## Related Projects

* [Statismo](https://github.com/statismo/statismo) is a c++ framework for statistical shape modeling. It supports all shape modeling tasks, from model building to shape analysis.

* [Scalismo](http://github.com/unibas-gravis/scalismo) is like Statismo a library for image analysis and shape modelling but designed for the Java Virtual Machine. It is written in [Scala](http://www.scala-lang.org/) and based on the same underlying concepts as statismo (and partly developed by the same people).

* [Boost](https://www.boost.org/)

* [VTK](http://www.vtk.org)
