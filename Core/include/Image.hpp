#include "Image.h"

namespace Core {
template <typename TPointType, typename TDataType>
const std::string &Image<TPointType, TDataType>::cameraId() const {
  return mCameraId;
}

template <typename TPointType, typename TDataType>
const std::unordered_map<std::string, ImagePoint> &
Image<TPointType, TDataType>::getImagePoints() const {
  return this->getPoints();
}

} // namespace Core
