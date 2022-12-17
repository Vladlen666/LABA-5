#include "polynomial.h"
#include <gtest.h>

TEST(Polynomial, can_create_polynomial)
{
  ASSERT_NO_THROW(Polynomial pol);
}

TEST(Polynomial, can_create_polynomial_from_string)
{
  ASSERT_NO_THROW(Polynomial pol(std::string("2x2")));
}

TEST(Polynomial, can_calculate_the_value_at_the_point_1)
{
  Polynomial pol(std::string("1"));
  EXPECT_EQ(pol.value_in_dot(1, 3, 5), 1);
}

TEST(Polynomial, can_calculate_the_value_at_the_point_2)
{
  Polynomial pol(std::string("-xyz"));
  EXPECT_EQ(pol.value_in_dot(1, 3, 5), -15);
}

TEST(Polynomial, can_calculate_the_value_at_the_point_3)
{
  Polynomial pol(std::string("y2"));
  EXPECT_EQ(pol.value_in_dot(1, 3, 5), 9);
}

TEST(Polynomial, can_calculate_the_value_at_the_point_4)
{
  Polynomial pol(std::string("4xz5"));
  EXPECT_EQ(pol.value_in_dot(1, 3, 5), 12500);
}

TEST(Polynomial, can_add_two_polynomials)
{
  Polynomial pol1(std::string("4xz5 - y2"));
  Polynomial pol2(std::string("y2 + 4"));
  EXPECT_EQ(pol1 + pol2, Polynomial(std::string("4+4xz5")));
}

TEST(Polynomial, can_subtract_two_polynomials)
{
  Polynomial pol1(std::string("4xz5 - y2"));
  Polynomial pol2(std::string("y2 + 4"));
  EXPECT_EQ(pol1 - pol2, Polynomial(std::string("-4-2y2+4xz5")));
}

TEST(Polynomial, can_multiply_two_polynomials)
{
  Polynomial pol1(std::string("4xz5 - y2"));
  Polynomial pol2(std::string("y2 + 4"));
  EXPECT_EQ(pol1 * pol2, Polynomial(std::string("4xy2z5+16xz5-y4-4y2")));
}
