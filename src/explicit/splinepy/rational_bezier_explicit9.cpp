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

#include "splinepy/splines/rational_bezier.hpp"

#ifdef SPLINEPY_MORE
template class splinepy::splines::RationalBezier<9, 1>;
template class splinepy::splines::RationalBezier<9, 2>;
template class splinepy::splines::RationalBezier<9, 3>;
template class splinepy::splines::RationalBezier<9, 4>;
template class splinepy::splines::RationalBezier<9, 5>;
template class splinepy::splines::RationalBezier<9, 6>;
template class splinepy::splines::RationalBezier<9, 7>;
template class splinepy::splines::RationalBezier<9, 8>;
template class splinepy::splines::RationalBezier<9, 9>;
template class splinepy::splines::RationalBezier<9, 10>;
#endif
