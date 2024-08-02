#include "../../App/Model/Maze/Maze.h"
#include "../Tests.h"

using namespace s21;

class MazeLoadTests : public testing::Test {
protected:
  Maze maze_;

  void SetUp() override {}
  void TearDown() override {}
};

TEST_F(MazeLoadTests, MazeLoadTest) {
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
}

TEST_F(MazeLoadTests, IncorrectMazeSize) {
    // Act
    OpResult result = maze_.load("test_files/maze/incorrect_size/IS_rows_less_0.txt");
    std::vector<Line> lines = std::move(maze_.get(500, 500));

    // Assert
    EXPECT_FALSE(result.IsSuccess());
    EXPECT_EQ(result.getErrorMessage(), "Incorrect maze size");

    EXPECT_EQ(lines.size(), 0);


    // Act
    result = maze_.load("test_files/maze/incorrect_size/IS_cols_less_0.txt");
    lines = std::move(maze_.get(500, 500));

    // Assert
    EXPECT_FALSE(result.IsSuccess());
    EXPECT_EQ(result.getErrorMessage(), "Incorrect maze size");

    EXPECT_EQ(lines.size(), 0);


    // Act
    result = maze_.load("test_files/maze/incorrect_size/IS_cols_more_50.txt");
    lines = std::move(maze_.get(500, 500));

    // Assert
    EXPECT_FALSE(result.IsSuccess());
    EXPECT_EQ(result.getErrorMessage(), "Incorrect maze size");

    EXPECT_EQ(lines.size(), 0);


    // Act
    result = maze_.load("test_files/maze/incorrect_size/IS_rows_more_50.txt");
    lines = std::move(maze_.get(500, 500));

    // Assert
    EXPECT_FALSE(result.IsSuccess());
    EXPECT_EQ(result.getErrorMessage(), "Incorrect maze size");

    EXPECT_EQ(lines.size(), 0);
}

TEST_F(MazeLoadTests, InvalidMazeData) {
    // Act
    OpResult result = maze_.load("test_files/maze/invalid_maze_data/invalid_data_v.txt");
    std::vector<Line> lines = std::move(maze_.get(500, 500));

    // Assert
    EXPECT_FALSE(result.IsSuccess());
    EXPECT_EQ(result.getErrorMessage(), "Invalid maze data");

    EXPECT_EQ(lines.size(), 0);


    // Act
    result = maze_.load("test_files/maze/invalid_maze_data/invalid_data_h.txt");
    lines = std::move(maze_.get(500, 500));

    // Assert
    EXPECT_FALSE(result.IsSuccess());
    EXPECT_EQ(result.getErrorMessage(), "Invalid maze data");

    EXPECT_EQ(lines.size(), 0);
}

TEST_F(MazeLoadTests, FileDoesNotExist) {
    // Act
    OpResult result = maze_.load("test_files/does_not_exist.txt");
    std::vector<Line> lines = std::move(maze_.get(500, 500));

    // Assert
    EXPECT_FALSE(result.IsSuccess());
    EXPECT_EQ(result.getErrorMessage(), "File not found");

    EXPECT_EQ(lines.size(), 0);
}