# BoneDoc

BoneDoc is a c++ command line tool for 3d shape analysis of human bones. Abstract concept in code are meant to faciliate protoyping for various types of anatomical studies.

## Prototypes:

* Thesis - logistic model-based prediction of ethnic groups for the femur, the humerus and the tibia bone

## Installation

Before compiling BoneDoc, ensure that your system is up to date and that a C++ compiler is installed.

BoneDoc needs to be compiled from source using [CMake](https://cmake.org/) workflow, considering dependencies [VTK](http://www.vtk.org) and [Boost](http://www.boost.org).

BoneDoc then needs to be compiled from sources using then [CMake](https://cmake.org/) workflow, taking into account dependencies [VTK](http://www.vtk.org) and [Boost](http://www.boost.org).

When all dependencies are met, complete the installation by following the steps below.

```
git clone https://github.com/alexander-wurl/BoneDoc.git .
cmake .
cmake --build .
```

## Quickstart

Designed to run as a service, BoneDoc will listen for HTTP requests if no startup parameters are provided.

```
.\BoneDoc.exe
BoneDocServer started. Listening on port 61180 ...
```

For local use, BoneDoc needs two arguments that can be passed via the command line.

Arguments are paths to the mesh file and the landmark file.

```
.\BoneDoc.exe .\data\FemurLeftFemaleA.vtk .\data\FemurLeftFemaleA-landmarks.csv bonedoc.conf

calculated parameters
—————————————————————
bone length  407.21mm
med. offset  24.60mm
lat. offset  18.61mm
ml width     29.79mm
ap width     27.13mm
head radius  21.38mm
inclination  130.96mm
anteversion  17.32mm
asians       92%
caucasians   8%
```

## Related Projects

* [Statismo](https://github.com/statismo/statismo) is a c++ framework for statistical shape modeling. It supports all shape modeling tasks, from model building to shape analysis.

* [Scalismo](http://github.com/unibas-gravis/scalismo) is like Statismo a library for image analysis and shape modelling but designed for the Java Virtual Machine. It is written in [Scala](http://www.scala-lang.org/) and based on the same underlying concepts as statismo (and partly developed by the same people).
