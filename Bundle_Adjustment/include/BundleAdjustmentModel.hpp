#include "BundleAdjustmentModel.h"

namespace BundleAdjustment {
template <typename TDataType>
void ComputeCollinearityProjection(
    const TDataType *const objectPoint, const TDataType *const bodyFrameParams,
    const TDataType *const refCameraToBodyFrameParams,
    const TDataType *const nonRefCameraToRefCameraParams) {
  /// Object point coordinates in mapping frame
  Eigen::Matrix<TDataType, 3, 1> rIm;
  rIm(0) = *(objectPoint + 0);
  rIm(1) = *(objectPoint + 1);
  rIm(2) = *(objectPoint + 2);

  /// From body frame to mapping frame
  // Translation
  Eigen::Matrix<TDataType, 3, 1> translationFromBodyFrameToMapping;
  translationFromBodyFrameToMapping(0) = *(bodyFrameParams + 0);
  translationFromBodyFrameToMapping(1) = *(bodyFrameParams + 1);
  translationFromBodyFrameToMapping(2) = *(bodyFrameParams + 2);
  // Rotation
  Eigen::Matrix<TDataType, 3, 1> rotationAngles;
  rotationAngles(0) = *(bodyFrameParams + 3);
  rotationAngles(1) = *(bodyFrameParams + 4);
  rotationAngles(2) = *(bodyFrameParams + 5);
  auto rotationFromBodyFrameToMapping = Core::ExteriorOrientation<
      TDataType>::CreateRotationMatrixFromEluerAnglesInRadians(rotationAngles);

  /// From reference camera to mapping frame
  // Translation
  Eigen::Matrix<TDataType, 3, 1> translationFromRefCameraToBodyFrame;
  translationFromRefCameraToBodyFrame(0) = *(refCameraToBodyFrameParams + 0);
  translationFromRefCameraToBodyFrame(1) = *(refCameraToBodyFrameParams + 1);
  translationFromRefCameraToBodyFrame(2) = *(refCameraToBodyFrameParams + 2);
  // Rotation
  rotationAngles(0) = *(refCameraToBodyFrameParams + 3);
  rotationAngles(1) = *(refCameraToBodyFrameParams + 4);
  rotationAngles(2) = *(refCameraToBodyFrameParams + 5);
  auto rotationFromRefCameraToMapping = Core::ExteriorOrientation<
      TDataType>::CreateRotationMatrixFromEluerAnglesInRadians(rotationAngles);

  /// From non-reference camera to reference camera
}
} // namespace BundleAdjustment
