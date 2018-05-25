#include "Image.h"
#include "Point.h"
#include "gtest/gtest.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(Image, AddAndGetPoint) {
  // Prepare a 2D Image point with default variance-covariance matrix
  Core::ImagePoint point(0.1, 0.2);
  std::string pointId = "1";

  Core::Image<Core::ImagePoint> image;
  image.addPoint(pointId, point);

  auto extractedPoint = image.getPoint(pointId);
  EXPECT_EQ(extractedPoint.value()[0], 0.1);
  EXPECT_EQ(extractedPoint.value()[1], 0.2);

  // If no pointId can be found in image
  EXPECT_TRUE(image.getPoint("2") == boost::none);
}

TEST(Image, AddAndDeletePoint) {
  // Prepare a 2D Image point with default variance-covariance matrix
  Core::ImagePoint point(0.1, 0.2);
  std::string pointId = "1";

  Core::Image<Core::ImagePoint> image;
  image.addPoint(pointId, point);

  // Delete point
  EXPECT_TRUE(image.deletePoint(pointId));

  // Expect false
  EXPECT_TRUE(!image.deletePoint(pointId));
}
