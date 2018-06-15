#include "Camera.h"
#include "RandomNumber.h"

#include "gtest/gtest.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(Image, ConstructFrameCamera) {
  using DataType = double;
  Core::RandomDoubleGenerator randomDoubleGenerator(0.0, 1.0);
  // Prepare EOPs
  Core::ExteriorOrientation<DataType> mountingParams;
  mountingParams.setTranslation(randomDoubleGenerator.getRandomNumber(),
                                randomDoubleGenerator.getRandomNumber(),
                                randomDoubleGenerator.getRandomNumber());
  mountingParams.setRotation(90.0, 30.0, 40.0);
  // Prepare IOPs
  Core::InteriorOrientation<DataType, 4> iops;
  iops.width = 2000;
  iops.height = 1000;
  iops.xPixelSize = 1.0;
  iops.yPixelSize = 1.0;
  iops.xyc = Core::Point<DataType, 3>(Eigen::Vector3d{0.1, 0.2, 500.0});
  iops.distortionParameters = Core::Point<DataType, 4>(
      Eigen::Matrix<DataType, 4, 1>{0.1, 0.2, 0.3, 0.4});

  // Generate FrameCamera object
  Core::FrameCamera<DataType, 4> frameCamera("camera", mountingParams, iops);

  // Compare referenceCameraId
  EXPECT_EQ(frameCamera.getReferenceCameraId(), "camera");

  // Get an mutable copy of mounting parameters
  auto &extractedMountingParams = frameCamera.getMountingParameters();
  // Compare translation components
  EXPECT_EQ(mountingParams.getTranslation()[0],
            extractedMountingParams.getTranslation()[0]);
  EXPECT_EQ(mountingParams.getTranslation()[1],
            extractedMountingParams.getTranslation()[1]);
  EXPECT_EQ(mountingParams.getTranslation()[2],
            extractedMountingParams.getTranslation()[2]);
  // Compare rotation
  EXPECT_EQ(mountingParams.getRotation()[0],
            extractedMountingParams.getRotation()[0]);
  EXPECT_EQ(mountingParams.getRotation()[1],
            extractedMountingParams.getRotation()[1]);
  EXPECT_EQ(mountingParams.getRotation()[2],
            extractedMountingParams.getRotation()[2]);

  // Change translation to (0.1, 0.2, 0.3)
  extractedMountingParams.setTranslation(0.1, 0.2, 0.3);
  // Get updated mounting parameters
  const auto &updatedMountingParams = frameCamera.getMountingParameters();
  EXPECT_EQ(updatedMountingParams.getTranslation()[0], 0.1);
  EXPECT_EQ(updatedMountingParams.getTranslation()[1], 0.2);
  EXPECT_EQ(updatedMountingParams.getTranslation()[2], 0.3);
}
