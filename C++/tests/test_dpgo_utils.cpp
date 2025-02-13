#include <filesystem>
#include <fstream>

#include <gtest/gtest.h>
#include <DPGO/DPGO_types.h>
#include <DPGO/DPGO_utils.h>
#include <Eigen/Dense>

class DPGOUtilsTest : public testing::Test {
 protected:
  DPGOUtilsTest() : n_poses_(3), dim_(0) {}

  Eigen::MatrixXd Make2dMatrix() {
    dim_ = 2;
    const int n_rows = n_poses_ * (dim_ + 1);
    const int n_cols = dim_;

    Eigen::MatrixXd M;
    M.setZero(n_rows, n_cols);
    int count = 0;
    for (int i = 0; i < n_rows; i++) {
      for (int j = 0; j < n_cols; j++) {
        M(i, j) = count;
        count++;
      }
    }

    return M;
  }

  Eigen::MatrixXd Make3dMatrix() {
    dim_ = 3;
    const int n_rows = n_poses_ * (dim_ + 1);
    const int n_cols = dim_;

    Eigen::MatrixXd M;
    M.setZero(n_rows, n_cols);
    int count = 0;
    for (int i = 0; i < n_rows; i++) {
      for (int j = 0; j < n_cols; j++) {
        M(i, j) = count;
        count++;
      }
    }

    return M;
  }

  const int n_poses_;
  int dim_;
};

TEST_F(DPGOUtilsTest, SetXFromTextFile2D) {
  const auto M = Make2dMatrix();

  // Write to .txt file
  const std::filesystem::path tmpfile{"./matrix_tmp.txt"};
  std::ofstream output(tmpfile);
  ASSERT_TRUE(output.is_open());
  output << M << std::endl;
  output.close();

  // Set new (dynamic) matrix X from file
  DPGO::Matrix X;
  const int result = DPGO::set_X_from_txt(tmpfile.string(), X, n_poses_, dim_);
  ASSERT_EQ(result, 0);

  // Confirm values
  const auto is_col_major = (X.Options == Eigen::StorageOptions::ColMajor);
  EXPECT_TRUE(is_col_major);  // a sanity check, since column-major is default
  const int n_rows = n_poses_ * (dim_ + 1);
  const int n_cols = dim_;
  int count = 0;
  for (int i = 0; i < n_rows; i++) {
    for (int j = 0; j < n_cols; j++) {
      EXPECT_EQ(X(i, j), count);
      count++;
    }
  }

  // Delete file for cleanup
  std::filesystem::remove(tmpfile);
}

TEST_F(DPGOUtilsTest, SetXFromTextFile3D) {
  const auto M = Make3dMatrix();

  // Write to .txt file
  const std::filesystem::path tmpfile{"./matrix_tmp.txt"};
  std::ofstream output(tmpfile);
  ASSERT_TRUE(output.is_open());
  output << M << std::endl;
  output.close();

  // Set new (dynamic) matrix X from file
  DPGO::Matrix X;
  const int result = DPGO::set_X_from_txt(tmpfile.string(), X, n_poses_, dim_);
  ASSERT_EQ(result, 0);

  // Confirm values
  const auto is_col_major = (X.Options == Eigen::StorageOptions::ColMajor);
  EXPECT_TRUE(is_col_major);  // a sanity check, since column-major is default
  const int n_rows = n_poses_ * (dim_ + 1);
  const int n_cols = dim_;
  int count = 0;
  for (int i = 0; i < n_rows; i++) {
    for (int j = 0; j < n_cols; j++) {
      EXPECT_EQ(X(i, j), count);
      count++;
    }
  }

  // Delete file for cleanup
  std::filesystem::remove(tmpfile);
}
