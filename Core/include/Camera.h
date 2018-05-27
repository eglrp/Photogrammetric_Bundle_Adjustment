#ifndef CORE_CAMERA_H
#define CORE_CAMERA_H

#include "Image.h"

namespace Core {
/**
 * This is the class for Interior Orientation Parameters (IOPs) of the utilized
 * frame camera
 * DataType: data type of iops
 * Size: the number of distortion parameters associated with iops (default = 7,
 * k1, k2, k3, p1, p2, a1, a2)
 */
template <typename DataType = double, int Size = 7> class InteriorOrientation {
public:
  /// Default constructor
  InteriorOrientation() = default;

  // Width and Height of image
  unsigned int width;
  unsigned int height;
  // Pixel size
  DataType xPixelSize;
  DataType yPixelSize;
  // Principal offset and Pricipal distance (xp, yp, c)
  Point<DataType, 3> xyc;
  // Distortion parameters (Size x 1 vector)
  Point<DataType, Size> distortionParameters;
  // r0
  DataType r0;
};

/**
 * This is the class for frame camera
 */
template <typename DataType = double, int Size = 7> class FrameCamera {
public:
  /// Defalut constructor
  FrameCamera() = default;
  ~FrameCamera() = default;

  /// Constructor
  FrameCamera(const std::string &referenceCameraId,
              const ExteriorOrientation<DataType> &mountingParams,
              const InteriorOrientation<DataType, Size> &iops);
  /// Accessor of mReferenceId
  const std::string &getReferenceCameraId() const;

private:
  /**
   * cameraId of its reference camera
   * Note: Each camera can only have one reference camera. If cameraId ==
   * referenceCameraId, it means the camera itself is a reference camera.
   */
  std::string mReferenceCameraId;
  /**
   * Mounting parameters (i.e., lever-arm and bore-sight angles)
   * Note: If this is a reference camera, the mounting parameters describes the
   * translation and rotation from the reference camera to the GNSS/INS center.
   * If this is a non-reference camera, the mounting parameters represent the
   * transformation from the non-reference camera to the reference camera.
   */
  ExteriorOrientation<DataType> mMountingParameters;
  /// Interior orientation parameters (IOPs) of the camera
  InteriorOrientation<DataType, Size> mIOPs;
};
} // namespace Core

#include "Camera.hpp"

#endif // CORE_CAMERA_H
