# hyperCube: A C Implementation of the CCSDS-123-B-2 Standard

An Open Source Implementation of [CCSDS-123-B-2](CCSDS_Compression.pdf), the
Low-Complexity Lossless and Near-Lossless Multispectral and Hyperspectral
Image Compression.

## Table of Contents
- [hyperCube: A C Implementation of the CCSDS-123-B-2 Standard](#hypercube-a-c-implementation-of-the-ccsds-123-b-2-standard)
  - [Table of Contents](#table-of-contents)
  - [Introduction](#introduction)
  - [Roadmap](#roadmap)
  - [Installation](#installation)
  - [Command Line Interface](#command-line-interface)
    - [Image Generator](#image-generator)
    - [Compressor](#compressor)
      - [Actions](#actions)
      - [Defaults](#defaults)
    - [Decompressor](#decompressor)
  - [Compiling for ARM](#compiling-for-arm)
  - [Documentation](#documentation)
  - [Authors and Acknowledgement](#authors-and-acknowledgement)

## Introduction

HyperC is an implementation of the [CCSDS-123 B-2](CCSDS_Compression.pdf),
designed to meet the FINCH-PayloadController-LosslessCompression requirement.
The required Compression Speed is givenby the
[FINCH-PayloadController-CompressionSpeed](https://www.notion.so/utat-ss/FINCH-PayloadController-CompressionSpeed-0a9a3c2992e44a239bd1d1e7e464b6c9)
requirement. The compression rate
required is provided by the
[FINCH-PayloadController-CompressionRate](https://www.notion.so/utat-ss/FINCH-PayloadController-CompressionRate-8cabbe2393b147b6ae5e73e8ee58c9f4)
requirement.

This project contains:

- Compressor
- Decompressor
- Hyperspectral Image formatting and generation

The raw hyperspectral image files are expected to be .uhi (Uncompressed
Hyperspectral Image) files, which makes getting and storing individual pixels
much faster than csv or mat files.

Compressed Images are stored in .vuf files (Variable Unsigned Files), which
are capable of storing unsigned integers of any length less than 32 bits.

## Roadmap

- [x] August 31: Finish Preliminary C Implementation
- [x] August 23: Present Progress to Industry Experts at Critical Design Review
- [x] Remove Dynamic Memory Allocation
- [x] Compile Project for ARM32, target: stm32h743zi 
- [ ] July 6: Run Predictor on NUCLEO-H743ZI2 board without external memory
- [ ] July 6: Run Predictor on NUCLEO-H743ZI2 board with    external memory
- [ ] August 6: Finish Encoder, Decoder, Reconstructor

## Installation

Download the repository using the command:

```bash
git clone https://github.com/Kevin-Caldwell/CCSDS-Compression-C.git
```

The build system for this project is CMake. In order to assemble the binaries, run the commands

```bash
mkdir build; cd build
cmake .
make
```

The assembled binaries should be found in the build folder:

- hc-imgen
- hc-compress
- hc-decompress

## Command Line Interface

### Image Generator

Hyperspectral Image Tools are available in the hc-imgen executable.
It provides a CLI for

- Image Generation using Perlin or Voronoi Noise
- Image Conversion from .csv to .uhi
- Image Conversion from .uhi to .csv

### Compressor

hc-compress is the Image Compressor, and the CLI Tags are:

- `-s` : Set Source File
- `-d` : Set Destionation File
- `-a` : Set Action (See Below)
- `-D` : Enable `DEBUG MODE`
- `-l` : Set Log File

#### Actions

Actions describe all the functions you can execute using hc-compress.
The list of possible actions are:

- `compress`: Compress an image in a .uhi file to a .vuf file
- `predict`: Run the predictor on an image. Input and output files are .uhi
- `encode`: Run Encoder on an image in a .uhi file into a .vuf file
- `test-x`: Validate x (predictor, encoder, compressor, uhi, vuf)

#### Defaults

- Source File: `../data/test-images/indian_pines.UHI`
- Destination File: `../data/results/indian_pines.UHI`
- Action: `predict`
- Debug: `False`
- Log File: `../data/logs/compressor.logs`

### Decompressor

The Decompressor has not been fully implemented yet.



## Compiling for ARM 

Using the arm-none-eabi-gcc compiler, the build command for this project is

```bash
arm-none-eabi-gcc --specs=nosys.specs  main/compressor.c src/**.c -I include -lm -o build/hc-compress
```

## Documentation

Documentation for all features have been documented in code, and can be
compiled for Doxygen using the preset file Doxyfile0:

```bash
doxygen Doxyfile0
```

The documentation can be viewed by opening the `doc/html/index.html` file in a browser.

## Authors and Acknowledgement

Developed by [Kevin Caldwell](https://github.com/Kevin-Caldwell), 
[Mirai Shinjo](https://github.com/mshinjo),
[Brian Tsoi](https://github.com/BrianShTsoi) and 
[Lanlin He](https://github.com/lalalalinn), assisted by the 
University of Toronto Aerospace Team (UTAT) Space Systems Team.

Developed for the Field Imaging Nanosatellite for Crop residue Hyperspectral mapping (FINCH) mission.