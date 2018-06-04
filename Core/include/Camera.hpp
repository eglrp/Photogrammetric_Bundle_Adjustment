#include "Camera.h"

namespace Core {
template <typename TDataType, int Size>
FrameCamera<TDataType, Size>::FrameCamera(
    const std::string &referenceCameraId,
    const ExteriorOrientation<TDataType> &mountingParams,
    const InteriorOrientation<TDataType, Size> &iops)
    : ExteriorOrientation<TDataType>(mountingParams),
      InteriorOrientation<TDataType, Size>(iops),
      mReferenceCameraId(referenceCameraId) {}

template <typename TDataType, int Size>
const std::string &FrameCamera<TDataType, Size>::getReferenceCameraId() const {
  return mReferenceCameraId;
}

} // namespace Core
