#include "InteriorOrientation.h"
#include "gtest/gtest.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// Prepare IOPs
using DataType = double;
constexpr unsigned int Size = 9;

Core::InteriorOrientation<DataType, Size> PrepareIOPs() {
  // Use the default model with 9 distortion parameters
  Core::InteriorOrientation<DataType, Size> iops;
  // Set xp, yp & c
  iops.xyc << 0.1, 0.2, 500.0;
  // Set width & height
  iops.width = 5000;
  iops.height = 3000;
  // Set pixel size
  iops.xPixelSize = 1.0;
  iops.yPixelSize = 1.0;
  // Set distortion parameters
  iops.distortionParameters << 0.0, 1e-5, 1e-7, 1e-9, 1e-3, 2e-3, 0.0, 0.0, 0.0;
  return iops;
}

TEST(InteriorOrientation, AddAndRemoveDistortions) {
  // Get IOPs
  auto iops = PrepareIOPs();
  // x and y image coordinates
  DataType x = 10;
  DataType y = -5;
  auto distortions = iops.calculateDistortion(x, y);
  std::cout << distortions[0] << "\t" << distortions[1] << std::endl;
  // Get distortion free coordinates
  DataType xDistortionFree = x - distortions[0] - iops.xyc[0];
  DataType yDistortionFree = y - distortions[1] - iops.xyc[1];
  // Add distortion to distortion-free image coordinates
  DataType tolerance = 1e-7;
  auto newImagePt =
      iops.addDistortion(xDistortionFree, yDistortionFree, tolerance);
  std::cout << newImagePt[0] << "\t" << newImagePt[1] << std::endl;
  // Compare image coordinates
  EXPECT_TRUE(std::abs(x - newImagePt[0]) < tolerance);
  EXPECT_TRUE(std::abs(y - newImagePt[1]) < tolerance);
}

TEST(InteriorOrientation, ConvertImageCoordinatesAndPixel) {
  // Get IOPs
  auto iops = PrepareIOPs();
  // Convert pixel to image coordinates
  DataType row = 100.47;
  DataType col = 3721.12;
  auto imageCoords = iops.ConvertPixelToImageCoordinates(row, col);
  // Convert image coordinates to pixel
  auto pixelCoords =
      iops.ConvertImageCoordinatesToPixel(imageCoords[0], imageCoords[1]);
  // Compare row & col
  EXPECT_DOUBLE_EQ(row, pixelCoords[0]);
  EXPECT_DOUBLE_EQ(col, pixelCoords[1]);
}
