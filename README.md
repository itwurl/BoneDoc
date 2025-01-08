# BoneDoc

BoneDoc is a C++ tool for 3D shape analysis of human bones, designed to calculate key anatomical parameters of the femur, humerus, and tibia bones, and then use these to make a logistic model-based prediction of the ethnic group.
Running as a service, BoneDoc listens on port 61180 by default, whether it is executed as a binary or inside a Docker container.

## Getting Started

### Binary

Ensure that your system is up to date and that a C++ compiler is installed. BoneDoc needs to be compiled from source using [CMake](https://cmake.org/) workflow, considering dependencies [VTK](http://www.vtk.org) and [Boost](http://www.boost.org). Then complete installation using git and cmake.

```
git clone https://github.com/alexander-wurl/BoneDoc.git .
cmake .
cmake --build .
```

To run BoneDoc and perform analysis locally, two arguments are required: path to mesh file (vtk format) and path to landmark file (csv format).

```
./BoneDoc <mesh-file-path> <landmark-file-path>
BoneDocServer started. Listening on port 61180 ...
```

### Docker

Alternatively, you can use BoneDoc inside a Docker container without compiling it yourself.

```
docker pull itawu/bonedoc:1.0
docker run -d -p 61180:61180 --name bonedoc itawu/bonedoc:1.0
```

So analyses can be performed either locally or via the container with a request like the one below.

```
curl "http://localhost:61180" \
     -H "Dataset: <Dataset>" \
     -H "Anatomy: <Anatomy>" \
     -H "Side: <Side>" \
     -H "Gender: <Gender>" \
     -H "EthnicGroup: <EthnicGroup>" \
     -H "Study: <Study>"
```

The response will then display the results of the analysis, including the calculated anatomical parameters and the predicted ethnic group based on the provided data.

```
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
* [Bonehost](https://bonehost.net): This web application facilitates 3D shape analysis of human bones.

* [Statismo](https://github.com/statismo/statismo): Is a C++ framework for statistical shape modeling.

* [Scalismo](http://github.com/unibas-gravis/scalismo): Written in [Scala](http://www.scala-lang.org/), shares concepts with Statismo and was developed by the same team.
