#ifndef BUNDLEADJUSTMENT_MODEL_H
#define BUNDLEADJUSTMENT_MODEL_H

#include "ceres/ceres.h"
#include "ceres/dynamic_autodiff_cost_function.h"
#include "ceres/rotation.h"

#include "ImageBlock.h"

namespace BundleAdjustment {
class BundleAdjustmentModel {
public:
  /// Defalut constructor and destructor
  BundleAdjustmentModel() = default;
  ~BundleAdjustmentModel() = default;

  /**
   * This function computes the back-projection of an object point through
   * collinearity model
   * @param[in] cameraIOPs A (3 + n) x 1 array containing IOPs of the utilized
   * cameras (i.e., xp, yp, c and n distortion parameters)
   * @param[in] objectPoint A 3 x 1 array containing object point coordinates
   * @param[in] bodyFrameParams A 6 x 1 array containing the eops of the body
   * frame at each imaging epoch (Note: If a direct geo-referencing unit is
   * onboard, the body frame is defined at the center of GNSS/INS unit.
   * Otherwise, the the body frame is defined at the reference camera of the
   * platform)
   * @param[in] refCameraToBodyFrameParams A 6 x 1 array containing the relative
   * orientation parameters from the reference camera to the body frame (i.e.,
   * lever-arm and bore-sight angles)
   * @param[in] nonRefCameraToRefCameraParams A 6 x 1 array contaning the
   * relative orientation parameters (i.e., lever-arm and bore-sight angles)
   * from the non-reference camera to the reference one
   * @param[in] residuals The 2 x 1 residual array (i.e, residuals for x and y
   * image coordinates)
   * @param[in] imagePoint Image coordinates with variance and co-variance
   * matrix
   * @param[in] distortionModelFunctor The function to compute distortions at
   * the image point with given camera IOPs
   */
  template <typename TDataType, typename TDistortionFunctorType>
  static void ComputeCollinearityProjection(
      const TDataType *const objectPoint,
      const TDataType *const bodyFrameParams,
      const TDataType *const refCameraToBodyFrameParams,
      const TDataType *const nonRefCameraToRefCameraParams);

  /**
   * This is the struct containing the collinearity model for platforms equipped
   * with either single or multiple frame cameras
   */
  struct CollinearityFrameCameraCost {
  public:
    template <typename TDataType>
    bool operator()(const TDataType *const camera, const TDataType *const point,
                    const TDataType *const eops,
                    const TDataType *residuals) const;
  };
};
} // namespace BundleAdjustment

#include "BundleAdjustmentModel.hpp"

#endif // BUNDLEADJUSTMENT_MODEL_H
