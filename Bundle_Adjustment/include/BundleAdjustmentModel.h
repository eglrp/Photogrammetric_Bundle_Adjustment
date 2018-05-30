#ifndef BUNDLEADJUSTMENT_MODEL_H
#define BUNDLEADJUSTMENT_MODEL_H

#include "ceres/ceres.h"
#include "ceres/dynamic_autodiff_cost_function.h"
#include "ceres/rotation.h"

#include "ImageBlock.h"

namespace BundleAdjustment {
class BundleAdjustmentModel {
public:
  // Defalut constructor and destructor
  BundleAdjustmentModel() = default;
  ~BundleAdjustmentModel() = default;
};
} // namespace BundleAdjustment

#include "BundleAdjustmentModel.hpp"

#endif // BUNDLEADJUSTMENT_MODEL_H
