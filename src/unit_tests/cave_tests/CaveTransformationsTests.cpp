#include "../../App/Model/Cave/Cave.h"
#include "../Tests.h"

using namespace s21;

class CaveTransformationsTests : public testing::Test {
protected:
  Cave cave_;

  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(CaveTransformationsTests, AutoTransformationsCave) {
  // Act
  OpResult loadResult = cave_.load("test_files/cave/test_cave.txt");
  OpResult transformResult = cave_.transform(true, 6, 3, 0);
  std::vector<Rect> field = std::move(cave_.get(500, 500));

  // Assert
  EXPECT_TRUE(loadResult.IsSuccess());
  EXPECT_EQ(loadResult.getErrorMessage(), "");

  EXPECT_TRUE(transformResult.IsSuccess());
  EXPECT_EQ(transformResult.getErrorMessage(), "");

  std::vector<Rect> expectedRects = {
    { 0, 0, 126, 126},
    { 375, 0, 126, 126},
    { 0, 125, 126, 126},
    { 250, 125, 126, 126},
    { 375, 125, 126, 126},
    { 0, 250, 126, 126},
    { 125, 250, 126, 126},
    { 250, 250, 126, 126},
    { 375, 250, 126, 126},
    { 0, 375, 126, 126},
    { 125, 375, 126, 126},
    { 250, 375, 126, 126},
    { 375, 375, 126, 126}
  };

  EXPECT_EQ(field.size(), expectedRects.size());  
  EXPECT_EQ(field, expectedRects);
}

TEST_F(CaveTransformationsTests, OneStepTransformationsCave) {
  // Act
  OpResult loadResult = cave_.load("test_files/cave/test_cave.txt");
  OpResult transformResult = cave_.transform(false, 6, 3, 0);
  std::vector<Rect> field = cave_.get(500, 500);

  // Assert
  EXPECT_TRUE(loadResult.IsSuccess());
  EXPECT_EQ(loadResult.getErrorMessage(), "");

  EXPECT_TRUE(transformResult.IsSuccess());
  EXPECT_EQ(transformResult.getErrorMessage(), "");

  std::vector<Rect> expectedField = {
    { 0, 0, 126, 126},
    { 375, 0, 126, 126},
    { 0, 125, 126, 126},
    { 250, 125, 126, 126},
    { 375, 125, 126, 126},
    { 125, 250, 126, 126},
    { 250, 250, 126, 126},
    { 375, 250, 126, 126},
    { 0, 375, 126, 126},
    { 125, 375, 126, 126},
    { 250, 375, 126, 126},
    { 375, 375, 126, 126}
  };

  EXPECT_EQ(field.size(), expectedField.size());  
  EXPECT_EQ(field, expectedField);


  // Act
  transformResult = cave_.transform(false, 6, 3, 0);
  field = std::move(cave_.get(500, 500));

  // Assert
  EXPECT_TRUE(transformResult.IsSuccess());
  EXPECT_EQ(transformResult.getErrorMessage(), "");

  expectedField = {
    { 0, 0, 126, 126},
    { 375, 0, 126, 126},
    { 0, 125, 126, 126},
    { 250, 125, 126, 126},
    { 375, 125, 126, 126},
    { 0, 250, 126, 126},
    { 125, 250, 126, 126},
    { 250, 250, 126, 126},
    { 375, 250, 126, 126},
    { 0, 375, 126, 126},
    { 125, 375, 126, 126},
    { 250, 375, 126, 126},
    { 375, 375, 126, 126},
  };

  EXPECT_EQ(field.size(), expectedField.size());  
  EXPECT_EQ(field, expectedField);
}

TEST_F(CaveTransformationsTests, MaxTransformationCave) {
  // Act 
  OpResult genResult = cave_.generate(50, 50, 40);
  OpResult transformResult = cave_.transform(true, 4, 3, 0);
  std::vector<Rect> field = cave_.get(500, 500);

  // Assert
  EXPECT_TRUE(genResult.IsSuccess());
  EXPECT_EQ(genResult.getErrorMessage(), "");

  EXPECT_TRUE(transformResult.IsSuccess());
  EXPECT_EQ(transformResult.getErrorMessage(), "");

  EXPECT_FALSE(field.empty());
}

TEST_F(CaveTransformationsTests, IncorrectTransformationsParameters) {
  // Act
  OpResult transformResult = cave_.transform(false, 0, 0, 0);
  
  // Assert
  EXPECT_FALSE(transformResult.IsSuccess());
  EXPECT_EQ(transformResult.getErrorMessage(), "Cave is empty");


  // Act
  OpResult loadResult = cave_.load("test_files/cave/test_cave.txt");
  transformResult = cave_.transform(false, -1, 0, 0);

  // Assert
  EXPECT_TRUE(loadResult.IsSuccess());
  EXPECT_EQ(loadResult.getErrorMessage(), "");

  EXPECT_FALSE(transformResult.IsSuccess());
  EXPECT_EQ(transformResult.getErrorMessage(), "Incorrect limits");


  // Act
  transformResult = cave_.transform(false, 0, -1, 0);
  
  // Assert
  EXPECT_FALSE(transformResult.IsSuccess());
  EXPECT_EQ(transformResult.getErrorMessage(), "Incorrect limits");


  // Act
  transformResult = cave_.transform(false, 10, 0, 0);
  
  // Assert
  EXPECT_FALSE(transformResult.IsSuccess());
  EXPECT_EQ(transformResult.getErrorMessage(), "Incorrect limits");


  // Act
  transformResult = cave_.transform(false, 0, 10, 0);
  
  // Assert
  EXPECT_FALSE(transformResult.IsSuccess());
  EXPECT_EQ(transformResult.getErrorMessage(), "Incorrect limits");


  // Act
  transformResult = cave_.transform(false, 3, 4, -10);
  
  // Assert
  EXPECT_FALSE(transformResult.IsSuccess());
  EXPECT_EQ(transformResult.getErrorMessage(), "Incorrect time");
}