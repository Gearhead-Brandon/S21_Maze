#include "../../App/Model/Cave/Cave.h"
#include "../Tests.h"

using namespace s21;

class CaveLoadTests : public testing::Test {
protected:
  Cave cave_;

  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(CaveLoadTests, LoadCave) {
  // Act 
  OpResult result = cave_.load("test_files/cave/cave1.txt");
  std::vector<Rect> field = cave_.get(500, 500);

  // Assert
  EXPECT_TRUE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "");

  std::vector<Rect> expectedField = {
    { 0, 0, 51, 51},
    { 100, 0, 51, 51},
    { 350, 0, 51, 51},
    { 400, 0, 51, 51},
    { 100, 50, 51, 51},
    { 150, 50, 51, 51},
    { 450, 50, 51, 51},
    { 100, 100, 51, 51},
    { 200, 100, 51, 51},
    { 300, 100, 51, 51},
    { 350, 100, 51, 51},
    { 450, 100, 51, 51},
    { 50, 150, 51, 51},
    { 100, 150, 51, 51},
    { 150, 150, 51, 51},
    { 200, 150, 51, 51},
    { 250, 150, 51, 51},
    { 300, 150, 51, 51},
    { 150, 200, 51, 51},
    { 200, 200, 51, 51},
    { 350, 200, 51, 51},
    { 400, 200, 51, 51},
    { 450, 200, 51, 51},
    { 50, 250, 51, 51},
    { 150, 250, 51, 51},
    { 250, 250, 51, 51},
    { 0, 300, 51, 51},
    { 50, 300, 51, 51},
    { 350, 300, 51, 51},
    { 300, 350, 51, 51},
    { 400, 350, 51, 51},
    { 450, 350, 51, 51},
    { 0, 400, 51, 51},
    { 250, 400, 51, 51},
    { 300, 400, 51, 51},
    { 50, 450, 51, 51},
    { 100, 450, 51, 51},
    { 250, 450, 51, 51},
    { 300, 450, 51, 51},
  };

  EXPECT_EQ(field.size(), expectedField.size());
  EXPECT_EQ(field, expectedField);
}

TEST_F(CaveLoadTests, IncorrectCaveSize) {
  // Act
  OpResult result = cave_.load("test_files/cave/incorrect_size/IS_cols_less_0.txt");
  
  // Assert
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "Incorrect cave size");


  // Act
  result = cave_.load("test_files/cave/incorrect_size/IS_rows_less_0.txt");
  
  // Assert
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "Incorrect cave size");


  // Act
  result = cave_.load("test_files/cave/incorrect_size/IS_cols_more_50.txt");
  
  // Assert
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "Incorrect cave size");


  // Act
  result = cave_.load("test_files/cave/incorrect_size/IS_rows_more_50.txt");
  
  // Assert
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "Incorrect cave size");
}

TEST_F(CaveLoadTests, IncorrectMazeData) {
  // Act
  OpResult result = cave_.load("test_files/cave/invalid_data.txt");

  // Assert
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "Invalid cave data");
}

TEST_F(CaveLoadTests, FileNotFound) {
  // Act
  OpResult result = cave_.load("test_files/file_not_exist.txt");
  std::vector<Rect> field = cave_.get(500, 500);

  // Assert
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "File not found");

  EXPECT_EQ(field.size(), 0);
}