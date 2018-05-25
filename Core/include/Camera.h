#ifndef CORE_CAMERA_H
#define CORE_CAMERA_H

#include "Image.h"

namespace Core {
/**
 * This is the class for Interior Orientation Parameters (IOPs) of the utilized
 * frame camera
 */
template <typename DataType = double, int Size> class InteriorOrientation {
public:
  // Width and Height of image
  unsigned int width;
  unsigned int height;
  // Pixel size
  DataType xPixelSize;
  DataType yPixelSize;
  // Principal offset
  DataType xp;
  DataType yp;
  // Principal distance
  double c;
  // Variance-covariance matrix for (xp, yp, c)
  Eigen::Matrix<DataType, 3, 3> xycCovariance =
      Eigen::Matrix<DataType, 3, 3>::Identity<3, 3>;
  // Distortion parameters (Size x 1 vector)
  Eigen::Matrix<DataType, Size, 1> distortionParameters;
  // Variance-covariance matrix for distortion parameters
  Eigen::Matrix<DataType, Size, Size> distortionCovariance =
      Eigen::Matrix<DataType, Size, Size>::Identity(Size, Size);
  // r0
  double r0;
};

/**
 * This is the class for frame camera
 */
template <typename DataType> class FrameCamera {
private:
  /**
   * cameraId of its reference camera
   * Note: Each camera can only have one reference camera. If cameraId ==
   * referenceCameraId, it means the camera itself is a reference camera.
   */
  std::string referenceCameraId;
  /**
   * Mounting parameters (i.e., lever-arm and bore-sight angles)
   * Note: If this is a reference camera, the mounting parameters describes the
   * translation and rotation from the reference camera to the GNSS/INS center.
   * If this is a non-reference camera, the mounting parameters represent the
   * transformation from the non-reference camera to the reference camera.
   */
  ExteriorOrientation<DataType> mMountingParameters;
  /// Interior orientation parameters (IOPs) of this camera
  InteriorOrientation<DataType> mIOPs;
};
} // namespace Core

#endif // CORE_CAMERA_H
