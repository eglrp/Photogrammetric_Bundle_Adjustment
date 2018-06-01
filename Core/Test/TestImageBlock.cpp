#include "ImageBlock.h"
#include "Point.h"
#include "RandomNumber.h"

#include "gtest/gtest.h"

#include <time.h>

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

// Prepare a global image block object
using DataType = double;
using CameraType = Core::FrameCamera<DataType, 7>;
using ImageType = Core::Image<Core::ImagePoint, DataType>;
using ObjectPointType = Core::ObjectPoint;
Core::ImageBlock<CameraType, ImageType, ObjectPointType, DataType> imageBlock;

TEST(ImageBlock, AddCameraToImageBlock) {
  // Prepare two camera objects
  CameraType camera1;
  imageBlock.addCamera("camera1", std::make_shared<CameraType>(camera1));
  CameraType camera2;
  imageBlock.addCamera("camera2", std::make_shared<CameraType>(camera2));

  // Check the number of cameras in the image block
  EXPECT_EQ(imageBlock.getNumberOfCameras(), 2);

  // Get camera with unknown cameraId
  ASSERT_THROW(imageBlock.getCamera("image3"), std::invalid_argument);
}

TEST(ImageBlock, AddImageToImageBlock) {
  // Prepare two image objects
  unsigned int numberOfImagePoints = 10;
  ImageType image1;
  ImageType image2;
  for (unsigned int pointId = 0; pointId < numberOfImagePoints; ++pointId) {
    Core::ImagePoint point(0.1 * static_cast<double>(pointId),
                           0.2 * static_cast<double>(pointId));
    std::string imgPtId = std::to_string(pointId);
    image1.addPoint(imgPtId, point);
    image2.addPoint(imgPtId, point);
  }

  // Add the two images to the image block
  imageBlock.addImage("image1", std::make_shared<ImageType>(image1));
  imageBlock.addImage("image2", std::make_shared<ImageType>(image2));

  // Check the number of images in the image block
  EXPECT_EQ(imageBlock.getNumberOfImages(), 2);
  // Get the 1st image object through imageId
  auto extractedImage = imageBlock.getImage("image1");
  EXPECT_EQ(extractedImage->getNumberOfPoints(), numberOfImagePoints);
  for (unsigned int pointId = 0; pointId < numberOfImagePoints; ++pointId) {
    auto extractedPoint = image1.getPoint(std::to_string(pointId));
    EXPECT_EQ(extractedPoint[0], 0.1 * static_cast<double>(pointId));
    EXPECT_EQ(extractedPoint[1], 0.2 * static_cast<double>(pointId));
  }

  // Get image with unknown imageId
  ASSERT_THROW(imageBlock.getImage("image3"), std::invalid_argument);
}

TEST(ImageBlock, AddObjectPointToImageBlock) {
  // Prepare object points
  unsigned int numberOfObjectPoints = 10;
  for (unsigned int pointId = 0; pointId < numberOfObjectPoints; ++pointId) {
    ObjectPointType point(0.1 * static_cast<double>(pointId),
                          0.2 * static_cast<double>(pointId),
                          0.3 * static_cast<double>(pointId));
    imageBlock.addObjectPoint(std::to_string(pointId),
                              std::make_shared<ObjectPointType>(point));
  }

  // Check the number of object points in the image block
  EXPECT_EQ(imageBlock.getNumberOfObjectPoints(), numberOfObjectPoints);

  // Compare every object point
  for (unsigned int pointId = 0; pointId < numberOfObjectPoints; ++pointId) {
    auto extractedPoint = imageBlock.getObjectPoint(std::to_string(pointId));
    EXPECT_EQ(extractedPoint[0], 0.1 * static_cast<double>(pointId));
    EXPECT_EQ(extractedPoint[1], 0.2 * static_cast<double>(pointId));
    EXPECT_EQ(extractedPoint[2], 0.3 * static_cast<double>(pointId));
  }

  // Get object points with unknown pointId
  ASSERT_THROW(imageBlock.getObjectPoint(std::to_string(numberOfObjectPoints)),
               std::invalid_argument);
}

TEST(ImageBlock, AddNavigationDataToImageBlock) {
  using NavigationType = Core::ExteriorOrientation<double>;
  // Prepare navigation data (GNSS/INS measurements)
  unsigned int numberOfNavigationMeasurements = 10;
  for (unsigned int navigationId = 0;
       navigationId < numberOfNavigationMeasurements; ++navigationId) {
    NavigationType navigationMeasurement;
    navigationMeasurement.SetTranslation(
        0.1 * static_cast<double>(navigationId),
        0.2 * static_cast<double>(navigationId),
        0.3 * static_cast<double>(navigationId));
    navigationMeasurement.SetRotation(45.0, 30.0, 90.0);
    imageBlock.addNavigationData(
        navigationId, std::make_shared<NavigationType>(navigationMeasurement));
  }
  // Check number of navigation measurements
  EXPECT_EQ(imageBlock.getNumberOfNavigationMeasurements(),
            numberOfNavigationMeasurements);
  // Get the 1st navigation measurement (i.e., timestamp = 1)
  auto extractedNavigationMeasurement = imageBlock.getNavigationMeasurement(1);
  // Compare translation
  auto translation = extractedNavigationMeasurement->getTranslation();
  EXPECT_EQ(translation[0], 0.1);
  EXPECT_EQ(translation[1], 0.2);
  EXPECT_EQ(translation[2], 0.3);
  // Compare rotation
  auto rotation = extractedNavigationMeasurement->getRotationInDegrees();
  EXPECT_EQ(rotation[0], 45.0);
  EXPECT_EQ(rotation[1], 30.0);
  EXPECT_EQ(rotation[2], 90.0);
  // Get timestamp = 10
  ASSERT_THROW(
      imageBlock.getNavigationMeasurement(numberOfNavigationMeasurements),
      std::invalid_argument);
}
