# BoneDoc

BoneDoc is a c++ command line tool for 3d shape analysis of human bones. Abstract concept in code faciliates protoyping for anatomical studies of various kinds.

## Prototypes:

* Thesis - logistic model based prediction of ethnic group for femur, humerus and tibia bone

For visual use BoneDoc and prototypes are integrated into 3D-Unity frontend 'BoneHost' which can be found [here](http://www.bonehost.net).

## Installation

BoneDoc needs to be compiled from sources using typical [CMake](https://cmake.org/) workflow. For the moment only linux (debian) is supported. Moreover BoneDoc depends on [VTK](http://www.vtk.org) and [Boost](http://www.boost.org).

## Quickstart

Starting BoneDoc from command line requires three input files (mesh, landmarks, config). The mesh represents a bone by polygonal data where actually vtk- and stl format can be processed with BoneDoc. Each row in a landmarks file represents an anatomical landmark. The config file contains size and label for all anatomical landmarks currently used.

So you are free to create and use your own data. For quick testing files in '/data' folder might be used like that:

```
>./BoneDoc data/FemurLeftFemaleA.vtk data/FemurLeftFemaleA-landmarks.csv config.txt
>
>407.208	24.6018	18.6065	29.7854	27.1256	21.382	130.959	17.3214	92	8
>anteversion: 27.25°
>antero-posterior width: 26.63mm
>bone length: 397.16mm
>head radius: 20.98mm
>inclination: 135.37°
>lateral offset: 18.65mm
>medial offset: 24.06mm
>medio-lateral width: 29.05mm
>asian: 85%
>caucasian: 15%
```

Output shows calculated anatomical parameters and calculated probalitity for asian and causian group of a left asian femur. Here parameters in detail cover bone length [mm], medial offset [mm], lateral offset [mm], ml width [mm], ap width [mm], head radius [mm], inclination [°], anteversion [°], probability for asian bone [%] and probability for caucasian bone [%].

## Related Projects

* [Statismo](https://github.com/statismo/statismo) is a c++ framework for statistical shape modeling. It supports all shape modeling tasks, from model building to shape analysis.

* [Scalismo](http://github.com/unibas-gravis/scalismo) is like Statismo a library for image analysis and shape modelling but designed for the Java Virtual Machine. It is written in [Scala](http://www.scala-lang.org/) and based on the same underlying concepts as statismo (and partly developed by the same people).

* [Boost] (https://www.boost.org/)
