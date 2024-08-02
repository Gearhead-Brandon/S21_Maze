#include "../../App/Model/Maze/Maze.h"
#include "../Tests.h"

using namespace s21;

class MazeQPathFindTests : public testing::Test {
protected:
  Maze maze_;

  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(MazeQPathFindTests, MazeQPathFindTest){
  // Act
  OpResult loadResult = maze_.load("test_files/maze/test_maze_4_4.txt");
  OpResult result = maze_.QPathFinding({0, 0}, {3, 3});
  PathRenderConfig config = std::move(maze_.getPath(500, 500));

  // Assert
  EXPECT_TRUE(loadResult.IsSuccess());
  EXPECT_EQ(loadResult.getErrorMessage(), "");

  EXPECT_TRUE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "");

  std::vector<Rect> expectedPoints = {
    {46.875, 46.875, 31.25, 31.25}, 
    {421.875, 421.875, 31.25, 31.25}
  };

  EXPECT_EQ(config.points_.size(), expectedPoints.size());
  EXPECT_EQ(config.points_, expectedPoints);

  std::vector<Line> expectedPath = {
    {437.5, 437.5, 312.5, 437.5},
    {312.5, 437.5, 312.5, 437.5},
    {312.5, 437.5, 312.5, 312.5},
    {312.5, 312.5, 312.5, 312.5},
    {312.5, 312.5, 312.5, 312.5},
    {312.5, 312.5, 437.5, 312.5},
    {437.5, 312.5, 437.5, 187.5},
    {437.5, 187.5, 437.5, 187.5},
    {437.5, 187.5, 437.5, 62.5},
    {437.5, 62.5, 437.5, 62.5},
    {437.5, 62.5, 312.5, 62.5},
    {312.5, 62.5, 312.5, 62.5},
    {312.5, 62.5, 187.5, 62.5},
    {187.5, 62.5, 187.5, 62.5},
    {187.5, 62.5, 62.5, 62.5},
    {62.5, 62.5, 62.5, 62.5},
  };

  EXPECT_EQ(config.path_.size(), expectedPath.size());
  EXPECT_EQ(config.path_, expectedPath);
}

TEST_F(MazeQPathFindTests, IsolatedMazeTest){
  // Act
  OpResult loadResult = maze_.load("test_files/maze/test_maze_isolated.txt");
  OpResult result = maze_.QPathFinding({0, 0}, {3, 4});

  // Assert
  EXPECT_TRUE(loadResult.IsSuccess());
  EXPECT_EQ(loadResult.getErrorMessage(), "");

  EXPECT_FALSE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "Path not found. Probably the labyrinth has isolated study areas");
}

TEST_F(MazeQPathFindTests, IncorrectPointsTest){
  // Act
  maze_.load("test_files/maze/test_maze_4_4.txt");
  OpResult result = maze_.QPathFinding({-1, 0}, {0, 0});

  // Assert
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "Incorrect point");


  // Act
  maze_.load("test_files/maze/test_maze_4_4.txt");
  result = maze_.QPathFinding({10, 0}, {0, 0});

  // Assert
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "Incorrect point");


  // Act
  maze_.load("test_files/maze/test_maze_4_4.txt");
  result = maze_.QPathFinding({0, -1}, {0, 0});

  // Assert
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "Incorrect point");


  // Act
  maze_.load("test_files/maze/test_maze_4_4.txt");
  result = maze_.QPathFinding({0, 10}, {0, 0});

  // Assert
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "Incorrect point");



  // Act
  maze_.load("test_files/maze/test_maze_4_4.txt");
  result = maze_.QPathFinding({0, 0}, {-1, 0});

  // Assert
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "Incorrect point");


  // Act
  maze_.load("test_files/maze/test_maze_4_4.txt");
  result = maze_.QPathFinding({0, 0}, {10, 0});

  // Assert
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "Incorrect point");


  // Act
  maze_.load("test_files/maze/test_maze_4_4.txt");
  result = maze_.QPathFinding({0, 0}, {0, -1});

  // Assert
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "Incorrect point");


  // Act
  maze_.load("test_files/maze/test_maze_4_4.txt");
  result = maze_.QPathFinding({0, 0}, {0, 10});

  // Assert
  EXPECT_FALSE(result.IsSuccess());
  EXPECT_EQ(result.getErrorMessage(), "Incorrect point");
}