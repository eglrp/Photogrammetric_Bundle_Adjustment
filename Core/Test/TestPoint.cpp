#include "Point.h"
#include "gtest/gtest.h"

TEST(Point, ImagePoint) {
  // Image point with default variance-covariance matrix
  ImagePoint point(0.1f, 0.2f, "1");
  EXPECT_EQ(point[0], 0.1f);
  EXPECT_EQ(point[1], 0.2f);
  EXPECT_EQ(point.pointId, "1");
}
