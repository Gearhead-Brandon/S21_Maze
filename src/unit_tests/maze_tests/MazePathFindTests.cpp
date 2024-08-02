#include "../../App/Model/Maze/Maze.h"
#include "../Tests.h"

using namespace s21;

class MazePathFindTests : public testing::Test {
protected:
  Maze maze_;

  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(MazePathFindTests, MazePathFindTest) {
    // Act
    OpResult result = maze_.load("test_files/maze/test_maze_4_4.txt");
    std::vector<Line> lines = std::move(maze_.get(500, 500));

    // Assert
    EXPECT_TRUE(result.IsSuccess());
    EXPECT_EQ(result.getErrorMessage(), "");

    std::vector<Line> expectedLines = {
        {0, 1, 500, 1},
        {1, 500, 1, 0},
        {499, 499, 0, 499},
        {499, 0, 499, 499},
        {0, 125, 125, 125},
        {250, 125, 375, 125},
        {125, 125, 125, 250},
        {375, 125, 375, 250},
        {250, 250, 375, 250},
        {0, 375, 125, 375},
        {250, 250, 250, 375},
        {125, 375, 250, 375},
        {375, 375, 500, 375}
    };

    EXPECT_EQ(lines.size(), expectedLines.size());
    EXPECT_EQ(lines, expectedLines);


    // Act
    maze_.setStartPosition({10.0f, 10.0f}, 500.0f, 500.0f);
    maze_.setEndPosition({480.0f, 480.0f}, 500.0f, 500.0f);
    PathRenderConfig config = std::move(maze_.getPath(500, 500));

    // Assert
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
        {62.5, 62.5, 62.5, 62.5}
    };

    EXPECT_EQ(config.path_.size(), expectedPath.size());
    EXPECT_EQ(config.path_, expectedPath);

    std::vector<Rect> expectedPoints = {
        {46.875, 46.875, 31.25, 31.25},
        {421.875, 421.875, 31.25, 31.25}
    };

    EXPECT_EQ(config.points_.size(), expectedPoints.size());
    EXPECT_EQ(config.points_, expectedPoints);


    // Act
    maze_.clearPath();
    maze_.setEndPosition({480.0f, 480.0f}, 500.0f, 500.0f);
    maze_.setStartPosition({10.0f, 10.0f}, 500.0f, 500.0f);
    config = std::move(maze_.getPath(500, 500));

    // Assert
    EXPECT_EQ(config.path_.size(), expectedPath.size());
    EXPECT_EQ(config.path_, expectedPath);

    EXPECT_EQ(config.points_.size(), expectedPoints.size());
    EXPECT_EQ(config.points_, expectedPoints);

    // for(auto point : config.points_){
    //     std::cout << "{" << point.x << ", " << point.y << ", " << point.width << ", " << point.height << "}," << std::endl;
    // }
    //std::cout << "{" << config.points_.x << ", " << config.points_.y << ", " << config.points_.width << ", " << config.points_.height << "}," << std::endl;

    // for(auto line : config.path_){
    //     std::cout << "{" << line.begin.col << ", " << line.begin.row << ", " << line.end.col << ", " << line.end.row << "}," << std::endl;
    // }
}

TEST_F(MazePathFindTests, PathDoesNotExists) {
    // Act
    OpResult result = maze_.load("test_files/maze/test_maze_isolated.txt");
    std::vector<Line> lines = std::move(maze_.get(500, 500));

    // Assert
    EXPECT_TRUE(result.IsSuccess());
    EXPECT_EQ(result.getErrorMessage(), "");


    // Act
    maze_.setStartPosition({10.0f, 10.0f}, 490.0f, 490.0f);

    // Assert
    EXPECT_THROW(maze_.setEndPosition({480.0f, 480.0f}, 500.0f, 500.0f), OpResult);
}

TEST_F(MazePathFindTests, EmptyMaze) {
    // Act
    maze_.setStartPosition({10.0f, 10.0f}, 490.0f, 490.0f);
    maze_.setEndPosition({480.0f, 480.0f}, 500.0f, 500.0f);
    std::vector<Line> lines = std::move(maze_.get(500, 500));

    // Assert
    EXPECT_TRUE(lines.empty());


    // Act
    maze_.clearPath();
    PathRenderConfig config = std::move(maze_.getPath(500, 500));

    // Assert
    EXPECT_TRUE(config.path_.empty());
}

TEST_F(MazePathFindTests, IncorrectMazeSize) {
    // Act
    maze_.setStartPosition({10.0f, 10.0f}, 500.0f, 500.0f);
    maze_.setEndPosition({480.0f, 480.0f}, 500.0f, 500.0f);
    PathRenderConfig config = std::move(maze_.getPath(0, 0));

    // Assert
    EXPECT_TRUE(config.path_.empty());   
}