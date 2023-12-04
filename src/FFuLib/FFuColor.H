// SPDX-FileCopyrightText: 2023 SAP SE
//
// SPDX-License-Identifier: Apache-2.0
//
// This file is part of FEDEM - https://openfedem.org
////////////////////////////////////////////////////////////////////////////////

#ifndef FFU_COLOR_H
#define FFU_COLOR_H

#include <array>

#define I3       std::array<int,3>
#define F3       std::array<float,3>
#define to24b(x) int(255.0*x+0.5)


/*!
  \brief Representation of a RGB color by integers in range [0,255].
*/

class FFuColor : public I3
{
public:
  //! \brief Default constructor.
  FFuColor(int r = 0, int g = 0, int b = 0) : I3({r,g,b}) {}
  //! \brief Copy constructor.
  FFuColor(const I3& c) : I3(c) {}
  //! \brief Conversion from float representation in range [0.0,1.0]
  FFuColor(const F3& c) : I3({to24b(c[0]),to24b(c[1]),to24b(c[2])}) {}
};

#undef I3
#undef F3
#undef to24b
#endif
