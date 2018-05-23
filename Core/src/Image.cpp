#include "Image.h"

namespace Core {
const std::string &Image::cameraId() const { return mCameraId; }

const ExteriorOrientation &Image::eop() const { return mEOPs; }

const std::unordered_map<std::string, ImagePoint> &
Image::getImagePoints() const {
  return this->getPoints();
}

} // namespace Core
