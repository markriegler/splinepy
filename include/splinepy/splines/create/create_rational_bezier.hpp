/*
MIT License

Copyright (c) 2021 Jaewook Lee

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <splinepy/splines/rational_bezier.hpp>
#include <splinepy/splines/splinepy_base.hpp>

namespace splinepy::splines::create {

/// dynamic creation of templated rational
std::shared_ptr<splinepy::splines::SplinepyBase>
CreateRationalBezier1(const int dim,
                      const int* degrees,
                      const double* control_points,
                      const double* weights);

std::shared_ptr<splinepy::splines::SplinepyBase>
CreateRationalBezier2(const int dim,
                      const int* degrees,
                      const double* control_points,
                      const double* weights);

std::shared_ptr<splinepy::splines::SplinepyBase>
CreateRationalBezier3(const int dim,
                      const int* degrees,
                      const double* control_points,
                      const double* weights);

#ifdef SPLINEPY_MORE
std::shared_ptr<splinepy::splines::SplinepyBase>
CreateRationalBezier4(const int dim,
                      const int* degrees,
                      const double* control_points,
                      const double* weights);

std::shared_ptr<splinepy::splines::SplinepyBase>
CreateRationalBezier5(const int dim,
                      const int* degrees,
                      const double* control_points,
                      const double* weights);

std::shared_ptr<splinepy::splines::SplinepyBase>
CreateRationalBezier6(const int dim,
                      const int* degrees,
                      const double* control_points,
                      const double* weights);

std::shared_ptr<splinepy::splines::SplinepyBase>
CreateRationalBezier7(const int dim,
                      const int* degrees,
                      const double* control_points,
                      const double* weights);

std::shared_ptr<splinepy::splines::SplinepyBase>
CreateRationalBezier8(const int dim,
                      const int* degrees,
                      const double* control_points,
                      const double* weights);

std::shared_ptr<splinepy::splines::SplinepyBase>
CreateRationalBezier9(const int dim,
                      const int* degrees,
                      const double* control_points,
                      const double* weights);

std::shared_ptr<splinepy::splines::SplinepyBase>
CreateRationalBezier10(const int dim,
                       const int* degrees,
                       const double* control_points,
                       const double* weights);
#endif

} // namespace splinepy::splines::create
