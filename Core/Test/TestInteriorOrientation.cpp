#include "InteriorOrientation.h"
#include "gtest/gtest.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(InteriorOrientation, AddAndRemoveDistortions) {
  using DataType = double;
  constexpr unsigned int size = 9;
  // Use the default model with 9 distortion parameters
  Core::InteriorOrientation<DataType, size> iops;
  // Set xp, yp & c
  iops.xyc << 0.1, 0.2, 500.0;
  // Set distortion parameters
  iops.distortionParameters << 0.0, 1e-5, 1e-7, 1e-9, 1e-3, 2e-3, 0.0, 0.0, 0.0;
  // x and y image coordinates
  DataType x = 10;
  DataType y = -5;
  auto distortions = iops.calculateDistortion(x, y);
  std::cout << distortions[0] << "\t" << distortions[1] << std::endl;
  // Get distortion free coordinates
  DataType xDistortionFree = x - distortions[0] - iops.xyc[0];
  DataType yDistortionFree = y - distortions[1] - iops.xyc[1];
  // Add distortion to distortion-free image coordinates
  DataType tolerance = 1e-6;
  auto newImagePt =
      iops.addDistortion(xDistortionFree, yDistortionFree, tolerance);
  std::cout << newImagePt[0] << "\t" << newImagePt[1] << std::endl;
  // Compare image coordinates
  EXPECT_TRUE(std::abs(x - newImagePt[0]) < tolerance);
  EXPECT_TRUE(std::abs(y - newImagePt[1]) < tolerance);
}
