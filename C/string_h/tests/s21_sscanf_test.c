#include <check.h>
#include <stdio.h>

#include "../s21_string.h"

// ==================================    %d TESTS
// ============================================
#define SIMPLE_DECIMAL_INT_TEST(testname, str, format) \
  START_TEST(testname) {                               \
    int libInt1 = -1;                                  \
    int myInt1 = -1;                                   \
                                                       \
    int libFunReturn, myFunReturn;                     \
                                                       \
    libFunReturn = sscanf(str, format, &libInt1);      \
    myFunReturn = s21_sscanf(str, format, &myInt1);    \
                                                       \
    ck_assert_int_eq(libInt1, myInt1);                 \
                                                       \
    ck_assert_int_eq(libFunReturn, myFunReturn);       \
  }                                                    \
  END_TEST

SIMPLE_DECIMAL_INT_TEST(test_0, "152", "%d");
SIMPLE_DECIMAL_INT_TEST(test_1, "-7372", "%d");
SIMPLE_DECIMAL_INT_TEST(test_2, "0", "%d");
SIMPLE_DECIMAL_INT_TEST(test_3, "-0", "%d");
SIMPLE_DECIMAL_INT_TEST(test_4, "003", "%d");
SIMPLE_DECIMAL_INT_TEST(test_5, "015", "%d");
SIMPLE_DECIMAL_INT_TEST(test_6, "2147483647", "%d");
SIMPLE_DECIMAL_INT_TEST(test_7, "-2147483648", "%d");
SIMPLE_DECIMAL_INT_TEST(test_8, "9000000000000", "%d");
SIMPLE_DECIMAL_INT_TEST(test_9, "-9000000000000", "%d");
SIMPLE_DECIMAL_INT_TEST(test_10, "iof-423asfb-", "iof-4%d");
SIMPLE_DECIMAL_INT_TEST(test_11, "b18d-2-3f04y8fin", "b%d");
SIMPLE_DECIMAL_INT_TEST(test_12, "09dsapdi", "%d");
SIMPLE_DECIMAL_INT_TEST(test_13, "c0-m-s0c", "c%d");
SIMPLE_DECIMAL_INT_TEST(test_14, "0imie21", "%d");
SIMPLE_DECIMAL_INT_TEST(test_15, "ds9nads", "ds%d");
SIMPLE_DECIMAL_INT_TEST(test_16, "n0n01", "n%d");
SIMPLE_DECIMAL_INT_TEST(test_17, "ddsa2.48823g", "ddsa%d");
SIMPLE_DECIMAL_INT_TEST(test_18, "dd0.2332d", "dd%d");
SIMPLE_DECIMAL_INT_TEST(test_19, "pji2poj", "pji%d");

TCase *simple_decimal_int() {
  TCase *s_d_i = tcase_create("Simple int tests");

  tcase_add_test(s_d_i, test_0);
  tcase_add_test(s_d_i, test_1);
  tcase_add_test(s_d_i, test_2);
  tcase_add_test(s_d_i, test_3);
  tcase_add_test(s_d_i, test_4);
  tcase_add_test(s_d_i, test_5);
  tcase_add_test(s_d_i, test_6);
  tcase_add_test(s_d_i, test_7);
  tcase_add_test(s_d_i, test_8);
  tcase_add_test(s_d_i, test_9);
  tcase_add_test(s_d_i, test_10);
  tcase_add_test(s_d_i, test_11);
  tcase_add_test(s_d_i, test_12);
  tcase_add_test(s_d_i, test_13);
  tcase_add_test(s_d_i, test_14);
  tcase_add_test(s_d_i, test_15);
  tcase_add_test(s_d_i, test_16);
  tcase_add_test(s_d_i, test_17);
  tcase_add_test(s_d_i, test_18);
  tcase_add_test(s_d_i, test_19);

  return s_d_i;
}

#define DECIMAL_INT_WITH_WIDTH_TEST(testname, str, format)   \
  START_TEST(testname) {                                     \
    int libInt1 = -1;                                        \
    int libInt2 = -1;                                        \
    int myInt1 = -1;                                         \
    int myInt2 = -1;                                         \
                                                             \
    int libFunReturn, myFunReturn;                           \
                                                             \
    libFunReturn = sscanf(str, format, &libInt1, &libInt2);  \
    myFunReturn = s21_sscanf(str, format, &myInt1, &myInt2); \
                                                             \
    ck_assert_int_eq(libInt1, myInt1);                       \
    ck_assert_int_eq(libInt2, myInt2);                       \
                                                             \
    ck_assert_int_eq(libFunReturn, myFunReturn);             \
  }                                                          \
  END_TEST

DECIMAL_INT_WITH_WIDTH_TEST(test_20, "152 -14", "%2d %d");
DECIMAL_INT_WITH_WIDTH_TEST(test_21, "-7372 3371.4", "%d %3d");
DECIMAL_INT_WITH_WIDTH_TEST(test_22, "0 40", "%1d %1d");
DECIMAL_INT_WITH_WIDTH_TEST(test_23, "-0, 66", "%d, %2d");
DECIMAL_INT_WITH_WIDTH_TEST(test_24, "003, 1", "%1d, %2d");
DECIMAL_INT_WITH_WIDTH_TEST(test_25, "015 15", "%d %12d");
DECIMAL_INT_WITH_WIDTH_TEST(test_26, "2147483647 338", "%6d %d");
DECIMAL_INT_WITH_WIDTH_TEST(test_27, "-2147483648 972223", "%4d %5d");
DECIMAL_INT_WITH_WIDTH_TEST(test_28, "9000000000000, 8000000000", "%4d, %d");
DECIMAL_INT_WITH_WIDTH_TEST(test_29, "-9000000000000 48822", "%1d %d");
DECIMAL_INT_WITH_WIDTH_TEST(test_30, "iof-423asfb-", "iof-4%1d %d");
DECIMAL_INT_WITH_WIDTH_TEST(test_31, "b18d-23-3f04y8fin", "b%dd-%3d");
DECIMAL_INT_WITH_WIDTH_TEST(test_32, "-094dsapdi", "%1d %1d");
DECIMAL_INT_WITH_WIDTH_TEST(test_33, "c0-m-s0125c", "c%d-m-s%2d");
DECIMAL_INT_WITH_WIDTH_TEST(test_34, "0imie21", "%dimie%1d");
DECIMAL_INT_WITH_WIDTH_TEST(test_35, "ds9n99ads", "ds%1dn%d");
DECIMAL_INT_WITH_WIDTH_TEST(test_36, "n0n01", "n%dn%1d");
DECIMAL_INT_WITH_WIDTH_TEST(test_37, "ddsa2.48823g", "ddsa%3d.%3d");
DECIMAL_INT_WITH_WIDTH_TEST(test_38, "dd0.2332d", "dd%d.%5d");
DECIMAL_INT_WITH_WIDTH_TEST(test_39, "pji2po214748364800j", "pji%dpo%17d");

TCase *decimal_int_with_width() {
  TCase *d_i_w_w = tcase_create("Decimal int with width tests");

  tcase_add_test(d_i_w_w, test_20);
  tcase_add_test(d_i_w_w, test_21);
  tcase_add_test(d_i_w_w, test_22);
  tcase_add_test(d_i_w_w, test_23);
  tcase_add_test(d_i_w_w, test_24);
  tcase_add_test(d_i_w_w, test_25);
  tcase_add_test(d_i_w_w, test_26);
  tcase_add_test(d_i_w_w, test_27);
  tcase_add_test(d_i_w_w, test_28);
  tcase_add_test(d_i_w_w, test_29);
  tcase_add_test(d_i_w_w, test_30);
  tcase_add_test(d_i_w_w, test_31);
  tcase_add_test(d_i_w_w, test_32);
  tcase_add_test(d_i_w_w, test_33);
  tcase_add_test(d_i_w_w, test_34);
  tcase_add_test(d_i_w_w, test_35);
  tcase_add_test(d_i_w_w, test_36);
  tcase_add_test(d_i_w_w, test_37);
  tcase_add_test(d_i_w_w, test_38);
  tcase_add_test(d_i_w_w, test_39);

  return d_i_w_w;
}

#define DECIMAL_INT_WITH_SKIP_TEST(testname, str, format)    \
  START_TEST(testname) {                                     \
    int libInt1 = -1;                                        \
    int libInt2 = -1;                                        \
    int myInt1 = -1;                                         \
    int myInt2 = -1;                                         \
                                                             \
    int libFunReturn, myFunReturn;                           \
                                                             \
    libFunReturn = sscanf(str, format, &libInt1, &libInt2);  \
    myFunReturn = s21_sscanf(str, format, &myInt1, &myInt2); \
                                                             \
    ck_assert_int_eq(libInt1, myInt1);                       \
    ck_assert_int_eq(libInt2, myInt2);                       \
                                                             \
    ck_assert_int_eq(libFunReturn, myFunReturn);             \
  }                                                          \
  END_TEST

DECIMAL_INT_WITH_SKIP_TEST(test_40, "152 -14 1", "%*d %d %d");
DECIMAL_INT_WITH_SKIP_TEST(test_41, "-7372 3371.4", "%d %*d %d");
DECIMAL_INT_WITH_SKIP_TEST(test_42, "0 40 11", "%1d %1d %*d");
DECIMAL_INT_WITH_SKIP_TEST(test_43, "-0, 66 322", "%*d, %2d %d");
DECIMAL_INT_WITH_SKIP_TEST(test_44, "003.1, 1", "%1d %*d.%d");
DECIMAL_INT_WITH_SKIP_TEST(test_45, "-9000000000000 48822", "%1d %*d %d");
DECIMAL_INT_WITH_SKIP_TEST(test_46, "iof-423a11sfb-", "iof-4%*da%1d %d");
DECIMAL_INT_WITH_SKIP_TEST(test_47, "b18d-23-3f04y8fin", "b%dd-%*d-%d");
DECIMAL_INT_WITH_SKIP_TEST(test_48, "-094d751sapdi", "%1d %*dd%1d");
DECIMAL_INT_WITH_SKIP_TEST(test_49, "c0-m-s0125c", "c%*d-m-s%2d %d");

TCase *decimal_int_with_skip() {
  TCase *d_i_w_s = tcase_create("Decimal int with skip tests");

  tcase_add_test(d_i_w_s, test_40);
  tcase_add_test(d_i_w_s, test_41);
  tcase_add_test(d_i_w_s, test_42);
  tcase_add_test(d_i_w_s, test_43);
  tcase_add_test(d_i_w_s, test_44);
  tcase_add_test(d_i_w_s, test_45);
  tcase_add_test(d_i_w_s, test_46);
  tcase_add_test(d_i_w_s, test_47);
  tcase_add_test(d_i_w_s, test_48);
  tcase_add_test(d_i_w_s, test_49);

  return d_i_w_s;
}

// ==================================    %f TESTS
// ============================================

#define FLOATING_POINT_NUMBER_TEST(testname, str, format) \
  START_TEST(testname) {                                  \
    float libFloat1 = -1;                                 \
    float myFloat1 = -1;                                  \
                                                          \
    int libFunReturn, myFunReturn;                        \
                                                          \
    libFunReturn = sscanf(str, format, &libFloat1);       \
    myFunReturn = s21_sscanf(str, format, &myFloat1);     \
                                                          \
    ck_assert_float_eq(libFloat1, myFloat1);              \
                                                          \
    ck_assert_int_eq(libFunReturn, myFunReturn);          \
  }                                                       \
  END_TEST

FLOATING_POINT_NUMBER_TEST(test_50, "134", "%f")
FLOATING_POINT_NUMBER_TEST(test_51, "1409.873", "%f")
FLOATING_POINT_NUMBER_TEST(test_52, "1.728", "%f")
FLOATING_POINT_NUMBER_TEST(test_53, "1938290.732873892", "%f")
FLOATING_POINT_NUMBER_TEST(test_54, "asd-38.5", "asd-%f")
FLOATING_POINT_NUMBER_TEST(test_55, "-12.523md", "%f")
FLOATING_POINT_NUMBER_TEST(test_56, "float-12341.742", "float-%f")
FLOATING_POINT_NUMBER_TEST(test_57, "asd_1938290.732873892", "asd_%f")
FLOATING_POINT_NUMBER_TEST(test_58, "-9000000000", "%f")
FLOATING_POINT_NUMBER_TEST(test_59, "9000000000", "%f")

TCase *simple_decimal_float() {
  TCase *f_p_n_t = tcase_create("floatingc point number tests");

  tcase_add_test(f_p_n_t, test_50);
  tcase_add_test(f_p_n_t, test_51);
  tcase_add_test(f_p_n_t, test_52);
  tcase_add_test(f_p_n_t, test_53);
  tcase_add_test(f_p_n_t, test_54);
  tcase_add_test(f_p_n_t, test_55);
  tcase_add_test(f_p_n_t, test_56);
  tcase_add_test(f_p_n_t, test_57);
  tcase_add_test(f_p_n_t, test_58);
  tcase_add_test(f_p_n_t, test_59);

  return f_p_n_t;
}

#define FLOATING_POINT_WITH_WIDTH_TEST(testname, str, format)    \
  START_TEST(testname) {                                         \
    float libFloat1 = -1;                                        \
    float libFloat2 = -1;                                        \
    float myFloat1 = -1;                                         \
    float myFloat2 = -1;                                         \
                                                                 \
    int libfunreturn, myfunreturn;                               \
                                                                 \
    libfunreturn = sscanf(str, format, &libFloat1, &libFloat2);  \
    myfunreturn = s21_sscanf(str, format, &myFloat1, &myFloat2); \
                                                                 \
    ck_assert_float_eq(libFloat1, myFloat1);                     \
    ck_assert_float_eq(libFloat2, myFloat2);                     \
                                                                 \
    ck_assert_int_eq(libfunreturn, myfunreturn);                 \
  }                                                              \
  END_TEST

FLOATING_POINT_WITH_WIDTH_TEST(test_60, "1723.63 187387.67217", "%3f %f")
FLOATING_POINT_WITH_WIDTH_TEST(test_61, "1723.63 187387.67217", "%f %3f")
FLOATING_POINT_WITH_WIDTH_TEST(test_62, "ads-12-345.67", "ads-%f-%2f")
FLOATING_POINT_WITH_WIDTH_TEST(test_63, "123.321-azs_123", "%3f-azs_%f")
FLOATING_POINT_WITH_WIDTH_TEST(test_64, "ssca12.3", "ssca%1f %f")
FLOATING_POINT_WITH_WIDTH_TEST(test_65, "2.2+2.2", "%1f+%f")
FLOATING_POINT_WITH_WIDTH_TEST(test_66, "123321", "%3f %f")
FLOATING_POINT_WITH_WIDTH_TEST(test_67, "ing-06.06_952.34", "ing-%f_%2f")
FLOATING_POINT_WITH_WIDTH_TEST(test_68, "1273.3727 12873", "%f %3f")
FLOATING_POINT_WITH_WIDTH_TEST(test_69, "ls627.38 2738.33", "ls%2f %f")

TCase *floating_point_with_witdh() {
  TCase *f_p_w_w = tcase_create("floating point numbers with width tests");

  tcase_add_test(f_p_w_w, test_60);
  tcase_add_test(f_p_w_w, test_61);
  tcase_add_test(f_p_w_w, test_62);
  tcase_add_test(f_p_w_w, test_63);
  tcase_add_test(f_p_w_w, test_64);
  tcase_add_test(f_p_w_w, test_65);
  tcase_add_test(f_p_w_w, test_66);
  tcase_add_test(f_p_w_w, test_67);
  tcase_add_test(f_p_w_w, test_68);
  tcase_add_test(f_p_w_w, test_69);

  return f_p_w_w;
}

#define FLOATING_POINT_WITH_SKIP(testname, str, format)       \
  START_TEST(testname) {                                      \
    float libFloat1 = -1;                                     \
    float libFloat2 = -1;                                     \
    float myFloat1 = -1;                                      \
    float myFloat2 = -1;                                      \
                                                              \
    int libReturn;                                            \
    int myReturn;                                             \
                                                              \
    libReturn = sscanf(str, format, &libFloat1, &libFloat2);  \
    myReturn = s21_sscanf(str, format, &myFloat1, &myFloat2); \
                                                              \
    ck_assert_float_eq(libFloat1, myFloat1);                  \
    ck_assert_float_eq(libFloat2, myFloat2);                  \
                                                              \
    ck_assert_int_eq(libReturn, myReturn);                    \
  }                                                           \
  END_TEST

FLOATING_POINT_WITH_SKIP(test_70, "1723.63 187387.67217 123.321", "%*f %f %f")
FLOATING_POINT_WITH_SKIP(test_71, "1723.63 187387.67217 123.321", "%f %*f %f")
FLOATING_POINT_WITH_SKIP(test_72, "ads-12-345.67-12.23", "ads-%*f-%f-%f")
FLOATING_POINT_WITH_SKIP(test_73, "123.321-azs_123_293.328", "%f-azs_%*f_%f")
FLOATING_POINT_WITH_SKIP(test_74, "ssca12.3-267.323_231.2", "ssca%*f-%f_%2f")
FLOATING_POINT_WITH_SKIP(test_75, "2.2+21 2.2=", "%f+%*f %f=4.4")
FLOATING_POINT_WITH_SKIP(test_76, "123321 123", "%3f %*f %f")
FLOATING_POINT_WITH_SKIP(test_77, "ing-06.06_952.34-01.10", "ing-%2f_%*f-%f")
FLOATING_POINT_WITH_SKIP(test_78, "1273.3727 12.873 773.3773", "%*f %1f %*f %f")
FLOATING_POINT_WITH_SKIP(test_79, "ls627.38cat2738.33", "ls%1f %*fcat%f")

TCase *floating_point_with_skip() {
  TCase *f_p_w_s = tcase_create("floating point numbers with skip tests");

  tcase_add_test(f_p_w_s, test_70);
  tcase_add_test(f_p_w_s, test_71);
  tcase_add_test(f_p_w_s, test_72);
  tcase_add_test(f_p_w_s, test_73);
  tcase_add_test(f_p_w_s, test_74);
  tcase_add_test(f_p_w_s, test_75);
  tcase_add_test(f_p_w_s, test_76);
  tcase_add_test(f_p_w_s, test_77);
  tcase_add_test(f_p_w_s, test_78);
  tcase_add_test(f_p_w_s, test_79);

  return f_p_w_s;
}

// ==================================    %lf TESTS
// ============================================

#define DOUBLE_POINT_NUMBER_TEST(testname, str, format) \
  START_TEST(testname) {                                \
    double libFloat1 = -1;                              \
    double myFloat1 = -1;                               \
                                                        \
    int libFunReturn, myFunReturn;                      \
                                                        \
    libFunReturn = sscanf(str, format, &libFloat1);     \
    myFunReturn = s21_sscanf(str, format, &myFloat1);   \
                                                        \
    ck_assert_float_eq(libFloat1, myFloat1);            \
                                                        \
    ck_assert_int_eq(libFunReturn, myFunReturn);        \
  }                                                     \
  END_TEST

DOUBLE_POINT_NUMBER_TEST(test_80, "134", "%lf")
DOUBLE_POINT_NUMBER_TEST(test_81, "1409.873233", "%lf")
DOUBLE_POINT_NUMBER_TEST(test_82, "0.728", "%lf")
DOUBLE_POINT_NUMBER_TEST(test_83, "1938290.732873892", "%lf")
DOUBLE_POINT_NUMBER_TEST(test_84, "as328.53234", "asd-%lf")
DOUBLE_POINT_NUMBER_TEST(test_85, "-1212.523md", "%lfmd")
DOUBLE_POINT_NUMBER_TEST(test_86, "double_121.742", "double_%lf")
DOUBLE_POINT_NUMBER_TEST(test_87, "asd_1938290.732873892", "asd_%lf")
DOUBLE_POINT_NUMBER_TEST(test_88, "-9000000000000", "%lf")
DOUBLE_POINT_NUMBER_TEST(test_89, "9000000000000", "%lf")

TCase *simple_decimal_float_double() {
  TCase *d_p_n_t = tcase_create("floating point number tests");

  tcase_add_test(d_p_n_t, test_80);
  tcase_add_test(d_p_n_t, test_81);
  tcase_add_test(d_p_n_t, test_82);
  tcase_add_test(d_p_n_t, test_83);
  tcase_add_test(d_p_n_t, test_84);
  tcase_add_test(d_p_n_t, test_85);
  tcase_add_test(d_p_n_t, test_86);
  tcase_add_test(d_p_n_t, test_87);
  tcase_add_test(d_p_n_t, test_88);
  tcase_add_test(d_p_n_t, test_89);

  return d_p_n_t;
}

#define DOUBLE_POINT_WITH_WIDTH_TEST(testname, str, format)      \
  START_TEST(testname) {                                         \
    double libFloat1 = -1;                                       \
    double libFloat2 = -1;                                       \
    double myFloat1 = -1;                                        \
    double myFloat2 = -1;                                        \
                                                                 \
    int libfunreturn, myfunreturn;                               \
                                                                 \
    libfunreturn = sscanf(str, format, &libFloat1, &libFloat2);  \
    myfunreturn = s21_sscanf(str, format, &myFloat1, &myFloat2); \
                                                                 \
    ck_assert_float_eq(libFloat1, myFloat1);                     \
    ck_assert_float_eq(libFloat2, myFloat2);                     \
                                                                 \
    ck_assert_int_eq(libfunreturn, myfunreturn);                 \
  }                                                              \
  END_TEST

DOUBLE_POINT_WITH_WIDTH_TEST(test_90, "1723.63-sda187387.67217", "%3lf %lf")
DOUBLE_POINT_WITH_WIDTH_TEST(test_91, "1723.63-asd187387.67217", "%lf-asd%3lf")
DOUBLE_POINT_WITH_WIDTH_TEST(test_92, "ads-12-345.67", "ads-%lf-%2lf")
DOUBLE_POINT_WITH_WIDTH_TEST(test_93, "123.321-azs_123", "%3lf-azs_%lf")
DOUBLE_POINT_WITH_WIDTH_TEST(test_94, "ssca12.3", "ssca%1lf %lf")
DOUBLE_POINT_WITH_WIDTH_TEST(test_95, "2.22+2.22", "%1lf+%lf")
DOUBLE_POINT_WITH_WIDTH_TEST(test_96, "123456", "%3lf %lf")
DOUBLE_POINT_WITH_WIDTH_TEST(test_97, "ing-06.06_952.34", "ing-%lf_%2lf")
DOUBLE_POINT_WITH_WIDTH_TEST(test_98, "1273.3727 12873", "%lf %3lf")
DOUBLE_POINT_WITH_WIDTH_TEST(test_99, "ls627.38 2738.33", "ls%2lf %lf")

TCase *double_point_with_witdh() {
  TCase *d_p_w_w =
      tcase_create("floating double point numbers with width tests");

  tcase_add_test(d_p_w_w, test_90);
  tcase_add_test(d_p_w_w, test_91);
  tcase_add_test(d_p_w_w, test_92);
  tcase_add_test(d_p_w_w, test_93);
  tcase_add_test(d_p_w_w, test_94);
  tcase_add_test(d_p_w_w, test_95);
  tcase_add_test(d_p_w_w, test_96);
  tcase_add_test(d_p_w_w, test_97);
  tcase_add_test(d_p_w_w, test_98);
  tcase_add_test(d_p_w_w, test_99);

  return d_p_w_w;
}

// ==================================    %e TESTS
// ============================================

#define FLOATING_SPECIFIER_E_TEST(testname, str, format) \
  START_TEST(testname) {                                 \
    float libFloat1 = -1;                                \
    float myFloat1 = -1;                                 \
                                                         \
    int libFunReturn, myFunReturn;                       \
                                                         \
    libFunReturn = sscanf(str, format, &libFloat1);      \
    myFunReturn = s21_sscanf(str, format, &myFloat1);    \
                                                         \
    ck_assert_float_eq(libFloat1, myFloat1);             \
                                                         \
    ck_assert_int_eq(libFunReturn, myFunReturn);         \
  }                                                      \
  END_TEST

FLOATING_SPECIFIER_E_TEST(test_100, "134.54", "%e")
FLOATING_SPECIFIER_E_TEST(test_101, "1409.873", "%e")
FLOATING_SPECIFIER_E_TEST(test_102, "a", "%e")
FLOATING_SPECIFIER_E_TEST(test_103, "1938290.732873892", "%e")
FLOATING_SPECIFIER_E_TEST(test_104, "asd-38.5", "asd-%e")
FLOATING_SPECIFIER_E_TEST(test_105, "-12.523md", "%e")
FLOATING_SPECIFIER_E_TEST(test_106, "float-12341.742", "float-%e")
FLOATING_SPECIFIER_E_TEST(test_107, "asd_1938290.732873892", "asd_%e")
FLOATING_SPECIFIER_E_TEST(test_108, "-9000000000", "%e")
FLOATING_SPECIFIER_E_TEST(test_109, "9000000000", "%e")

TCase *specifier_e_test() {
  TCase *s_e_t = tcase_create("floating specifier e tests");

  tcase_add_test(s_e_t, test_100);
  tcase_add_test(s_e_t, test_101);
  tcase_add_test(s_e_t, test_102);
  tcase_add_test(s_e_t, test_103);
  tcase_add_test(s_e_t, test_104);
  tcase_add_test(s_e_t, test_105);
  tcase_add_test(s_e_t, test_106);
  tcase_add_test(s_e_t, test_107);
  tcase_add_test(s_e_t, test_108);
  tcase_add_test(s_e_t, test_109);

  return s_e_t;
}

#define SPECIFIER_E_WITH_WIDTH_TEST(testname, str, format)       \
  START_TEST(testname) {                                         \
    float libFloat1 = -1;                                        \
    float libFloat2 = -1;                                        \
    float myFloat1 = -1;                                         \
    float myFloat2 = -1;                                         \
                                                                 \
    int libfunreturn, myfunreturn;                               \
                                                                 \
    libfunreturn = sscanf(str, format, &libFloat1, &libFloat2);  \
    myfunreturn = s21_sscanf(str, format, &myFloat1, &myFloat2); \
                                                                 \
    ck_assert_float_eq(libFloat1, myFloat1);                     \
    ck_assert_float_eq(libFloat2, myFloat2);                     \
                                                                 \
    ck_assert_int_eq(libfunreturn, myfunreturn);                 \
  }                                                              \
  END_TEST

SPECIFIER_E_WITH_WIDTH_TEST(test_110, "1723.63 187387.67217", "%3e %e")
SPECIFIER_E_WITH_WIDTH_TEST(test_111, "1723.63 187387.67217", "%e %3e")
SPECIFIER_E_WITH_WIDTH_TEST(test_112, "ads-12-345.67", "ads-%e-%2e")
SPECIFIER_E_WITH_WIDTH_TEST(test_113, "123.321-azs_123", "%3e-azs_%e")
SPECIFIER_E_WITH_WIDTH_TEST(test_114, "ssca12.3", "ssca%1e %e")
SPECIFIER_E_WITH_WIDTH_TEST(test_115, "2.2+2.2", "%1e+%e")
SPECIFIER_E_WITH_WIDTH_TEST(test_116, "123321", "%3e %e")
SPECIFIER_E_WITH_WIDTH_TEST(test_117, "ing-06.06_952.34", "ing-%e_%2e")
SPECIFIER_E_WITH_WIDTH_TEST(test_118, "1273.3727 12873", "%e %3e")
SPECIFIER_E_WITH_WIDTH_TEST(test_119, "ls627.38 2738.33", "ls%2e %e")

TCase *specifier_e_with_witdh() {
  TCase *s_e_w_w =
      tcase_create("floating point specifier e numbers with width tests");

  tcase_add_test(s_e_w_w, test_110);
  tcase_add_test(s_e_w_w, test_111);
  tcase_add_test(s_e_w_w, test_112);
  tcase_add_test(s_e_w_w, test_113);
  tcase_add_test(s_e_w_w, test_114);
  tcase_add_test(s_e_w_w, test_115);
  tcase_add_test(s_e_w_w, test_116);
  tcase_add_test(s_e_w_w, test_117);
  tcase_add_test(s_e_w_w, test_118);
  tcase_add_test(s_e_w_w, test_119);

  return s_e_w_w;
}

#define SPECIFIER_E_WITH_SKIP(testname, str, format)          \
  START_TEST(testname) {                                      \
    float libFloat1 = -1;                                     \
    float libFloat2 = -1;                                     \
    float myFloat1 = -1;                                      \
    float myFloat2 = -1;                                      \
                                                              \
    int libReturn;                                            \
    int myReturn;                                             \
                                                              \
    libReturn = sscanf(str, format, &libFloat1, &libFloat2);  \
    myReturn = s21_sscanf(str, format, &myFloat1, &myFloat2); \
                                                              \
    ck_assert_float_eq(libFloat1, myFloat1);                  \
    ck_assert_float_eq(libFloat2, myFloat2);                  \
                                                              \
    ck_assert_int_eq(libReturn, myReturn);                    \
  }                                                           \
  END_TEST

SPECIFIER_E_WITH_SKIP(test_120, "1723.63 187387.67217 123.321", "%*e %e %e")
SPECIFIER_E_WITH_SKIP(test_121, "1723.63 187387.67217 123.321", "%e %*e %e")
SPECIFIER_E_WITH_SKIP(test_122, "ads-12-345.67-12.23", "ads-%*e-%e-%e")
SPECIFIER_E_WITH_SKIP(test_123, "123.321-azs_123_293.328", "%e-azs_%*e_%e")
SPECIFIER_E_WITH_SKIP(test_124, "ssca12.3-267.323_231.2", "ssca%*e-%e_%2e")
SPECIFIER_E_WITH_SKIP(test_125, "2.2+21 2.2=", "%e+%*e %e=4.4")
SPECIFIER_E_WITH_SKIP(test_126, "123321 123", "%3e %*e %e")
SPECIFIER_E_WITH_SKIP(test_127, "ing-06.06_952.34-01.10", "ing-%2e_%*e-%e")
SPECIFIER_E_WITH_SKIP(test_128, "1273.3727 12.873 773.3773", "%*e %1e %*e %e")
SPECIFIER_E_WITH_SKIP(test_129, "ls627.38cat2738.33", "ls%1e %*ecat%e")

TCase *specifier_e_with_skip() {
  TCase *s_e_w_s =
      tcase_create("floating point specifier e numbers with skip tests");

  tcase_add_test(s_e_w_s, test_120);
  tcase_add_test(s_e_w_s, test_121);
  tcase_add_test(s_e_w_s, test_122);
  tcase_add_test(s_e_w_s, test_123);
  tcase_add_test(s_e_w_s, test_124);
  tcase_add_test(s_e_w_s, test_125);
  tcase_add_test(s_e_w_s, test_126);
  tcase_add_test(s_e_w_s, test_127);
  tcase_add_test(s_e_w_s, test_128);
  tcase_add_test(s_e_w_s, test_129);

  return s_e_w_s;
}

// ==================================    %g TESTS
// ============================================

#define FLOATING_SPECIFIER_G_TEST(testname, str, format) \
  START_TEST(testname) {                                 \
    float libFloat1 = -1;                                \
    float myFloat1 = -1;                                 \
                                                         \
    int libFunReturn, myFunReturn;                       \
                                                         \
    libFunReturn = sscanf(str, format, &libFloat1);      \
    myFunReturn = s21_sscanf(str, format, &myFloat1);    \
                                                         \
    ck_assert_float_eq(libFloat1, myFloat1);             \
                                                         \
    ck_assert_int_eq(libFunReturn, myFunReturn);         \
  }                                                      \
  END_TEST

FLOATING_SPECIFIER_G_TEST(test_130, "134.54", "%g")
FLOATING_SPECIFIER_G_TEST(test_131, "1409.873", "%g")
FLOATING_SPECIFIER_G_TEST(test_132, "a", "%g")
FLOATING_SPECIFIER_G_TEST(test_133, "1938290.732873892", "%g")
FLOATING_SPECIFIER_G_TEST(test_134, "asd-38.5", "asd-%g")
FLOATING_SPECIFIER_G_TEST(test_135, "-12.523md", "%g")
FLOATING_SPECIFIER_G_TEST(test_136, "float-12341.742", "float-%g")
FLOATING_SPECIFIER_G_TEST(test_137, "asd_1938290.732873892", "asd_%g")
FLOATING_SPECIFIER_G_TEST(test_138, "-9000000000", "%g")
FLOATING_SPECIFIER_G_TEST(test_139, "9000000000", "%g")

TCase *specifier_g_test() {
  TCase *s_g_t = tcase_create("floating specifier g tests");

  tcase_add_test(s_g_t, test_130);
  tcase_add_test(s_g_t, test_131);
  tcase_add_test(s_g_t, test_132);
  tcase_add_test(s_g_t, test_133);
  tcase_add_test(s_g_t, test_134);
  tcase_add_test(s_g_t, test_135);
  tcase_add_test(s_g_t, test_136);
  tcase_add_test(s_g_t, test_137);
  tcase_add_test(s_g_t, test_138);
  tcase_add_test(s_g_t, test_139);

  return s_g_t;
}

#define SPECIFIER_G_WITH_WIDTH_TEST(testname, str, format)       \
  START_TEST(testname) {                                         \
    float libFloat1 = -1;                                        \
    float libFloat2 = -1;                                        \
    float myFloat1 = -1;                                         \
    float myFloat2 = -1;                                         \
                                                                 \
    int libfunreturn, myfunreturn;                               \
                                                                 \
    libfunreturn = sscanf(str, format, &libFloat1, &libFloat2);  \
    myfunreturn = s21_sscanf(str, format, &myFloat1, &myFloat2); \
                                                                 \
    ck_assert_float_eq(libFloat1, myFloat1);                     \
    ck_assert_float_eq(libFloat2, myFloat2);                     \
                                                                 \
    ck_assert_int_eq(libfunreturn, myfunreturn);                 \
  }                                                              \
  END_TEST

SPECIFIER_G_WITH_WIDTH_TEST(test_140, "1723.63 187387.67217", "%3g %g")
SPECIFIER_G_WITH_WIDTH_TEST(test_141, "1723.63 187387.67217", "%g %3g")
SPECIFIER_G_WITH_WIDTH_TEST(test_142, "ads-12-345.67", "ads-%g-%2g")
SPECIFIER_G_WITH_WIDTH_TEST(test_143, "123.321-azs_123", "%3g-azs_%g")
SPECIFIER_G_WITH_WIDTH_TEST(test_144, "ssca12.3", "ssca%1g %g")
SPECIFIER_G_WITH_WIDTH_TEST(test_145, "2.2+2.2", "%1g+%g")
SPECIFIER_G_WITH_WIDTH_TEST(test_146, "123321", "%3g %g")
SPECIFIER_G_WITH_WIDTH_TEST(test_147, "ing-06.06_952.34", "ing-%g_%2g")
SPECIFIER_G_WITH_WIDTH_TEST(test_148, "1273.3727 12873", "%g %3g")
SPECIFIER_G_WITH_WIDTH_TEST(test_149, "ls627.38 2738.33", "ls%2g %g")

TCase *specifier_g_with_witdh() {
  TCase *s_g_w_w =
      tcase_create("floating point specifier g numbers with width tests");

  tcase_add_test(s_g_w_w, test_140);
  tcase_add_test(s_g_w_w, test_141);
  tcase_add_test(s_g_w_w, test_142);
  tcase_add_test(s_g_w_w, test_143);
  tcase_add_test(s_g_w_w, test_144);
  tcase_add_test(s_g_w_w, test_145);
  tcase_add_test(s_g_w_w, test_146);
  tcase_add_test(s_g_w_w, test_147);
  tcase_add_test(s_g_w_w, test_148);
  tcase_add_test(s_g_w_w, test_149);

  return s_g_w_w;
}

#define SPECIFIER_E_WITH_SKIP(testname, str, format)          \
  START_TEST(testname) {                                      \
    float libFloat1 = -1;                                     \
    float libFloat2 = -1;                                     \
    float myFloat1 = -1;                                      \
    float myFloat2 = -1;                                      \
                                                              \
    int libReturn;                                            \
    int myReturn;                                             \
                                                              \
    libReturn = sscanf(str, format, &libFloat1, &libFloat2);  \
    myReturn = s21_sscanf(str, format, &myFloat1, &myFloat2); \
                                                              \
    ck_assert_float_eq(libFloat1, myFloat1);                  \
    ck_assert_float_eq(libFloat2, myFloat2);                  \
                                                              \
    ck_assert_int_eq(libReturn, myReturn);                    \
  }                                                           \
  END_TEST

SPECIFIER_E_WITH_SKIP(test_150, "1723.63 187387.67217 123.321", "%*g %g %g")
SPECIFIER_E_WITH_SKIP(test_151, "1723.63 187387.67217 123.321", "%g %*g %g")
SPECIFIER_E_WITH_SKIP(test_152, "ads-12-345.67-12.23", "ads-%*g-%g-%g")
SPECIFIER_E_WITH_SKIP(test_153, "123.321-azs_123_293.328", "%g-azs_%*g_%g")
SPECIFIER_E_WITH_SKIP(test_154, "ssca12.3-267.323_231.2", "ssca%*g-%g_%2g")
SPECIFIER_E_WITH_SKIP(test_155, "2.2+21 2.2=", "%g+%*g %g=4.4")
SPECIFIER_E_WITH_SKIP(test_156, "123321 123", "%3g %*g %g")
SPECIFIER_E_WITH_SKIP(test_157, "ing-06.06_952.34-01.10", "ing-%2g_%*g-%g")
SPECIFIER_E_WITH_SKIP(test_158, "1273.3727 12.873 773.3773", "%*g %1g %*g %g")
SPECIFIER_E_WITH_SKIP(test_159, "ls627.38cat2738.33", "ls%1g %*gcat%g")

TCase *specifier_g_with_skip() {
  TCase *s_g_w_s =
      tcase_create("floating point specifier g numbers with skip tests");

  tcase_add_test(s_g_w_s, test_150);
  tcase_add_test(s_g_w_s, test_151);
  tcase_add_test(s_g_w_s, test_152);
  tcase_add_test(s_g_w_s, test_153);
  tcase_add_test(s_g_w_s, test_154);
  tcase_add_test(s_g_w_s, test_155);
  tcase_add_test(s_g_w_s, test_156);
  tcase_add_test(s_g_w_s, test_157);
  tcase_add_test(s_g_w_s, test_158);
  tcase_add_test(s_g_w_s, test_159);

  return s_g_w_s;
}

// ==================================    %s TESTS
// ============================================

#define STRING_TEST(testname, str, format)            \
  START_TEST(testname) {                              \
    char libString1[1024];                            \
    char myString1[1024];                             \
                                                      \
    int libFunReturn, myFunReturn;                    \
                                                      \
    libFunReturn = sscanf(str, format, libString1);   \
    myFunReturn = s21_sscanf(str, format, myString1); \
                                                      \
    ck_assert_str_eq(libString1, myString1);          \
                                                      \
    ck_assert_int_eq(libFunReturn, myFunReturn);      \
  }                                                   \
  END_TEST

STRING_TEST(test_160, "Hello school 21", "%s")
STRING_TEST(test_161, "Hello school 21", "Hello %s")
STRING_TEST(test_162, "Hello school 21", "Hello school %s")
STRING_TEST(test_163, "asdfghjk= will", "asdfghjk= %s")
STRING_TEST(test_164, "hekoom=122-1201", "%s")
STRING_TEST(test_165, "1_2_3_4_=10-0", "%s")
STRING_TEST(test_166, "123456789", "%s")
STRING_TEST(test_167, "hsj2j2h3-+_;s", "%s")
STRING_TEST(test_168, "NULL", "%s")
STRING_TEST(test_169, "Yes", "%s")

TCase *string_test() {
  TCase *s_t = tcase_create("string tests");

  tcase_add_test(s_t, test_160);
  tcase_add_test(s_t, test_161);
  tcase_add_test(s_t, test_162);
  tcase_add_test(s_t, test_163);
  tcase_add_test(s_t, test_164);
  tcase_add_test(s_t, test_165);
  tcase_add_test(s_t, test_166);
  tcase_add_test(s_t, test_167);
  tcase_add_test(s_t, test_168);
  tcase_add_test(s_t, test_169);

  return s_t;
}

#define FOR_TWO_STRING_TEST(testname, str, format)               \
  START_TEST(testname) {                                         \
    char libString1[1024];                                       \
    char myString1[1024];                                        \
    char libString2[1024];                                       \
    char myString2[1024];                                        \
                                                                 \
    int libFunReturn, myFunReturn;                               \
                                                                 \
    libFunReturn = sscanf(str, format, libString1, libString2);  \
    myFunReturn = s21_sscanf(str, format, myString1, myString2); \
                                                                 \
    ck_assert_str_eq(libString1, myString1);                     \
    ck_assert_str_eq(libString2, myString2);                     \
                                                                 \
    ck_assert_int_eq(libFunReturn, myFunReturn);                 \
  }                                                              \
  END_TEST

FOR_TWO_STRING_TEST(test_170, "Hello school 21", "%s %s")
FOR_TWO_STRING_TEST(test_171, "Hello school 21", "Hello %s %s")
FOR_TWO_STRING_TEST(test_172, "Hello school 21", "%s school %s")
FOR_TWO_STRING_TEST(test_173, "asdfghjk= will - good", "asdfghjk= %s - %s")
FOR_TWO_STRING_TEST(test_174, "hekoom=122 -1201", "%s %s")
FOR_TWO_STRING_TEST(test_175, "1_2_3_4_= 21=-02983+_s", "%s %s")
FOR_TWO_STRING_TEST(test_176, "123456789 12345678900987654321", "%s %9s")
FOR_TWO_STRING_TEST(test_177, "hsj2j2h3-+_;s 1", "%s %s")
FOR_TWO_STRING_TEST(test_178, "NULL null", "%2s %s")
FOR_TWO_STRING_TEST(test_179, "hello world", "%s %2s")

TCase *for_two_string() {
  TCase *f_w_s = tcase_create("for two strings test");

  tcase_add_test(f_w_s, test_170);
  tcase_add_test(f_w_s, test_171);
  tcase_add_test(f_w_s, test_172);
  tcase_add_test(f_w_s, test_173);
  tcase_add_test(f_w_s, test_174);
  tcase_add_test(f_w_s, test_175);
  tcase_add_test(f_w_s, test_176);
  tcase_add_test(f_w_s, test_177);
  tcase_add_test(f_w_s, test_178);
  tcase_add_test(f_w_s, test_179);

  return f_w_s;
}

// ==================================    %c TESTS
// ============================================

#define SIMBOL_CHAR_TEST(testname, str, format)        \
  START_TEST(testname) {                               \
    char libString1;                                   \
    char myString1;                                    \
                                                       \
    int libFunReturn, myFunReturn;                     \
                                                       \
    libFunReturn = sscanf(str, format, &libString1);   \
    myFunReturn = s21_sscanf(str, format, &myString1); \
                                                       \
    ck_assert_int_eq(libString1, myString1);           \
                                                       \
    ck_assert_int_eq(libFunReturn, myFunReturn);       \
  }                                                    \
  END_TEST

SIMBOL_CHAR_TEST(test_180, "\t\n \n 123 \t", "%c")
SIMBOL_CHAR_TEST(test_181, "\t\n \n \ta", "   %c")
SIMBOL_CHAR_TEST(test_182, "1 2 3 = + - 5", "1 2 3 = + - %c")
SIMBOL_CHAR_TEST(test_183, "asdfghjk= \t 2", "asdfghjk= %c")
SIMBOL_CHAR_TEST(test_184, "\n\t a \t", "%c")
SIMBOL_CHAR_TEST(test_185, "\t \0 \t 2", "%c")
SIMBOL_CHAR_TEST(test_186, "+=-! i", "+=-! %c")
SIMBOL_CHAR_TEST(test_187, "hsj2j2h3-+_;s", "hsj%c")
SIMBOL_CHAR_TEST(test_188, "NULL", "NU%c")
SIMBOL_CHAR_TEST(test_189, "Yes", "Y%c")

TCase *simbol_char_test() {
  TCase *s_c_t = tcase_create("simbol char tests");

  tcase_add_test(s_c_t, test_180);
  tcase_add_test(s_c_t, test_181);
  tcase_add_test(s_c_t, test_182);
  tcase_add_test(s_c_t, test_183);
  tcase_add_test(s_c_t, test_184);
  tcase_add_test(s_c_t, test_185);
  tcase_add_test(s_c_t, test_186);
  tcase_add_test(s_c_t, test_187);
  tcase_add_test(s_c_t, test_188);
  tcase_add_test(s_c_t, test_189);

  return s_c_t;
}

#define TWO_SIMBOL_CHAR_TEST(testname, str, format)                \
  START_TEST(testname) {                                           \
    char libString1;                                               \
    char myString1;                                                \
    char libString2;                                               \
    char myString2;                                                \
                                                                   \
    int libFunReturn, myFunReturn;                                 \
                                                                   \
    libFunReturn = sscanf(str, format, &libString1, &libString2);  \
    myFunReturn = s21_sscanf(str, format, &myString1, &myString2); \
                                                                   \
    ck_assert_int_eq(libString1, myString1);                       \
    ck_assert_int_eq(libString2, myString2);                       \
                                                                   \
    ck_assert_int_eq(libFunReturn, myFunReturn);                   \
  }                                                                \
  END_TEST

TWO_SIMBOL_CHAR_TEST(test_190, "\t\n \n 123 \t", "%c %c")
TWO_SIMBOL_CHAR_TEST(test_191, "\t\n \n \ta \t b", "   %c %c")
TWO_SIMBOL_CHAR_TEST(test_192, "1 2 3 = + - 5", "1 2 3 = %c %*c %c")
TWO_SIMBOL_CHAR_TEST(test_193, "asdfghjk= \t 2", "asdfghj%c= %*c %c")
TWO_SIMBOL_CHAR_TEST(test_194, "\n\t a \t", "%c %c")
TWO_SIMBOL_CHAR_TEST(test_195, "\t \0 \t 2_3", "%c_%c")
TWO_SIMBOL_CHAR_TEST(test_196, "+=-! i +=-! j", "+=-! %c +=-! %c")
TWO_SIMBOL_CHAR_TEST(test_197, "hsj2j2h3-+_;s", "hs%c2%c")
TWO_SIMBOL_CHAR_TEST(test_198, "NULL", "NU%c%c")
TWO_SIMBOL_CHAR_TEST(test_199, "Yes NO", "%ces %c")

TCase *two_simbol_char_test() {
  TCase *t_s_c_t = tcase_create("two simbol char tests");

  tcase_add_test(t_s_c_t, test_190);
  tcase_add_test(t_s_c_t, test_191);
  tcase_add_test(t_s_c_t, test_192);
  tcase_add_test(t_s_c_t, test_193);
  tcase_add_test(t_s_c_t, test_194);
  tcase_add_test(t_s_c_t, test_195);
  tcase_add_test(t_s_c_t, test_196);
  tcase_add_test(t_s_c_t, test_197);
  tcase_add_test(t_s_c_t, test_198);
  tcase_add_test(t_s_c_t, test_199);

  return t_s_c_t;
}

// ==================================    %u TESTS
// ============================================

#define U_DECIMAL_INT_WITH_SKIP_TEST(testname, str, format)  \
  START_TEST(testname) {                                     \
    int libInt1 = -1;                                        \
    int libInt2 = -1;                                        \
    int myInt1 = -1;                                         \
    int myInt2 = -1;                                         \
                                                             \
    int libFunReturn, myFunReturn;                           \
                                                             \
    libFunReturn = sscanf(str, format, &libInt1, &libInt2);  \
    myFunReturn = s21_sscanf(str, format, &myInt1, &myInt2); \
                                                             \
    ck_assert_int_eq(libInt1, myInt1);                       \
    ck_assert_int_eq(libInt2, myInt2);                       \
                                                             \
    ck_assert_int_eq(libFunReturn, myFunReturn);             \
  }                                                          \
  END_TEST

U_DECIMAL_INT_WITH_SKIP_TEST(test_200, "+2112 175", " %u %u");
U_DECIMAL_INT_WITH_SKIP_TEST(test_201, "152 -14", "%2u %u");
U_DECIMAL_INT_WITH_SKIP_TEST(test_202, "-7372 3371.4", "%u %3u");
U_DECIMAL_INT_WITH_SKIP_TEST(test_203, "0 40", "%1u %1u");
U_DECIMAL_INT_WITH_SKIP_TEST(test_204, "003, 1", "%1u, %2u");
U_DECIMAL_INT_WITH_SKIP_TEST(test_205, "015 15", "%u %12u");
U_DECIMAL_INT_WITH_SKIP_TEST(test_206, "2147483647 338", "%6u %u");
U_DECIMAL_INT_WITH_SKIP_TEST(test_207, "-2147483648 972223", "%4u %5u");
U_DECIMAL_INT_WITH_SKIP_TEST(test_208, "9000000000000, 8000000000", "%4u, %u");
U_DECIMAL_INT_WITH_SKIP_TEST(test_209, "-9000000000000 48822", "%1u %u");
U_DECIMAL_INT_WITH_SKIP_TEST(test_210, "iof-423asfb-", "iof-4%1u %u");
U_DECIMAL_INT_WITH_SKIP_TEST(test_211, "b18d-23-3f04y8fin", "b%ud-%3u");
U_DECIMAL_INT_WITH_SKIP_TEST(test_212, "-094dsapdi", "%1u %1u");
U_DECIMAL_INT_WITH_SKIP_TEST(test_213, "c0-m-s0125c", "c%u-m-s%2u");
U_DECIMAL_INT_WITH_SKIP_TEST(test_214, "0imie21", "%uimie%1u");
U_DECIMAL_INT_WITH_SKIP_TEST(test_215, "ds9n99ads", "ds%1un%u");
U_DECIMAL_INT_WITH_SKIP_TEST(test_216, "n0n01", "n%un%1u");
U_DECIMAL_INT_WITH_SKIP_TEST(test_217, "ddsa2.48823g", "ddsa%3u.%3u");
U_DECIMAL_INT_WITH_SKIP_TEST(test_218, "dd0.2332d", "dd%u.%5u");
U_DECIMAL_INT_WITH_SKIP_TEST(test_219, "pji2po214748364800j", "pji%upo%17u");

TCase *u_decimal_int_with_skip() {
  TCase *u_d_i_w_s = tcase_create("Decimal int with skip tests");

  tcase_add_test(u_d_i_w_s, test_200);
  tcase_add_test(u_d_i_w_s, test_201);
  tcase_add_test(u_d_i_w_s, test_202);
  tcase_add_test(u_d_i_w_s, test_203);
  tcase_add_test(u_d_i_w_s, test_204);
  tcase_add_test(u_d_i_w_s, test_205);
  tcase_add_test(u_d_i_w_s, test_206);
  tcase_add_test(u_d_i_w_s, test_207);
  tcase_add_test(u_d_i_w_s, test_208);
  tcase_add_test(u_d_i_w_s, test_209);
  tcase_add_test(u_d_i_w_s, test_210);
  tcase_add_test(u_d_i_w_s, test_211);
  tcase_add_test(u_d_i_w_s, test_212);
  tcase_add_test(u_d_i_w_s, test_213);
  tcase_add_test(u_d_i_w_s, test_214);
  tcase_add_test(u_d_i_w_s, test_215);
  tcase_add_test(u_d_i_w_s, test_216);
  tcase_add_test(u_d_i_w_s, test_217);
  tcase_add_test(u_d_i_w_s, test_218);
  tcase_add_test(u_d_i_w_s, test_219);

  return u_d_i_w_s;
}

// ==================================    %i TESTS
// ============================================

#define I_DECIMAL_INT_WITH_SKIP_TEST(testname, str, format)  \
  START_TEST(testname) {                                     \
    int libInt1 = -1;                                        \
    int libInt2 = -1;                                        \
    int myInt1 = -1;                                         \
    int myInt2 = -1;                                         \
                                                             \
    int libFunReturn, myFunReturn;                           \
                                                             \
    libFunReturn = sscanf(str, format, &libInt1, &libInt2);  \
    myFunReturn = s21_sscanf(str, format, &myInt1, &myInt2); \
                                                             \
    ck_assert_int_eq(libInt1, myInt1);                       \
    ck_assert_int_eq(libInt2, myInt2);                       \
                                                             \
    ck_assert_int_eq(libFunReturn, myFunReturn);             \
  }                                                          \
  END_TEST

I_DECIMAL_INT_WITH_SKIP_TEST(test_220, "+2112 175", " %i %i");
I_DECIMAL_INT_WITH_SKIP_TEST(test_221, "0xFF 12", "%2i %i");
I_DECIMAL_INT_WITH_SKIP_TEST(test_222, "-7372 3371.4", "%i %3i");
I_DECIMAL_INT_WITH_SKIP_TEST(test_223, "0 40", "%1i %1i");
I_DECIMAL_INT_WITH_SKIP_TEST(test_224, "003, 1", "%1i, %2i");
I_DECIMAL_INT_WITH_SKIP_TEST(test_225, "015 15", "%i %12i");
I_DECIMAL_INT_WITH_SKIP_TEST(test_226, "2147483647 338", "%6i %i");
I_DECIMAL_INT_WITH_SKIP_TEST(test_227, "-2147483648 972223", "%4i %5i");
I_DECIMAL_INT_WITH_SKIP_TEST(test_228, "9000000000000, 8000000000", "%4i, %i");
I_DECIMAL_INT_WITH_SKIP_TEST(test_229, "-9000000000000 48822", "%1i %i");
I_DECIMAL_INT_WITH_SKIP_TEST(test_230, "iof-423asfb-", "iof-4%1i %i")
I_DECIMAL_INT_WITH_SKIP_TEST(test_232, "-094dsapdi", "%1i %1i");
I_DECIMAL_INT_WITH_SKIP_TEST(test_233, "c0-m-s0125c", "c%i-m-s%2i");
I_DECIMAL_INT_WITH_SKIP_TEST(test_234, "0imie21", "%iimie%1i");
I_DECIMAL_INT_WITH_SKIP_TEST(test_235, "ds9n99ads", "ds%1in%i");
I_DECIMAL_INT_WITH_SKIP_TEST(test_236, "n0n01", "n%in%1i");
I_DECIMAL_INT_WITH_SKIP_TEST(test_237, "ddsa2.48823g", "ddsa%3i.%3i");
I_DECIMAL_INT_WITH_SKIP_TEST(test_238, "dd0.2332d", "dd%i.%5i");
I_DECIMAL_INT_WITH_SKIP_TEST(test_239, "pji2po214748364800j", "pji%ipo%17i");

TCase *i_decimal_int_with_skip() {
  TCase *i_d_i_w_s = tcase_create("Decimal int with skip tests");

  tcase_add_test(i_d_i_w_s, test_220);
  tcase_add_test(i_d_i_w_s, test_221);
  tcase_add_test(i_d_i_w_s, test_222);
  tcase_add_test(i_d_i_w_s, test_223);
  tcase_add_test(i_d_i_w_s, test_224);
  tcase_add_test(i_d_i_w_s, test_225);
  tcase_add_test(i_d_i_w_s, test_226);
  tcase_add_test(i_d_i_w_s, test_227);
  tcase_add_test(i_d_i_w_s, test_228);
  tcase_add_test(i_d_i_w_s, test_229);
  tcase_add_test(i_d_i_w_s, test_230);
  tcase_add_test(i_d_i_w_s, test_232);
  tcase_add_test(i_d_i_w_s, test_233);
  tcase_add_test(i_d_i_w_s, test_234);
  tcase_add_test(i_d_i_w_s, test_235);
  tcase_add_test(i_d_i_w_s, test_236);
  tcase_add_test(i_d_i_w_s, test_237);
  tcase_add_test(i_d_i_w_s, test_238);
  tcase_add_test(i_d_i_w_s, test_239);

  return i_d_i_w_s;
}

// ==================================    %x and X TESTS
// ============================================

#define X_DECIMAL_INT_WITH_SKIP_TEST(testname, str, format)  \
  START_TEST(testname) {                                     \
    int libInt1 = -1;                                        \
    int libInt2 = -1;                                        \
    int myInt1 = -1;                                         \
    int myInt2 = -1;                                         \
                                                             \
    int libFunReturn, myFunReturn;                           \
                                                             \
    libFunReturn = sscanf(str, format, &libInt1, &libInt2);  \
    myFunReturn = s21_sscanf(str, format, &myInt1, &myInt2); \
                                                             \
    ck_assert_int_eq(libInt1, myInt1);                       \
    ck_assert_int_eq(libInt2, myInt2);                       \
                                                             \
    ck_assert_int_eq(libFunReturn, myFunReturn);             \
  }                                                          \
  END_TEST

X_DECIMAL_INT_WITH_SKIP_TEST(test_240, "07777 175", " %x %x");
X_DECIMAL_INT_WITH_SKIP_TEST(test_241, "152 -14", "%2X %X");
X_DECIMAL_INT_WITH_SKIP_TEST(test_242, "-7372 3371.4", "%x %3x");
X_DECIMAL_INT_WITH_SKIP_TEST(test_243, "0 40", "%1x %1x");
X_DECIMAL_INT_WITH_SKIP_TEST(test_244, "003, 1", "%1x, %2x");
X_DECIMAL_INT_WITH_SKIP_TEST(test_245, "015 15", "%x %12x");
X_DECIMAL_INT_WITH_SKIP_TEST(test_246, "2147483647 338", "%6x %x");
X_DECIMAL_INT_WITH_SKIP_TEST(test_247, "-2147483648 972223", "%4x %5x");
X_DECIMAL_INT_WITH_SKIP_TEST(test_248, "9000000000000, 8000000000", "%4x, %x");
X_DECIMAL_INT_WITH_SKIP_TEST(test_249, "-9000000000000 07777", "%1x %x");
X_DECIMAL_INT_WITH_SKIP_TEST(test_250, "iof-423asfb-", "iof-4%1x %x");
X_DECIMAL_INT_WITH_SKIP_TEST(test_251, "b18d-23-3f04y8fin", "b%xd-%3x");
X_DECIMAL_INT_WITH_SKIP_TEST(test_252, "-094dsapdi", "%1x %1x");
X_DECIMAL_INT_WITH_SKIP_TEST(test_253, "c0-m-s0125c", "c%x-m-s%2x");
X_DECIMAL_INT_WITH_SKIP_TEST(test_254, "0imie21", "%ximie%1x");
X_DECIMAL_INT_WITH_SKIP_TEST(test_255, "ds9n99ads", "ds%1xn%x");
X_DECIMAL_INT_WITH_SKIP_TEST(test_256, "n0n01", "n%xn%1x");
X_DECIMAL_INT_WITH_SKIP_TEST(test_257, "ddsa2.48823g", "ddsa%3x.%3x");
X_DECIMAL_INT_WITH_SKIP_TEST(test_258, "dd0.2332d", "dd%x.%5x");
X_DECIMAL_INT_WITH_SKIP_TEST(test_259, "pji2po214748364800j", "pji%xpo%17x");

TCase *x_decimal_int_with_skip() {
  TCase *x_d_i_w_s = tcase_create("Decimal int with skip tests");

  tcase_add_test(x_d_i_w_s, test_240);
  tcase_add_test(x_d_i_w_s, test_241);
  tcase_add_test(x_d_i_w_s, test_242);
  tcase_add_test(x_d_i_w_s, test_243);
  tcase_add_test(x_d_i_w_s, test_244);
  tcase_add_test(x_d_i_w_s, test_245);
  tcase_add_test(x_d_i_w_s, test_246);
  tcase_add_test(x_d_i_w_s, test_247);
  tcase_add_test(x_d_i_w_s, test_248);
  tcase_add_test(x_d_i_w_s, test_249);
  tcase_add_test(x_d_i_w_s, test_250);
  tcase_add_test(x_d_i_w_s, test_251);
  tcase_add_test(x_d_i_w_s, test_252);
  tcase_add_test(x_d_i_w_s, test_253);
  tcase_add_test(x_d_i_w_s, test_254);
  tcase_add_test(x_d_i_w_s, test_255);
  tcase_add_test(x_d_i_w_s, test_256);
  tcase_add_test(x_d_i_w_s, test_257);
  tcase_add_test(x_d_i_w_s, test_258);
  tcase_add_test(x_d_i_w_s, test_259);

  return x_d_i_w_s;
}

// ==================================    %o TESTS
// ============================================

#define O_DECIMAL_INT_WITH_SKIP_TEST(testname, str, format)  \
  START_TEST(testname) {                                     \
    int libInt1 = -1;                                        \
    int libInt2 = -1;                                        \
    int myInt1 = -1;                                         \
    int myInt2 = -1;                                         \
                                                             \
    int libFunReturn, myFunReturn;                           \
                                                             \
    libFunReturn = sscanf(str, format, &libInt1, &libInt2);  \
    myFunReturn = s21_sscanf(str, format, &myInt1, &myInt2); \
                                                             \
    ck_assert_int_eq(libInt1, myInt1);                       \
    ck_assert_int_eq(libInt2, myInt2);                       \
                                                             \
    ck_assert_int_eq(libFunReturn, myFunReturn);             \
  }                                                          \
  END_TEST

O_DECIMAL_INT_WITH_SKIP_TEST(test_260, "07777 175", " %o %o");
O_DECIMAL_INT_WITH_SKIP_TEST(test_261, "152 -14", "%2o %o");
O_DECIMAL_INT_WITH_SKIP_TEST(test_262, "-7372 3371.4", "%o %3o");
O_DECIMAL_INT_WITH_SKIP_TEST(test_263, "0 40", "%1o %1o");
O_DECIMAL_INT_WITH_SKIP_TEST(test_264, "003, 1", "%1o, %2o");
O_DECIMAL_INT_WITH_SKIP_TEST(test_265, "015 15", "%o %12o");
O_DECIMAL_INT_WITH_SKIP_TEST(test_266, "2147483647 338", "%6o %o");
O_DECIMAL_INT_WITH_SKIP_TEST(test_267, "-2147483648 972223", "%4o %5o");
O_DECIMAL_INT_WITH_SKIP_TEST(test_268, "9000000000000, 8000000000", "%4o, %o");
O_DECIMAL_INT_WITH_SKIP_TEST(test_269, "-9000000000000 07777", "%1o %o");
O_DECIMAL_INT_WITH_SKIP_TEST(test_270, "iof-423asfb-", "iof-4%1o %o");
O_DECIMAL_INT_WITH_SKIP_TEST(test_271, "b18d-23-3f04y8fin", "b%od-%3o");
O_DECIMAL_INT_WITH_SKIP_TEST(test_272, "-094dsapdi", "%1o %1o");
O_DECIMAL_INT_WITH_SKIP_TEST(test_273, "c0-m-s0125c", "c%o-m-s%2o");
O_DECIMAL_INT_WITH_SKIP_TEST(test_274, "0imie21", "%oimie%1o");
O_DECIMAL_INT_WITH_SKIP_TEST(test_275, "ds9n99ads", "ds%1on%o");
O_DECIMAL_INT_WITH_SKIP_TEST(test_276, "n0n01", "n%on%1o");
O_DECIMAL_INT_WITH_SKIP_TEST(test_277, "ddsa2.48823g", "ddsa%3o.%3o");
O_DECIMAL_INT_WITH_SKIP_TEST(test_278, "dd0.2332d", "dd%o.%5o");
O_DECIMAL_INT_WITH_SKIP_TEST(test_279, "pji2po214748364800j", "pji%opo%17o");

TCase *o_decimal_int_with_skip() {
  TCase *o_d_i_w_s = tcase_create("Decimal int with skip tests");

  tcase_add_test(o_d_i_w_s, test_260);
  tcase_add_test(o_d_i_w_s, test_261);
  tcase_add_test(o_d_i_w_s, test_262);
  tcase_add_test(o_d_i_w_s, test_263);
  tcase_add_test(o_d_i_w_s, test_264);
  tcase_add_test(o_d_i_w_s, test_265);
  tcase_add_test(o_d_i_w_s, test_266);
  tcase_add_test(o_d_i_w_s, test_267);
  tcase_add_test(o_d_i_w_s, test_268);
  tcase_add_test(o_d_i_w_s, test_269);
  tcase_add_test(o_d_i_w_s, test_270);
  tcase_add_test(o_d_i_w_s, test_271);
  tcase_add_test(o_d_i_w_s, test_272);
  tcase_add_test(o_d_i_w_s, test_273);
  tcase_add_test(o_d_i_w_s, test_274);
  tcase_add_test(o_d_i_w_s, test_275);
  tcase_add_test(o_d_i_w_s, test_276);
  tcase_add_test(o_d_i_w_s, test_277);
  tcase_add_test(o_d_i_w_s, test_278);
  tcase_add_test(o_d_i_w_s, test_279);

  return o_d_i_w_s;
}

// ==================================    %p TESTS
// ============================================

#define POINTERL_TEST(testname, str, format)        \
  START_TEST(testname) {                            \
    void *libInt1;                                  \
    void *myInt1;                                   \
                                                    \
    int libFunReturn, myFunReturn;                  \
                                                    \
    libFunReturn = sscanf(str, format, &libInt1);   \
    myFunReturn = s21_sscanf(str, format, &myInt1); \
                                                    \
    ck_assert_ptr_eq(libInt1, myInt1);              \
                                                    \
    ck_assert_int_eq(libFunReturn, myFunReturn);    \
  }                                                 \
  END_TEST

POINTERL_TEST(test_280, "0x7ffd75ec5240 0x7f5ec5240", "%p");
POINTERL_TEST(test_281, "7ffd75ec5240 -14", "%2p");
POINTERL_TEST(test_282, "-0x7ffd75ec5240 0x7ffd75ec5240.4", "%p");

TCase *pointerl_test() {
  TCase *p_t = tcase_create("Decimal int with skip tests");

  tcase_add_test(p_t, test_280);
  tcase_add_test(p_t, test_281);
  tcase_add_test(p_t, test_282);
  return p_t;
}

Suite *sscanf_suite() {
  Suite *s = suite_create("SSCANF");
  //--%d--//
  suite_add_tcase(s, simple_decimal_int());
  suite_add_tcase(s, decimal_int_with_width());
  suite_add_tcase(s, decimal_int_with_skip());

  //--%f--//
  suite_add_tcase(s, simple_decimal_float());
  suite_add_tcase(s, floating_point_with_witdh());
  suite_add_tcase(s, floating_point_with_skip());

  //--%lf--//
  suite_add_tcase(s, simple_decimal_float_double());
  suite_add_tcase(s, double_point_with_witdh());

  //--%e--//
  suite_add_tcase(s, specifier_e_test());
  suite_add_tcase(s, specifier_e_with_witdh());
  suite_add_tcase(s, specifier_e_with_skip());

  //--%g--//
  suite_add_tcase(s, specifier_g_test());
  suite_add_tcase(s, specifier_g_with_witdh());
  suite_add_tcase(s, specifier_g_with_skip());

  //--%s--//
  suite_add_tcase(s, string_test());
  suite_add_tcase(s, for_two_string());

  //--%c--//
  suite_add_tcase(s, simbol_char_test());
  suite_add_tcase(s, two_simbol_char_test());

  //--%u--//
  suite_add_tcase(s, u_decimal_int_with_skip());

  //--%i--//
  suite_add_tcase(s, i_decimal_int_with_skip());

  //--%x--//
  suite_add_tcase(s, x_decimal_int_with_skip());

  //--%o--//
  suite_add_tcase(s, o_decimal_int_with_skip());

  //--%p--//
  suite_add_tcase(s, pointerl_test());

  return s;
}