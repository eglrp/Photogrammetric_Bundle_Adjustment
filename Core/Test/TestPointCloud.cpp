#include "Point.h"
#include "PointCloud.h"
#include "gtest/gtest.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(PointCloud, BasicPointCloudOperation) {
  using PointType = Core::PointXYZf;
  // Prepare several 3D points
  std::string pointId1 = "1";
  PointType point1({0.1f, 0.2f, 0.3f});
  std::string pointId2 = "2";
  PointType point2({0.4f, 0.5f, 0.6f});

  Core::PointCloud<PointType> pointCloud;
  pointCloud.addPoint(pointId1, point1);
  pointCloud.addPoint(pointId2, point2);

  // Extract point with pointId
  auto extractedPoint1 = pointCloud.getPoint(pointId1);
  EXPECT_EQ(extractedPoint1[0], 0.1f);
  EXPECT_EQ(extractedPoint1[1], 0.2f);
  EXPECT_EQ(extractedPoint1[2], 0.3f);

  auto extractedPoint2 = pointCloud.getPoint(pointId2);
  EXPECT_EQ(extractedPoint2[0], 0.4f);
  EXPECT_EQ(extractedPoint2[1], 0.5f);
  EXPECT_EQ(extractedPoint2[2], 0.6f);

  // pointId3 cannot be found in pointCloud
  std::string pointId3 = "3";
  ASSERT_THROW(pointCloud.getPoint("pointId3"), std::invalid_argument);

  // Get number of points
  EXPECT_EQ(pointCloud.getNumberOfPoints(), 2);

  // Delete points
  EXPECT_TRUE(pointCloud.deletePoint(pointId1));
  EXPECT_EQ(pointCloud.getNumberOfPoints(), 1);
  // pointId3 cannot be found in pointCloud
  EXPECT_TRUE(!pointCloud.deletePoint(pointId3));
}
