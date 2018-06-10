#include "Camera.h"

namespace Core {
template <typename TDataType, int Size>
FrameCamera<TDataType, Size>::FrameCamera(
    const std::string &referenceCameraId,
    const ExteriorOrientation<TDataType> &mountingParams,
    const InteriorOrientation<TDataType, Size> &iops)
    : mMountingParameters(mountingParams), InteriorOrientation<TDataType, Size>(
                                               iops),
      mReferenceCameraId(referenceCameraId) {}

template <typename TDataType, int Size>
const std::string &FrameCamera<TDataType, Size>::getReferenceCameraId() const {
  return mReferenceCameraId;
}

template <typename TDataType, int Size>
const ExteriorOrientation<TDataType> &
FrameCamera<TDataType, Size>::getMountingParameters() const {
  return mMountingParameters;
}

template <typename TDataType, int Size>
ExteriorOrientation<TDataType> &
FrameCamera<TDataType, Size>::getMountingParameters() {
  return mMountingParameters;
}

} // namespace Core
