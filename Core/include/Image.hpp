#include "Image.h"

namespace Core {
template <typename PointType, typename DataType>
const std::string &Image<PointType, DataType>::cameraId() const {
  return mCameraId;
}

template <typename PointType, typename DataType>
const ExteriorOrientation<DataType> &Image<PointType, DataType>::eop() const {
  return mEOPs;
}

template <typename PointType, typename DataType>
const std::unordered_map<std::string, ImagePoint> &
Image<PointType, DataType>::getImagePoints() const {
  return this->getPoints();
}

template <typename PointType, typename DataType>
unsigned int Image<PointType, DataType>::getTimeTag() const {
  return mTimeTag;
}

} // namespace Core
