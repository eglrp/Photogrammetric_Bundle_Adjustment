#include "Image.h"
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
  EXPECT_EQ(extractedPoint[0], 0.1);
  EXPECT_EQ(extractedPoint[1], 0.2);

  // If no pointId can be found in image
  ASSERT_THROW(image.getPoint("2"), std::invalid_argument);
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
