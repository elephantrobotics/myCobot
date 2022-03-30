/*
 * Copyright (c) 2020, Christopher Durand
 *
 * This file is part of the modm project.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include <cmath>

#ifdef __AVR__

extern "C"
{
  float cosf(float x)
  {
    return ::cos(x);
  }

  float sinf(float x)
  {
    return ::sin(x);
  }

  float tanf(float x)
  {
    return ::tan(x);
  }

  float fabsf(float x)
  {
    return ::fabs(x);
  }

  float fmodf(float x, float y)
  {
    return ::fmod(x, y);
  }

  float cbrtf(float x)
  {
    return ::cbrt(x);
  }

  float hypotf(float x, float y)
  {
    return ::hypot(x, y);
  }

  float squaref(float x)
  {
    return ::square(x);
  }

  float floorf(float x)
  {
    return ::floor(x);
  }

  float ceilf(float x)
  {
    return ::ceil(x);
  }

  float frexpf(float value, int* exp)
  {
    return ::frexp(value, exp);
  }

  float ldexpf(float x, int exp)
  {
    return ::ldexp(x, exp);
  }

  float expf(float x)
  {
    return ::exp(x);
  }

  float coshf(float x)
  {
    return ::cosh(x);
  }

  float sinhf(float x)
  {
    return ::sinh(x);
  }

  float tanhf(float x)
  {
    return ::tanh(x);
  }

  float acosf(float x)
  {
    return ::acos(x);
  }

  float asinf(float x)
  {
    return ::asin(x);
  }

  float atanf(float x)
  {
    return ::atan(x);
  }

  float atan2f(float y, float x)
  {
    return ::atan2(y, x);
  }

  float logf(float x)
  {
    return ::log(x);
  }

  float log10f(float x)
  {
    return ::log10(x);
  }

  float powf(float x, float y)
  {
    return ::pow(x, y);
  }

  bool isnanf(float x)
  {
    return ::isnan(x);
  }

  bool isinff(float x)
  {
    return ::isinf(x);
  }

  bool isfinitef(float x)
  {
    return ::isfinite(x);
  }

  float copysignf(float x, float y)
  {
    return ::copysign(x, y);
  }

  int signbitf(float x)
  {
    return ::signbit(x);
  }

  float fdimf(float x, float y)
  {
    return ::fdim(x, y);
  }

  float fmaf(float x, float y, float z)
  {
    return ::fma(x, y, z);
  }

  float fmaxf(float x, float y)
  {
    return ::fmax(x, y);
  }

  float fminf(float x, float y)
  {
    return ::fmin(x, y);
  }

  float truncf(float x)
  {
    return ::trunc(x);
  }

  float roundf(float x)
  {
    return ::round(x);
  }

  long lroundf(float x)
  {
    return ::lround(x);
  }

  long lrintf(float x)
  {
    return ::lrint(x);
  }
} // extern "C"

#endif // __AVR__
