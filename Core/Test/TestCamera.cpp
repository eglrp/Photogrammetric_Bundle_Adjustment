#include "Camera.h"
#include "gtest/gtest.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(Image, ConstructFrameCamera) {
  using DataType = double;
  // Prepare EOPs
  Core::ExteriorOrientation<DataType> mountingParams;
  mountingParams.SetTranslation(0.1, 0.2, 0.3);
  mountingParams.SetRotation(90.0, 30.0, 40.0);
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
}
