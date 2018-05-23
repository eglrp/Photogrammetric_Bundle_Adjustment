#ifndef CORE_CAMERA_H
#define CORE_CAMERA_H

#include "Image.h"

namespace Core {
/**
 * This is the class for Interior Orientation Parameters (IOPs) of the utilized
 * frame camera
 */
class InteriorOrientation {
  // Width and Height of image
  unsigned int width;
  unsigned int height;
  // Pixel size
  double xPixelSize;
  double yPixelSize;
  // Focal length
  double c;
  // Principal offset
  double xp;
  double yp;
  // Distortion parameters
  double k1;
  double k2;
  double k3;
  double p1;
  double p2;
  double a1;
  double a2;
  // r0
  double r0;
};

/**
 * This is the class for frame camera
 */
class FrameCamera {
private:
  /// Flag for reference and non-reference camera
  /// true: reference camera; false: non-reference camera
  bool mReferenceCamera;
  /**
   * Mounting parameters (i.e., lever-arm and bore-sight angles)
   * Note: If this is a reference camera, the mounting parameters describes the
   * translation and rotation from the reference camera to the GNSS/INS center.
   * If this is a non-reference camera, the mounting parameters represent the
   * transformation from the non-reference camera to the reference camera.
   */
  ExteriorOrientation mMountingParameters;
};
} // namespace Core

#endif // CORE_CAMERA_H
