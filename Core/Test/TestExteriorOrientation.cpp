#include "ExteriorOrientation.h"
#include "gtest/gtest.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(ExteriorOrientation, EulerAnglesToRotationMatrix) {
  using DataType = double;
  // Define omega, phi, and kappa angles in degrees
  DataType omega = 30.0;
  DataType phi = 45.0;
  DataType kappa = 120.0;
  // Create rotation matrix
  auto rotationMatrix = Core::ExteriorOrientation<
      DataType>::CreateRotationMatrixFromEulerAnglesInDegrees(Eigen::Vector3d{
      omega, phi, kappa});
  // Convert rotation matrix back to Euler angles
  auto eulerAngles = Core::ExteriorOrientation<
      DataType>::GetEulerAnglesInDegreesFromRotationMatrix(rotationMatrix);
  // Compare angles
  EXPECT_DOUBLE_EQ(omega, eulerAngles[0]);
  EXPECT_DOUBLE_EQ(phi, eulerAngles[1]);
  EXPECT_DOUBLE_EQ(kappa, eulerAngles[2]);
}
