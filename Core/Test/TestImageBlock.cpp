#include "ImageBlock.h"
#include "Point.h"
#include "gtest/gtest.h"

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

TEST(ImageBlock, AddAndGetImageToImageBlock) {
  using CameraType = Core::FrameCamera<double, 6>;
  using ImageType = Core::Image<Core::ImagePoint, double>;
  using ObjectPointType = Core::ObjectPoint;
  Core::ImageBlock<CameraType, ImageType, ObjectPointType, double> imageBlock;
  // Prepare two image objects

  unsigned int numberOfImagePoints = 10;
  ImageType image1;
  ImageType image2;
  for (unsigned int pointId = 0; pointId < numberOfImagePoints; ++pointId) {
    Core::ImagePoint point(0.1 * pointId, 0.2 * pointId);
    std::string imgPtId = std::to_string(pointId);
    image1.addPoint(imgPtId, point);
    image2.addPoint(imgPtId, point);
  }

  imageBlock.getNumberOfImages();

  // Add the two images to the image block
  std::string imageId1 = "image1";
  imageBlock.addImage(imageId1, std::make_shared<ImageType>(image1));
  imageBlock.addImage("image2", std::make_shared<ImageType>(image2));

  // Check the number of images in the image block
  EXPECT_EQ(imageBlock.getNumberOfImages(), 2);
}
