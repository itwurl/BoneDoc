# BoneDoc

BoneDoc is a C++ tool for 3D shape analysis of human bones, designed to calculate key anatomical parameters of the femur, humerus, and tibia bones, and then use these to make a logistic model-based prediction of the ethnic group.
Running as a service, BoneDoc listens on port 61180 by default, whether it is executed as a binary or inside a Docker container.

## Getting Started

### Binary

Ensure that your system is up to date and that a C++ compiler is installed. BoneDoc needs to be compiled from source using [CMake](https://cmake.org/) workflow, considering dependencies [VTK](http://www.vtk.org) and [Boost](http://www.boost.org). Then clone the repository and use CMake to configure and build the project.

```
git clone https://github.com/itwurl/BoneDoc.git .
cmake .
cmake --build .
```

To run the binary and perform analysis, two arguments are required: the path to the mesh file and the path to the landmark file. Without arguments, BoneDoc starts as an HTTP service, waiting for appropriate requests.

```
./BoneDoc <vtk-file-path> <csv-file-path>
```

After analysis, results are printed, showing anatomical parameters and the predicted ethnic group based on the provided data.

### Docker Image

Instead of running BoneDoc as a standalone binary via the command line, you can use the pre-built Docker image from Docker Hub and start a container:

```
docker pull itwurl/bonedoc:1.0
docker run -d -p 61180:61180 --name bonedoc itwurl/bonedoc:1.0
```

### Test the BoneDoc API

Once the container is running locally, you can test the BoneDoc REST service with a simple curl request:

```
curl -X GET "http://localhost:61180" \
  -H "Dataset: HumerusRightMaleC" \
  -H "Anatomy: Humerus" \
  -H "Side: Right" \
  -H "Gender: Male" \
  -H "EthnicGroup: Caucasian" \
  -H "Study: Thesis"
```

### Expected response:

```
Bone Length: 328mm
Medial Offset: 21.2mm
Lateral Offset: 23.2mm
ML Width: 24.8mm
AP Width: 19.5mm
Head Radius: 25.6mm
Inclination: 121.9°
Retroversion: 20.8°
Asian: 1%
Caucasian: 99%
```

This setup allows you to perform analyses either locally or within the container. BoneDoc operates in a client-server architecture, providing flexibility for various use cases.

### BoneHost

BoneHost implements a client-server architecture, utilizing BoneDoc as a microservice, which is already deployed online as a web service. See bonehost.net for more information.

## Related Projects
* [Bonehost](https://bonehost.net): This web application facilitates 3D shape analysis of human bones.

* [Statismo](https://github.com/statismo/statismo): Is a C++ framework for statistical shape modeling.

* [Scalismo](http://hub.com/unibas-gravis/scalismo): Written in [Scala](http://www.scala-lang.org/), shares concepts with Statismo and was developed by the same team.
