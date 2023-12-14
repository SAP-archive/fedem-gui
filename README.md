<!---
  SPDX-FileCopyrightText: 2023 SAP SE

  SPDX-License-Identifier: Apache-2.0

  This file is part of FEDEM - https://openfedem.org
--->

[![REUSE status](https://api.reuse.software/badge/github.com/SAP/fedem-gui)](https://api.reuse.software/info/github.com/SAP/fedem-gui)

# FEDEM GUI

![Fedem Logo](https://github.com/SAP/fedem-foundation/blob/main/cfg/FedemLogo.png "Welcome to FEDEM")

**Welcome to FEDEM! - Finite Element Dynamics of Elastic Mechanisms.**

## About this project

This project contains the complete source code of
the Graphical User Interface of FEDEM. It also uses elements from
the [fedem-mdb](https://github.com/SAP/fedem-mdb) project,
which is consumed as a submodule by this repository.
See [src/README.md](src/README.md) for details on the source code organization.

The FEDEM solvers themselves are maintained in a parallel project
[fedem-solvers](https://github.com/SAP/fedem-solvers).

Refer to our web page [openfedem.org](https://openfedem.org/)
for overall information on the FEDEM project.

## Requirements and Setup

The FEDEM GUI project relies on the following third-party modules,
which are not included in this repository:

* [Qt 4.8](https://download.qt.io/archive/qt/4.8/) -
  Cross-platform graphical user interface framework
* [Coin 4.0](https://github.com/coin3d/coin) -
  OpenGL-based 3D graphics library
* [SoQt 1.6](https://github.com/coin3d/soqt) -
  Coupling module between Coin and Qt
* [SmallChange 1.0](https://github.com/coin3d/smallchange) -
  Some Open Inventor extensions for Coin
* [Simage 1.8](https://github.com/coin3d/simage) -
  Library for saving images and animations from the Coin view
* [zlib 1.2](https://zlib.net/) -
  File compression library

You need to build and install these modules separately,
before building the FEDEM GUI application itself,
see [here](BUILD.md#build-of-external-3rd-party-modules) for details.
The first four of the packages above are mandatory,
whereas the latter two are optional.
This means the build will work without them,
but with some features being absent.

In addition, we also use the library [Qwt 6.1.2](https://qwt.sourceforge.io/)
for doing the 2D curve plotting.
However, the sources for that library is embedded in this repository,
in the [src/Qwt](src/Qwt) folder.

Provided you have installed the third-party modules listed above,
you can configure and build the FEDEM GUI from the sources by following
the instructions given [here](BUILD.md#build-the-fedem-gui-application).

### Activation of features compile-time

Many of the features in the FEDEM GUI can be activated/deactivated compile-time
using command-line options on the form `-DUSE_(feature)=ON/OFF`
when running cmake, where `=ON` activates a feature which is off by default,
and `=OFF` deactivates a feature which is on by default.
Currently, the following options can be specified to toggle features On or Off:

* USE_COMAPI - Build with the COM API
* USE_CONTROL - Build with control system support
* USE_DIGTWIN - Build with some Digitial Twin features
* USE_FATIGUE - Build with durability calculation support
* USE_MESHING - Build with FE meshing support
* USE_OILWELL - Build with oil well modeling support
* USE_RISER - Build with marine structures modeling support
* USE_SEVENTS - Build with simulation event support
* USE_TIREAPI - Build with the Tire model API
* USE_VTF - Build with VTF export support
* USE_VTFX - Build with VTFx export support
* USE_WINDPOW - Build with Wind turbine modeling support

## Contributing

This project is open to feature requests/suggestions, bug reports etc. via [GitHub issues](https://github.com/SAP/fedem-gui/issues). Contribution and feedback are encouraged and always welcome. For more information about how to contribute, the project structure, as well as additional contribution information, see our [Contribution Guidelines](CONTRIBUTING.md).

## Security / Disclosure

If you find any bug that may be a security problem, please follow our instructions at [in our security policy](https://github.com/SAP/fedem-gui/security/policy) on how to report it. Please do not create GitHub issues for security-related doubts or problems.

## Code of Conduct

We as members, contributors, and leaders pledge to make participation in our community a harassment-free experience for everyone. By participating in this project, you agree to abide by its [Code of Conduct](https://github.com/SAP/.github/blob/main/CODE_OF_CONDUCT.md) at all times.

## Licensing

Copyright 2023 SAP SE or an SAP affiliate company and fedem-gui contributors. Please see our [LICENSE](LICENSE) for copyright and license information. Detailed information including third-party components and their licensing/copyright information is available [via the REUSE tool](https://api.reuse.software/info/github.com/SAP/fedem-gui).
