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

#include <cassert>
#include <memory>
#include <vector>

#include "splinepy/utils/print.hpp"

namespace splinepy::utils {

/// Function to support negative indexing
template<typename IndexType, typename SizeType>
IndexType WrapId(IndexType i, const SizeType n) {
  if (i < 0) {
    i += n;
  }

#ifndef NDEBUG
  if (i < 0 || (SizeType) i >= n) {
    splinepy::utils::PrintAndThrowError("Index out of range");
  }
#endif

  return i;
};

/// Forward declaration, as ControlPointPointers has it as member.
struct WeightPointers;

/// Helper class than contains pointers to the beginning pointer of each
/// control point. This provides general, type-invariant interface to access
/// core spline's control points.
/// This must only be created by SplinepyBase class and each splines holds a
/// shared_ptr of control points. SplinepyBase's dtor will set
/// invalid_ flag to false, so that it will stop updating the control points
/// if spline doesn't exist.
///
/// For rational splines, this type holds shared pointer to weight_pointers_.
/// Backend splines saveds weighted control points and we always expose
/// unweighted control points, which means that each time we sync, we need to
/// apply weights to the control points.
///
/// In splinepy, this will be part of PhysicalSpaceArray.
/// More specifically, _source_ptr attribute.
struct ControlPointPointers {

  /// first pointers of each control points.
  std::vector<double*> coordinate_begins_;

  /// dimension of control points
  int dim_{-1};

  /// flag to let them know that this comes from a rational splines
  bool for_rational_{false};

  /// shared_ptr for weight pointers
  std::shared_ptr<WeightPointers> weight_pointers_ = nullptr;

  /// Validity flag. Set to false by parent spline's dtor. Stops any syncing
  ///
  bool invalid_{false};

  /// Returns Number of control points
  int Len() const { return coordinate_begins_.size(); }

  /// Returns dimension
  int Dim() const {
    assert(dim_ > 0);
    return dim_;
  };

  /// Set a single row
  void SetRow(const int id, const double* values);

  /// Sets multiple rows.
  /// If tparam is true, we assume that values will have same size (len * dim)
  /// as control points. Other wise, (n_rows * dim)
  template<bool same_sized_value>
  void SetRows(const int* ids, const int n_rows, const double* values);

  /// Sync whole control points with values.
  void Sync(const double* values);
};

/// Similar to ControlPointPointers, but for weights.
/// This same layout as ControlPointPointers, because in BSplineLib, weights
/// are saved as last element of the homogeneous control points, which means
/// that it is not contiguous. bezman, however, has a contiguous array, but
/// this approach is applicable for both case.
struct WeightPointers {
  /// Pointer to weights.
  std::vector<double*> weights_;

  /// weak_ptr to partner control points. shared_ptr will cause
  /// cyclic dependency
  std::weak_ptr<ControlPointPointers> control_point_pointers_;

  /// Dimension of the weights are always one.
  static const int dim_{1};

  /// Validity flag.
  bool invalid_{false};

  /// Number of weights. Same as number of control points
  int Len() const { return weights_.size(); }

  /// Dimension. Always one.
  int Dim() const {
    assert(dim_ > 0);
    return dim_;
  };

  /// Sets one row entry. It updates weights
  /// and adjusts weighted control points.
  void SetRow(const int id, double const& value);

  /// Same as ControlPointPointer's SetRows. Here, it calls
  /// SetRow iteratively.
  template<bool same_sized_value>
  void SetRows(const int* ids, const int n_rows, const double* values);

  /// Syncs whole array by calling SetRow iteratively.
  void Sync(const double* values);
};

template<bool same_sized_values>
void ControlPointPointers::SetRows(const int* ids,
                                   const int n_rows,
                                   const double* values) {
  if (invalid_) {
    return;
  }
  const auto dim = Dim();
  const auto len = Len();

  if (for_rational_) {
    const auto& weights = weight_pointers_->weights_;
    for (int i{}; i < n_rows; ++i) {
      // get id
      const auto current_id = WrapId(ids[i], len);
      // get destinations and sources
      auto* current_coord = coordinate_begins_[current_id];
      const double* current_value;
      if constexpr (same_sized_values) {
        current_value = &values[current_id * dim];
      } else {
        current_value = &values[i * dim];
      }
      const auto& current_weight = *weights[current_id];

      for (int j{}; j < dim; ++j) {
        // saves weighted control points
        current_coord[j] = current_value[j] * current_weight;
      }
    }
  } else {
    for (int i{}; i < n_rows; ++i) {
      // get id
      const auto current_id = WrapId(ids[i], len);
      // get destinations and sources
      auto* current_coord = coordinate_begins_[current_id];
      const double* current_value;
      if constexpr (same_sized_values) {
        current_value = &values[current_id * dim];
      } else {
        current_value = &values[i * dim];
      }

      for (int j{}; j < dim; ++j) {
        // saves weighted control points
        current_coord[j] = current_value[j];
      }
    }
  }
}

template<bool same_sized_values>
void WeightPointers::SetRows(const int* ids,
                             const int n_rows,
                             const double* values) {
  if (invalid_) {
    return;
  }

  for (int i{}; i < n_rows; ++i) {
    if constexpr (same_sized_values) {
      SetRow(ids[i], values[ids[i]]);
    } else {
      SetRow(ids[i], values[i]);
    }
  }
}

} // namespace splinepy::utils
