#include "PointCloud.h"

namespace Core {
template <typename TPointType>
bool PointCloud<TPointType>::addPoint(const std::string &pointId,
                                      const TPointType &point) {
  if (mPoints.count(pointId) != 0) {
    return false;
  } else {
    mPoints[pointId] = point;
    return true;
  }
}

template <typename TPointType>
bool PointCloud<TPointType>::deletePoint(const std::string &pointId) {
  auto search = mPoints.find(pointId);
  if (search != mPoints.end()) {
    mPoints.erase(search);
  } else {
    return false;
  }
  return true;
}

template <typename TPointType>
const TPointType &
PointCloud<TPointType>::getPoint(const std::string &pointId) const {
  auto search = mPoints.find(pointId);
  if (search != mPoints.end()) {
    return search->second;
  } else {
    throw std::invalid_argument("Cannot find the pointId!");
  }
}

template <typename TPointType>
TPointType &PointCloud<TPointType>::getPoint(const std::string &pointId) {
  auto search = mPoints.find(pointId);
  if (search != mPoints.end()) {
    return search->second;
  } else {
    throw std::invalid_argument("Cannot find the pointId!");
  }
}

template <typename TPointType>
unsigned int PointCloud<TPointType>::getNumberOfPoints() const {
  return mPoints.size();
}

template <typename TPointType>
const std::unordered_map<std::string, TPointType> &
PointCloud<TPointType>::getPoints() const {
  return mPoints;
}
} // namespace Core
