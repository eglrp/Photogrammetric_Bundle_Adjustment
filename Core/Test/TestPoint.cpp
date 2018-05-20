#include "Point.h"
#include "gtest/gtest.h"

TEST(Point, PointInitialization) {
  // 2D Image point with default variance-covariance matrix
  Core::ImagePoint imgPt(0.1f, 0.2f, "1");
  EXPECT_EQ(imgPt[0], 0.1f);
  EXPECT_EQ(imgPt[1], 0.2f);
  // Identity matrix
  EXPECT_EQ(imgPt.covariance(0, 0), 1.0);
  EXPECT_EQ(imgPt.covariance(0, 1), 0.0);
  EXPECT_EQ(imgPt.covariance(1, 0), 0.0);
  EXPECT_EQ(imgPt.covariance(1, 1), 1.0);

  // 3D point with a use-defined variance-covariance matrix
  Eigen::Matrix3d variance;
  variance << 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 0.1, 0.2, 0.3;
  Core::ObjectPoint objPt(0.1f, 0.2f, 0.3f, "1", variance);
  // Variance-covariance matrix
  EXPECT_EQ(objPt.covariance(0, 0), 0.4);
  EXPECT_EQ(objPt.covariance(0, 1), 0.5);
  EXPECT_EQ(objPt.covariance(0, 2), 0.6);
  EXPECT_EQ(objPt.covariance(1, 0), 0.7);
  EXPECT_EQ(objPt.covariance(1, 1), 0.8);
  EXPECT_EQ(objPt.covariance(1, 2), 0.9);
  EXPECT_EQ(objPt.covariance(2, 0), 0.1);
  EXPECT_EQ(objPt.covariance(2, 1), 0.2);
  EXPECT_EQ(objPt.covariance(2, 2), 0.3);
}
