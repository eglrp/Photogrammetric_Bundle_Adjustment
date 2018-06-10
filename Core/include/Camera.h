#ifndef CORE_CAMERA_H
#define CORE_CAMERA_H

#include "Image.h"
#include "InteriorOrientation.h"

namespace Core {
/**
 * This is the class for frame camera
 */
template <typename TDataType = double, int Size = 9>
class FrameCamera : public InteriorOrientation<TDataType, Size> {
public:
  /// Defalut constructor
  FrameCamera() = default;
  ~FrameCamera() = default;

  /// Constructor
  FrameCamera(const std::string &referenceCameraId,
              const ExteriorOrientation<TDataType> &mountingParams,
              const InteriorOrientation<TDataType, Size> &iops);

  /// Accessor of mReferenceId
  const std::string &getReferenceCameraId() const;
  /// Accessor of mMountingParameters
  const ExteriorOrientation<TDataType> &getMountingParameters() const;
  ExteriorOrientation<TDataType> &getMountingParameters();

private:
  /**
   * cameraId of its reference camera
   * Note: Each camera can only have one reference camera. If cameraId ==
   * referenceCameraId, it means the camera itself is a reference camera.
   * For single camera, the reference camera is always itself.
   */
  std::string mReferenceCameraId;

  /**
   * Note: If this is a reference camera, the mounting parameters describes the
   * translation and rotation from the reference camera to the GNSS/INS body
   * frame. If this is a non-reference camera, the mounting parameters represent
   * the transformation from the non-reference camera to the reference one.
   */
  ExteriorOrientation<TDataType> mMountingParameters;
};
} // namespace Core

#include "Camera.hpp"

#endif // CORE_CAMERA_H
