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
   * This function computes the re-projection errors of an image point through
   * collinearity model
   * @param[in] cameraIOPs A (3 + n) x 1 array containing IOPs of the utilized
   * cameras (i.e., xp, yp, c and n distortion parameters)
   * @param[in] objectPoint A 3 x 1 array containing object point coordinates
   * @param[in] bodyFrameEOPs A 6 x 1 array containing the eops of the body
   * frame at each imaging epoch (Note: If POS unit is onboard the platform, the
   * EOPs of the body frame is defined by the GNSS/INS measurements. Otherwise,
   * the eops of the body frame is defined at the reference camera of the
   * platform)
   * @param[in] refCameraToBodyFrameParams A 6 x 1 array containing the relative
   * orientation parameters (i.e., lever-arm and bore-sight angles) from the
   * reference camera to the body frame
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
  template <typename TDataType, typename TImagePointType,
            typename TDistortionFunctorType>
  static void ComputeCollinearityReprojectionErrors(
      const TDataType *const cameraIOPs, const TDataType *const objectPoint,
      const TDataType *const bodyFrameEOPs,
      const TDataType *const refCameraToBodyFrameParams,
      const TDataType *const nonRefCameraToRefCameraParams,
      const TDataType *residuals, const TImagePointType &imagePoint,
      TDistortionFunctorType distortionModelFunctor);

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
