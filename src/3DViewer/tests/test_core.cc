#include <gtest/gtest.h>

#include "../model/model.h"

TEST(Model, EmptyFile) {
  s21::Model model;
  s21::Data data;
  s21::Errors err;
  std::string path = "./pics/empty.obj";
  model.InitData(data);

  model.ParseObjFile(path, data, err);
  EXPECT_TRUE(err.err_ == s21::ErrorCodes::kEmptyFile);
}

TEST(Model, MysticFile) {
  s21::Model model;
  s21::Data data;
  s21::Errors err;
  std::string path = "./pics/qwerty.obj";

  model.ParseObjFile(path, data, err);
  EXPECT_TRUE(err.err_ == s21::ErrorCodes::kEmptyFile);
}

TEST(Model, WrongFile) {
  s21::Model model;
  s21::Data data;
  s21::Errors err;
  std::string path = "./pics/wrong.obj";

  model.ParseObjFile(path, data, err);
  EXPECT_TRUE(err.err_ == s21::ErrorCodes::kWrongCountOfCoords);
}

TEST(Model, SmallFile) {
  s21::Model model;
  s21::Data data;
  s21::Errors err;
  std::string path = "./pics/cub.obj";

  std::vector<double> expected_vertexes = {
      1.000000,  -1.000000, -1.000000, 1.000000,  -1.000000, 1.000000,
      -1.000000, -1.000000, 1.000000,  -1.000000, -1.000000, -1.000000,
      1.000000,  1.000000,  -0.999999, 0.999999,  1.000000,  1.000001,
      -1.000000, 1.000000,  1.000000,  -1.000000, 1.000000,  -1.000000};

  std::vector<std::vector<int>> expected_polygons = {
      {1, 2, 2, 3, 3, 1}, {7, 6, 6, 5, 5, 7}, {4, 5, 5, 1, 1, 4},
      {5, 6, 6, 2, 2, 5}, {2, 6, 6, 7, 7, 2}, {0, 3, 3, 7, 7, 0},
      {0, 1, 1, 3, 3, 0}, {4, 7, 7, 5, 5, 4}, {0, 4, 4, 1, 1, 0},
      {1, 5, 5, 2, 2, 1}, {3, 2, 2, 7, 7, 3}, {4, 0, 0, 7, 7, 4}};

  model.ParseObjFile(path, data, err);
  EXPECT_EQ(data.vertex_, expected_vertexes);
  EXPECT_EQ(data.polygons_, expected_polygons);
  EXPECT_EQ(data.polygons_.size(), 12);
  EXPECT_EQ(data.vertex_in_facete_count_, 36);
  EXPECT_TRUE(err.err_ == s21::ErrorCodes::kOk);
}

TEST(Model, NormallizeModel) {
  s21::Model model;
  s21::Data data;
  s21::Errors err;
  std::string path = "./pics/calc.obj";

  std::vector<double> expected_vertexes = {1, -1, -1, 1, -1, 1, -1, -1, 1};
  std::vector<double> expected_normilize_vertexes = {2, 0,  -2, 2, 0,
                                                     2, -2, 0,  2};

  model.ParseObjFile(path, data, err);

  EXPECT_EQ(data.vertex_.size(), 9);
  EXPECT_EQ(data.polygons_.size(), 4);

  auto it1 = expected_vertexes.begin();
  auto it2 = data.vertex_.begin();

  for (; it2 != data.vertex_.end(); ++it1, ++it2) EXPECT_EQ(*it1, *it2);

  model.Normalize(data);

  auto it3 = expected_normilize_vertexes.begin();
  auto it4 = data.vertex_.begin();

  for (; it4 != data.vertex_.end(); ++it3, ++it4) EXPECT_EQ(*it3, *it4);
}

TEST(Model, ScaleModel) {
  s21::Model model;
  s21::Data data;
  s21::Errors err;
  std::string path = "./pics/cub.obj";

  std::vector<double> expected_vertexes = {4, -4, -4, 4,  -4, 4,  -4, -4,
                                           4, -4, -4, -4, 4,  4,  -4, 3.99999,
                                           4, 4,  -4, 4,  4,  -4, 4,  -4};

  model.ParseObjFile(path, data, err);
  model.Normalize(data);
  model.Scale(data, 2);

  auto it1 = data.vertex_.begin();
  auto it2 = expected_vertexes.begin();

  for (; it1 != data.vertex_.end(); ++it1, ++it2)
    EXPECT_TRUE(std::abs(*it1 - *it2) < 1e-5);
}

TEST(Model, MoveModel) {
  s21::Model model;
  s21::Data data;
  s21::Errors err;
  std::string path = "./pics/cub.obj";

  model.ParseObjFile(path, data, err);
  model.Normalize(data);

  std::vector<double> expected_vertexes1 = {
      2.1, -2, -2, 2.1, -2, 2, -1.9, -2, 2, -1.9, -2, -2,
      2.1, 2,  -2, 2.1, 2,  2, -1.9, 2,  2, -1.9, 2,  -2};
  std::vector<double> expected_vertexes2 = {
      2.1, -1.9, -2, 2.1, -1.9, 2, -1.9, -1.9, 2, -1.9, -1.9, -2,
      2.1, 2.1,  -2, 2.1, 2.1,  2, -1.9, 2.1,  2, -1.9, 2.1,  -2};
  std::vector<double> expected_vertexes3 = {
      2.1, -1.9, -1.9, 2.1, -1.9, 2.1, -1.9, -1.9, 2.1, -1.9, -1.9, -1.9,
      2.1, 2.1,  -1.9, 2.1, 2.1,  2.1, -1.9, 2.1,  2.1, -1.9, 2.1,  -1.9};

  s21::Mover move;

  model.Transformate(&move, 'x', data, 10);
  auto it1 = data.vertex_.begin();
  auto it2 = expected_vertexes1.begin();

  for (; it1 != data.vertex_.end(); ++it1, ++it2)
    EXPECT_TRUE(std::abs(*it1 - *it2) < 1e-5);

  model.Transformate(&move, 'y', data, 10);
  it1 = data.vertex_.begin();
  auto it3 = expected_vertexes2.begin();

  for (; it1 != data.vertex_.end(); ++it1, ++it3)
    EXPECT_TRUE(std::abs(*it1 - *it3) < 1e-5);

  model.Transformate(&move, 'z', data, 10);
  it1 = data.vertex_.begin();
  auto it4 = expected_vertexes3.begin();

  for (; it1 != data.vertex_.end(); ++it1, ++it4)
    EXPECT_TRUE(std::abs(*it1 - *it4) < 1e-5);
}

TEST(Model, RotateModel) {
  s21::Model model;
  s21::Data data;
  s21::Errors err;
  std::string path = "./pics/cub.obj";

  std::vector<double> expected_vertexes1 = {
      2.31691,  -1.62232, -2, 2.31691,  -1.62232, 2,  -1.62232, -2.31691, 2,
      -1.62232, -2.31691, -2, 1.62232,  2.31691,  -2, 1.62232,  2.31691,  2,
      -2.31691, 1.62232,  2,  -2.31691, 1.62232,  -2};
  std::vector<double> expected_vertexes2 = {
      2.62901,  -1.62232, -1.56729, 1.93442,  -1.62232, 2.37194,
      -1.94497, -2.31691, 1.6879,   -1.25038, -2.31691, -2.25133,
      1.94497,  2.31691,  -1.6879,  1.25037,  2.31691,  2.25133,
      -2.62901, 1.62232,  1.56729,  -1.93442, 1.62232,  -2.37194};
  std::vector<double> expected_vertexes3 = {
      2.62901,  -1.32551, -1.82519, 1.93442,  -2.00955, 2.05419,
      -1.94497, -2.57481, 1.25993,  -1.25038, -1.89077, -2.61945,
      1.94497,  2.57481,  -1.25993, 1.25037,  1.89077,  2.61945,
      -2.62901, 1.32552,  1.82519,  -1.93442, 2.00956,  -2.0542};

  model.ParseObjFile(path, data, err);
  model.Normalize(data);

  s21::Rotater rotate;

  model.Transformate(&rotate, 'x', data, 10);
  auto it1 = data.vertex_.begin();
  auto it2 = expected_vertexes1.begin();

  for (; it1 != data.vertex_.end(); ++it1, ++it2)
    EXPECT_TRUE(std::abs(*it1 - *it2) < 1e-5);

  model.Transformate(&rotate, 'y', data, 10);
  it1 = data.vertex_.begin();
  auto it3 = expected_vertexes2.begin();

  for (; it1 != data.vertex_.end(); ++it1, ++it3)
    EXPECT_TRUE(std::abs(*it1 - *it3) < 1e-5);

  model.Transformate(&rotate, 'z', data, 10);
  it1 = data.vertex_.begin();
  auto it4 = expected_vertexes3.begin();

  for (; it1 != data.vertex_.end(); ++it1, ++it4)
    EXPECT_TRUE(std::abs(*it1 - *it4) < 1e-5);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
