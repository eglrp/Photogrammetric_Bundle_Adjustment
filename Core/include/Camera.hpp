#include "Camera.h"

namespace Core {
template <typename DataType, int Size>
FrameCamera<DataType, Size>::FrameCamera(
    const std::string &referenceCameraId,
    const ExteriorOrientation<DataType> &mountingParams,
    const InteriorOrientation<DataType, Size> &iops)
    : mReferenceCameraId(referenceCameraId),
      mMountingParameters(mountingParams), mIOPs(iops) {}

template <typename DataType, int Size>
const std::string &FrameCamera<DataType, Size>::getReferenceCameraId() const {
  return mReferenceCameraId;
}

} // namespace Core
