#include "PointCloud.h"

namespace Core {
template <typename PointType>
bool PointCloud<PointType>::addPoint(const std::string &pointId,
                                     const PointType &point) {
  if (mPoints.count(pointId) != 0) {
    return false;
  } else {
    mPoints[pointId] = point;
    return true;
  }
}

template <typename PointType>
bool PointCloud<PointType>::deletePoint(const std::string &pointId) {
  auto search = mPoints.find(pointId);
  if (search != mPoints.end()) {
    mPoints.erase(search);
  } else {
    return false;
  }
  return true;
}

template <typename PointType>
PointType &PointCloud<PointType>::getPoint(const std::string &pointId) {
  auto search = mPoints.find(pointId);
  if (search != mPoints.end()) {
    return search->second;
  } else {
    throw std::invalid_argument("Cannot find the pointId!");
  }
}

template <typename PointType>
unsigned int PointCloud<PointType>::getNumberOfPoints() const {
  return mPoints.size();
}

template <typename PointType>
const std::unordered_map<std::string, PointType> &
PointCloud<PointType>::getPoints() const {
  return mPoints;
}
} // namespace Core
