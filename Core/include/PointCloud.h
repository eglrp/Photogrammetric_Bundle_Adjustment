#ifndef CORE_POINTCLOUD_H
#define CORE_POINTCLOUD_H

#include <unordered_map>

#include "boost/optional.hpp"

namespace Core {
/**
 * This is the class for a point cloud
 */
template <typename PointType> class PointCloud {
public:
  /// Default constructor
  PointCloud() = default;

  /**
   * Given an point and corresponding pointId, add it to mPoints
   * @return True: if point is added to mPoints; False: if the pointId is
   * already in mImagePoints
   */
  bool addPoint(const std::string &pointId, const PointType &point);

  /**
   * Delete point at pointId from mPoints
   * @return True: if point is deleted; False: if no pointId can be found in
   * mPoints
   */
  bool deletePoint(const std::string &pointId);

  /**
   * Return point at pointId
   * @return If no pointId can be found, return boost::none.
   */
  boost::optional<PointType> getPoint(const std::string &pointId) const;

  /**
   * Return the number of points in mImagePoints
   */
  unsigned int getNumberOfPoints() const;

  /**
   * Return the set of points
   */
  const std::unordered_map<std::string, PointType> &getPoints() const;

private:
  /// The set of points are stored in an unordered_map
  std::unordered_map<std::string, PointType> mPoints;
};
} // namespace Core

#include "PointCloud.hpp"

#endif // CORE_POINT_CLOUD_H
