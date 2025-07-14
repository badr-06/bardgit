#include <gtest/gtest.h>

#include "s21_matrix.hpp"

const double matrix_3_3_[3][3] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};

TEST(Constructor, Default) {
  S21Matrix tp;

  EXPECT_EQ(3, tp.GetRows());
  EXPECT_EQ(3, tp.GetCols());

  for (int i = 0; i < tp.GetRows(); i++) {
    for (int j = 0; j < tp.GetCols(); j++) {
      EXPECT_EQ(0, tp(i, j));
    }
  }
}

TEST(Constructor, RowsCols) {
  S21Matrix tp(3, 3);

  EXPECT_EQ(3, tp.GetRows());
  EXPECT_EQ(3, tp.GetCols());

  for (int i = 0; i < tp.GetRows(); i++) {
    for (int j = 0; j < tp.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(0, tp(i, j));
    }
  }

  EXPECT_THROW(S21Matrix pt(0, 0), std::invalid_argument);
}

TEST(Constructor, Сloning) {
  S21Matrix tp(3, 3);
  S21Matrix pt(tp);

  EXPECT_EQ(pt.GetRows(), tp.GetRows());
  EXPECT_EQ(pt.GetRows(), tp.GetCols());

  EXPECT_EQ(tp.EqMatrix(pt), true);
}

TEST(Constructor, Move) {
  S21Matrix tp(2, 2);
  tp.init(1);

  S21Matrix pt(std::move(tp));

  EXPECT_DOUBLE_EQ(pt(0, 0), 1.0);
  EXPECT_DOUBLE_EQ(pt(0, 1), 2.0);
  EXPECT_DOUBLE_EQ(pt(1, 0), 3.0);
  EXPECT_DOUBLE_EQ(pt(1, 1), 4.0);

  EXPECT_FALSE(tp.check_matrix());
}

TEST(Eqmatrix, equal) {
  S21Matrix tp(3, 3);
  tp.init(1);
  S21Matrix pt(tp);
  S21Matrix p;

  EXPECT_EQ(tp.EqMatrix(pt), true);

  EXPECT_EQ(tp.EqMatrix(p), false);
}

TEST(SumMatrix, sum) {
  S21Matrix tp(3, 3);
  tp.init(1);
  S21Matrix pt(3, 3);
  pt.init(1);

  tp.SumMatrix(pt);

  for (int i = 0; i < tp.GetRows(); i++) {
    for (int j = 0; j < tp.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(tp(i, j), pt(i, j) + pt(i, j));
      EXPECT_TRUE(tp(i, j) != pt(i, j));
    }
  }

  S21Matrix p(3, 2);
  p.init(1);

  EXPECT_THROW(pt.SumMatrix(p), std::invalid_argument);
}

TEST(SubMatrix, sub) {
  S21Matrix tp(3, 3);
  tp.init(1);
  S21Matrix pt(3, 3);
  pt.init(1);

  tp.SubMatrix(pt);

  for (int i = 0; i < tp.GetRows(); i++) {
    for (int j = 0; j < tp.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(tp(i, j), pt(i, j) - pt(i, j));
      EXPECT_TRUE(tp(i, j) != pt(i, j));
    }
  }

  S21Matrix p(3, 2);
  p.init(1);

  EXPECT_THROW(pt.SubMatrix(p), std::invalid_argument);
}

TEST(MulNumber, Mul_N) {
  S21Matrix tp(3, 3);
  tp.init(1);
  S21Matrix pt(3, 3);
  pt.init(1);
  double s = 2;
  tp.MulNumber(s);

  for (int i = 0; i < tp.GetRows(); i++) {
    for (int j = 0; j < tp.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(tp(i, j), pt(i, j) * 2);
      EXPECT_TRUE(tp(i, j) != pt(i, j));
    }
  }
}

TEST(MulMatrix, Mul_M) {
  S21Matrix tp(3, 3);
  tp.init(1);
  S21Matrix pt(3, 3);
  pt.init(1);
  S21Matrix date(3, 3);

  tp.MulMatrix(pt);

  date.SetRowsCols(0, 0, 30);
  date.SetRowsCols(0, 1, 36);
  date.SetRowsCols(0, 2, 42);
  date.SetRowsCols(1, 0, 66);
  date.SetRowsCols(1, 1, 81);
  date.SetRowsCols(1, 2, 96);
  date.SetRowsCols(2, 0, 102);
  date.SetRowsCols(2, 1, 126);
  date.SetRowsCols(2, 2, 150);

  for (int i = 0; i < tp.GetRows(); i++) {
    for (int j = 0; j < tp.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(tp(i, j), date(i, j));
      EXPECT_TRUE(tp(i, j) != pt(i, j));
    }
  }

  S21Matrix p(2, 2);
  p.init(1);
  EXPECT_THROW(pt.MulMatrix(p), std::invalid_argument);
}

TEST(Transpose, test) {
  S21Matrix tp(3, 3);
  tp.init(1);
  S21Matrix pt = tp.Transpose();

  for (int i = 0; i < tp.GetRows(); i++) {
    for (int j = 0; j < tp.GetCols(); j++) {
      EXPECT_EQ(tp(i, j), pt(j, i));
    }
  }
}

TEST(CalcCompl, algebraic_complement_matrix) {
  S21Matrix tp(3, 3);
  S21Matrix pt(3, 3);
  S21Matrix tt(3, 3);
  tp.init(1);
  tt.init(1);

  tp.SetRowsCols(1, 0, 0);
  tp.SetRowsCols(1, 1, 4);
  tp.SetRowsCols(1, 2, 2);
  tp.SetRowsCols(2, 0, 5);
  tp.SetRowsCols(2, 1, 2);
  tp.SetRowsCols(2, 2, 1);

  S21Matrix date = tp.CalcComplements();

  pt.SetRowsCols(0, 0, 0);
  pt.SetRowsCols(0, 1, 10);
  pt.SetRowsCols(0, 2, -20);
  pt.SetRowsCols(1, 0, 4);
  pt.SetRowsCols(1, 1, -14);
  pt.SetRowsCols(1, 2, 8);
  pt.SetRowsCols(2, 0, -8);
  pt.SetRowsCols(2, 1, -2);
  pt.SetRowsCols(2, 2, 4);

  for (int i = 0; i < tp.GetRows(); i++) {
    for (int j = 0; j < tp.GetCols(); j++) {
      EXPECT_EQ(date(i, j), pt(i, j));
    }
  }

  S21Matrix p(2, 3);
  p.init(1);
  EXPECT_THROW(p.CalcComplements(), std::invalid_argument);
}

TEST(Determinant, Oprdel) {
  S21Matrix tp(3, 3);
  tp.init(1);
  double s = -40.0;
  tp.SetRowsCols(1, 0, 0);
  tp.SetRowsCols(1, 1, 4);
  tp.SetRowsCols(1, 2, 2);
  tp.SetRowsCols(2, 0, 5);
  tp.SetRowsCols(2, 1, 2);
  tp.SetRowsCols(2, 2, 1);
  EXPECT_DOUBLE_EQ(tp.Determinant(), s);

  S21Matrix p(2, 3);
  p.init(1);
  EXPECT_THROW(p.Determinant(), std::invalid_argument);
}

TEST(inverse_matrix, test) {
  S21Matrix tp(3, 3);
  S21Matrix pt(3, 3);
  S21Matrix tt(3, 3);
  tp.init(1);
  tt.init(1);

  tp.SetRowsCols(0, 0, 2);
  tp.SetRowsCols(0, 1, 5);
  tp.SetRowsCols(0, 2, 7);
  tp.SetRowsCols(1, 0, 6);
  tp.SetRowsCols(1, 1, 3);
  tp.SetRowsCols(1, 2, 4);
  tp.SetRowsCols(2, 0, 5);
  tp.SetRowsCols(2, 1, -2);
  tp.SetRowsCols(2, 2, -3);

  S21Matrix date = tp.InverseMatrix();

  pt.SetRowsCols(0, 0, 1);
  pt.SetRowsCols(0, 1, -1);
  pt.SetRowsCols(0, 2, 1);
  pt.SetRowsCols(1, 0, -38);
  pt.SetRowsCols(1, 1, 41);
  pt.SetRowsCols(1, 2, -34);
  pt.SetRowsCols(2, 0, 27);
  pt.SetRowsCols(2, 1, -29);
  pt.SetRowsCols(2, 2, 24);

  for (int i = 0; i < tp.GetRows(); i++) {
    for (int j = 0; j < tp.GetCols(); j++) {
      EXPECT_NEAR(date(i, j), pt(i, j), 1e-10);
    }
  }

  EXPECT_THROW(tt.InverseMatrix(), std::invalid_argument);
}

TEST(Operator, sum) {
  S21Matrix tp(3, 3);
  tp.init(1);
  S21Matrix pt(3, 3);
  pt.init(1);

  S21Matrix date = tp + pt;

  for (int i = 0; i < tp.GetRows(); i++) {
    for (int j = 0; j < tp.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(date(i, j), tp(i, j) + pt(i, j));
      EXPECT_TRUE(date(i, j) != pt(i, j));
    }
  }

  S21Matrix p(3, 2);
  p.init(1);

  EXPECT_THROW(tp + p, std::invalid_argument);
}

TEST(Operator, sub) {
  S21Matrix tp(3, 3);
  tp.init(1);
  S21Matrix pt(3, 3);
  pt.init(1);

  S21Matrix date = tp - pt;

  for (int i = 0; i < tp.GetRows(); i++) {
    for (int j = 0; j < tp.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(date(i, j), tp(i, j) - pt(i, j));
      EXPECT_TRUE(date(i, j) != pt(i, j));
    }
  }

  S21Matrix p(3, 2);
  p.init(1);

  EXPECT_THROW(tp - (p), std::invalid_argument);
}

TEST(Operator, Mul_m) {
  S21Matrix tp(3, 3);
  tp.init(1);
  S21Matrix date(3, 3);
  date.init(1);

  S21Matrix pt = tp * date;

  date.SetRowsCols(0, 0, 30);
  date.SetRowsCols(0, 1, 36);
  date.SetRowsCols(0, 2, 42);
  date.SetRowsCols(1, 0, 66);
  date.SetRowsCols(1, 1, 81);
  date.SetRowsCols(1, 2, 96);
  date.SetRowsCols(2, 0, 102);
  date.SetRowsCols(2, 1, 126);
  date.SetRowsCols(2, 2, 150);

  for (int i = 0; i < tp.GetRows(); i++) {
    for (int j = 0; j < tp.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(date(i, j), pt(i, j));
    }
  }

  S21Matrix p(2, 2);
  p.init(1);

  EXPECT_THROW(tp * p, std::invalid_argument);
}

TEST(Operator, Mul_n) {
  S21Matrix tp(3, 3);
  tp.init(1);
  double s = 2;
  S21Matrix pt(3, 3);
  pt.init(1);

  S21Matrix date = tp * s;

  for (int i = 0; i < tp.GetRows(); i++) {
    for (int j = 0; j < tp.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(date(i, j), pt(i, j) * 2);
    }
  }
}

TEST(Operator, comparison_Equal) {
  S21Matrix tp(3, 3);
  tp.init(1);
  S21Matrix pt(3, 3);
  pt.init(1);
  S21Matrix date_1(3, 3);
  date_1.init(1);
  S21Matrix date_2(2, 2);

  date_1.SetRowsCols(1, 1, 0);

  EXPECT_TRUE(tp == pt);
  EXPECT_FALSE(tp == date_1);
  EXPECT_FALSE(tp == date_2);
}

TEST(Operator, Equal) {
  S21Matrix tp(3, 3);
  tp.init(1);
  S21Matrix pt = tp;

  for (int i = 0; i < tp.GetRows(); i++) {
    for (int j = 0; j < tp.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(tp(i, j), pt(i, j));
    }
  }
}

TEST(Operator, Sum_Equal) {
  S21Matrix tp(3, 3);
  tp.init(1);
  S21Matrix pt(3, 3);
  pt.init(1);

  tp += pt;

  for (int i = 0; i < tp.GetRows(); i++) {
    for (int j = 0; j < tp.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(tp(i, j), pt(i, j) + pt(i, j));
    }
  }
}

TEST(Operator, Sub_Equal) {
  S21Matrix tp(3, 3);
  tp.init(1);
  S21Matrix pt(3, 3);
  pt.init(1);

  tp -= pt;

  for (int i = 0; i < tp.GetRows(); i++) {
    for (int j = 0; j < tp.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(tp(i, j), pt(i, j) - pt(i, j));
    }
  }
}

TEST(Operator, Mul_m_Equal) {
  S21Matrix tp(3, 3);
  tp.init(1);
  S21Matrix pt(3, 3);
  pt.init(1);

  tp *= pt;

  S21Matrix date;

  date.SetRowsCols(0, 0, 30);
  date.SetRowsCols(0, 1, 36);
  date.SetRowsCols(0, 2, 42);
  date.SetRowsCols(1, 0, 66);
  date.SetRowsCols(1, 1, 81);
  date.SetRowsCols(1, 2, 96);
  date.SetRowsCols(2, 0, 102);
  date.SetRowsCols(2, 1, 126);
  date.SetRowsCols(2, 2, 150);

  for (int i = 0; i < tp.GetRows(); i++) {
    for (int j = 0; j < tp.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(tp(i, j), date(i, j));
    }
  }
}

TEST(Operator, Mul_n_Equal) {
  S21Matrix tp(3, 3);
  tp.init(1);
  S21Matrix pt(3, 3);
  pt.init(1);

  tp *= 2.5;

  for (int i = 0; i < tp.GetRows(); i++) {
    for (int j = 0; j < tp.GetCols(); j++) {
      EXPECT_DOUBLE_EQ(tp(i, j), pt(i, j) * 2.5);
    }
  }
}

TEST(Operator, index) {
  S21Matrix tp(3, 3);
  tp.SetRowsCols(0, 0, 1);
  tp.SetRowsCols(0, 1, 2);
  tp.SetRowsCols(0, 2, 3);
  tp.SetRowsCols(1, 0, 4);
  tp.SetRowsCols(1, 1, 5);
  tp.SetRowsCols(1, 2, 6);
  tp.SetRowsCols(2, 0, 7);
  tp.SetRowsCols(2, 1, 8);
  tp.SetRowsCols(2, 2, 9);

  EXPECT_EQ(tp(1, 1), 5);
  EXPECT_EQ(tp(2, 1), 8);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}