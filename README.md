# BoneDoc

BoneDoc is a c++ command line tool for 3d shape analysis of human bones. Abstract concept in code faciliates protoyping for anatomical studies of various kinds.

## Prototypes:

* Thesis - logistic model based prediction of ethnic group for femur, humerus and tibia bone

## Installation

BoneDoc needs to be compiled from sources using typical [CMake](https://cmake.org/) workflow considering dependencies [VTK](http://www.vtk.org) and [Boost](http://www.boost.org).
So assure cmake, boost and vtk are installed to start building process.
To start process clone repository BoneDoc first, then run CMake as desribed below.

```
>git clone https://github.com/alexander-wurl/BoneDoc.git .
>cd BoneDoc
>cmake .
>cmake --build .
```

## Quickstart

Since BoneDoc is designed to run as a service, 
it will listen for HTTP requests on port 61180 if no parameters are provided at startup.

```
.\BoneDoc.exe
BoneDocServer started. Listening on port 61180 ...
```

For local use BoneDoc needs 3 arguments which can be passed via the command line.

Arguments are paths to a mesh file, a landmark file and a configuration file.

```
.\BoneDoc.exe .\data\FemurLeftFemaleA.vtk .\data\FemurLeftFemaleA-landmarks.csv .\bonedoc.conf
407.20 24.60 18.60 29.78 27.12 21.38 130.95 17.32 92 8
```

Starting BoneDoc from command line requires three parameters.

```
bin/BoneDoc data/FemurLeftFemaleA.vtk data/FemurLeftFemaleA-landmarks.csv bin/bonehost.conf
407.21 24.62 18.61 29.79 27.13 21.38 130.96 17.32 92 8
```

Calculated and returned results for femur bone covers bone length [mm], medial offset [mm], lateral offset [mm], ml width [mm], ap width [mm], head radius [mm], inclination [°], anteversion [°], probability for asian bone [%] and probability for caucasian bone [%].


## Related Projects

* [Statismo](https://github.com/statismo/statismo) is a c++ framework for statistical shape modeling. It supports all shape modeling tasks, from model building to shape analysis.

* [Scalismo](http://github.com/unibas-gravis/scalismo) is like Statismo a library for image analysis and shape modelling but designed for the Java Virtual Machine. It is written in [Scala](http://www.scala-lang.org/) and based on the same underlying concepts as statismo (and partly developed by the same people).

* [Boost](https://www.boost.org/)

* [VTK](http://www.vtk.org)
