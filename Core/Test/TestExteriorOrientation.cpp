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

TEST(ExteriorOrientation, TransformTo) {
  using DataType = double;
  // Transform from a to b
  Core::ExteriorOrientation<DataType> exterior;
  exterior.setRotation(-90.0, 0.0, 0.0);
  exterior.setTranslation(1.0, 0.0, 0.0);
  // Reverse transform from b to a
  auto rotation = Core::ExteriorOrientation<DataType>::
      CreateRotationMatrixFromEulerAnglesInDegrees(
          exterior.getRotationInDegrees());
  auto reverseRotationAngles = Core::ExteriorOrientation<DataType>::
      GetEulerAnglesInDegreesFromRotationMatrix(rotation.transpose());
  auto reverseTranslation = -rotation.transpose() * exterior.getTranslation();
  Core::ExteriorOrientation<DataType> reverseExterior;
  reverseExterior.setRotation(reverseRotationAngles[0],
                              reverseRotationAngles[1],
                              reverseRotationAngles[2]);
  reverseExterior.setTranslation(reverseTranslation[0], reverseTranslation[1],
                                 reverseTranslation[2]);
  // Combined transformation a -> b -> a
  auto combined = exterior.transformTo(reverseExterior);
  auto combinedTranslation = combined.getTranslation();
  EXPECT_DOUBLE_EQ(combinedTranslation[0], 0.0);
  EXPECT_DOUBLE_EQ(combinedTranslation[1], 0.0);
  EXPECT_DOUBLE_EQ(combinedTranslation[2], 0.0);
  auto combinedRotation = combined.getRotation();
  EXPECT_DOUBLE_EQ(combinedRotation[0], 0.0);
  EXPECT_DOUBLE_EQ(combinedRotation[1], 0.0);
  EXPECT_DOUBLE_EQ(combinedRotation[2], 0.0);
}
