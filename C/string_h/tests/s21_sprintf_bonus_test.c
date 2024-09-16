#include <check.h>
#include <limits.h>
#include <stdio.h>

#include "../s21_string.h"

#define BUFF_SIZE 256

#define COMPARE_DEST_STRINGS_AND_RETURNS(testName, format, ...) \
  START_TEST(testName) {                                        \
    int libFunReturn;                                           \
    int myFunReturn;                                            \
    char libFun[BUFF_SIZE];                                     \
    char myFun[BUFF_SIZE];                                      \
    memset(libFun, '1', BUFF_SIZE);                             \
    memset(myFun, '1', BUFF_SIZE);                              \
                                                                \
    libFunReturn = sprintf(libFun, format, ##__VA_ARGS__);      \
    myFunReturn = s21_sprintf(myFun, format, ##__VA_ARGS__);    \
                                                                \
    ck_assert_str_eq(libFun, myFun);                            \
    ck_assert_mem_eq(libFun, myFun, BUFF_SIZE);                 \
    ck_assert_int_eq(libFunReturn, myFunReturn);                \
  }                                                             \
  END_TEST

// =================================INT=========================
// Int with length in arg
COMPARE_DEST_STRINGS_AND_RETURNS(test_0, "%*dabcdef", 7, 15)
COMPARE_DEST_STRINGS_AND_RETURNS(test_1, "nfk%*dvjdas;", -3, 1222375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_2, "n9-%*d3fn4", 4, -3333)
COMPARE_DEST_STRINGS_AND_RETURNS(test_3, "qwe%*d, ", 16, INT_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_4, "%*d-j?e12l", -4, INT_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_5, "-j=%*dxz_{k}", 1, 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_6, "modq%*d.wfq-[]", 2, -0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_7, "oadsp;d%*d", 6, -134)
COMPARE_DEST_STRINGS_AND_RETURNS(test_8, "z~x%*dc", -21, 1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_9, ";[]czx;[]zx];[]%*d", 7, 700909291)

// Int with precision in arg
COMPARE_DEST_STRINGS_AND_RETURNS(test_10, "%.*dabcdef", 7, 15)
COMPARE_DEST_STRINGS_AND_RETURNS(test_11, "nfk%3.*dvjdas;", -3, 1222375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_12, "n9-%.*d3fn4", 4, -3333)
COMPARE_DEST_STRINGS_AND_RETURNS(test_13, "qwe%16.*d, ", 16, INT_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_14, "%4.*d-j?e12l", -4, INT_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_15, "-j=%1.*dxz_{k}", 1, 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_16, "modq%2.*d.wfq-[]", 2, -0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_17, "oadsp;d%6.*d", 6, -134)
COMPARE_DEST_STRINGS_AND_RETURNS(test_18, "z~x%*.*dc", 21, 4, 1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_19, ";[]czx;[]zx];[]%*.*d", 7, -7,
                                 700909291)

// Int with 0 placeholder
COMPARE_DEST_STRINGS_AND_RETURNS(test_20, "%0*dabcdef", 7, 15)
COMPARE_DEST_STRINGS_AND_RETURNS(test_21, "nfk%03dvjdas;", 1222375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_22, "n9-%0*d3fn4", 4, -3333)
COMPARE_DEST_STRINGS_AND_RETURNS(test_23, "qwe%016d, ", INT_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_24, "%0*d-j?e12l", 4, INT_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_25, "-j=%0*dxz_{k}", 1, 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_26, "modq%0*d.wfq-[]", 2, -0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_27, "oadsp;d%06d", -134)
COMPARE_DEST_STRINGS_AND_RETURNS(test_28, "z~x%0*dc", 21, 1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_29, ";[]czx;[]zx];[]%0*d", 7, 700909291)

// =================================LONG LONG INT=========================
// Long long int with length in arg
COMPARE_DEST_STRINGS_AND_RETURNS(test_30, "%*Ldabcdef", 7, 15ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_31, "nfk%*Ldvjdas;", -3, 1222375ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_32, "n9-%*Ld3fn4", 4, -3333ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_33, "qwe%*Ld, ", 16, LLONG_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_34, "%*Ld-j?e12l", 4, LLONG_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_35, "-j=%*Ldxz_{k}", 1, 0ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_36, "modq%*Ld.wfq-[]", 2, -0ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_37, "oadsp;d%*Ld", 6, -134ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_38, "z~x%*Ldc", 21, 1ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_39, ";[]czx;[]zx];[]%*Ld", 7, 700909291ll)

// Long long int with precision in arg
COMPARE_DEST_STRINGS_AND_RETURNS(test_40, "%.*Ldabcdef", 7, 15ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_41, "nfk%3.*Ldvjdas;", -3, 1222375ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_42, "n9-%.*Ld3fn4", 4, -3333ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_43, "qwe%16.*Ld, ", 16, LLONG_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_44, "%4.*Ld-j?e12l", -4, LLONG_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_45, "-j=%1.*Ldxz_{k}", 1, 0ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_46, "modq%2.*Ld.wfq-[]", 2, -0ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_47, "oadsp;d%6.*Ld", 6, -134ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_48, "z~x%*.*Ldc", 21, 4, 1ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_49, ";[]czx;[]zx];[]%*.*Ld", 7, -7,
                                 700909291ll)

// Long long int with 0 placeholder
COMPARE_DEST_STRINGS_AND_RETURNS(test_50, "%0*Ldabcdef", 7, 15LL)
COMPARE_DEST_STRINGS_AND_RETURNS(test_51, "nfk%03Ldvjdas;", 1222375LL)
COMPARE_DEST_STRINGS_AND_RETURNS(test_52, "n9-%0*Ld3fn4", 4, -3333LL)
COMPARE_DEST_STRINGS_AND_RETURNS(test_53, "qwe%016Ld, ", LLONG_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_54, "%0*Ld-j?e12l", 4, LLONG_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_55, "-j=%0*Ldxz_{k}", 1, 0LL)
COMPARE_DEST_STRINGS_AND_RETURNS(test_56, "modq%0*Ld.wfq-[]", 2, -0LL)
COMPARE_DEST_STRINGS_AND_RETURNS(test_57, "oadsp;d%06Ld", -134LL)
COMPARE_DEST_STRINGS_AND_RETURNS(test_58, "z~x%0*Ldc", 21, 1LL)
COMPARE_DEST_STRINGS_AND_RETURNS(test_59, ";[]czx;[]zx];[]%0*Ld", 7,
                                 700909291LL)

// =================================UNSIGNED INT=========================
// Unsigned int with length in arg
COMPARE_DEST_STRINGS_AND_RETURNS(test_60, "%*uabcdef", 7, 15u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_61, "nfk%*uvjdas;", -3, 1222375u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_62, "n9-%*u3fn4", 4, -3333)
COMPARE_DEST_STRINGS_AND_RETURNS(test_63, "qwe%*u, ", 16, UINT_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_64, "%*u-j?e12l", -4, 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_65, "-j=%*uxz_{k}", 1, 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_66, "modq%*u.wfq-[]", 2, -0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_67, "oadsp;d%*u", 6, -134u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_68, "z~x%*uc", -21, 1u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_69, ";[]czx;[]zx];[]%*u", 7, 700909291u)

// Unsigned int with precision in arg
COMPARE_DEST_STRINGS_AND_RETURNS(test_70, "%.*uabcdef", 7, 15u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_71, "nfk%3.*uvjdas;", -3, 1222375u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_72, "n9-%.*u3fn4", 4, -3333)
COMPARE_DEST_STRINGS_AND_RETURNS(test_73, "qwe%16.*u, ", 16, UINT_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_74, "%4.*u-j?e12l", -4, 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_75, "-j=%1.*uxz_{k}", 1, 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_76, "modq%2.*u.wfq-[]", 2, -0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_77, "oadsp;d%6.*u", 6, -134u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_78, "z~x%*.*uc", 21, 4, 1u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_79, ";[]czx;[]zx];[]%*.*u", 7, -7,
                                 700909291u)

// Unsigned int with 0 placeholder
COMPARE_DEST_STRINGS_AND_RETURNS(test_80, "%0*uabcdef", 7, 15u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_81, "nfk%03dvjdas;", 1222375u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_82, "n9-%0*u3fn4", 4, -3333)
COMPARE_DEST_STRINGS_AND_RETURNS(test_83, "qwe%016d, ", UINT_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_84, "%0*u-j?e12l", 4, 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_85, "-j=%0*uxz_{k}", 1, 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_86, "modq%0*u.wfq-[]", 2, -0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_87, "oadsp;d%06d", -134u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_88, "z~x%0*uc", 21, 1u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_89, ";[]czx;[]zx];[]%0*u", 7, 700909291u)

// =================================UNSIGNED LONG LONG
// INT========================= Unsigned long long int with length in arg
COMPARE_DEST_STRINGS_AND_RETURNS(test_90, "%*Luabcdef", 7, 15ull)
COMPARE_DEST_STRINGS_AND_RETURNS(test_91, "nfk%*Luvjdas;", -3, 1222375ull)
COMPARE_DEST_STRINGS_AND_RETURNS(test_92, "n9-%*Lu3fn4", 4, -3333ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_93, "qwe%*Lu, ", 16, ULLONG_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_94, "%*Lu-j?e12l", 4, 0ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_95, "-j=%*Luxz_{k}", 1, 0ull)
COMPARE_DEST_STRINGS_AND_RETURNS(test_96, "modq%*Lu.wfq-[]", 2, -0ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_97, "oadsp;d%*Lu", 6, -134ull)
COMPARE_DEST_STRINGS_AND_RETURNS(test_98, "z~x%*Luc", 21, 1ull)
COMPARE_DEST_STRINGS_AND_RETURNS(test_99, ";[]czx;[]zx];[]%*Lu", 7,
                                 700909291ull)

// Unsigned long long int with precision in arg
COMPARE_DEST_STRINGS_AND_RETURNS(test_100, "%.*Luabcdef", 7, 15ull)
COMPARE_DEST_STRINGS_AND_RETURNS(test_101, "nfk%3.*Luvjdas;", -3, 1222375ull)
COMPARE_DEST_STRINGS_AND_RETURNS(test_102, "n9-%.*Lu3fn4", 4, -3333ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_103, "qwe%16.*Lu, ", 16, ULLONG_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_104, "%4.*Lu-j?e12l", -4, 0ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_105, "-j=%1.*Luxz_{k}", 1, 0ull)
COMPARE_DEST_STRINGS_AND_RETURNS(test_106, "modq%2.*Lu.wfq-[]", 2, -0ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_107, "oadsp;d%6.*Lu", 6, -134ull)
COMPARE_DEST_STRINGS_AND_RETURNS(test_108, "z~x%*.*Luc", 21, 4, 1ull)
COMPARE_DEST_STRINGS_AND_RETURNS(test_109, ";[]czx;[]zx];[]%*.*Lu", 7, -7,
                                 700909291ull)

// Unsigned long long int with 0 placeholder
COMPARE_DEST_STRINGS_AND_RETURNS(test_110, "%0*Luabcdef", 7, 15uLL)
COMPARE_DEST_STRINGS_AND_RETURNS(test_111, "nfk%03Ldvjdas;", 1222375uLL)
COMPARE_DEST_STRINGS_AND_RETURNS(test_112, "n9-%0*Lu3fn4", 4, -3333LL)
COMPARE_DEST_STRINGS_AND_RETURNS(test_113, "qwe%016Ld, ", ULLONG_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_114, "%0*Lu-j?e12l", 4, 0LL)
COMPARE_DEST_STRINGS_AND_RETURNS(test_115, "-j=%0*Luxz_{k}", 1, 0uLL)
COMPARE_DEST_STRINGS_AND_RETURNS(test_116, "modq%0*Lu.wfq-[]", 2, -0uLL)
COMPARE_DEST_STRINGS_AND_RETURNS(test_117, "oadsp;d%06Ld", -134uLL)
COMPARE_DEST_STRINGS_AND_RETURNS(test_118, "z~x%0*Luc", 21, 1uLL)
COMPARE_DEST_STRINGS_AND_RETURNS(test_119, ";[]czx;[]zx];[]%0*Lu", 7,
                                 700909291uLL)

// =================================STRING=========================
// String with length in arg
COMPARE_DEST_STRINGS_AND_RETURNS(test_120, "%*sabcdef", 7, "1f5")
COMPARE_DEST_STRINGS_AND_RETURNS(test_121, "nfk%*svjdas;", -3, "1222ds375")
COMPARE_DEST_STRINGS_AND_RETURNS(test_122, "n9-%*s3fn4", 4, "-33s33")
COMPARE_DEST_STRINGS_AND_RETURNS(test_123, "qwe%*s, ", 16, "INT_MAX")
COMPARE_DEST_STRINGS_AND_RETURNS(test_124, "%*s-j?e12l", -4, "INT_MIN")
COMPARE_DEST_STRINGS_AND_RETURNS(test_125, "-j=%*sxz_{k}", 1, "0fd")
COMPARE_DEST_STRINGS_AND_RETURNS(test_126, "modq%*s.wfq-[]", 2, "-0dsads")
COMPARE_DEST_STRINGS_AND_RETURNS(test_127, "oadsp;d%*s", 6, "-sda134dsa")
COMPARE_DEST_STRINGS_AND_RETURNS(test_128, "z~x%*sc", -21, "1")
COMPARE_DEST_STRINGS_AND_RETURNS(test_129, ";[]czx;[]zx];[]%*s", 7,
                                 "70sda090sd9291")

// String with precision in arg
COMPARE_DEST_STRINGS_AND_RETURNS(test_130, "%.*sabcdef", 7, "1dsad5")
COMPARE_DEST_STRINGS_AND_RETURNS(test_131, "nfk%3.*svjdas;", -3, "1222dsa375")
COMPARE_DEST_STRINGS_AND_RETURNS(test_132, "n9-%.*s3fn4", 4, "-dasd33dsa33")
COMPARE_DEST_STRINGS_AND_RETURNS(test_133, "qwe%16.*s, ", 16, "INT_MAX")
COMPARE_DEST_STRINGS_AND_RETURNS(test_134, "%4.*s-j?e12l", -4, "INT_MIN")
COMPARE_DEST_STRINGS_AND_RETURNS(test_135, "-j=%1.*sxz_{k}", 1, "0dsa")
COMPARE_DEST_STRINGS_AND_RETURNS(test_136, "modq%2.*s.wfq-[]", 2, "-0ads")
COMPARE_DEST_STRINGS_AND_RETURNS(test_137, "oadsp;d%6.*s", 6, "-13das4")
COMPARE_DEST_STRINGS_AND_RETURNS(test_138, "z~x%*.*sc", 21, 4, "dasdas1")
COMPARE_DEST_STRINGS_AND_RETURNS(test_139, ";[]czx;[]zx];[]%*.*s", 7, -7,
                                 "700909dsads291")

// =================================CHAR=========================
// CHAR with length in arg
COMPARE_DEST_STRINGS_AND_RETURNS(test_140, "%*cabcdef", 7, 'c')
COMPARE_DEST_STRINGS_AND_RETURNS(test_141, "nfk%*cvjdas;", -3, 'e')
COMPARE_DEST_STRINGS_AND_RETURNS(test_142, "n9-%*c3fn4", 4, 123)
COMPARE_DEST_STRINGS_AND_RETURNS(test_143, "qwe%*c, ", 16, CHAR_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_144, "%*c-j?e12l", -4, CHAR_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_145, "-j=%*cxz_{k}", 1, -47)
COMPARE_DEST_STRINGS_AND_RETURNS(test_146, "modq%*c.wfq-[]", 2, 'f')
COMPARE_DEST_STRINGS_AND_RETURNS(test_147, "oadsp;d%*c", 6, 'a')
COMPARE_DEST_STRINGS_AND_RETURNS(test_148, "z~x%*cc", -21, '1')
COMPARE_DEST_STRINGS_AND_RETURNS(test_149, ";[]czx;[]zx];[]%*c", 7, '7')

// =================================DOUBLE=========================
// Double with length in arg
COMPARE_DEST_STRINGS_AND_RETURNS(test_150, "%*fabcdef", 7, 15.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_151, "nfk%*fvjdas;", -3, 1222.375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_152, "n9-%*f3fn4", 4, -333.3)
COMPARE_DEST_STRINGS_AND_RETURNS(test_153, "qwe%*f, ", 16,
                                 78234.032186321641864)
COMPARE_DEST_STRINGS_AND_RETURNS(test_154, "%*f-j?e12l", -4,
                                 -67812.812392178391283)
COMPARE_DEST_STRINGS_AND_RETURNS(test_155, "-j=%*fxz_{k}", 1, 0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_156, "modq%*f.wfq-[]", 2, -0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_157, "oadsp;d%*f", 6, -134.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_158, "z~x%*fc", -21, 1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_159, ";[]czx;[]zx];[]%*f", 7, 70090.9291)

// Double with precision in arg
COMPARE_DEST_STRINGS_AND_RETURNS(test_160, "%.*fabcdef", 7, 15.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_161, "nfk%3.*fvjdas;", -3, 12.22375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_162, "n9-%.*f3fn4", 4, -333.3)
COMPARE_DEST_STRINGS_AND_RETURNS(test_163, "qwe%16.*f, ", 16,
                                 78234.032186321641864)
COMPARE_DEST_STRINGS_AND_RETURNS(test_164, "%4.*f-j?e12l", -4,
                                 -67812.812392178391283)
COMPARE_DEST_STRINGS_AND_RETURNS(test_165, "-j=%1.*fxz_{k}", 1, 0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_166, "modq%2.*f.wfq-[]", 2, -0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_167, "oadsp;d%6.*f", 6, -13.04)
COMPARE_DEST_STRINGS_AND_RETURNS(test_168, "z~x%*.*fc", 21, 4, 1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_169, ";[]czx;[]zx];[]%*.*f", 7, -7,
                                 700909.291)

// Double with 0 placeholder
COMPARE_DEST_STRINGS_AND_RETURNS(test_170, "%0*fabcdef", 7, 15.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_171, "nfk%03fvjdas;", 1222.375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_172, "n9-%0*f3fn4", 16, -333.3)
COMPARE_DEST_STRINGS_AND_RETURNS(test_173, "qwe%016f, ", 78234.032186321641864)
COMPARE_DEST_STRINGS_AND_RETURNS(test_174, "%0*f-j?e12l", 4,
                                 -67812.812392178391283)
COMPARE_DEST_STRINGS_AND_RETURNS(test_175, "-j=%0*fxz_{k}", 1, 0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_176, "modq%0*f.wfq-[]", 2, -0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_177, "oadsp;d%06f", -134.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_178, "z~x%0*fc", 21, 1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_179, ";[]czx;[]zx];[]%0*f", 7, 70090.9291)

// Double with required point
COMPARE_DEST_STRINGS_AND_RETURNS(test_180, "%#*fabcdef", 0, 15.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_181, "nfk%#3fvjdas;", 1222.375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_182, "n9-%#*f3fn4", 4, -333.3)
COMPARE_DEST_STRINGS_AND_RETURNS(test_183, "qwe%#16f, ", 78234.032186321641864)
COMPARE_DEST_STRINGS_AND_RETURNS(test_184, "%#*f-j?e12l", 4,
                                 -67812.812392178391283)
COMPARE_DEST_STRINGS_AND_RETURNS(test_185, "-j=%#*fxz_{k}", 1, 0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_186, "modq%#*f.wfq-[]", 2, -0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_187, "oadsp;d%#6.0f", -134.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_188, "z~x%#*fc", 21, 1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_189, ";[]czx;[]zx];[]%#*f", 7, 70090.9291)

// =================================LONG DOUBLE=========================
// Simple long double
COMPARE_DEST_STRINGS_AND_RETURNS(test_190, "%Lfabcdef", 1.5l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_191, "nfk%Lfvjdas;",
                                 122544325233253452.37553425423543l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_192, "n9-%Lf3fn4", -3.3354325234532453l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_193, "qwe%Lf, ", 784324324254354353.0L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_194, "%Lf-j?e12l", -0.8736218937621367L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_195, "-j=%Lfxz_{k}", .0532452335l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_196, "modq%Lf.wfq-[]", -0.000001l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_197, "oadsp;d%Lf",
                                 -1.0000000000000000000000l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_198, "z~x%Lfc",
                                 1.031244324213124213134241321234l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_199, ";[]czx;[]zx];[]%Lf",
                                 704312409092.91l)

// Long double with precision
COMPARE_DEST_STRINGS_AND_RETURNS(test_200, "%.17Lfabcdef",
                                 15.000423142341243211l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_201, "nfk%.30Lfvjdas;",
                                 14123412324.2432141234312375l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_202, "n9-%.14Lf3fn4",
                                 -33423133.334213424234232l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_203, "qwe%.16Lf, ", 784324324254354353.0L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_204, "%.64Lf-j?e12l", -0.87362189367L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_205, "-j=%.21Lfxz_{k}",
                                 0.00421343243242130001l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_206, "modq%.2Lf.wfq-[]",
                                 -0.0341242341234l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_207, "oadsp;d%.0Lf", -1.0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_208, "z~x%.14Lfc", 1.43214312344l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_209, ";[]czx;[]zx];[]%.7Lf",
                                 7042134123342309092.91l)

// Long double with min length
COMPARE_DEST_STRINGS_AND_RETURNS(test_210, "%6Lfabcdef", 1.567564l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_211, "nfk%3Lfvjdas;", 1276547456722.375l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_212, "n9-%4Lf3fn4",
                                 -33375647456.3754754674l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_213, "qwe%16Lf, ", 784324324254354353.0L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_214, "%4Lf-j?e12l", -0.8736218937621367L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_215, "-j=%1Lfxz_{k}", 0.0075647400004l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_216, "modq%2Lf.wfq-[]", -.450l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_217, "oadsp;d%6Lf", -137645745754.4l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_218, "z~x%21Lfc", 1.0745676457764l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_219, ";[]czx;[]zx];[]%7Lf",
                                 700.9097457546291l)

// Long double with min length left aligment
COMPARE_DEST_STRINGS_AND_RETURNS(test_220, "%-7Lfabcdef", 1.57564745745l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_221, "nfk%-3Lfvjdas;", 125746756223.75l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_222, "n9-%-4Lf3fn4", -33.3765476453l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_223, "qwe%-16Lf, ", 784324324254354353.0L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_224, "%-4Lf-j?e12l", -0.8736218937621367L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_225, "-j=%-1Lfxz_{k}", 0.754674567450l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_226, "modq%-2Lf.wfq-[]", -0.574675640l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_227, "oadsp;d%-6Lf", -137457546.4l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_228, "z~x%-21Lfc", 1.754675460l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_229, ";[]czx;[]zx];[]%-7Lf",
                                 70097645745609.291l)

// Long double with plus sign display
COMPARE_DEST_STRINGS_AND_RETURNS(test_230, "%+Lfabcdef", 1.57654754675467l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_231, "nfk%+Lfvjdas;",
                                 12546622.375647545775l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_232, "n9-%+Lf3fn4",
                                 -3.334765476457645745675467547456754675474573l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_233, "qwe%+6Lf, ", 784324324254354353.0L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_234, "%+Lf-j?e12l", -0.8736218937621367L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_235, "-j=%+Lfxz_{k}", 0.0567474567l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_236, "modq%+Lf.wfq-[]", -0.0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_237, "oadsp;d%+Lf",
                                 -174567457654754673.4l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_238, "z~x%+Lfc", 1.0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_239, ";[]czx;[]zx];[]%+Lf",
                                 70074567456547690.975467457654291l)

// Long double with space instead of plus
COMPARE_DEST_STRINGS_AND_RETURNS(test_240, "% Lfabcdef", 0.1754674574565L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_241, "nfk% Lfvjdas;",
                                 1027546754674522375.0L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_242, "n9-% Lf3fn4", -33765475745630.3L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_243, "qwe% 6Lf, ", 784324324254354353.0L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_244, "% Lf-j?e12l", -0.8736218937621367L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_245, "-j=% Lfxz_{k}", .07564745674560L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_246, "modq% Lf.wfq-[]", -.0764574564576L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_247, "oadsp;d% Lf",
                                 -13.474567564745674564576L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_248, "z~x% Lfc", 1.0L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_249, ";[]czx;[]zx];[]% Lf",
                                 756476457456.700909291L)

// Long double with all of advanced specs
COMPARE_DEST_STRINGS_AND_RETURNS(test_250, "%-+3.27Lfabc%Lfdef",
                                 17654745674565.0L,
                                 44.047564746574567546754674L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_251, "nfk%- 5.33Lfvjd%-3Lfas;",
                                 122.0237556775L, -19765475647542.071L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_252, "n9-%+-4.44Lf3f%6Lfn4",
                                 -3335746.756455603L, 82.0L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_253, "qwe%-+3.66Lf, %+6.14Lf",
                                 784324324254354353.0L, 423.34214141423123L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_254, "% -8.84Lf-j?e12l", -0.87367L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_255, "-j=%- 2.221Lfxz_{k}",
                                 07564764575467.754674560L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_256, "modq%+-1.Lf.wfq% Lf-[]", -0.760L,
                                 967.0L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_257, "oadsp;d%+-3.0Lf", -1.0L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_258, "z~x%-+9.21Lfc", 1.0547765745467L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_259, ";[]czx;[]zx];[]%11.7Lf",
                                 7009092.091766754L)

// Long double with length in arg
COMPARE_DEST_STRINGS_AND_RETURNS(test_260, "%*Lfabcdef", 31, 4324541.543l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_261, "nfk%*Lfvjdas;", -3,
                                 12223423423.432423475l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_262, "n9-%*Lf3fn4", 4,
                                 -3333.423432423432423423442342342l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_263, "qwe%*Lf, ", 16, 7843244234.03264l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_264, "%*Lf-j?e12l", 4, -0.8736219l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_265, "-j=%*Lfxz_{k}", 1, 0.0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_266, "modq%*Lf.wfq-[]", 2, -0.0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_267, "oadsp;d%*Lf", 6, -13.4l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_268, "z~x%*Lfc", 21, 1.432452l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_269, ";[]czx;[]zx];[]%*Lf", 7,
                                 70090.9291l)

// Long double with precision in arg
COMPARE_DEST_STRINGS_AND_RETURNS(test_270, "%.*Lfabcdef", 27,
                                 15.342453534523540l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_271, "nfk%3.*Lfvjdas;", -3,
                                 122532.375542l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_272, "n9-%.*Lf3fn4", 14, -333.345354345l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_273, "qwe%16.*Lf, ", 57,
                                 7843243234.032184l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_274, "%4.*Lf-j?e12l", -4,
                                 -0.8737367812369l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_275, "-j=%1.*Lfxz_{k}", 1, 0.5234l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_276, "modq%2.*Lf.wfq-[]", 2,
                                 -053425.2534254325l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_277, "oadsp;d%6.*Lf", 6, -134545.5342532l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_278, "z~x%*.*Lfc", 21, 4, 1.545234l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_279, ";[]czx;[]zx];[]%*.*Lf", 7, -7,
                                 70090.92542491l)

// Long double with 0 placeholder
COMPARE_DEST_STRINGS_AND_RETURNS(test_280, "%0*Lfabcdef", 7, 15.0345L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_281, "nfk%03Lfvjdas;", 1222.543545375L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_282, "n9-%0*Lf3fn4", 4, -333.3L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_283, "qwe%016Lf, ",
                                 78433424234.0321863255424l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_284, "%0*Lf-j?e12l", 4,
                                 -0.873621893762367812369l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_285, "-j=%0*Lfxz_{k}", 1, 0.6L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_286, "modq%0*Lf.wfq-[]", 2,
                                 -0.21332234523L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_287, "oadsp;d%06Lf", -13.4L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_288, "z~x%0*Lfc", 21, 1.345234435234523L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_289, ";[]czx;[]zx];[]%0*Lf", 7,
                                 7009.09291L)

// Long double with required point
COMPARE_DEST_STRINGS_AND_RETURNS(test_290, "%#*Lfabcdef", 0, 15.0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_291, "nfk%#3Lfvjdas;", 1222.375L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_292, "n9-%#*Lf3fn4", 4, -333.3L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_293, "qwe%#16Lf, ",
                                 78432434.032186325534564L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_294, "%#*Lf-j?e12l", 4,
                                 -0.873687367812369L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_295, "-j=%#*Lfxz_{k}", 1, 0.0L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_296, "modq%#*Lf.wfq-[]", 2, -0.0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_297, "oadsp;d%#6.0Lf", -1356345645234.0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_298, "z~x%#*Lfc", 21, 1.0L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_299, ";[]czx;[]zx];[]%#*Lf", 7,
                                 70090.9291L)

// ================================EXPONENCIAL
// DOUBLE=================================== Exp double with all of advanced
// specs
COMPARE_DEST_STRINGS_AND_RETURNS(test_300, "%-+3.7eabc%edef", 15.0, 4.4044)
COMPARE_DEST_STRINGS_AND_RETURNS(test_301, "nfk%- 5.3evjd%-3eas;", 122.02375,
                                 -192.071)
COMPARE_DEST_STRINGS_AND_RETURNS(test_302, "n9-%+-4.4e3f%6en4", -333.03, 82.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_303, "qwe%-+3.16e, %+6.4e",
                                 0.000000000000000000001, 4798.3)
COMPARE_DEST_STRINGS_AND_RETURNS(test_304, "% -8.4e-j?e12l",
                                 10000000000000000000.000)
COMPARE_DEST_STRINGS_AND_RETURNS(test_305, "-j=%- 2.1exz_{k}", 0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_306, "modq%+-1.2e.wfq% e-[]", -0.0, 967.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_307, "oadsp;d%+-3.0e", -1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_308, "z~x%-+9.13ec", 1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_309, ";[]czx;[]zx];[]%11.7e", 7009092.091)

// Exp double with length in arg
COMPARE_DEST_STRINGS_AND_RETURNS(test_310, "%*eabcdef", 7, 15.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_311, "nfk%*evjdas;", -3, 1222.375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_312, "n9-%*e3fn4", 4, -333.3)
COMPARE_DEST_STRINGS_AND_RETURNS(test_313, "qwe%*e, ", 16,
                                 78234.032186321641864)
COMPARE_DEST_STRINGS_AND_RETURNS(test_314, "%*e-j?e12l", -4,
                                 -67812.812392178391283)
COMPARE_DEST_STRINGS_AND_RETURNS(test_315, "-j=%*exz_{k}", 1, 0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_316, "modq%*e.wfq-[]", 2, -0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_317, "oadsp;d%*e", 6, -134.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_318, "z~x%*ec", -21, 1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_319, ";[]czx;[]zx];[]%*e", 7, 70090.9291)

// Exp double with precision in ar2
COMPARE_DEST_STRINGS_AND_RETURNS(test_320, "%.*eabcdef", 7, 15.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_321, "nfk%3.*evjdas;", -3, 12.22375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_322, "n9-%.*e3fn4", 4, -333.3)
COMPARE_DEST_STRINGS_AND_RETURNS(test_323, "qwe%16.*e, ", 16,
                                 78234.032186321641864)
COMPARE_DEST_STRINGS_AND_RETURNS(test_324, "%4.*e-j?e12l", -4,
                                 -67812.812392178391283)
COMPARE_DEST_STRINGS_AND_RETURNS(test_325, "-j=%1.*exz_{k}", 1, 0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_326, "modq%2.*e.wfq-[]", 2, -0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_327, "oadsp;d%6.*e", 6, -13.04)
COMPARE_DEST_STRINGS_AND_RETURNS(test_328, "z~x%*.*ec", 21, 4, 1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_329, ";[]czx;[]zx];[]%*.*e", 7, -7,
                                 700909.291)

// Exp double with 0 placeholder
COMPARE_DEST_STRINGS_AND_RETURNS(test_330, "%0*eabcdef", 7, 15.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_331, "nfk%03evjdas;", 1222.375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_332, "n9-%0*e3fn4", 4, -333.3)
COMPARE_DEST_STRINGS_AND_RETURNS(test_333, "qwe%016e, ", 78234.032186321641864)
COMPARE_DEST_STRINGS_AND_RETURNS(test_334, "%0*e-j?e12l", 4,
                                 -67812.812392178391283)
COMPARE_DEST_STRINGS_AND_RETURNS(test_335, "-j=%0*exz_{k}", 1, 0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_336, "modq%0*e.wfq-[]", 2, -0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_337, "oadsp;d%06e", -134.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_338, "z~x%0*ec", 21, 1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_339, ";[]czx;[]zx];[]%0*e", 7, 70090.9291)

// Exp double with required point
COMPARE_DEST_STRINGS_AND_RETURNS(test_340, "%#*eabcdef", 0, 15.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_341, "nfk%#3evjdas;", 1222.375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_342, "n9-%#*e3fn4", 4, -333.3)
COMPARE_DEST_STRINGS_AND_RETURNS(test_343, "qwe%#16e, ", 78234.032186321641864)
COMPARE_DEST_STRINGS_AND_RETURNS(test_344, "%#*e-j?e12l", 4,
                                 -67812.812392178391283)
COMPARE_DEST_STRINGS_AND_RETURNS(test_345, "-j=%#*exz_{k}", 1, 0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_346, "modq%#*e.wfq-[]", 2, -0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_347, "oadsp;d%#6.0e", -134.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_348, "z~x%#*ec", 21, 1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_349, ";[]czx;[]zx];[]%#*e", 7, 70090.9291)

// =================================LONG EXPONENCIAL
// DOUBLE========================= Long exp double with all of advanced specs
COMPARE_DEST_STRINGS_AND_RETURNS(test_350, "%-+3.16LEabc%LEdef",
                                 17654745674565.0L, 44.04754674L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_351, "nfk%- 5.LEvjd%-3LEas;", 122.02775L,
                                 -19765475642.071L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_352, "n9-%+-4.2LE3f%6LEn4",
                                 -333755746.756475603L, 82.0L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_353, "qwe%-+3.12LE, %+6.14LE",
                                 7834.032186325544l, 423.34214141423L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_354, "% -8.3LE-j?e12l", -0.8736218912369l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_355, "-j=%- 2.4LExz_{k}",
                                 0756467.75467460L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_356, "modq%+-1.11LE.wfq% LE-[]",
                                 -0.75465460L, 967.0L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_357, "oadsp;d%+-3.0LE", -1.0L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_358, "z~x%-+9.21LEc", 1.0547765745467L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_359, ";[]czx;[]zx];[]%11.7LE",
                                 7009092.09176754L)

// Long exp double with length in arg
COMPARE_DEST_STRINGS_AND_RETURNS(test_360, "%*LEabcdef", 31,
                                 432341.542343432423l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_361, "nfk%*LEvjdas;", -3,
                                 12223423423.432423475l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_362, "n9-%*LE3fn4", 4, -3333.423432342l)
COMPARE_DEST_STRINGS_AND_RETURNS(
    test_363, "qwe%*LE, ", 16, 7843243242323423424234.03218632553543251641864l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_364, "%*LE-j?e12l", 4, -0.873712892369l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_365, "-j=%*LExz_{k}", 1, 0.0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_366, "modq%*LE.wfq-[]", 2, -0.0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_367, "oadsp;d%*LE", 6, -13.4l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_368, "z~x%*LEc", 21, 1.432422452l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_369, ";[]czx;[]zx];[]%*LE", 7,
                                 70090.9291l)

// Long exp double with precision in arg
COMPARE_DEST_STRINGS_AND_RETURNS(test_370, "%.*LEabcdef", 13,
                                 15.342453534523540l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_371, "nfk%3.*LEvjdas;", -3,
                                 1225432532.37554235432l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_372, "n9-%.*LE3fn4", 14,
                                 -333.34532543252353452354345l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_373, "qwe%16.*LE, ", 17,
                                 7843424234.03214l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_374, "%4.*LE-j?e12l", -4, -0.87362369l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_375, "-j=%1.*LExz_{k}", 1, 0.5432545234l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_376, "modq%2.*LE.wfq-[]", 2,
                                 -054235453425.2534254325l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_377, "oadsp;d%6.*LE", 6,
                                 -1345234523545.5342532345432l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_378, "z~x%*.*LEc", 21, 4, 1.543255234l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_379, ";[]czx;[]zx];[]%*.*LE", 7, -7,
                                 70090.9254532491l)

// Long exp double with 0 placeholder
COMPARE_DEST_STRINGS_AND_RETURNS(test_380, "%0*LEabcdef", 7, 15.0345L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_381, "nfk%03LEvjdas;", 1222.543545375L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_382, "n9-%0*LE3fn4", 4, -333.3L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_383, "qwe%016LE, ", 78424234.03218631864l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_384, "%0*LE-j?e12l", 4, -0.873621893l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_385, "-j=%0*LExz_{k}", 1, 0.6L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_386, "modq%0*LE.wfq-[]", 2, -0.2133523L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_387, "oadsp;d%06LE", -13.4L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_388, "z~x%0*LEc", 21, 1.345523L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_389, ";[]czx;[]zx];[]%0*LE", 7,
                                 7009.09291L)

// Long exp double with required point
COMPARE_DEST_STRINGS_AND_RETURNS(test_390, "%#*LEabcdef", 0, 15.0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_391, "nfk%#3LEvjdas;", 1222.375L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_392, "n9-%#*LE3fn4", 4, -333.3L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_393, "qwe%#16LE, ",
                                 7843243244234.0321863255423534534534L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_394, "%#*LE-j?e12l", 4,
                                 -0.81367128936218L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_395, "-j=%#*LExz_{k}", 1, 0.0L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_396, "modq%#*LE.wfq-[]", 2, -0.0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_397, "oadsp;d%#6.0LE", -1356334.0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_398, "z~x%#*LEc", 21, 1.0L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_399, ";[]czx;[]zx];[]%#*LE", 7,
                                 70090.9291L)

// ================================G DOUBLE===================================
// G double with all of advanced specs
COMPARE_DEST_STRINGS_AND_RETURNS(test_400, "%-+3.7gabc%gdef", 15.0, 4.4044)
COMPARE_DEST_STRINGS_AND_RETURNS(test_401, "nfk%- 5.3gvjd%-3gas;", 122.02375,
                                 -192.071)
COMPARE_DEST_STRINGS_AND_RETURNS(test_402, "n9-%+-4.4g3f%6gn4", -333.03, 82.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_403, "qwe%-+3.16g, %+6.4g",
                                 0.000000000000000000001, 4798.3)
COMPARE_DEST_STRINGS_AND_RETURNS(test_404, "% -8.4g-j?e12l",
                                 10000000000000000000.000)
COMPARE_DEST_STRINGS_AND_RETURNS(test_405, "-j=%- 2.1gxz_{k}", 3.7)
COMPARE_DEST_STRINGS_AND_RETURNS(test_406, "modq%+-1.2g.wfq% g-[]", -0.0, 967.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_407, "oadsp;d%+-3.0g", -1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_408, "z~x%-+9.13gc", 1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_409, ";[]czx;[]zx];[]%11.7g", 7009092.091)

// G double with length in arg
COMPARE_DEST_STRINGS_AND_RETURNS(test_410, "%*gabcdef", 7, 15.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_411, "nfk%*gvjdas;", -3, 1222.375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_412, "n9-%*g3fn4", 4, -333.3)
COMPARE_DEST_STRINGS_AND_RETURNS(test_413, "qwe%*g, ", 16,
                                 78234.032186321641864)
COMPARE_DEST_STRINGS_AND_RETURNS(test_414, "%*g-j?e12l", -4,
                                 -67812.812392178391283)
COMPARE_DEST_STRINGS_AND_RETURNS(test_415, "-j=%*gxz_{k}", 1, 0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_416, "modq%*g.wfq-[]", 2, -0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_417, "oadsp;d%*g", 6, -134.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_418, "z~x%*gc", -21, 1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_419, ";[]czx;[]zx];[]%*g", 7, 70090.9291)

// G double with precision in arg
COMPARE_DEST_STRINGS_AND_RETURNS(test_420, "%.*gabcdef", 7, 15.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_421, "nfk%3.*gvjdas;", -3, 12.22375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_422, "n9-%.*g3fn4", 4, -333.3)
COMPARE_DEST_STRINGS_AND_RETURNS(test_423, "qwe%16.*g, ", 16,
                                 78234.032186321641864)
COMPARE_DEST_STRINGS_AND_RETURNS(test_424, "%4.*g-j?e12l", -4,
                                 -67812.812392178391283)
COMPARE_DEST_STRINGS_AND_RETURNS(test_425, "-j=%1.*gxz_{k}", 1, 3.7)
COMPARE_DEST_STRINGS_AND_RETURNS(test_426, "modq%2.*g.wfq-[]", 2, -0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_427, "oadsp;d%6.*g", 6, -13.04)
COMPARE_DEST_STRINGS_AND_RETURNS(test_428, "z~x%*.*gc", 21, 4, 1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_429, ";[]czx;[]zx];[]%*.*g", 7, -7,
                                 700909.291)

// G double with 0 placeholder
COMPARE_DEST_STRINGS_AND_RETURNS(test_430, "%0*gabcdef", 7, 15.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_431, "nfk%03gvjdas;", 1222.375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_432, "n9-%0*g3fn4", 4, -333.3)
COMPARE_DEST_STRINGS_AND_RETURNS(test_433, "qwe%016g, ", 78234.032186321641864)
COMPARE_DEST_STRINGS_AND_RETURNS(test_434, "%0*g-j?e12l", 4,
                                 -67812.812392178391283)
COMPARE_DEST_STRINGS_AND_RETURNS(test_435, "-j=%0*gxz_{k}", 1, 0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_436, "modq%0*g.wfq-[]", 2, -0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_437, "oadsp;d%06g", -134.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_438, "z~x%0*gc", 21, 1.2)
COMPARE_DEST_STRINGS_AND_RETURNS(test_439, ";[]czx;[]zx];[]%0*g", 7, 70090.9291)

// G double with required point
COMPARE_DEST_STRINGS_AND_RETURNS(test_440, "%#*gabcdef", 0, 15.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_441, "nfk%#3gvjdas;", 1222.375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_442, "n9-%#*g3fn4", 4, -333.3)
COMPARE_DEST_STRINGS_AND_RETURNS(test_443, "qwe%#16eg ", 78234.032186321641864)
COMPARE_DEST_STRINGS_AND_RETURNS(test_444, "%#*g-j?e12l", 4,
                                 -67812.812392178391283)
COMPARE_DEST_STRINGS_AND_RETURNS(test_445, "-j=%#*gxz_{k}", 1, 0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_446, "modq%#*g.wfq-[]", 2, -0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_447, "oadsp;d%#6.0g", -134.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_448, "z~x%#*gc", 21, 1.2)
COMPARE_DEST_STRINGS_AND_RETURNS(test_449, ";[]czx;[]zx];[]%#*g", 7, 70090.9291)

// =================================LONG G DOUBLE=========================
// Long g double with all of advanced specs
COMPARE_DEST_STRINGS_AND_RETURNS(test_450, "%-+3.27LGabc%LGdef",
                                 17654745674565.0L, 44.0475647446754674L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_451, "nfk%- 5.11LGvjd%-3LGas;",
                                 122.023754675L, -19775642.071L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_452, "n9-%+-4.44LG3f%6LGn4",
                                 -3337567546.75647564603L, 82.0L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_453, "qwe%-+3.66LG, %+6.14LG",
                                 7843244234.0864l, 423.342123123L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_454, "% -8.6LG-j?e12l", -1.134l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_455, "-j=%- 2.221LGxz_{k}",
                                 0756475467.7546745674560L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_456, "modq%+-1.22LG.wfq% LG-[]",
                                 -0.754675460L, 967.0L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_457, "oadsp;d%+-3.0LG", -1.0L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_458, "z~x%-+9.7LGc", 1.0547765745467L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_459, ";[]czx;[]zx];[]%11.7LG",
                                 7009092.0917654L)

// Long g double with length in arg
COMPARE_DEST_STRINGS_AND_RETURNS(test_460, "%*LGabcdef", 31, 432441.5423423l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_461, "nfk%*LGvjdas;", -3,
                                 122223.432423475l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_462, "n9-%*LG3fn4", 4, -3333.42342342l)
COMPARE_DEST_STRINGS_AND_RETURNS(
    test_463, "qwe%*LG, ", 16, 7843244234.03218632554235345345345345341641864l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_464, "%*LG-j?e12l", 4, -0.8736218937669l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_465, "-j=%*LGxz_{k}", 1, 0.0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_466, "modq%*LG.wfq-[]", 2, -0.0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_467, "oadsp;d%*LG", 6, -13.4l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_468, "z~x%*LGc", 21, 1.432423422l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_469, ";[]czx;[]zx];[]%*LG", 7,
                                 70090.9291l)

// Long g double with precision in arg
COMPARE_DEST_STRINGS_AND_RETURNS(test_470, "%.*LGabcdef", 11, 15.34240l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_471, "nfk%3.*LGvjdas;", -3,
                                 12532.3755435432l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_472, "n9-%.*LG3fn4", 14, -333.3454345l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_473, "qwe%16.*LG, ", 57,
                                 784324234.0341864l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_474, "%4.*LG-j?e12l", -4,
                                 -0.812627367812369l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_475, "-j=%1.*LGxz_{k}", 1, 0.54234l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_476, "modq%2.*LG.wfq-[]", 2,
                                 -0543425.2534254325l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_477, "oadsp;d%6.*LG", 6, -134545.535432l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_478, "z~x%*.*LGc", 21, 4, 1.54324l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_479, ";[]czx;[]zx];[]%*.*LG", 7, -7,
                                 70090.922491l)

// Long g double with 0 placeholder
COMPARE_DEST_STRINGS_AND_RETURNS(test_480, "%0*LGabcdef", 7, 15.0345L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_481, "nfk%03LGvjdas;", 1222.5435L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_482, "n9-%0*LG3fn4", 4, -333.3L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_483, "qwe%016LG, ", 7844.03864l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_484, "%0*LG-j?e12l", 4, -0.87362169l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_485, "-j=%0*LGxz_{k}", 1, 0.6L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_486, "modq%0*LG.wfq-[]", 2, -0.2133223L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_487, "oadsp;d%06LG", -13.4L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_488, "z~x%0*LGc", 21, 1.34523523L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_489, ";[]czx;[]zx];[]%0*LG", 7,
                                 7009.09291L)

// Long g double with required point
COMPARE_DEST_STRINGS_AND_RETURNS(test_490, "%#*LGabcdef", 0, 15.0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_491, "nfk%#3LGvjdas;", 1222.375L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_492, "n9-%#*LG3fn4", 4, -333.3L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_493, "qwe%#16LG, ", 78424234.032864L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_494, "%#*LG-j?e12l", 4, -0.8736269L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_495, "-j=%#*LGxz_{k}", 1, 0.0L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_496, "modq%#*LG.wfq-[]", 2, -0.0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_497, "oadsp;d%#6.0LG", -13534.0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_498, "z~x%#*LGc", 4, 1.2L)
COMPARE_DEST_STRINGS_AND_RETURNS(test_499, ";[]czx;[]zx];[]%#*LG", 7,
                                 70090.9291L)

// ================================I INT===================================
// Simple i int
COMPARE_DEST_STRINGS_AND_RETURNS(test_500, "|%+07i|abc|%i|def", 15, 04444)
COMPARE_DEST_STRINGS_AND_RETURNS(test_501, "nfk|%- 5.3i|vjd|%-3i|as;", 1222375,
                                 -19271)
COMPARE_DEST_STRINGS_AND_RETURNS(test_502, "n9-|%+-4.4i|3f|%6i|n4", -0x3A33, 82)
COMPARE_DEST_STRINGS_AND_RETURNS(test_503, "qwe|%-+3.16i|, |%+6.4i|", INT_MAX,
                                 47983)
COMPARE_DEST_STRINGS_AND_RETURNS(test_504, "|% -8.4i|-j?e12l", INT_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_505, "-j=|%- 2.1i|xz_{k}", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_506, "modq|%+-1.2i|.wfq|% i|-[]", -0,
                                 0x9ff2)
COMPARE_DEST_STRINGS_AND_RETURNS(test_507, "oadsp;d|%+-3.0i|", -1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_508, "z~x|%-+9.21i|c", 1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_509, ";[]czx;[]zx];[]|%11.7i|", 700909291)

// ================================OCTAL INT===================================
// Simple octal int
COMPARE_DEST_STRINGS_AND_RETURNS(test_510, "|%07o|abc|%o|def", 15, 04444)
COMPARE_DEST_STRINGS_AND_RETURNS(test_511, "nfk|%-5.3o|vjd|%-3o|as;", 1222375,
                                 -19271)
COMPARE_DEST_STRINGS_AND_RETURNS(test_512, "n9-|%-4.4o|3f|%6o|n4", -0x3A33, 82)
COMPARE_DEST_STRINGS_AND_RETURNS(test_513, "qwe|%-#3.16o|, |%6.4o|", INT_MAX,
                                 47983)
COMPARE_DEST_STRINGS_AND_RETURNS(test_514, "|%-8.4o|-j?e12l", INT_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_515, "-j=|%-2.1o|xz_{k}", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_516, "modq|%-#o|.wfq|%#o|-[]", -0, 0x9ff2)
COMPARE_DEST_STRINGS_AND_RETURNS(test_517, "oadsp;d|%-3.0o|", -1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_518, "z~x|%-9.21o|c", 1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_519, ";[]czx;[]zx];[]|%11.7o|", 700909291)

// ================================HEX INT===================================
// Simple hex int
COMPARE_DEST_STRINGS_AND_RETURNS(test_520, "|%07x|abc|%X|def", 15, 04444)
COMPARE_DEST_STRINGS_AND_RETURNS(test_521, "nfk|%-#5.3x|vjd|%-3x|as;", 1222375,
                                 -19271)
COMPARE_DEST_STRINGS_AND_RETURNS(test_522, "n9-|%-4.4X|3f|%6X|n4", -0x3A33, 82)
COMPARE_DEST_STRINGS_AND_RETURNS(test_523, "qwe|%-3.16x|, |%6.4X|", INT_MAX,
                                 47983)
COMPARE_DEST_STRINGS_AND_RETURNS(test_524, "|%-8.4X|-j?e12l", INT_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_525, "-j=|%-#2.1x|xz_{k}", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_526, "modq|%-1.2x|.wfq|%X|-[]", -0,
                                 0x9ff2)
COMPARE_DEST_STRINGS_AND_RETURNS(test_527, "oadsp;d|%-3.0X|", -1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_528, "z~x|%-#9.21x|c", 1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_529, ";[]czx;[]zx];[]|%11.7X|", 700909291)

// ========================================POINTER========================
COMPARE_DEST_STRINGS_AND_RETURNS(test_530, "%pabcdef", "d3123d")
COMPARE_DEST_STRINGS_AND_RETURNS(test_531, "nfkvjd%pas;", "1e12d")
COMPARE_DEST_STRINGS_AND_RETURNS(test_532, "n9-%17pn4", "321c23")
COMPARE_DEST_STRINGS_AND_RETURNS(test_533, "qwe%3p, ", "INT_MAX")
COMPARE_DEST_STRINGS_AND_RETURNS(test_534, "%-32p-j?e12l", "INT_MIN")
COMPARE_DEST_STRINGS_AND_RETURNS(test_535, "-j=%*pxz_{k}", 13, "d0as")
COMPARE_DEST_STRINGS_AND_RETURNS(test_536, "modq%*p.wfq-[]", 2, "31dds")
COMPARE_DEST_STRINGS_AND_RETURNS(test_537, "oadsp;d%-*p", 31, "31255ds")
COMPARE_DEST_STRINGS_AND_RETURNS(test_538, "z~x%*p", -21, "133")
COMPARE_DEST_STRINGS_AND_RETURNS(test_539, ";[]czx;[]zx];[]%p", "314da")

// ================================COUNT
// RETURN===================================
START_TEST(test_540) {
  int libFunReturn;
  int myFunReturn;
  char libFun[BUFF_SIZE];
  char myFun[BUFF_SIZE];
  int libN1 = -2;
  int libN2 = -2;
  int myN1 = -2;
  int myN2 = -2;
  memset(libFun, '1', BUFF_SIZE);
  memset(myFun, '1', BUFF_SIZE);

  char *format = "dadsd%ndwa%nw";

  libFunReturn = sprintf(libFun, format, &libN1, &libN2);
  myFunReturn = s21_sprintf(myFun, format, &myN1, &myN2);

  ck_assert_int_eq(libN1, myN1);
  ck_assert_int_eq(libN2, myN2);
  ck_assert_int_eq(libFunReturn, myFunReturn);
}
END_TEST

START_TEST(test_541) {
  int libFunReturn;
  int myFunReturn;
  char libFun[BUFF_SIZE];
  char myFun[BUFF_SIZE];
  long int libN1 = -2;
  long int libN2 = -2;
  long int myN1 = -2;
  long int myN2 = -2;
  memset(libFun, '1', BUFF_SIZE);
  memset(myFun, '1', BUFF_SIZE);

  char *format = "oi0-d21d%ln%ln";

  libFunReturn = sprintf(libFun, format, &libN1, &libN2);
  myFunReturn = s21_sprintf(myFun, format, &myN1, &myN2);

  ck_assert_int_eq(libN1, myN1);
  ck_assert_int_eq(libN2, myN2);
  ck_assert_int_eq(libFunReturn, myFunReturn);
}
END_TEST

START_TEST(test_542) {
  int libFunReturn;
  int myFunReturn;
  char libFun[BUFF_SIZE];
  char myFun[BUFF_SIZE];
  long long int libN1 = -2;
  long long int libN2 = -2;
  long long int myN1 = -2;
  long long int myN2 = -2;
  memset(libFun, '1', BUFF_SIZE);
  memset(myFun, '1', BUFF_SIZE);

  char *format = "%llnf03m4%llnf4";

  libFunReturn = sprintf(libFun, format, &libN1, &libN2);
  myFunReturn = s21_sprintf(myFun, format, &myN1, &myN2);

  ck_assert_int_eq(libN1, myN1);
  ck_assert_int_eq(libN2, myN2);
  ck_assert_int_eq(libFunReturn, myFunReturn);
}
END_TEST

START_TEST(test_543) {
  int libFunReturn;
  int myFunReturn;
  char libFun[BUFF_SIZE];
  char myFun[BUFF_SIZE];
  short int libN1 = -2;
  short int libN2 = -2;
  short int myN1 = -2;
  short int myN2 = -2;
  memset(libFun, '1', BUFF_SIZE);
  memset(myFun, '1', BUFF_SIZE);

  char *format = "%hnf03m4%hnf4";

  libFunReturn = sprintf(libFun, format, &libN1, &libN2);
  myFunReturn = s21_sprintf(myFun, format, &myN1, &myN2);

  ck_assert_int_eq(libN1, myN1);
  ck_assert_int_eq(libN2, myN2);
  ck_assert_int_eq(libFunReturn, myFunReturn);
}
END_TEST

START_TEST(test_544) {
  int libFunReturn;
  int myFunReturn;
  char libFun[BUFF_SIZE];
  char myFun[BUFF_SIZE];
  signed char libN1 = -2;
  signed char libN2 = -2;
  signed char myN1 = -2;
  signed char myN2 = -2;
  memset(libFun, '1', BUFF_SIZE);
  memset(myFun, '1', BUFF_SIZE);

  char *format = "dfe32%hhnsg%hhnh2dfg";

  libFunReturn = sprintf(libFun, format, &libN1, &libN2);
  myFunReturn = s21_sprintf(myFun, format, &myN1, &myN2);

  ck_assert_int_eq(libN1, myN1);
  ck_assert_int_eq(libN2, myN2);
  ck_assert_int_eq(libFunReturn, myFunReturn);
}
END_TEST

START_TEST(test_545) {
  int libFunReturn;
  int myFunReturn;
  char libFun[BUFF_SIZE];
  char myFun[BUFF_SIZE];
  int libN1 = -2;
  int libN2 = -2;
  int myN1 = -2;
  int myN2 = -2;
  memset(libFun, '1', BUFF_SIZE);
  memset(myFun, '1', BUFF_SIZE);

  char *format = "%n%4dab%ncdef";

  libFunReturn = sprintf(libFun, format, &libN1, 15, &libN2);
  myFunReturn = s21_sprintf(myFun, format, &myN1, 15, &myN2);

  ck_assert_int_eq(libN1, myN1);
  ck_assert_int_eq(libN2, myN2);
  ck_assert_int_eq(libFunReturn, myFunReturn);
}
END_TEST

START_TEST(test_546) {
  int libFunReturn;
  int myFunReturn;
  char libFun[BUFF_SIZE];
  char myFun[BUFF_SIZE];
  int libN1 = -2;
  int libN2 = -2;
  int myN1 = -2;
  int myN2 = -2;
  memset(libFun, '1', BUFF_SIZE);
  memset(myFun, '1', BUFF_SIZE);

  char *format = ";[]%nczx;[%u]z%nx];[]";

  libFunReturn = sprintf(libFun, format, &libN1, 700909291u, &libN2);
  myFunReturn = s21_sprintf(myFun, format, &myN1, 700909291u, &myN2);

  ck_assert_int_eq(libN1, myN1);
  ck_assert_int_eq(libN2, myN2);
  ck_assert_int_eq(libFunReturn, myFunReturn);
}
END_TEST

START_TEST(test_547) {
  int libFunReturn;
  int myFunReturn;
  char libFun[BUFF_SIZE];
  char myFun[BUFF_SIZE];
  int libN1 = -2;
  int libN2 = -2;
  int myN1 = -2;
  int myN2 = -2;
  memset(libFun, '1', BUFF_SIZE);
  memset(myFun, '1', BUFF_SIZE);

  char *format = "mo%ndq%2c.wfq-[]%n";

  libFunReturn = sprintf(libFun, format, &libN1, '\n', &libN2);
  myFunReturn = s21_sprintf(myFun, format, &myN1, '\n', &myN2);

  ck_assert_int_eq(libN1, myN1);
  ck_assert_int_eq(libN2, myN2);
  ck_assert_int_eq(libFunReturn, myFunReturn);
}
END_TEST

START_TEST(test_548) {
  int libFunReturn;
  int myFunReturn;
  char libFun[BUFF_SIZE];
  char myFun[BUFF_SIZE];
  int libN1 = -2;
  int libN2 = -2;
  int myN1 = -2;
  int myN2 = -2;
  memset(libFun, '1', BUFF_SIZE);
  memset(myFun, '1', BUFF_SIZE);

  char *format = "oad%nsp;d%lc%n";

  libFunReturn = sprintf(libFun, format, &libN1, L'%', &libN2);
  myFunReturn = s21_sprintf(myFun, format, &myN1, L'%', &myN2);

  ck_assert_int_eq(libN1, myN1);
  ck_assert_int_eq(libN2, myN2);
  ck_assert_int_eq(libFunReturn, myFunReturn);
}
END_TEST

START_TEST(test_549) {
  int libFunReturn;
  int myFunReturn;
  char libFun[BUFF_SIZE];
  char myFun[BUFF_SIZE];
  int libN1 = -2;
  int libN2 = -2;
  int myN1 = -2;
  int myN2 = -2;
  memset(libFun, '1', BUFF_SIZE);
  memset(myFun, '1', BUFF_SIZE);

  char *format = "q%nwe%.16s,%n ";

  libFunReturn = sprintf(libFun, format, &libN1, "UIN\tT_MAX", &libN2);
  myFunReturn = s21_sprintf(myFun, format, &myN1, "UIN\tT_MAX", &myN2);

  ck_assert_int_eq(libN1, myN1);
  ck_assert_int_eq(libN2, myN2);
  ck_assert_int_eq(libFunReturn, myFunReturn);
}
END_TEST

START_TEST(test_550) {
  int libFunReturn;
  int myFunReturn;
  char libFun[BUFF_SIZE];
  char myFun[BUFF_SIZE];
  int libN1 = -2;
  int libN2 = -2;
  int myN1 = -2;
  int myN2 = -2;
  memset(libFun, '1', BUFF_SIZE);
  memset(myFun, '1', BUFF_SIZE);

  char *format = ";[]czx%n;[]zx];[]%ls%n";

  libFunReturn = sprintf(libFun, format, &libN1, L"700\v909291lu", &libN2);
  myFunReturn = s21_sprintf(myFun, format, &myN1, L"700\v909291lu", &myN2);

  ck_assert_int_eq(libN1, myN1);
  ck_assert_int_eq(libN2, myN2);
  ck_assert_int_eq(libFunReturn, myFunReturn);
}
END_TEST

START_TEST(test_551) {
  int libFunReturn;
  int myFunReturn;
  char libFun[BUFF_SIZE];
  char myFun[BUFF_SIZE];
  int libN1 = -2;
  int libN2 = -2;
  int myN1 = -2;
  int myN2 = -2;
  memset(libFun, '1', BUFF_SIZE);
  memset(myFun, '1', BUFF_SIZE);

  char *format = "nf%nk%fvjdas%n;";

  libFunReturn = sprintf(libFun, format, &libN1, 1222.375, &libN2);
  myFunReturn = s21_sprintf(myFun, format, &myN1, 1222.375, &myN2);

  ck_assert_int_eq(libN1, myN1);
  ck_assert_int_eq(libN2, myN2);
  ck_assert_int_eq(libFunReturn, myFunReturn);
}
END_TEST

START_TEST(test_552) {
  int libFunReturn;
  int myFunReturn;
  char libFun[BUFF_SIZE];
  char myFun[BUFF_SIZE];
  int libN1 = -2;
  int libN2 = -2;
  int myN1 = -2;
  int myN2 = -2;
  memset(libFun, '1', BUFF_SIZE);
  memset(myFun, '1', BUFF_SIZE);

  char *format = "nf%nk%17pvjdas%n;";

  libFunReturn = sprintf(libFun, format, &libN1, "1222.375", &libN2);
  myFunReturn = s21_sprintf(myFun, format, &myN1, "1222.375", &myN2);

  ck_assert_int_eq(libN1, myN1);
  ck_assert_int_eq(libN2, myN2);
  ck_assert_int_eq(libFunReturn, myFunReturn);
}
END_TEST

static TCase *decimal_tests() {
  TCase *d_t = tcase_create("Decimal tests");

  tcase_add_test(d_t, test_0);
  tcase_add_test(d_t, test_1);
  tcase_add_test(d_t, test_2);
  tcase_add_test(d_t, test_3);
  tcase_add_test(d_t, test_4);
  tcase_add_test(d_t, test_5);
  tcase_add_test(d_t, test_6);
  tcase_add_test(d_t, test_7);
  tcase_add_test(d_t, test_8);
  tcase_add_test(d_t, test_9);
  tcase_add_test(d_t, test_10);
  tcase_add_test(d_t, test_11);
  tcase_add_test(d_t, test_12);
  tcase_add_test(d_t, test_13);
  tcase_add_test(d_t, test_14);
  tcase_add_test(d_t, test_15);
  tcase_add_test(d_t, test_16);
  tcase_add_test(d_t, test_17);
  tcase_add_test(d_t, test_18);
  tcase_add_test(d_t, test_19);
  tcase_add_test(d_t, test_20);
  tcase_add_test(d_t, test_21);
  tcase_add_test(d_t, test_22);
  tcase_add_test(d_t, test_23);
  tcase_add_test(d_t, test_24);
  tcase_add_test(d_t, test_25);
  tcase_add_test(d_t, test_26);
  tcase_add_test(d_t, test_27);
  tcase_add_test(d_t, test_28);
  tcase_add_test(d_t, test_29);
  tcase_add_test(d_t, test_30);
  tcase_add_test(d_t, test_31);
  tcase_add_test(d_t, test_32);
  tcase_add_test(d_t, test_33);
  tcase_add_test(d_t, test_34);
  tcase_add_test(d_t, test_35);
  tcase_add_test(d_t, test_36);
  tcase_add_test(d_t, test_37);
  tcase_add_test(d_t, test_38);
  tcase_add_test(d_t, test_39);
  tcase_add_test(d_t, test_40);
  tcase_add_test(d_t, test_41);
  tcase_add_test(d_t, test_42);
  tcase_add_test(d_t, test_43);
  tcase_add_test(d_t, test_44);
  tcase_add_test(d_t, test_45);
  tcase_add_test(d_t, test_46);
  tcase_add_test(d_t, test_47);
  tcase_add_test(d_t, test_48);
  tcase_add_test(d_t, test_49);
  tcase_add_test(d_t, test_50);
  tcase_add_test(d_t, test_51);
  tcase_add_test(d_t, test_52);
  tcase_add_test(d_t, test_53);
  tcase_add_test(d_t, test_54);
  tcase_add_test(d_t, test_55);
  tcase_add_test(d_t, test_56);
  tcase_add_test(d_t, test_57);
  tcase_add_test(d_t, test_58);
  tcase_add_test(d_t, test_59);

  return d_t;
}

static TCase *unsigned_tests() {
  TCase *u_t = tcase_create("Unsigned tests");

  tcase_add_test(u_t, test_60);
  tcase_add_test(u_t, test_61);
  tcase_add_test(u_t, test_62);
  tcase_add_test(u_t, test_63);
  tcase_add_test(u_t, test_64);
  tcase_add_test(u_t, test_65);
  tcase_add_test(u_t, test_66);
  tcase_add_test(u_t, test_67);
  tcase_add_test(u_t, test_68);
  tcase_add_test(u_t, test_69);
  tcase_add_test(u_t, test_70);
  tcase_add_test(u_t, test_71);
  tcase_add_test(u_t, test_72);
  tcase_add_test(u_t, test_73);
  tcase_add_test(u_t, test_74);
  tcase_add_test(u_t, test_75);
  tcase_add_test(u_t, test_76);
  tcase_add_test(u_t, test_77);
  tcase_add_test(u_t, test_78);
  tcase_add_test(u_t, test_79);
  tcase_add_test(u_t, test_80);
  tcase_add_test(u_t, test_81);
  tcase_add_test(u_t, test_82);
  tcase_add_test(u_t, test_83);
  tcase_add_test(u_t, test_84);
  tcase_add_test(u_t, test_85);
  tcase_add_test(u_t, test_86);
  tcase_add_test(u_t, test_87);
  tcase_add_test(u_t, test_88);
  tcase_add_test(u_t, test_89);
  tcase_add_test(u_t, test_90);
  tcase_add_test(u_t, test_91);
  tcase_add_test(u_t, test_92);
  tcase_add_test(u_t, test_93);
  tcase_add_test(u_t, test_94);
  tcase_add_test(u_t, test_95);
  tcase_add_test(u_t, test_96);
  tcase_add_test(u_t, test_97);
  tcase_add_test(u_t, test_98);
  tcase_add_test(u_t, test_99);
  tcase_add_test(u_t, test_100);
  tcase_add_test(u_t, test_101);
  tcase_add_test(u_t, test_102);
  tcase_add_test(u_t, test_103);
  tcase_add_test(u_t, test_104);
  tcase_add_test(u_t, test_105);
  tcase_add_test(u_t, test_106);
  tcase_add_test(u_t, test_107);
  tcase_add_test(u_t, test_108);
  tcase_add_test(u_t, test_109);
  tcase_add_test(u_t, test_110);
  tcase_add_test(u_t, test_111);
  tcase_add_test(u_t, test_112);
  tcase_add_test(u_t, test_113);
  tcase_add_test(u_t, test_114);
  tcase_add_test(u_t, test_115);
  tcase_add_test(u_t, test_116);
  tcase_add_test(u_t, test_117);
  tcase_add_test(u_t, test_118);
  tcase_add_test(u_t, test_119);

  return u_t;
}

static TCase *string_tests() {
  TCase *s_t = tcase_create("String tests");

  tcase_add_test(s_t, test_120);
  tcase_add_test(s_t, test_121);
  tcase_add_test(s_t, test_122);
  tcase_add_test(s_t, test_123);
  tcase_add_test(s_t, test_124);
  tcase_add_test(s_t, test_125);
  tcase_add_test(s_t, test_126);
  tcase_add_test(s_t, test_127);
  tcase_add_test(s_t, test_128);
  tcase_add_test(s_t, test_129);
  tcase_add_test(s_t, test_130);
  tcase_add_test(s_t, test_131);
  tcase_add_test(s_t, test_132);
  tcase_add_test(s_t, test_133);
  tcase_add_test(s_t, test_134);
  tcase_add_test(s_t, test_135);
  tcase_add_test(s_t, test_136);
  tcase_add_test(s_t, test_137);
  tcase_add_test(s_t, test_138);
  tcase_add_test(s_t, test_139);

  return s_t;
}

static TCase *char_tests() {
  TCase *c_t = tcase_create("Char tests");

  tcase_add_test(c_t, test_140);
  tcase_add_test(c_t, test_141);
  tcase_add_test(c_t, test_142);
  tcase_add_test(c_t, test_143);
  tcase_add_test(c_t, test_144);
  tcase_add_test(c_t, test_145);
  tcase_add_test(c_t, test_146);
  tcase_add_test(c_t, test_147);
  tcase_add_test(c_t, test_148);
  tcase_add_test(c_t, test_149);

  return c_t;
}

static TCase *double_tests() {
  TCase *d_t = tcase_create("Double tests");

  tcase_add_test(d_t, test_150);
  tcase_add_test(d_t, test_151);
  tcase_add_test(d_t, test_152);
  tcase_add_test(d_t, test_153);
  tcase_add_test(d_t, test_154);
  tcase_add_test(d_t, test_155);
  tcase_add_test(d_t, test_156);
  tcase_add_test(d_t, test_157);
  tcase_add_test(d_t, test_158);
  tcase_add_test(d_t, test_159);
  tcase_add_test(d_t, test_160);
  tcase_add_test(d_t, test_161);
  tcase_add_test(d_t, test_162);
  tcase_add_test(d_t, test_163);
  tcase_add_test(d_t, test_164);
  tcase_add_test(d_t, test_165);
  tcase_add_test(d_t, test_166);
  tcase_add_test(d_t, test_167);
  tcase_add_test(d_t, test_168);
  tcase_add_test(d_t, test_169);
  tcase_add_test(d_t, test_170);
  tcase_add_test(d_t, test_171);
  tcase_add_test(d_t, test_172);
  tcase_add_test(d_t, test_173);
  tcase_add_test(d_t, test_174);
  tcase_add_test(d_t, test_175);
  tcase_add_test(d_t, test_176);
  tcase_add_test(d_t, test_177);
  tcase_add_test(d_t, test_178);
  tcase_add_test(d_t, test_179);
  tcase_add_test(d_t, test_180);
  tcase_add_test(d_t, test_181);
  tcase_add_test(d_t, test_182);
  tcase_add_test(d_t, test_183);
  tcase_add_test(d_t, test_184);
  tcase_add_test(d_t, test_185);
  tcase_add_test(d_t, test_186);
  tcase_add_test(d_t, test_187);
  tcase_add_test(d_t, test_188);
  tcase_add_test(d_t, test_189);
  tcase_add_test(d_t, test_190);
  tcase_add_test(d_t, test_191);
  tcase_add_test(d_t, test_192);
  tcase_add_test(d_t, test_193);
  tcase_add_test(d_t, test_194);
  tcase_add_test(d_t, test_195);
  tcase_add_test(d_t, test_196);
  tcase_add_test(d_t, test_197);
  tcase_add_test(d_t, test_198);
  tcase_add_test(d_t, test_199);
  tcase_add_test(d_t, test_200);
  tcase_add_test(d_t, test_201);
  tcase_add_test(d_t, test_202);
  tcase_add_test(d_t, test_203);
  tcase_add_test(d_t, test_204);
  tcase_add_test(d_t, test_205);
  tcase_add_test(d_t, test_206);
  tcase_add_test(d_t, test_207);
  tcase_add_test(d_t, test_208);
  tcase_add_test(d_t, test_209);
  tcase_add_test(d_t, test_210);
  tcase_add_test(d_t, test_211);
  tcase_add_test(d_t, test_212);
  tcase_add_test(d_t, test_213);
  tcase_add_test(d_t, test_214);
  tcase_add_test(d_t, test_215);
  tcase_add_test(d_t, test_216);
  tcase_add_test(d_t, test_217);
  tcase_add_test(d_t, test_218);
  tcase_add_test(d_t, test_219);
  tcase_add_test(d_t, test_220);
  tcase_add_test(d_t, test_221);
  tcase_add_test(d_t, test_222);
  tcase_add_test(d_t, test_223);
  tcase_add_test(d_t, test_224);
  tcase_add_test(d_t, test_225);
  tcase_add_test(d_t, test_226);
  tcase_add_test(d_t, test_227);
  tcase_add_test(d_t, test_228);
  tcase_add_test(d_t, test_229);
  tcase_add_test(d_t, test_230);
  tcase_add_test(d_t, test_231);
  tcase_add_test(d_t, test_232);
  tcase_add_test(d_t, test_233);
  tcase_add_test(d_t, test_234);
  tcase_add_test(d_t, test_235);
  tcase_add_test(d_t, test_236);
  tcase_add_test(d_t, test_237);
  tcase_add_test(d_t, test_238);
  tcase_add_test(d_t, test_239);
  tcase_add_test(d_t, test_240);
  tcase_add_test(d_t, test_241);
  tcase_add_test(d_t, test_242);
  tcase_add_test(d_t, test_243);
  tcase_add_test(d_t, test_244);
  tcase_add_test(d_t, test_245);
  tcase_add_test(d_t, test_246);
  tcase_add_test(d_t, test_247);
  tcase_add_test(d_t, test_248);
  tcase_add_test(d_t, test_249);
  tcase_add_test(d_t, test_250);
  tcase_add_test(d_t, test_251);
  tcase_add_test(d_t, test_252);
  tcase_add_test(d_t, test_253);
  tcase_add_test(d_t, test_254);
  tcase_add_test(d_t, test_255);
  tcase_add_test(d_t, test_256);
  tcase_add_test(d_t, test_257);
  tcase_add_test(d_t, test_258);
  tcase_add_test(d_t, test_259);
  tcase_add_test(d_t, test_260);
  tcase_add_test(d_t, test_261);
  tcase_add_test(d_t, test_262);
  tcase_add_test(d_t, test_263);
  tcase_add_test(d_t, test_264);
  tcase_add_test(d_t, test_265);
  tcase_add_test(d_t, test_266);
  tcase_add_test(d_t, test_267);
  tcase_add_test(d_t, test_268);
  tcase_add_test(d_t, test_269);
  tcase_add_test(d_t, test_270);
  tcase_add_test(d_t, test_271);
  tcase_add_test(d_t, test_272);
  tcase_add_test(d_t, test_273);
  tcase_add_test(d_t, test_274);
  tcase_add_test(d_t, test_275);
  tcase_add_test(d_t, test_276);
  tcase_add_test(d_t, test_277);
  tcase_add_test(d_t, test_278);
  tcase_add_test(d_t, test_279);
  tcase_add_test(d_t, test_280);
  tcase_add_test(d_t, test_281);
  tcase_add_test(d_t, test_282);
  tcase_add_test(d_t, test_283);
  tcase_add_test(d_t, test_284);
  tcase_add_test(d_t, test_285);
  tcase_add_test(d_t, test_286);
  tcase_add_test(d_t, test_287);
  tcase_add_test(d_t, test_288);
  tcase_add_test(d_t, test_289);
  tcase_add_test(d_t, test_290);
  tcase_add_test(d_t, test_291);
  tcase_add_test(d_t, test_292);
  tcase_add_test(d_t, test_293);
  tcase_add_test(d_t, test_294);
  tcase_add_test(d_t, test_295);
  tcase_add_test(d_t, test_296);
  tcase_add_test(d_t, test_297);
  tcase_add_test(d_t, test_298);
  tcase_add_test(d_t, test_299);

  return d_t;
}

static TCase *exp_double_tests() {
  TCase *e_d_t = tcase_create("Exponencial double tests");

  tcase_add_test(e_d_t, test_300);
  tcase_add_test(e_d_t, test_301);
  tcase_add_test(e_d_t, test_302);
  tcase_add_test(e_d_t, test_303);
  tcase_add_test(e_d_t, test_304);
  tcase_add_test(e_d_t, test_305);
  tcase_add_test(e_d_t, test_306);
  tcase_add_test(e_d_t, test_307);
  tcase_add_test(e_d_t, test_308);
  tcase_add_test(e_d_t, test_309);
  tcase_add_test(e_d_t, test_310);
  tcase_add_test(e_d_t, test_311);
  tcase_add_test(e_d_t, test_312);
  tcase_add_test(e_d_t, test_313);
  tcase_add_test(e_d_t, test_314);
  tcase_add_test(e_d_t, test_315);
  tcase_add_test(e_d_t, test_316);
  tcase_add_test(e_d_t, test_317);
  tcase_add_test(e_d_t, test_318);
  tcase_add_test(e_d_t, test_319);
  tcase_add_test(e_d_t, test_320);
  tcase_add_test(e_d_t, test_321);
  tcase_add_test(e_d_t, test_322);
  tcase_add_test(e_d_t, test_323);
  tcase_add_test(e_d_t, test_324);
  tcase_add_test(e_d_t, test_325);
  tcase_add_test(e_d_t, test_326);
  tcase_add_test(e_d_t, test_327);
  tcase_add_test(e_d_t, test_328);
  tcase_add_test(e_d_t, test_329);
  tcase_add_test(e_d_t, test_330);
  tcase_add_test(e_d_t, test_331);
  tcase_add_test(e_d_t, test_332);
  tcase_add_test(e_d_t, test_333);
  tcase_add_test(e_d_t, test_334);
  tcase_add_test(e_d_t, test_335);
  tcase_add_test(e_d_t, test_336);
  tcase_add_test(e_d_t, test_337);
  tcase_add_test(e_d_t, test_338);
  tcase_add_test(e_d_t, test_339);
  tcase_add_test(e_d_t, test_340);
  tcase_add_test(e_d_t, test_341);
  tcase_add_test(e_d_t, test_342);
  tcase_add_test(e_d_t, test_343);
  tcase_add_test(e_d_t, test_344);
  tcase_add_test(e_d_t, test_345);
  tcase_add_test(e_d_t, test_346);
  tcase_add_test(e_d_t, test_347);
  tcase_add_test(e_d_t, test_348);
  tcase_add_test(e_d_t, test_349);
  tcase_add_test(e_d_t, test_350);
  tcase_add_test(e_d_t, test_351);
  tcase_add_test(e_d_t, test_352);
  tcase_add_test(e_d_t, test_353);
  tcase_add_test(e_d_t, test_354);
  tcase_add_test(e_d_t, test_355);
  tcase_add_test(e_d_t, test_356);
  tcase_add_test(e_d_t, test_357);
  tcase_add_test(e_d_t, test_358);
  tcase_add_test(e_d_t, test_359);
  tcase_add_test(e_d_t, test_360);
  tcase_add_test(e_d_t, test_361);
  tcase_add_test(e_d_t, test_362);
  tcase_add_test(e_d_t, test_363);
  tcase_add_test(e_d_t, test_364);
  tcase_add_test(e_d_t, test_365);
  tcase_add_test(e_d_t, test_366);
  tcase_add_test(e_d_t, test_367);
  tcase_add_test(e_d_t, test_368);
  tcase_add_test(e_d_t, test_369);
  tcase_add_test(e_d_t, test_370);
  tcase_add_test(e_d_t, test_371);
  tcase_add_test(e_d_t, test_372);
  tcase_add_test(e_d_t, test_373);
  tcase_add_test(e_d_t, test_374);
  tcase_add_test(e_d_t, test_375);
  tcase_add_test(e_d_t, test_376);
  tcase_add_test(e_d_t, test_377);
  tcase_add_test(e_d_t, test_378);
  tcase_add_test(e_d_t, test_379);
  tcase_add_test(e_d_t, test_380);
  tcase_add_test(e_d_t, test_381);
  tcase_add_test(e_d_t, test_382);
  tcase_add_test(e_d_t, test_383);
  tcase_add_test(e_d_t, test_384);
  tcase_add_test(e_d_t, test_385);
  tcase_add_test(e_d_t, test_386);
  tcase_add_test(e_d_t, test_387);
  tcase_add_test(e_d_t, test_388);
  tcase_add_test(e_d_t, test_389);
  tcase_add_test(e_d_t, test_390);
  tcase_add_test(e_d_t, test_391);
  tcase_add_test(e_d_t, test_392);
  tcase_add_test(e_d_t, test_393);
  tcase_add_test(e_d_t, test_394);
  tcase_add_test(e_d_t, test_395);
  tcase_add_test(e_d_t, test_396);
  tcase_add_test(e_d_t, test_397);
  tcase_add_test(e_d_t, test_398);
  tcase_add_test(e_d_t, test_399);

  return e_d_t;
}

static TCase *g_double_tests() {
  TCase *g_d_t = tcase_create("G double tests");

  tcase_add_test(g_d_t, test_400);
  tcase_add_test(g_d_t, test_401);
  tcase_add_test(g_d_t, test_402);
  tcase_add_test(g_d_t, test_403);
  tcase_add_test(g_d_t, test_404);
  tcase_add_test(g_d_t, test_405);
  tcase_add_test(g_d_t, test_406);
  tcase_add_test(g_d_t, test_407);
  tcase_add_test(g_d_t, test_408);
  tcase_add_test(g_d_t, test_409);
  tcase_add_test(g_d_t, test_410);
  tcase_add_test(g_d_t, test_411);
  tcase_add_test(g_d_t, test_412);
  tcase_add_test(g_d_t, test_413);
  tcase_add_test(g_d_t, test_414);
  tcase_add_test(g_d_t, test_415);
  tcase_add_test(g_d_t, test_416);
  tcase_add_test(g_d_t, test_417);
  tcase_add_test(g_d_t, test_418);
  tcase_add_test(g_d_t, test_419);
  tcase_add_test(g_d_t, test_420);
  tcase_add_test(g_d_t, test_421);
  tcase_add_test(g_d_t, test_422);
  tcase_add_test(g_d_t, test_423);
  tcase_add_test(g_d_t, test_424);
  tcase_add_test(g_d_t, test_425);
  tcase_add_test(g_d_t, test_426);
  tcase_add_test(g_d_t, test_427);
  tcase_add_test(g_d_t, test_428);
  tcase_add_test(g_d_t, test_429);
  tcase_add_test(g_d_t, test_430);
  tcase_add_test(g_d_t, test_431);
  tcase_add_test(g_d_t, test_432);
  tcase_add_test(g_d_t, test_433);
  tcase_add_test(g_d_t, test_434);
  tcase_add_test(g_d_t, test_435);
  tcase_add_test(g_d_t, test_436);
  tcase_add_test(g_d_t, test_437);
  tcase_add_test(g_d_t, test_438);
  tcase_add_test(g_d_t, test_439);
  tcase_add_test(g_d_t, test_440);
  tcase_add_test(g_d_t, test_441);
  tcase_add_test(g_d_t, test_442);
  tcase_add_test(g_d_t, test_443);
  tcase_add_test(g_d_t, test_444);
  tcase_add_test(g_d_t, test_445);
  tcase_add_test(g_d_t, test_446);
  tcase_add_test(g_d_t, test_447);
  tcase_add_test(g_d_t, test_448);
  tcase_add_test(g_d_t, test_449);
  tcase_add_test(g_d_t, test_450);
  tcase_add_test(g_d_t, test_451);
  tcase_add_test(g_d_t, test_452);
  tcase_add_test(g_d_t, test_453);
  tcase_add_test(g_d_t, test_454);
  tcase_add_test(g_d_t, test_455);
  tcase_add_test(g_d_t, test_456);
  tcase_add_test(g_d_t, test_457);
  tcase_add_test(g_d_t, test_458);
  tcase_add_test(g_d_t, test_459);
  tcase_add_test(g_d_t, test_460);
  tcase_add_test(g_d_t, test_461);
  tcase_add_test(g_d_t, test_462);
  tcase_add_test(g_d_t, test_463);
  tcase_add_test(g_d_t, test_464);
  tcase_add_test(g_d_t, test_465);
  tcase_add_test(g_d_t, test_466);
  tcase_add_test(g_d_t, test_467);
  tcase_add_test(g_d_t, test_468);
  tcase_add_test(g_d_t, test_469);
  tcase_add_test(g_d_t, test_470);
  tcase_add_test(g_d_t, test_471);
  tcase_add_test(g_d_t, test_472);
  tcase_add_test(g_d_t, test_473);
  tcase_add_test(g_d_t, test_474);
  tcase_add_test(g_d_t, test_475);
  tcase_add_test(g_d_t, test_476);
  tcase_add_test(g_d_t, test_477);
  tcase_add_test(g_d_t, test_478);
  tcase_add_test(g_d_t, test_479);
  tcase_add_test(g_d_t, test_480);
  tcase_add_test(g_d_t, test_481);
  tcase_add_test(g_d_t, test_482);
  tcase_add_test(g_d_t, test_483);
  tcase_add_test(g_d_t, test_484);
  tcase_add_test(g_d_t, test_485);
  tcase_add_test(g_d_t, test_486);
  tcase_add_test(g_d_t, test_487);
  tcase_add_test(g_d_t, test_488);
  tcase_add_test(g_d_t, test_489);
  tcase_add_test(g_d_t, test_490);
  tcase_add_test(g_d_t, test_491);
  tcase_add_test(g_d_t, test_492);
  tcase_add_test(g_d_t, test_493);
  tcase_add_test(g_d_t, test_494);
  tcase_add_test(g_d_t, test_495);
  tcase_add_test(g_d_t, test_496);
  tcase_add_test(g_d_t, test_497);
  tcase_add_test(g_d_t, test_498);
  tcase_add_test(g_d_t, test_499);

  return g_d_t;
}

static TCase *i_decimal_tests() {
  TCase *i_d_t = tcase_create("I decimal tests");

  tcase_add_test(i_d_t, test_500);
  tcase_add_test(i_d_t, test_501);
  tcase_add_test(i_d_t, test_502);
  tcase_add_test(i_d_t, test_503);
  tcase_add_test(i_d_t, test_504);
  tcase_add_test(i_d_t, test_505);
  tcase_add_test(i_d_t, test_506);
  tcase_add_test(i_d_t, test_507);
  tcase_add_test(i_d_t, test_508);
  tcase_add_test(i_d_t, test_509);

  return i_d_t;
}

static TCase *octal_decimal_tests() {
  TCase *o_d_t = tcase_create("Octal decimal tests");

  tcase_add_test(o_d_t, test_510);
  tcase_add_test(o_d_t, test_511);
  tcase_add_test(o_d_t, test_512);
  tcase_add_test(o_d_t, test_513);
  tcase_add_test(o_d_t, test_514);
  tcase_add_test(o_d_t, test_515);
  tcase_add_test(o_d_t, test_516);
  tcase_add_test(o_d_t, test_517);
  tcase_add_test(o_d_t, test_518);
  tcase_add_test(o_d_t, test_519);

  return o_d_t;
}

static TCase *hex_decimal_tests() {
  TCase *x_d_t = tcase_create("Hex decimal tests");

  tcase_add_test(x_d_t, test_520);
  tcase_add_test(x_d_t, test_521);
  tcase_add_test(x_d_t, test_522);
  tcase_add_test(x_d_t, test_523);
  tcase_add_test(x_d_t, test_524);
  tcase_add_test(x_d_t, test_525);
  tcase_add_test(x_d_t, test_526);
  tcase_add_test(x_d_t, test_527);
  tcase_add_test(x_d_t, test_528);
  tcase_add_test(x_d_t, test_529);

  return x_d_t;
}

static TCase *pointer_tests() {
  TCase *p_t = tcase_create("Pointer tests");

  tcase_add_test(p_t, test_530);
  tcase_add_test(p_t, test_531);
  tcase_add_test(p_t, test_532);
  tcase_add_test(p_t, test_533);
  tcase_add_test(p_t, test_534);
  tcase_add_test(p_t, test_535);
  tcase_add_test(p_t, test_536);
  tcase_add_test(p_t, test_537);
  tcase_add_test(p_t, test_538);
  tcase_add_test(p_t, test_539);

  return p_t;
}

static TCase *counter_value_tests() {
  TCase *c_v_t = tcase_create("N spec tests");

  tcase_add_test(c_v_t, test_540);
  tcase_add_test(c_v_t, test_541);
  tcase_add_test(c_v_t, test_542);
  tcase_add_test(c_v_t, test_543);
  tcase_add_test(c_v_t, test_544);
  tcase_add_test(c_v_t, test_545);
  tcase_add_test(c_v_t, test_546);
  tcase_add_test(c_v_t, test_547);
  tcase_add_test(c_v_t, test_548);
  tcase_add_test(c_v_t, test_549);
  tcase_add_test(c_v_t, test_550);
  tcase_add_test(c_v_t, test_551);
  tcase_add_test(c_v_t, test_552);

  return c_v_t;
}

Suite *sprintf_bonus_suite() {
  Suite *s = suite_create("SPRINTF BONUS PART");
  suite_add_tcase(s, decimal_tests());
  suite_add_tcase(s, unsigned_tests());
  suite_add_tcase(s, string_tests());
  suite_add_tcase(s, char_tests());
  suite_add_tcase(s, double_tests());
  suite_add_tcase(s, exp_double_tests());
  suite_add_tcase(s, g_double_tests());
  suite_add_tcase(s, i_decimal_tests());
  suite_add_tcase(s, octal_decimal_tests());
  suite_add_tcase(s, hex_decimal_tests());
  suite_add_tcase(s, pointer_tests());
  suite_add_tcase(s, counter_value_tests());

  return s;
}