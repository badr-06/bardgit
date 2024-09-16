#include <check.h>
#include <limits.h>
#include <stdio.h>

#include "../s21_string.h"

#define BUFF_SIZE 128

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

// ==============================JUST TEXT===============================
// Without specifiers
COMPARE_DEST_STRINGS_AND_RETURNS(test_0, "abcdef")
COMPARE_DEST_STRINGS_AND_RETURNS(test_1, "nfkvjdas;")
COMPARE_DEST_STRINGS_AND_RETURNS(test_2, "%%n9-3fn4")
COMPARE_DEST_STRINGS_AND_RETURNS(test_3, "qwe")
COMPARE_DEST_STRINGS_AND_RETURNS(test_4, "-j?e12l%%")
COMPARE_DEST_STRINGS_AND_RETURNS(test_5, "-j=xz_{k}")
COMPARE_DEST_STRINGS_AND_RETURNS(test_6, "mod%%q.wfq-[]")
COMPARE_DEST_STRINGS_AND_RETURNS(test_7, "oa%%dsp;d")
COMPARE_DEST_STRINGS_AND_RETURNS(test_8, "z~xc")
COMPARE_DEST_STRINGS_AND_RETURNS(test_9, ";[]czx;[]zx];[]")

// Escapes
COMPARE_DEST_STRINGS_AND_RETURNS(test_10, "%%\\abcdef")
COMPARE_DEST_STRINGS_AND_RETURNS(test_11, "nfkv\055jdas;")
COMPARE_DEST_STRINGS_AND_RETURNS(test_12, "n9-3\nfn4")
COMPARE_DEST_STRINGS_AND_RETURNS(test_13, "\tqwe%%")
COMPARE_DEST_STRINGS_AND_RETURNS(test_14, "-j?e12l\"")
COMPARE_DEST_STRINGS_AND_RETURNS(test_15, "\n-j=xz_{k}\t%%")
COMPARE_DEST_STRINGS_AND_RETURNS(test_16, "%%modq\\.wfq-[]\033")
COMPARE_DEST_STRINGS_AND_RETURNS(test_17, "oa\vdsp;d\t")
COMPARE_DEST_STRINGS_AND_RETURNS(test_18, "z~\t\n\'\"\?xc")
COMPARE_DEST_STRINGS_AND_RETURNS(test_19, ";[]czx\xac;[]zx];[]%%")

// ================================INT===================================
// Simple int
COMPARE_DEST_STRINGS_AND_RETURNS(test_20, "%dabcdef", 15)
COMPARE_DEST_STRINGS_AND_RETURNS(test_21, "nfk%dvjdas;", 1222375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_22, "n9-%d3fn4", -3333)
COMPARE_DEST_STRINGS_AND_RETURNS(test_23, "qwe%d, ", INT_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_24, "%d-j?e12l", INT_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_25, "-j=%dxz_{k}", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_26, "modq%d.wfq-[]", -0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_27, "oadsp;d%d", -1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_28, "z~x%dc", 1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_29, ";[]czx;[]zx];[]%d", 700909291)

// Int with precision
COMPARE_DEST_STRINGS_AND_RETURNS(test_30, "%.7dabcdef", 15)
COMPARE_DEST_STRINGS_AND_RETURNS(test_31, "nfk%.3dvjdas;", 1222375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_32, "n9-%.4d3fn4", -3333)
COMPARE_DEST_STRINGS_AND_RETURNS(test_33, "qwe%.16d, ", INT_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_34, "%.4d-j?e12l", INT_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_35, "-j=%.1dxz_{k}", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_36, "modq%.2d.wfq-[]", -0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_37, "oadsp;d%.0d", -1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_38, "z~x%.21dc", 1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_39, ";[]czx;[]zx];[]%.7d", 700909291)

// Int with min length
COMPARE_DEST_STRINGS_AND_RETURNS(test_40, "%7dabcdef", 15)
COMPARE_DEST_STRINGS_AND_RETURNS(test_41, "nfk%3dvjdas;", 1222375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_42, "n9-%4d3fn4", -3333)
COMPARE_DEST_STRINGS_AND_RETURNS(test_43, "qwe%16d, ", INT_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_44, "%4d-j?e12l", INT_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_45, "-j=%1dxz_{k}", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_46, "modq%2d.wfq-[]", -0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_47, "oadsp;d%6d", -134)
COMPARE_DEST_STRINGS_AND_RETURNS(test_48, "z~x%21dc", 1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_49, ";[]czx;[]zx];[]%7d", 700909291)

// Int with min length left aligment
COMPARE_DEST_STRINGS_AND_RETURNS(test_50, "%-7dabcdef", 15)
COMPARE_DEST_STRINGS_AND_RETURNS(test_51, "nfk%-3dvjdas;", 1222375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_52, "n9-%-4d3fn4", -3333)
COMPARE_DEST_STRINGS_AND_RETURNS(test_53, "qwe%-16d, ", INT_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_54, "%-4d-j?e12l", INT_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_55, "-j=%-1dxz_{k}", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_56, "modq%-2d.wfq-[]", -0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_57, "oadsp;d%-6d", -134)
COMPARE_DEST_STRINGS_AND_RETURNS(test_58, "z~x%-21dc", 1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_59, ";[]czx;[]zx];[]%-7d", 700909291)

// Int with plus sign display
COMPARE_DEST_STRINGS_AND_RETURNS(test_60, "%+dabcdef", 15)
COMPARE_DEST_STRINGS_AND_RETURNS(test_61, "nfk%+dvjdas;", 1222375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_62, "n9-%+d3fn4", -3333)
COMPARE_DEST_STRINGS_AND_RETURNS(test_63, "qwe%+6d, ", INT_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_64, "%+d-j?e12l", INT_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_65, "-j=%+dxz_{k}", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_66, "modq%+d.wfq-[]", -0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_67, "oadsp;d%+d", -134)
COMPARE_DEST_STRINGS_AND_RETURNS(test_68, "z~x%+dc", 1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_69, ";[]czx;[]zx];[]%+d", 700909291)

// Int with space instead of plus
COMPARE_DEST_STRINGS_AND_RETURNS(test_70, "% dabcdef", 15)
COMPARE_DEST_STRINGS_AND_RETURNS(test_71, "nfk% dvjdas;", 1222375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_72, "n9-% d3fn4", -3333)
COMPARE_DEST_STRINGS_AND_RETURNS(test_73, "qwe% 6d, ", INT_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_74, "% d-j?e12l", INT_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_75, "-j=% dxz_{k}", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_76, "modq% d.wfq-[]", -0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_77, "oadsp;d% d", -134)
COMPARE_DEST_STRINGS_AND_RETURNS(test_78, "z~x% dc", 1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_79, ";[]czx;[]zx];[]% d", 700909291)

// Int with all of advanced specs
COMPARE_DEST_STRINGS_AND_RETURNS(test_80, "%-+3.7dabc%ddef", 15, 4444)
COMPARE_DEST_STRINGS_AND_RETURNS(test_81, "nfk%- 5.3dvjd%-3das;", 1222375,
                                 -19271)
COMPARE_DEST_STRINGS_AND_RETURNS(test_82, "n9-%+-4.4d3f%6dn4", -3333, 82)
COMPARE_DEST_STRINGS_AND_RETURNS(test_83, "qwe%-+3.16d, %+6.4d", INT_MAX, 47983)
COMPARE_DEST_STRINGS_AND_RETURNS(test_84, "% -8.4d-j?e12l", INT_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_85, "-j=%- 2.1dxz_{k}", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_86, "modq%+-1.2d.wfq% d-[]", -0, 9672)
COMPARE_DEST_STRINGS_AND_RETURNS(test_87, "oadsp;d%+-3.0d", -1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_88, "z~x%-+9.21dc", 1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_89, ";[]czx;[]zx];[]%11.7d", 700909291)

// ================================LONG INT===================================
// Simple long int
COMPARE_DEST_STRINGS_AND_RETURNS(test_90, "%ldabcdef", 15l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_91, "nfk%ldvjdas;", 7962471094)
COMPARE_DEST_STRINGS_AND_RETURNS(test_92, "n9-%ld3fn4", -3333l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_93, "qwe%ld, ", LONG_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_94, "%ld-j?e12l", LONG_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_95, "-j=%ldxz_{k}", 0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_96, "modq%ld.wfq-[]", -0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_97, "oadsp;d%ld", -1l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_98, "z~x%ldc", 1l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_99, ";[]czx;[]zx];[]%ld", 700909291l)

// Long int with precision
COMPARE_DEST_STRINGS_AND_RETURNS(test_100, "%.7ldabcdef", 15l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_101, "nfk%.3ldvjdas;", 7962471094)
COMPARE_DEST_STRINGS_AND_RETURNS(test_102, "n9-%.4ld3fn4", -3333l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_103, "qwe%.16ld, ", LONG_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_104, "%.4ld-j?e12l", LONG_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_105, "-j=%.1ldxz_{k}", 0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_106, "modq%.2ld.wfq-[]", -0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_107, "oadsp;d%.0ld", -1l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_108, "z~x%.21ldc", 1l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_109, ";[]czx;[]zx];[]%.7ld", 700909291l)

// Long int with min length
COMPARE_DEST_STRINGS_AND_RETURNS(test_110, "%7ldabcdef", 15l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_111, "nfk%3ldvjdas;", 7962471094)
COMPARE_DEST_STRINGS_AND_RETURNS(test_112, "n9-%4ld3fn4", -3333l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_113, "qwe%16ld, ", LONG_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_114, "%4ld-j?e12l", LONG_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_115, "-j=%1ldxz_{k}", 0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_116, "modq%2ld.wfq-[]", -0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_117, "oadsp;d%6ld", -134l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_118, "z~x%21ldc", 1l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_119, ";[]czx;[]zx];[]%7ld", 700909291l)

// Long int with min length left aligment
COMPARE_DEST_STRINGS_AND_RETURNS(test_120, "%-7ldabcdef", 15l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_121, "nfk%-3ldvjdas;", 7962471094)
COMPARE_DEST_STRINGS_AND_RETURNS(test_122, "n9-%-4ld3fn4", -3333l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_123, "qwe%-16ld, ", LONG_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_124, "%-4ld-j?e12l", LONG_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_125, "-j=%-1ldxz_{k}", 0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_126, "modq%-2ld.wfq-[]", -0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_127, "oadsp;d%-6ld", -134l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_128, "z~x%-21ldc", 1l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_129, ";[]czx;[]zx];[]%-7ld", 700909291l)

// Long int with plus sign display
COMPARE_DEST_STRINGS_AND_RETURNS(test_130, "%+ldabcdef", 15l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_131, "nfk%+ldvjdas;", 7962471094)
COMPARE_DEST_STRINGS_AND_RETURNS(test_132, "n9-%+ld3fn4", -3333l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_133, "qwe%+6ld, ", LONG_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_134, "%+ld-j?e12l", LONG_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_135, "-j=%+ldxz_{k}", 0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_136, "modq%+ld.wfq-[]", -0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_137, "oadsp;d%+ld", -134l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_138, "z~x%+ldc", 1l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_139, ";[]czx;[]zx];[]%+ld", 700909291l)

// Long int with space instead of plus
COMPARE_DEST_STRINGS_AND_RETURNS(test_140, "% ldabcdef", 15l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_141, "nfk% ldvjdas;", 7962471094)
COMPARE_DEST_STRINGS_AND_RETURNS(test_142, "n9-% ld3fn4", -3333l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_143, "qwe% 6ld, ", LONG_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_144, "% ld-j?e12l", LONG_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_145, "-j=% ldxz_{k}", 0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_146, "modq% ld.wfq-[]", -0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_147, "oadsp;d% ld", -134l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_148, "z~x% ldc", 1l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_149, ";[]czx;[]zx];[]% ld", 700909291l)

// Long int with all of advanced specs
COMPARE_DEST_STRINGS_AND_RETURNS(test_150, "%-+3.7ldabc%lddef", 15l, 4444l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_151, "nfk%- 5.3ldvjd%-3ldas;", 7962471094,
                                 -19271l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_152, "n9-%+-4.4ld3f%6ldn4", -3333l, 82l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_153, "qwe%-+3.16ld, %+6.4ld", LONG_MAX,
                                 47983l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_154, "% -8.4ld-j?e12l", LONG_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_155, "-j=%- 2.1ldxz_{k}", 0l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_156, "modq%+-1.2ld.wfq% ld-[]", -0l,
                                 9672l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_157, "oadsp;d%+-3.0ld", -1l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_158, "z~x%-+9.21ldc", 1l)
COMPARE_DEST_STRINGS_AND_RETURNS(test_159, ";[]czx;[]zx];[]%11.7ld", 700909291l)

// ================================LONG LONG
// INT=================================== Simple long long int
COMPARE_DEST_STRINGS_AND_RETURNS(test_160, "%lldabcdef", 15ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_161, "nfk%lldvjdas;",
                                 7933333363323232320ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_162, "n9-%lld3fn4", -3333ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_163, "qwe%lld, ", LLONG_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_164, "%lld-j?e12l", LLONG_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_165, "-j=%lldxz_{k}", 0ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_166, "modq%lld.wfq-[]", -0ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_167, "oadsp;d%lld", -1ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_168, "z~x%lldc", 1ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_169, ";[]czx;[]zx];[]%lld", 700909291ll)

// Long long int with precision
COMPARE_DEST_STRINGS_AND_RETURNS(test_170, "%.7lldabcdef", 15ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_171, "nfk%.3lldvjdas;",
                                 7933333363323232320ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_172, "n9-%.4lld3fn4", -3333ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_173, "qwe%.16lld, ", LLONG_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_174, "%.4lld-j?e12l", LLONG_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_175, "-j=%.1lldxz_{k}", 0ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_176, "modq%.2lld.wfq-[]", -0ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_177, "oadsp;d%.0lld", -1ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_178, "z~x%.21lldc", 1ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_179, ";[]czx;[]zx];[]%.7lld", 700909291ll)

// Long long int with min length
COMPARE_DEST_STRINGS_AND_RETURNS(test_180, "%7lldabcdef", 15ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_181, "nfk%3lldvjdas;",
                                 7933333363323232320ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_182, "n9-%4lld3fn4", -3333ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_183, "qwe%16lld, ", LLONG_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_184, "%4lld-j?e12l", LLONG_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_185, "-j=%1lldxz_{k}", 0ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_186, "modq%2lld.wfq-[]", -0ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_187, "oadsp;d%6lld", -134ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_188, "z~x%21lldc", 1ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_189, ";[]czx;[]zx];[]%7lld", 700909291ll)

// Long long int with min length left aligment
COMPARE_DEST_STRINGS_AND_RETURNS(test_190, "%-7lldabcdef", 15ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_191, "nfk%-3lldvjdas;",
                                 7933333363323232320ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_192, "n9-%-4lld3fn4", -3333ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_193, "qwe%-16lld, ", LLONG_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_194, "%-4lld-j?e12l", LLONG_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_195, "-j=%-1lldxz_{k}", 0ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_196, "modq%-2lld.wfq-[]", -0ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_197, "oadsp;d%-6lld", -134ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_198, "z~x%-21lldc", 1ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_199, ";[]czx;[]zx];[]%-7lld", 700909291ll)

// Long long int with plus sign display
COMPARE_DEST_STRINGS_AND_RETURNS(test_200, "%+lldabcdef", 15ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_201, "nfk%+lldvjdas;",
                                 7933333363323232320ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_202, "n9-%+lld3fn4", -3333ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_203, "qwe%+6lld, ", LLONG_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_204, "%+lld-j?e12l", LLONG_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_205, "-j=%+lldxz_{k}", 0ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_206, "modq%+lld.wfq-[]", -0ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_207, "oadsp;d%+lld", -134ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_208, "z~x%+lldc", 1ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_209, ";[]czx;[]zx];[]%+lld", 700909291ll)

// Long long int with space instead of plus
COMPARE_DEST_STRINGS_AND_RETURNS(test_210, "% lldabcdef", 15ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_211, "nfk% lldvjdas;",
                                 7933333363323232320ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_212, "n9-% lld3fn4", -3333ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_213, "qwe% 6lld, ", LLONG_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_214, "% lld-j?e12l", LLONG_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_215, "-j=% lldxz_{k}", 0ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_216, "modq% lld.wfq-[]", -0ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_217, "oadsp;d% lld", -134ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_218, "z~x% lldc", 1ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_219, ";[]czx;[]zx];[]% lld", 700909291ll)

// Long long int with all of advanced specs
COMPARE_DEST_STRINGS_AND_RETURNS(test_220, "%-+3.7lldabc%llddef", 15ll, 4444ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_221, "nfk%- 5.3lldvjd%-3lldas;",
                                 7933333363323232320ll, -19271ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_222, "n9-%+-4.4lld3f%6lldn4", -3333ll,
                                 82ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_223, "qwe%-+3.16lld, %+6.4lld", LLONG_MAX,
                                 47983ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_224, "% -8.4lld-j?e12l", LLONG_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_225, "-j=%- 2.1lldxz_{k}", 0ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_226, "modq%+-1.2lld.wfq% lld-[]", -0ll,
                                 9672ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_227, "oadsp;d%+-3.0lld", -1ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_228, "z~x%-+9.21lldc", 1ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_229, ";[]czx;[]zx];[]%11.7lld",
                                 700909291ll)

// ================================SHORT INT===================================
// Simple short int
COMPARE_DEST_STRINGS_AND_RETURNS(test_230, "%hdabcdef", 15)
COMPARE_DEST_STRINGS_AND_RETURNS(test_231, "nfk%hdvjdas;", 12223)
COMPARE_DEST_STRINGS_AND_RETURNS(test_232, "n9-%hd3fn4", -3333)
COMPARE_DEST_STRINGS_AND_RETURNS(test_233, "qwe%hd, ", SHRT_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_234, "%hd-j?e12l", SHRT_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_235, "-j=%hdxz_{k}", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_236, "modq%hd.wfq-[]", -0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_237, "oadsp;d%hd", -1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_238, "z~x%hdc", 1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_239, ";[]czx;[]zx];[]%hd", 7009)

// Short int with precision
COMPARE_DEST_STRINGS_AND_RETURNS(test_240, "%.7hdabcdef", 15)
COMPARE_DEST_STRINGS_AND_RETURNS(test_241, "nfk%.3hdvjdas;", 12223)
COMPARE_DEST_STRINGS_AND_RETURNS(test_242, "n9-%.4hd3fn4", -3333)
COMPARE_DEST_STRINGS_AND_RETURNS(test_243, "qwe%.16hd, ", SHRT_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_244, "%.4hd-j?e12l", SHRT_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_245, "-j=%.1hdxz_{k}", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_246, "modq%.2hd.wfq-[]", -0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_247, "oadsp;d%.0hd", -1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_248, "z~x%.21hdc", 1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_249, ";[]czx;[]zx];[]%.7hd", 7009)

// Short int with min length
COMPARE_DEST_STRINGS_AND_RETURNS(test_250, "%7hdabcdef", 15)
COMPARE_DEST_STRINGS_AND_RETURNS(test_251, "nfk%3hdvjdas;", 12223)
COMPARE_DEST_STRINGS_AND_RETURNS(test_252, "n9-%4hd3fn4", -3333)
COMPARE_DEST_STRINGS_AND_RETURNS(test_253, "qwe%16hd, ", SHRT_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_254, "%4hd-j?e12l", SHRT_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_255, "-j=%1hdxz_{k}", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_256, "modq%2hd.wfq-[]", -0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_257, "oadsp;d%6hd", -134)
COMPARE_DEST_STRINGS_AND_RETURNS(test_258, "z~x%21hdc", 1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_259, ";[]czx;[]zx];[]%7hd", 7009)

// Short int with min length left aligment
COMPARE_DEST_STRINGS_AND_RETURNS(test_260, "%-7hdabcdef", 15)
COMPARE_DEST_STRINGS_AND_RETURNS(test_261, "nfk%-3hdvjdas;", 12223)
COMPARE_DEST_STRINGS_AND_RETURNS(test_262, "n9-%-4hd3fn4", -3333)
COMPARE_DEST_STRINGS_AND_RETURNS(test_263, "qwe%-16hd, ", SHRT_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_264, "%-4hd-j?e12l", SHRT_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_265, "-j=%-1hdxz_{k}", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_266, "modq%-2hd.wfq-[]", -0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_267, "oadsp;d%-6hd", -134)
COMPARE_DEST_STRINGS_AND_RETURNS(test_268, "z~x%-21hdc", 1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_269, ";[]czx;[]zx];[]%-7hd", 7009)

// Short int with plus sign display
COMPARE_DEST_STRINGS_AND_RETURNS(test_270, "%+hdabcdef", 15)
COMPARE_DEST_STRINGS_AND_RETURNS(test_271, "nfk%+hdvjdas;", 12223)
COMPARE_DEST_STRINGS_AND_RETURNS(test_272, "n9-%+hd3fn4", -3333)
COMPARE_DEST_STRINGS_AND_RETURNS(test_273, "qwe%+6hd, ", SHRT_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_274, "%+hd-j?e12l", SHRT_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_275, "-j=%+hdxz_{k}", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_276, "modq%+hd.wfq-[]", -0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_277, "oadsp;d%+hd", -134)
COMPARE_DEST_STRINGS_AND_RETURNS(test_278, "z~x%+hdc", 1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_279, ";[]czx;[]zx];[]%+hd", 7009)

// Short int with space instead of plus
COMPARE_DEST_STRINGS_AND_RETURNS(test_280, "% hdabcdef", 15)
COMPARE_DEST_STRINGS_AND_RETURNS(test_281, "nfk% hdvjdas;", 12223)
COMPARE_DEST_STRINGS_AND_RETURNS(test_282, "n9-% hd3fn4", -3333)
COMPARE_DEST_STRINGS_AND_RETURNS(test_283, "qwe% 6hd, ", SHRT_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_284, "% hd-j?e12l", SHRT_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_285, "-j=% hdxz_{k}", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_286, "modq% hd.wfq-[]", -0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_287, "oadsp;d% hd", -134)
COMPARE_DEST_STRINGS_AND_RETURNS(test_288, "z~x% hdc", 1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_289, ";[]czx;[]zx];[]% hd", 7009)

// Short int with all of advanced specs
COMPARE_DEST_STRINGS_AND_RETURNS(test_290, "%-+3.7hdabc%hddef", 15, 4444)
COMPARE_DEST_STRINGS_AND_RETURNS(test_291, "nfk%- 5.3hdvjd%-3hdas;", 12223,
                                 -19271)
COMPARE_DEST_STRINGS_AND_RETURNS(test_292, "n9-%+-4.4hd3f%6hdn4", -3333, 82)
COMPARE_DEST_STRINGS_AND_RETURNS(test_293, "qwe%-+3.16hd, %+6.4hd", SHRT_MAX,
                                 4798)
COMPARE_DEST_STRINGS_AND_RETURNS(test_294, "% -8.4hd-j?e12l", SHRT_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_295, "-j=%- 2.1hdxz_{k}", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_296, "modq%+-1.2hd.wfq% hd-[]", -0, 9672)
COMPARE_DEST_STRINGS_AND_RETURNS(test_297, "oadsp;d%+-3.0hd", -1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_298, "z~x%-+9.21hdc", 1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_299, ";[]czx;[]zx];[]%11.7hd", 7009)

// ================================SHORT SHORT
// INT=================================== Simple short short int
COMPARE_DEST_STRINGS_AND_RETURNS(test_300, "%hhdabcdef", 15)
COMPARE_DEST_STRINGS_AND_RETURNS(test_301, "nfk%hhdvjdas;", 122)
COMPARE_DEST_STRINGS_AND_RETURNS(test_302, "n9-%hhd3fn4", -33)
COMPARE_DEST_STRINGS_AND_RETURNS(test_303, "qwe%hhd, ", INT8_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_304, "%hhd-j?e12l", INT8_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_305, "-j=%hhdxz_{k}", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_306, "modq%hhd.wfq-[]", -0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_307, "oadsp;d%hhd", -1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_308, "z~x%hhdc", 1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_309, ";[]czx;[]zx];[]%hhd", 70)

// Short short int with precision
COMPARE_DEST_STRINGS_AND_RETURNS(test_310, "%.7hhdabcdef", 15)
COMPARE_DEST_STRINGS_AND_RETURNS(test_311, "nfk%.3hhdvjdas;", 122)
COMPARE_DEST_STRINGS_AND_RETURNS(test_312, "n9-%.4hhd3fn4", -33)
COMPARE_DEST_STRINGS_AND_RETURNS(test_313, "qwe%.16hhd, ", INT8_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_314, "%.4hhd-j?e12l", INT8_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_315, "-j=%.1hhdxz_{k}", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_316, "modq%.2hhd.wfq-[]", -0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_317, "oadsp;d%.0hhd", -1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_318, "z~x%.21hhdc", 1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_319, ";[]czx;[]zx];[]%.7hhd", 70)

// Short short int with min length
COMPARE_DEST_STRINGS_AND_RETURNS(test_320, "%7hhdabcdef", 15)
COMPARE_DEST_STRINGS_AND_RETURNS(test_321, "nfk%3hhdvjdas;", 122)
COMPARE_DEST_STRINGS_AND_RETURNS(test_322, "n9-%4hhd3fn4", -33)
COMPARE_DEST_STRINGS_AND_RETURNS(test_323, "qwe%16hhd, ", INT8_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_324, "%4hhd-j?e12l", INT8_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_325, "-j=%1hhdxz_{k}", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_326, "modq%2hhd.wfq-[]", -0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_327, "oadsp;d%6hhd", -13)
COMPARE_DEST_STRINGS_AND_RETURNS(test_328, "z~x%21hhdc", 1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_329, ";[]czx;[]zx];[]%7hhd", 70)

// Short short int with min length left aligment
COMPARE_DEST_STRINGS_AND_RETURNS(test_330, "%-7hhdabcdef", 15)
COMPARE_DEST_STRINGS_AND_RETURNS(test_331, "nfk%-3hhdvjdas;", 122)
COMPARE_DEST_STRINGS_AND_RETURNS(test_332, "n9-%-4hhd3fn4", -33)
COMPARE_DEST_STRINGS_AND_RETURNS(test_333, "qwe%-16hhd, ", INT8_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_334, "%-4hhd-j?e12l", INT8_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_335, "-j=%-1hhdxz_{k}", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_336, "modq%-2hhd.wfq-[]", -0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_337, "oadsp;d%-6hhd", -13)
COMPARE_DEST_STRINGS_AND_RETURNS(test_338, "z~x%-21hhdc", 1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_339, ";[]czx;[]zx];[]%-7hhd", 70)

// Short short int with plus sign display
COMPARE_DEST_STRINGS_AND_RETURNS(test_340, "%+hhdabcdef", 15)
COMPARE_DEST_STRINGS_AND_RETURNS(test_341, "nfk%+hhdvjdas;", 122)
COMPARE_DEST_STRINGS_AND_RETURNS(test_342, "n9-%+hhd3fn4", -33)
COMPARE_DEST_STRINGS_AND_RETURNS(test_343, "qwe%+6hhd, ", INT8_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_344, "%+hhd-j?e12l", INT8_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_345, "-j=%+hhdxz_{k}", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_346, "modq%+hhd.wfq-[]", -0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_347, "oadsp;d%+hhd", -13)
COMPARE_DEST_STRINGS_AND_RETURNS(test_348, "z~x%+hhdc", 1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_349, ";[]czx;[]zx];[]%+hhd", 70)

// Short short int with space instead of plus
COMPARE_DEST_STRINGS_AND_RETURNS(test_350, "% hhdabcdef", 15)
COMPARE_DEST_STRINGS_AND_RETURNS(test_351, "nfk% hhdvjdas;", 122)
COMPARE_DEST_STRINGS_AND_RETURNS(test_352, "n9-% hhd3fn4", -33)
COMPARE_DEST_STRINGS_AND_RETURNS(test_353, "qwe% 6hhd, ", INT8_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_354, "% hhd-j?e12l", INT8_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_355, "-j=% hhdxz_{k}", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_356, "modq% hhd.wfq-[]", -0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_357, "oadsp;d% hhd", -13)
COMPARE_DEST_STRINGS_AND_RETURNS(test_358, "z~x% hhdc", 1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_359, ";[]czx;[]zx];[]% hhd", 70)

// Short short int with all of advanced specs
COMPARE_DEST_STRINGS_AND_RETURNS(test_360, "%-+3.7hhdabc%hhddef", 15, 44)
COMPARE_DEST_STRINGS_AND_RETURNS(test_361, "nfk%- 5.3hhdvjd%-3hhdas;", 122, -19)
COMPARE_DEST_STRINGS_AND_RETURNS(test_362, "n9-%+-4.4hhd3f%6hhdn4", -33, 82)
COMPARE_DEST_STRINGS_AND_RETURNS(test_363, "qwe%-+3.16hhd, %+6.4hhd", INT8_MAX,
                                 47)
COMPARE_DEST_STRINGS_AND_RETURNS(test_364, "% -8.4hhd-j?e12l", INT8_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_365, "-j=%- 2.1hhdxz_{k}", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_366, "modq%+-1.2hhd.wfq% hhd-[]", -0, 96)
COMPARE_DEST_STRINGS_AND_RETURNS(test_367, "oadsp;d%+-3.0hhd", -1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_368, "z~x%-+9.21hhdc", 1)
COMPARE_DEST_STRINGS_AND_RETURNS(test_369, ";[]czx;[]zx];[]%11.7hhd", 70)

// ================================UNSIGNED===================================
// Simple unsigned
COMPARE_DEST_STRINGS_AND_RETURNS(test_370, "%uabcdef", 15u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_371, "nfk%uvjdas;", 1222375u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_372, "n9-%u3fn4", 3333u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_373, "qwe%u, ", UINT_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_374, "%u-j?e12l", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_375, "-j=%uxz_{k}", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_376, "modq%u.wfq-[]", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_377, "oadsp;d%u", 1u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_378, "z~x%uc", 1u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_379, ";[]czx;[]zx];[]%u", 700909291u)

// Unsigned with precision
COMPARE_DEST_STRINGS_AND_RETURNS(test_380, "%.7uabcdef", 15u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_381, "nfk%.3uvjdas;", 1222375u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_382, "n9-%.4u3fn4", 3333u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_383, "qwe%.16u, ", UINT_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_384, "%.4u-j?e12l", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_385, "-j=%.1uxz_{k}", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_386, "modq%.2u.wfq-[]", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_387, "oadsp;d%.0u", 1u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_388, "z~x%.21uc", 1u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_389, ";[]czx;[]zx];[]%.7u", 700909291u)

// Unsigned with min length
COMPARE_DEST_STRINGS_AND_RETURNS(test_390, "%7uabcdef", 15u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_391, "nfk%3uvjdas;", 1222375u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_392, "n9-%4u3fn4", 3333u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_393, "qwe%16u, ", UINT_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_394, "%4u-j?e12l", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_395, "-j=%1uxz_{k}", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_396, "modq%2u.wfq-[]", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_397, "oadsp;d%6u", 134u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_398, "z~x%21uc", 1u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_399, ";[]czx;[]zx];[]%7u", 700909291u)

// Unsigned with min length left aligment
COMPARE_DEST_STRINGS_AND_RETURNS(test_400, "%-7uabcdef", 15u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_401, "nfk%-3uvjdas;", 1222375u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_402, "n9-%-4u3fn4", 3333u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_403, "qwe%-16u, ", UINT_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_404, "%-4u-j?e12l", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_405, "-j=%-1uxz_{k}", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_406, "modq%-2u.wfq-[]", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_407, "oadsp;d%-6u", 134u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_408, "z~x%-21uc", 1u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_409, ";[]czx;[]zx];[]%-7u", 700909291u)

// Unsigned with all of advanced specs
COMPARE_DEST_STRINGS_AND_RETURNS(test_410, "%-3.7uabc%udef", 15, 4444u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_411, "nfk%-5.3uvjd%-3uas;", 1222375,
                                 19271u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_412, "n9-%-4.4u3f%6un4", 3333, 82u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_413, "qwe%-3.16u, %6.4u", UINT_MAX,
                                 47983u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_414, "%-8.4u-j?e12l", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_415, "-j=%-2.1uxz_{k}", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_416, "modq%-1.2u.wfq%u-[]", 0, 9672u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_417, "oadsp;d%-3.0u", 1u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_418, "z~x%-9.21uc", 1u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_419, ";[]czx;[]zx];[]%11.7u", 700909291u)

// ================================UNSIGNED
// LONG=================================== Simple long unsigned
COMPARE_DEST_STRINGS_AND_RETURNS(test_420, "%luabcdef", 15lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_421, "nfk%luvjdas;", 7962471094u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_422, "n9-%lu3fn4", 3333lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_423, "qwe%lu, ", ULONG_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_424, "%lu-j?e12l", 0lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_425, "-j=%luxz_{k}", 0lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_426, "modq%lu.wfq-[]", 0lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_427, "oadsp;d%lu", 1lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_428, "z~x%luc", 1lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_429, ";[]czx;[]zx];[]%lu", 700909291lu)

// Long unsigned with precision
COMPARE_DEST_STRINGS_AND_RETURNS(test_430, "%.7luabcdef", 15lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_431, "nfk%.3luvjdas;", 7962471094u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_432, "n9-%.4lu3fn4", 3333lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_433, "qwe%.16lu, ", ULONG_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_434, "%.4lu-j?e12l", 0lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_435, "-j=%.1luxz_{k}", 0lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_436, "modq%.2lu.wfq-[]", 0lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_437, "oadsp;d%.0lu", 1lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_438, "z~x%.21luc", 1lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_439, ";[]czx;[]zx];[]%.7lu", 700909291lu)

// Long unsigned with min length
COMPARE_DEST_STRINGS_AND_RETURNS(test_440, "%7luabcdef", 15lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_441, "nfk%3luvjdas;", 7962471094u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_442, "n9-%4lu3fn4", 3333lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_443, "qwe%16lu, ", ULONG_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_444, "%4lu-j?e12l", 0lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_445, "-j=%1luxz_{k}", 0lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_446, "modq%2lu.wfq-[]", 0lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_447, "oadsp;d%6lu", 134lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_448, "z~x%21luc", 1lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_449, ";[]czx;[]zx];[]%7lu", 700909291lu)

// Long unsigned with min length left aligment
COMPARE_DEST_STRINGS_AND_RETURNS(test_450, "%-7luabcdef", 15lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_451, "nfk%-3luvjdas;", 7962471094u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_452, "n9-%-4lu3fn4", 3333lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_453, "qwe%-16lu, ", ULONG_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_454, "%-4lu-j?e12l", 0lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_455, "-j=%-1luxz_{k}", 0lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_456, "modq%-2lu.wfq-[]", 0lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_457, "oadsp;d%-6lu", 134lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_458, "z~x%-21luc", 1lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_459, ";[]czx;[]zx];[]%-7lu", 700909291lu)

// Long unsigned with all of advanced specs
COMPARE_DEST_STRINGS_AND_RETURNS(test_460, "%-3.7luabc%ludef", 15l, 4444lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_461, "nfk%-5.3luvjd%-3luas;", 7962471094,
                                 19271lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_462, "n9-%-4.4lu3f%6lun4", 3333l, 82lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_463, "qwe%-3.16lu, %6.4lu", ULONG_MAX,
                                 47983lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_464, "%-8.4lu-j?e12l", 0lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_465, "-j=%-2.1luxz_{k}", 0lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_466, "modq%-1.2lu.wfq%lu-[]", 0l, 9672lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_467, "oadsp;d%-3.0lu", 1lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_468, "z~x%-9.21luc", 1lu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_469, ";[]czx;[]zx];[]%11.7lu",
                                 700909291lu)

// ================================UNSIGNED LONG
// LONG=================================== Simple long long unsigned
COMPARE_DEST_STRINGS_AND_RETURNS(test_470, "%lluabcdef", 15llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_471, "nfk%lluvjdas;",
                                 7933333363323232320llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_472, "n9-%llu3fn4", 3333llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_473, "qwe%llu, ", ULLONG_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_474, "%llu-j?e12l", 0llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_475, "-j=%lluxz_{k}", 0llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_476, "modq%llu.wfq-[]", 0llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_477, "oadsp;d%llu", 1llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_478, "z~x%lluc", 1llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_479, ";[]czx;[]zx];[]%llu", 700909291llu)

// Long long unsigned with precision
COMPARE_DEST_STRINGS_AND_RETURNS(test_480, "%.7lluabcdef", 15llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_481, "nfk%.3lluvjdas;",
                                 7933333363323232320llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_482, "n9-%.4llu3fn4", 3333llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_483, "qwe%.16llu, ", ULLONG_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_484, "%.4llu-j?e12l", 0llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_485, "-j=%.1lluxz_{k}", 0llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_486, "modq%.2llu.wfq-[]", 0llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_487, "oadsp;d%.0llu", 1llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_488, "z~x%.21lluc", 1llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_489, ";[]czx;[]zx];[]%.7llu",
                                 700909291llu)

// Long long unsigned with min length
COMPARE_DEST_STRINGS_AND_RETURNS(test_490, "%7lluabcdef", 15llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_491, "nfk%3lluvjdas;",
                                 7933333363323232320llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_492, "n9-%4llu3fn4", 3333llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_493, "qwe%16llu, ", ULLONG_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_494, "%4llu-j?e12l", 0llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_495, "-j=%1lluxz_{k}", 0llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_496, "modq%2llu.wfq-[]", 0llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_497, "oadsp;d%6llu", 134llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_498, "z~x%21lluc", 1llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_499, ";[]czx;[]zx];[]%7llu", 700909291llu)

// Long long unsigned with min length left aligment
COMPARE_DEST_STRINGS_AND_RETURNS(test_500, "%-7lluabcdef", 15llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_501, "nfk%-3lluvjdas;",
                                 7933333363323232320llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_502, "n9-%-4llu3fn4", 3333llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_503, "qwe%-16llu, ", ULLONG_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_504, "%-4llu-j?e12l", 0llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_505, "-j=%-1lluxz_{k}", 0llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_506, "modq%-2llu.wfq-[]", 0llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_507, "oadsp;d%-6llu", 134llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_508, "z~x%-21lluc", 1llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_509, ";[]czx;[]zx];[]%-7llu",
                                 700909291llu)

// Long long unsigned with all of advanced specs
COMPARE_DEST_STRINGS_AND_RETURNS(test_510, "%-3.7lluabc%lludef", 15ll, 4444llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_511, "nfk%-5.3lluvjd%-3lluas;",
                                 7933333363323232320ll, 19271llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_512, "n9-%-4.4llu3f%6llun4", 3333ll,
                                 82llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_513, "qwe%-3.16llu, %6.4llu", ULLONG_MAX,
                                 47983ll)
COMPARE_DEST_STRINGS_AND_RETURNS(test_514, "%-8.4llu-j?e12l", 0llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_515, "-j=%-2.1lluxz_{k}", 0llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_516, "modq%-1.2llu.wfq%llu-[]", 0ll,
                                 9672llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_517, "oadsp;d%-3.0llu", 1llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_518, "z~x%-9.21lluc", 1llu)
COMPARE_DEST_STRINGS_AND_RETURNS(test_519, ";[]czx;[]zx];[]%11.7llu",
                                 700909291llu)

// ================================UNSIGNED
// SHORT=================================== Simple short unsigned
COMPARE_DEST_STRINGS_AND_RETURNS(test_520, "%huabcdef", 15u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_521, "nfk%huvjdas;", 12223u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_522, "n9-%hu3fn4", 3333u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_523, "qwe%hu, ", USHRT_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_524, "%hu-j?e12l", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_525, "-j=%huxz_{k}", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_526, "modq%hu.wfq-[]", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_527, "oadsp;d%hu", 1u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_528, "z~x%huc", 1u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_529, ";[]czx;[]zx];[]%hu", 7009u)

// Short unsigned with precision
COMPARE_DEST_STRINGS_AND_RETURNS(test_530, "%.7huabcdef", 15u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_531, "nfk%.3huvjdas;", 12223u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_532, "n9-%.4hu3fn4", 3333u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_533, "qwe%.16hu, ", USHRT_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_534, "%.4hu-j?e12l", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_535, "-j=%.1huxz_{k}", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_536, "modq%.2hu.wfq-[]", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_537, "oadsp;d%.0hu", 1u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_538, "z~x%.21huc", 1u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_539, ";[]czx;[]zx];[]%.7hu", 7009u)

// Short unsigned with min length
COMPARE_DEST_STRINGS_AND_RETURNS(test_540, "%7huabcdef", 15u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_541, "nfk%3huvjdas;", 12223u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_542, "n9-%4hu3fn4", 3333u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_543, "qwe%16hu, ", USHRT_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_544, "%4hu-j?e12l", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_545, "-j=%1huxz_{k}", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_546, "modq%2hu.wfq-[]", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_547, "oadsp;d%6hu", 134u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_548, "z~x%21huc", 1u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_549, ";[]czx;[]zx];[]%7hu", 7009u)

// Short unsigned with min length left aligment
COMPARE_DEST_STRINGS_AND_RETURNS(test_550, "%-7huabcdef", 15u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_551, "nfk%-3huvjdas;", 12223u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_552, "n9-%-4hu3fn4", 3333u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_553, "qwe%-16hu, ", USHRT_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_554, "%-4hu-j?e12l", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_555, "-j=%-1huxz_{k}", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_556, "modq%-2hu.wfq-[]", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_557, "oadsp;d%-6hu", 134u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_558, "z~x%-21huc", 1u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_559, ";[]czx;[]zx];[]%-7hu", 7009u)

// Short unsigned with all of advanced specs
COMPARE_DEST_STRINGS_AND_RETURNS(test_560, "%-3.7huabc%hudef", 15, 4444u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_561, "nfk%-5.3huvjd%-3huas;", 12223,
                                 19271u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_562, "n9-%-4.4hu3f%6hun4", 3333, 82u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_563, "qwe%-3.16hu, %6.4hu", USHRT_MAX,
                                 4798u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_564, "%-8.4hu-j?e12l", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_565, "-j=%-2.1huxz_{k}", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_566, "modq%-1.2hu.wfq%hu-[]", 0, 9672u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_567, "oadsp;d%-3.0hu", 1u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_568, "z~x%-9.21huc", 1u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_569, ";[]czx;[]zx];[]%11.7hu", 7009u)

// ================================UNSIGNED SHORT
// SHORT=================================== Simple short short unsigned
COMPARE_DEST_STRINGS_AND_RETURNS(test_570, "%hhuabcdef", 15u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_571, "nfk%hhuvjdas;", 122u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_572, "n9-%hhu3fn4", 33u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_573, "qwe%hhu, ", UINT8_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_574, "%hhu-j?e12l", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_575, "-j=%hhuxz_{k}", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_576, "modq%hhu.wfq-[]", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_577, "oadsp;d%hhu", 1u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_578, "z~x%hhuc", 1u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_579, ";[]czx;[]zx];[]%hhu", 70u)

// Short short unsigned with precision
COMPARE_DEST_STRINGS_AND_RETURNS(test_580, "%.7hhuabcdef", 15u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_581, "nfk%.3hhuvjdas;", 122u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_582, "n9-%.4hhu3fn4", 33u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_583, "qwe%.16hhu, ", UINT8_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_584, "%.4hhu-j?e12l", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_585, "-j=%.1hhuxz_{k}", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_586, "modq%.2hhu.wfq-[]", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_587, "oadsp;d%.0hhu", 1u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_588, "z~x%.21hhuc", 1u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_589, ";[]czx;[]zx];[]%.7hhu", 70u)

// Short short unsigned with min length
COMPARE_DEST_STRINGS_AND_RETURNS(test_590, "%7hhuabcdef", 15u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_591, "nfk%3hhuvjdas;", 122u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_592, "n9-%4hhu3fn4", 33u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_593, "qwe%16hhu, ", UINT8_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_594, "%4hhu-j?e12l", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_595, "-j=%1hhuxz_{k}", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_596, "modq%2hhu.wfq-[]", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_597, "oadsp;d%6hhu", 13u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_598, "z~x%21hhuc", 1u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_599, ";[]czx;[]zx];[]%7hhu", 70u)

// Short short unsigned with min length left aligment
COMPARE_DEST_STRINGS_AND_RETURNS(test_600, "%-7hhuabcdef", 15u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_601, "nfk%-3hhuvjdas;", 122u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_602, "n9-%-4hhu3fn4", 33u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_603, "qwe%-16hhu, ", UINT8_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_604, "%-4hhu-j?e12l", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_605, "-j=%-1hhuxz_{k}", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_606, "modq%-2hhu.wfq-[]", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_607, "oadsp;d%-6hhu", 13u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_608, "z~x%-21hhuc", 1u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_609, ";[]czx;[]zx];[]%-7hhu", 70u)

// Short short unsigned with all of advanced specs
COMPARE_DEST_STRINGS_AND_RETURNS(test_610, "%-3.7hhuabc%hhudef", 15, 44u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_611, "nfk%-5.3hhuvjd%-3hhuas;", 122, 19u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_612, "n9-%-4.4hhu3f%6hhun4", 33, 82u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_613, "qwe%-55.44hhu, %6.4hhu", UINT8_MAX,
                                 47u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_614, "%-8.4hhu-j?e12l", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_615, "-j=%-2.1hhuxz_{k}", 0u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_616, "modq%-1.2hhu.wfq%hhu-[]", 0, 96u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_617, "oadsp;d%-3.0hhu", 1u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_618, "z~x%-9.21hhuc", 1u)
COMPARE_DEST_STRINGS_AND_RETURNS(test_619, ";[]czx;[]zx];[]%11.7hhu", 70u)

// ====================================CHAR======================================
// Simple char
COMPARE_DEST_STRINGS_AND_RETURNS(test_620, "%cabcdef", 'c')
COMPARE_DEST_STRINGS_AND_RETURNS(test_621, "nfk%cvjdas;", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_622, "n9-%c3fn4", 121)
COMPARE_DEST_STRINGS_AND_RETURNS(test_623, "qwe%c, ", CHAR_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_624, "%c-j?e12l", CHAR_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_625, "-j=%cxz_{k}", '\0')
COMPARE_DEST_STRINGS_AND_RETURNS(test_626, "modq%c.wfq-[]", '\n')
COMPARE_DEST_STRINGS_AND_RETURNS(test_627, "oadsp;d%c", '%')
COMPARE_DEST_STRINGS_AND_RETURNS(test_628, "z~x%cc", '0')
COMPARE_DEST_STRINGS_AND_RETURNS(test_629, ";[]czx;[]zx];[]%c", '\t')

// Char with min length
COMPARE_DEST_STRINGS_AND_RETURNS(test_630, "%7cabcdef", 'c')
COMPARE_DEST_STRINGS_AND_RETURNS(test_631, "nfk%3cvjdas;", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_632, "n9-%4c3fn4", 121)
COMPARE_DEST_STRINGS_AND_RETURNS(test_633, "qwe%16c, ", CHAR_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_634, "%4c-j?e12l", CHAR_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_635, "-j=%1cx%cz_{k}", '\0', 125)
COMPARE_DEST_STRINGS_AND_RETURNS(test_636, "modq%2c.wfq-[]", '\n')
COMPARE_DEST_STRINGS_AND_RETURNS(test_637, "oadsp;d%6c", '%')
COMPARE_DEST_STRINGS_AND_RETURNS(test_638, "z~x%21cc", '0')
COMPARE_DEST_STRINGS_AND_RETURNS(test_639, ";[]czx;[]zzx];[]%7c", '\t')

// Char with min length left aligment
COMPARE_DEST_STRINGS_AND_RETURNS(test_640, "%-7cabcdef", 'c')
COMPARE_DEST_STRINGS_AND_RETURNS(test_641, "nfk%-3cvjdas;", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_642, "n9-%-4c3fn4", 121)
COMPARE_DEST_STRINGS_AND_RETURNS(test_643, "qwe%-16c, ", CHAR_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_644, "%-4c-j?e12l", CHAR_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_645, "-j=%-1cxz_{k}", '\0')
COMPARE_DEST_STRINGS_AND_RETURNS(test_646, "modq%-c.wfq-[]", '\n')
COMPARE_DEST_STRINGS_AND_RETURNS(test_647, "oadsp;d%-6c", '%')
COMPARE_DEST_STRINGS_AND_RETURNS(test_648, "z~x%-21cc", '0')
COMPARE_DEST_STRINGS_AND_RETURNS(test_649, ";[]czx;[]zxzx];[]%-7c", '\t')

// ================================WCHAR (LONG
// CHAR)=================================== Simple wchar
COMPARE_DEST_STRINGS_AND_RETURNS(test_650, "%lcabcdef", L'c')
COMPARE_DEST_STRINGS_AND_RETURNS(test_651, "nfk%lcvjdas;", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_652, "n9-%lc3fn4", 121)
COMPARE_DEST_STRINGS_AND_RETURNS(test_653, "qwe%lc, ", WCHAR_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_654, "%lc-j?e12l", WCHAR_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_655, "-j=%lcxz_{k}", L'\0')
COMPARE_DEST_STRINGS_AND_RETURNS(test_656, "modq%lc.wfq-[]", L'\n')
COMPARE_DEST_STRINGS_AND_RETURNS(test_657, "oadsp;d%lc", L'%')
COMPARE_DEST_STRINGS_AND_RETURNS(test_658, "z~x%lcc", L'0')
COMPARE_DEST_STRINGS_AND_RETURNS(test_659, ";[]czx;[]zx];[]%lc", L'\t')

// Wchar with min length
COMPARE_DEST_STRINGS_AND_RETURNS(test_660, "%7lcabcdef", L'c')
COMPARE_DEST_STRINGS_AND_RETURNS(test_661, "nfk%3lcvjdas;", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_662, "n9-%4lc3fn4", 121)
COMPARE_DEST_STRINGS_AND_RETURNS(test_663, "qwe%16lc, ", WCHAR_MAX)
COMPARE_DEST_STRINGS_AND_RETURNS(test_664, "%4lc-j?e12l", WCHAR_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_665, "-j=%1lcxz_{k}", L'\0')
COMPARE_DEST_STRINGS_AND_RETURNS(test_666, "modq%2lc.wfq-[]", L'\n')
COMPARE_DEST_STRINGS_AND_RETURNS(test_667, "oadsp;d%6lc", L'%')
COMPARE_DEST_STRINGS_AND_RETURNS(test_668, "z~x%21lcc", L'0')
COMPARE_DEST_STRINGS_AND_RETURNS(test_669, ";[]czx;[]zzx];[]%7lc", L'\t')

// Wchar with min length left aligment
COMPARE_DEST_STRINGS_AND_RETURNS(test_670, "%-7lcabcd%cef", L'c', '5')
COMPARE_DEST_STRINGS_AND_RETURNS(test_671, "nfk%-3lcvjdas;", 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_672, "n9-%-4lc3fn4", 121)
COMPARE_DEST_STRINGS_AND_RETURNS(test_673, "qwe%-16lc, %c", WCHAR_MAX, 0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_674, "%-4lc-j?e12l", WCHAR_MIN)
COMPARE_DEST_STRINGS_AND_RETURNS(test_675, "-j=%-1lcxz_{k}", L'\0')
COMPARE_DEST_STRINGS_AND_RETURNS(test_676, "modq%-lc.wfq-[]", L'\n')
COMPARE_DEST_STRINGS_AND_RETURNS(test_677, "oadsp;d%-6lc", L'%')
COMPARE_DEST_STRINGS_AND_RETURNS(test_678, "z~x%-21lcc", L'0')
COMPARE_DEST_STRINGS_AND_RETURNS(test_679, ";[]czx;[]zxzx];[]%-7lc", L'\t')

// ================================STRING===================================
// Simple string
COMPARE_DEST_STRINGS_AND_RETURNS(test_680, "%sabcdef", "15u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_681, "nfk%svjdas;", "1222375\0u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_682, "n9-%s3fn4", "3333u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_683, "qwe%s, ", "UIN\nT_MAX")
COMPARE_DEST_STRINGS_AND_RETURNS(test_684, "%s-j?e12l", "0\\u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_685, "-j=%sxz_{k}", "0%%u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_686, "modq%s.wfq-[]", "%d0u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_687, "oadsp;d%s", "1\tu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_688, "z~x%sc", "1\vu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_689, ";[]czx;[]zx];[]%s", "700909291u")

// String with precision
COMPARE_DEST_STRINGS_AND_RETURNS(test_690, "%.7sabcdef", "15u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_691, "nfk%.3svjdas;", "1222375u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_692, "n9-%.4s3fn4", "3333u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_693, "qwe%.16s, ", "UIN\tT_MAX")
COMPARE_DEST_STRINGS_AND_RETURNS(test_694, "%.4s-j?e12l", "0u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_695, "-j=%.1sxz_{k}", "0u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_696, "modq%.2s.wfq-[]", "0u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_697, "oadsp;d%.0s", "1\0u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_698, "z~x%.21sc", "1u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_699, ";[]czx;[]zx];[]%.7s", "700909291u")

// String with min length
COMPARE_DEST_STRINGS_AND_RETURNS(test_700, "%7sabcdef", "15u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_701, "nfk%3svjdas;", "1222375u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_702, "n9-%4s3fn4", "3333u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_703, "qwe%16s, ", "UI\0NT_MAX")
COMPARE_DEST_STRINGS_AND_RETURNS(test_704, "%4s-j?e12l", "0u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_705, "-j=%1sxz_{k}", "0u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_706, "modq%2s.wfq-[]", "0u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_707, "oadsp;d%6s", "134u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_708, "z~x%21sc", "1u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_709, ";[]czx;[]zx];[]%7s", "700909291u")

// String with min length left aligment
COMPARE_DEST_STRINGS_AND_RETURNS(test_710, "%-7sabcdef", "15u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_711, "nfk%-3svjdas;", "12\n22375u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_712, "n9-%-4s3fn4", "3333u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_713, "qwe%-16s, ", "UINT_MAX")
COMPARE_DEST_STRINGS_AND_RETURNS(test_714, "%-4s-j?e12l", "0u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_715, "-j=%-1sxz_{k}", "0u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_716, "modq%-2s.wfq-[]", "0u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_717, "oadsp;d%-6s", "134u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_718, "z~x%-21sc", "1u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_719, ";[]czx;[]zx];[]%-7s",
                                 "700909\0291u")

// String with all of advanced specs
COMPARE_DEST_STRINGS_AND_RETURNS(test_720, "%-3.7sabc%sdef", "15", "444\\4u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_721, "nfk%-5.3svjd%-3sas;", "1222375",
                                 "19271u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_722, "n9-%-4.4s3f%6sn4", "3333", "82u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_723, "qwe%-3.16s, %6.4s", "UINT_MAX",
                                 "47983u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_724, "%-8.4s-j?e12l", "0u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_725, "-j=%-2.1sxz_{k}", "0u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_726, "modq%-1.2s.wfq%s-[]", "0", "9672u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_727, "oadsp;d%-3.0s", "1u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_728, "z~x%-9.21sc", "1u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_729, ";[]czx;[]zx];[]%11.7s",
                                 "700909291u")

// ================================WCHAR STRING (LONG
// STRING)=================================== Simple wchar string
COMPARE_DEST_STRINGS_AND_RETURNS(test_730, "%lsabcdef", L"15lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_731, "nfk%lsvjdas;", L"7962471094u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_732, "n9-%ls3fn4", L"3333lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_733, "qwe%ls, ", L"ULON\nG_MAX")
COMPARE_DEST_STRINGS_AND_RETURNS(test_734, "%ls-j?e12l", L"0lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_735, "-j=%lsxz_{k}", L"0lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_736, "modq%ls.wfq-[]", L"0lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_737, "oadsp;d%ls", L"1lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_738, "z~x%lsc", L"1lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_739, ";[]czx;[]zx];[]%ls",
                                 L"700\v909291lu")

// Wchar string with precision
COMPARE_DEST_STRINGS_AND_RETURNS(test_740, "%.7lsabcdef", L"15lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_741, "nfk%.3lsvjdas;", L"7962471094u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_742, "n9-%.4ls3fn4", L"333%3lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_743, "qwe%.16ls, ", L"ULONG_MAX")
COMPARE_DEST_STRINGS_AND_RETURNS(test_744, "%.4ls-j?e12l", L"0lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_745, "-j=%.1lsxz_{k}", L"0lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_746, "modq%.2ls.wfq-[]", L"0lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_747, "oadsp;d%.0ls", L"1lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_748, "z~x%.21lsc", L"1lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_749, ";[]czx;[]zx];[]%.7ls",
                                 L"700909291lu")

// Wchar string with min length
COMPARE_DEST_STRINGS_AND_RETURNS(test_750, "%7lsabcdef", L"15lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_751, "nfk%3lsvjdas;", L"7962\n471094u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_752, "n9-%4ls3fn4", L"3333lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_753, "qwe%16ls, ", L"ULONG_MAX")
COMPARE_DEST_STRINGS_AND_RETURNS(test_754, "%4ls-j?e12l", L"0\\lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_755, "-j=%1lsxz_{k}", L"0lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_756, "modq%2ls.wfq-[]", L"0lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_757, "oadsp;d%6ls", L"134lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_758, "z~x%21lsc", L"1lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_759, ";[]czx;[]zx];[]%7ls",
                                 L"700%%909291lu")

// Wchar string with min length left aligment
COMPARE_DEST_STRINGS_AND_RETURNS(test_760, "%-7lsabcdef", L"15lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_761, "nfk%-3lsvjdas;", L"7962471094u")
COMPARE_DEST_STRINGS_AND_RETURNS(test_762, "n9-%-4ls3fn4", L"3333\0lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_763, "qwe%-16ls, ", L"ULONG_MAX")
COMPARE_DEST_STRINGS_AND_RETURNS(test_764, "%-4ls-j?e12l", L"0lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_765, "-j=%-1lsxz_{k}", L"0lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_766, "modq%-2ls.wfq-[]", L"0lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_767, "oadsp;d%-6ls", L"134lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_768, "z~x%-21lsc", L"1lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_769, ";[]czx;[]zx];[]%-7ls",
                                 L"700909291lu")

// Wchar string with all of advanced specs
COMPARE_DEST_STRINGS_AND_RETURNS(test_770, "%-3.7lsabc%lsdef", L"15l",
                                 L"4444lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_771, "nfk%-5.3lsvjd%-3lsuas;",
                                 L"7962471094", L"19271lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_772, "n9-%-4.4ls3f%6lsn4", L"3333l",
                                 L"82lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_773, "qwe%-3.16ls, %6.4ls",
                                 L"ULONG\t_MAX", L"47983lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_774, "%-8.4ls-j?e12l", L"0lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_775, "-j=%-2.1lsxz_{k}", L"0lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_776, "modq%-1.2ls.wfq%ls-[]", L"0\0l",
                                 L"967\02lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_777, "oadsp;d%-3.0ls", L"1lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_778, "z~x%-9.21lsc", L"1lu")
COMPARE_DEST_STRINGS_AND_RETURNS(test_779, ";[]czx;[]zx];[]%11.7ls",
                                 L"700909291lu")

// ================================DOUBLE===================================
// Simple double
COMPARE_DEST_STRINGS_AND_RETURNS(test_780, "%fabcdef", 1.5)
COMPARE_DEST_STRINGS_AND_RETURNS(test_781, "nfk%fvjdas;", 1222.375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_782, "n9-%f3fn4", -3.333)
COMPARE_DEST_STRINGS_AND_RETURNS(test_783, "qwe%f, ", 0.000000000000000000001)
COMPARE_DEST_STRINGS_AND_RETURNS(test_784, "%f-j?e12l",
                                 10000000000000000000.000)
COMPARE_DEST_STRINGS_AND_RETURNS(test_785, "-j=%fxz_{k}", .0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_786, "modq%f.wfq-[]", -0.4444444)
COMPARE_DEST_STRINGS_AND_RETURNS(test_787, "oadsp;d%f", -1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_788, "z~x%fc", 1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_789, ";[]czx;[]zx];[]%f", 7009092.91)

// Double with precision
COMPARE_DEST_STRINGS_AND_RETURNS(test_790, "%.7fabcdef", 15.0001)
COMPARE_DEST_STRINGS_AND_RETURNS(test_791, "nfk%.3fvjdas;", 122.2375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_792, "n9-%.4f3fn4", -3333.33245)
COMPARE_DEST_STRINGS_AND_RETURNS(test_793, "qwe%.16f, ",
                                 0.000000000000000000001)
COMPARE_DEST_STRINGS_AND_RETURNS(test_794, "%.4f-j?e12l",
                                 10000000000000000000.000)
COMPARE_DEST_STRINGS_AND_RETURNS(test_795, "-j=%.1fxz_{k}", 0.000001)
COMPARE_DEST_STRINGS_AND_RETURNS(test_796, "modq%.2f.wfq-[]", -0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_797, "oadsp;d%.0f", -1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_798, "z~x%.21fc", 1.44)
COMPARE_DEST_STRINGS_AND_RETURNS(test_799, ";[]czx;[]zx];[]%.7f", 7009092.91)

// Double with min length
COMPARE_DEST_STRINGS_AND_RETURNS(test_800, "%7fabcdef", 1.5)
COMPARE_DEST_STRINGS_AND_RETURNS(test_801, "nfk%3fvjdas;", 1222.375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_802, "n9-%4f3fn4", -333.3)
COMPARE_DEST_STRINGS_AND_RETURNS(test_803, "qwe%16f, ", 0.000000000000000000001)
COMPARE_DEST_STRINGS_AND_RETURNS(test_804, "%4f-j?e12l",
                                 10000000000000000000.000)
COMPARE_DEST_STRINGS_AND_RETURNS(test_805, "-j=%1fxz_{k}", 0.0000004)
COMPARE_DEST_STRINGS_AND_RETURNS(test_806, "modq%2f.wfq-[]", -.450)
COMPARE_DEST_STRINGS_AND_RETURNS(test_807, "oadsp;d%6f", -13.4)
COMPARE_DEST_STRINGS_AND_RETURNS(test_808, "z~x%21fc", 1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_809, ";[]czx;[]zx];[]%7f", 700.909291)

// Double with min length left aligment
COMPARE_DEST_STRINGS_AND_RETURNS(test_810, "%-7fabcdef", 1.5)
COMPARE_DEST_STRINGS_AND_RETURNS(test_811, "nfk%-3fvjdas;", 12223.75)
COMPARE_DEST_STRINGS_AND_RETURNS(test_812, "n9-%-4f3fn4", -33.33)
COMPARE_DEST_STRINGS_AND_RETURNS(test_813, "qwe%-16f, ",
                                 0.000000000000000000001)
COMPARE_DEST_STRINGS_AND_RETURNS(test_814, "%-4f-j?e12l",
                                 10000000000000000000.000)
COMPARE_DEST_STRINGS_AND_RETURNS(test_815, "-j=%-1fxz_{k}", 0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_816, "modq%-2f.wfq-[]", -0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_817, "oadsp;d%-6f", -13.4)
COMPARE_DEST_STRINGS_AND_RETURNS(test_818, "z~x%-21fc", 1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_819, ";[]czx;[]zx];[]%-7f", 700909.291)

// Double with plus sign display
COMPARE_DEST_STRINGS_AND_RETURNS(test_820, "%+fabcdef", 1.5)
COMPARE_DEST_STRINGS_AND_RETURNS(test_821, "nfk%+fvjdas;", 1222.375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_822, "n9-%+f3fn4", -3.333)
COMPARE_DEST_STRINGS_AND_RETURNS(test_823, "qwe%+6f, ", 0.000000000000000000001)
COMPARE_DEST_STRINGS_AND_RETURNS(test_824, "%+f-j?e12l",
                                 10000000000000000000.000)
COMPARE_DEST_STRINGS_AND_RETURNS(test_825, "-j=%+fxz_{k}", 0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_826, "modq%+f.wfq-[]", -0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_827, "oadsp;d%+f", -13.4)
COMPARE_DEST_STRINGS_AND_RETURNS(test_828, "z~x%+fc", 1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_829, ";[]czx;[]zx];[]%+f", 70090.9291)

// Double with space instead of plus
COMPARE_DEST_STRINGS_AND_RETURNS(test_830, "% fabcdef", 0.15)
COMPARE_DEST_STRINGS_AND_RETURNS(test_831, "nfk% fvjdas;", 10222375.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_832, "n9-% f3fn4", -3330.3)
COMPARE_DEST_STRINGS_AND_RETURNS(test_833, "qwe% 6f, ", 0.000000000000000000001)
COMPARE_DEST_STRINGS_AND_RETURNS(test_834, "% f-j?e12l",
                                 10000000000000000000.000)
COMPARE_DEST_STRINGS_AND_RETURNS(test_835, "-j=% fxz_{k}", .00)
COMPARE_DEST_STRINGS_AND_RETURNS(test_836, "modq% f.wfq-[]", -.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_837, "oadsp;d% f", -13.4)
COMPARE_DEST_STRINGS_AND_RETURNS(test_838, "z~x% fc", 1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_839, ";[]czx;[]zx];[]% f", .700909291)

// Double with all of advanced specs
COMPARE_DEST_STRINGS_AND_RETURNS(test_840, "%-+3.7fabc%fdef", 15.0, 44.044)
COMPARE_DEST_STRINGS_AND_RETURNS(test_841, "nfk%- 5.3fvjd%-3fas;", 122.02375,
                                 -192.071)
COMPARE_DEST_STRINGS_AND_RETURNS(test_842, "n9-%+-4.4f3f%6fn4", -333.03, 82.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_843, "qwe%-+3.16f, %+6.4f",
                                 0.000000000000000000001, 4798.3)
COMPARE_DEST_STRINGS_AND_RETURNS(test_844, "% -8.4f-j?e12l",
                                 10000000000000000000.000)
COMPARE_DEST_STRINGS_AND_RETURNS(test_845, "-j=%- 2.1fxz_{k}", 0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_846, "modq%+-1.2f.wfq% f-[]", -0.0, 967.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_847, "oadsp;d%+-3.0f", -1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_848, "z~x%-+9.13fc", 1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_849, ";[]czx;[]zx];[]%11.7f", 7009092.091)

// ================================DOUBLE (l don't change
// anything)=================================== Simple double
COMPARE_DEST_STRINGS_AND_RETURNS(test_850, "%lfabcdef", 1.5)
COMPARE_DEST_STRINGS_AND_RETURNS(test_851, "nfk%lfvjdas;", 1222.375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_852, "n9-%lf3fn4", -3.333)
COMPARE_DEST_STRINGS_AND_RETURNS(test_853, "qwe%lf, ", 0.000000000000000000001)
COMPARE_DEST_STRINGS_AND_RETURNS(test_854, "%lf-j?e12l",
                                 10000000000000000000.000)
COMPARE_DEST_STRINGS_AND_RETURNS(test_855, "-j=%lfxz_{k}", .0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_856, "modq%lf.wfq-[]", -0.000001)
COMPARE_DEST_STRINGS_AND_RETURNS(test_857, "oadsp;d%lf", -1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_858, "z~x%lfc", 1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_859, ";[]czx;[]zx];[]%lf", 7009092.91)

// Double with precision
COMPARE_DEST_STRINGS_AND_RETURNS(test_860, "%.7lfabcdef", 15.0001)
COMPARE_DEST_STRINGS_AND_RETURNS(test_861, "nfk%.3lfvjdas;", 122.2375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_862, "n9-%.4lf3fn4", -3333.33232)
COMPARE_DEST_STRINGS_AND_RETURNS(test_863, "qwe%.16lf, ",
                                 0.000000000000000000001)
COMPARE_DEST_STRINGS_AND_RETURNS(test_864, "%.4lf-j?e12l",
                                 10000000000000000000.000)
COMPARE_DEST_STRINGS_AND_RETURNS(test_865, "-j=%.1lfxz_{k}", 0.000001)
COMPARE_DEST_STRINGS_AND_RETURNS(test_866, "modq%.2lf.wfq-[]", -0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_867, "oadsp;d%.0lf", -1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_868, "z~x%.21lfc", 1.44)
COMPARE_DEST_STRINGS_AND_RETURNS(test_869, ";[]czx;[]zx];[]%.7lf", 7009092.91)

// Double with min length
COMPARE_DEST_STRINGS_AND_RETURNS(test_870, "%7lfabcdef", 1.5)
COMPARE_DEST_STRINGS_AND_RETURNS(test_871, "nfk%3lfvjdas;", 1222.375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_872, "n9-%4lf3fn4", -333.3)
COMPARE_DEST_STRINGS_AND_RETURNS(test_873, "qwe%16lf, ",
                                 0.000000000000000000001)
COMPARE_DEST_STRINGS_AND_RETURNS(test_874, "%4lf-j?e12l",
                                 10000000000000000000.000)
COMPARE_DEST_STRINGS_AND_RETURNS(test_875, "-j=%1lfxz_{k}", 0.0000004)
COMPARE_DEST_STRINGS_AND_RETURNS(test_876, "modq%2lf.wfq-[]", -.450)
COMPARE_DEST_STRINGS_AND_RETURNS(test_877, "oadsp;d%6lf", -13.4)
COMPARE_DEST_STRINGS_AND_RETURNS(test_878, "z~x%21lfc", 1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_879, ";[]czx;[]zx];[]%7lf", 700.909291)

// Double with min length left aligment
COMPARE_DEST_STRINGS_AND_RETURNS(test_880, "%-7lfabcdef", 1.5)
COMPARE_DEST_STRINGS_AND_RETURNS(test_881, "nfk%-3lfvjdas;", 12223.75)
COMPARE_DEST_STRINGS_AND_RETURNS(test_882, "n9-%-4lf3fn4", -33.33)
COMPARE_DEST_STRINGS_AND_RETURNS(test_883, "qwe%-16lf, ",
                                 0.000000000000000000001)
COMPARE_DEST_STRINGS_AND_RETURNS(test_884, "%-4lf-j?e12l",
                                 10000000000000000000.000)
COMPARE_DEST_STRINGS_AND_RETURNS(test_885, "-j=%-1lfxz_{k}", 0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_886, "modq%-2lf.wfq-[]", -0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_887, "oadsp;d%-6lf", -13.4)
COMPARE_DEST_STRINGS_AND_RETURNS(test_888, "z~x%-21lfc", 1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_889, ";[]czx;[]zx];[]%-7lf", 700909.291)

// Double with plus sign display
COMPARE_DEST_STRINGS_AND_RETURNS(test_890, "%+lfabcdef", 1.5)
COMPARE_DEST_STRINGS_AND_RETURNS(test_891, "nfk%+lfvjdas;", 1222.375)
COMPARE_DEST_STRINGS_AND_RETURNS(test_892, "n9-%+lf3fn4", -3.333)
COMPARE_DEST_STRINGS_AND_RETURNS(test_893, "qwe%+6lf, ",
                                 0.000000000000000000001)
COMPARE_DEST_STRINGS_AND_RETURNS(test_894, "%+lf-j?e12l",
                                 10000000000000000000.000)
COMPARE_DEST_STRINGS_AND_RETURNS(test_895, "-j=%+lfxz_{k}", 0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_896, "modq%+lf.wfq-[]", -0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_897, "oadsp;d%+lf", -13.4)
COMPARE_DEST_STRINGS_AND_RETURNS(test_898, "z~x%+lfc", 1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_899, ";[]czx;[]zx];[]%+lf", 70090.9291)

// Double with space instead of plus
COMPARE_DEST_STRINGS_AND_RETURNS(test_900, "% lfabcdef", 0.15)
COMPARE_DEST_STRINGS_AND_RETURNS(test_901, "nfk% lfvjdas;", 10222375.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_902, "n9-% lf3fn4", -3330.3)
COMPARE_DEST_STRINGS_AND_RETURNS(test_903, "qwe% 6lf, ",
                                 0.000000000000000000001)
COMPARE_DEST_STRINGS_AND_RETURNS(test_904, "% lf-j?e12l",
                                 10000000000000000000.000)
COMPARE_DEST_STRINGS_AND_RETURNS(test_905, "-j=% lfxz_{k}", .00)
COMPARE_DEST_STRINGS_AND_RETURNS(test_906, "modq% lf.wfq-[]", -.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_907, "oadsp;d% lf", -13.4)
COMPARE_DEST_STRINGS_AND_RETURNS(test_908, "z~x% lfc", 1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_909, ";[]czx;[]zx];[]% lf", .700909291)

// Double with all of advanced specs
COMPARE_DEST_STRINGS_AND_RETURNS(test_910, "%-+3.7lfabc%lfdef", 15.0, 44.044)
COMPARE_DEST_STRINGS_AND_RETURNS(test_911, "nfk%- 5.3lfvjd%-3lfas;", 122.02375,
                                 -192.071)
COMPARE_DEST_STRINGS_AND_RETURNS(test_912, "n9-%+-4.4lf3f%6lfn4", -333.03, 82.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_913, "qwe%-+3.16lf, %+6.4lf",
                                 0.000000000000000000001, 4798.3)
COMPARE_DEST_STRINGS_AND_RETURNS(test_914, "% -8.4lf-j?e12l",
                                 10000000000000000000.000)
COMPARE_DEST_STRINGS_AND_RETURNS(test_915, "-j=%- 2.1lfxz_{k}", 0.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_916, "modq%+-1.2lf.wfq% lf-[]", -0.0,
                                 967.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_917, "oadsp;d%+-3.0lf", -1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_918, "z~x%-+9.13lfc", 1.0)
COMPARE_DEST_STRINGS_AND_RETURNS(test_919, ";[]czx;[]zx];[]%11.7lf",
                                 7009092.091)

TCase *without_specs() {
  TCase *w_s = tcase_create("Without specifiers");
  tcase_add_test(w_s, test_0);
  tcase_add_test(w_s, test_1);
  tcase_add_test(w_s, test_2);
  tcase_add_test(w_s, test_3);
  tcase_add_test(w_s, test_4);
  tcase_add_test(w_s, test_5);
  tcase_add_test(w_s, test_6);
  tcase_add_test(w_s, test_7);
  tcase_add_test(w_s, test_8);
  tcase_add_test(w_s, test_9);
  tcase_add_test(w_s, test_10);
  tcase_add_test(w_s, test_11);
  tcase_add_test(w_s, test_12);
  tcase_add_test(w_s, test_13);
  tcase_add_test(w_s, test_14);
  tcase_add_test(w_s, test_15);
  tcase_add_test(w_s, test_16);
  tcase_add_test(w_s, test_17);
  tcase_add_test(w_s, test_18);
  tcase_add_test(w_s, test_19);
  return w_s;
}

TCase *decimal_tests() {
  TCase *d_t = tcase_create("Decimal tests");
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
  tcase_add_test(d_t, test_60);
  tcase_add_test(d_t, test_61);
  tcase_add_test(d_t, test_62);
  tcase_add_test(d_t, test_63);
  tcase_add_test(d_t, test_64);
  tcase_add_test(d_t, test_65);
  tcase_add_test(d_t, test_66);
  tcase_add_test(d_t, test_67);
  tcase_add_test(d_t, test_68);
  tcase_add_test(d_t, test_69);
  tcase_add_test(d_t, test_70);
  tcase_add_test(d_t, test_71);
  tcase_add_test(d_t, test_72);
  tcase_add_test(d_t, test_73);
  tcase_add_test(d_t, test_74);
  tcase_add_test(d_t, test_75);
  tcase_add_test(d_t, test_76);
  tcase_add_test(d_t, test_77);
  tcase_add_test(d_t, test_78);
  tcase_add_test(d_t, test_79);
  tcase_add_test(d_t, test_80);
  tcase_add_test(d_t, test_81);
  tcase_add_test(d_t, test_82);
  tcase_add_test(d_t, test_83);
  tcase_add_test(d_t, test_84);
  tcase_add_test(d_t, test_85);
  tcase_add_test(d_t, test_86);
  tcase_add_test(d_t, test_87);
  tcase_add_test(d_t, test_88);
  tcase_add_test(d_t, test_89);
  tcase_add_test(d_t, test_90);
  tcase_add_test(d_t, test_91);
  tcase_add_test(d_t, test_92);
  tcase_add_test(d_t, test_93);
  tcase_add_test(d_t, test_94);
  tcase_add_test(d_t, test_95);
  tcase_add_test(d_t, test_96);
  tcase_add_test(d_t, test_97);
  tcase_add_test(d_t, test_98);
  tcase_add_test(d_t, test_99);
  tcase_add_test(d_t, test_100);
  tcase_add_test(d_t, test_101);
  tcase_add_test(d_t, test_102);
  tcase_add_test(d_t, test_103);
  tcase_add_test(d_t, test_104);
  tcase_add_test(d_t, test_105);
  tcase_add_test(d_t, test_106);
  tcase_add_test(d_t, test_107);
  tcase_add_test(d_t, test_108);
  tcase_add_test(d_t, test_109);
  tcase_add_test(d_t, test_110);
  tcase_add_test(d_t, test_111);
  tcase_add_test(d_t, test_112);
  tcase_add_test(d_t, test_113);
  tcase_add_test(d_t, test_114);
  tcase_add_test(d_t, test_115);
  tcase_add_test(d_t, test_116);
  tcase_add_test(d_t, test_117);
  tcase_add_test(d_t, test_118);
  tcase_add_test(d_t, test_119);
  tcase_add_test(d_t, test_120);
  tcase_add_test(d_t, test_121);
  tcase_add_test(d_t, test_122);
  tcase_add_test(d_t, test_123);
  tcase_add_test(d_t, test_124);
  tcase_add_test(d_t, test_125);
  tcase_add_test(d_t, test_126);
  tcase_add_test(d_t, test_127);
  tcase_add_test(d_t, test_128);
  tcase_add_test(d_t, test_129);
  tcase_add_test(d_t, test_130);
  tcase_add_test(d_t, test_131);
  tcase_add_test(d_t, test_132);
  tcase_add_test(d_t, test_133);
  tcase_add_test(d_t, test_134);
  tcase_add_test(d_t, test_135);
  tcase_add_test(d_t, test_136);
  tcase_add_test(d_t, test_137);
  tcase_add_test(d_t, test_138);
  tcase_add_test(d_t, test_139);
  tcase_add_test(d_t, test_140);
  tcase_add_test(d_t, test_141);
  tcase_add_test(d_t, test_142);
  tcase_add_test(d_t, test_143);
  tcase_add_test(d_t, test_144);
  tcase_add_test(d_t, test_145);
  tcase_add_test(d_t, test_146);
  tcase_add_test(d_t, test_147);
  tcase_add_test(d_t, test_148);
  tcase_add_test(d_t, test_149);
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
  tcase_add_test(d_t, test_300);
  tcase_add_test(d_t, test_301);
  tcase_add_test(d_t, test_302);
  tcase_add_test(d_t, test_303);
  tcase_add_test(d_t, test_304);
  tcase_add_test(d_t, test_305);
  tcase_add_test(d_t, test_306);
  tcase_add_test(d_t, test_307);
  tcase_add_test(d_t, test_308);
  tcase_add_test(d_t, test_309);
  tcase_add_test(d_t, test_310);
  tcase_add_test(d_t, test_311);
  tcase_add_test(d_t, test_312);
  tcase_add_test(d_t, test_313);
  tcase_add_test(d_t, test_314);
  tcase_add_test(d_t, test_315);
  tcase_add_test(d_t, test_316);
  tcase_add_test(d_t, test_317);
  tcase_add_test(d_t, test_318);
  tcase_add_test(d_t, test_319);
  tcase_add_test(d_t, test_320);
  tcase_add_test(d_t, test_321);
  tcase_add_test(d_t, test_322);
  tcase_add_test(d_t, test_323);
  tcase_add_test(d_t, test_324);
  tcase_add_test(d_t, test_325);
  tcase_add_test(d_t, test_326);
  tcase_add_test(d_t, test_327);
  tcase_add_test(d_t, test_328);
  tcase_add_test(d_t, test_329);
  tcase_add_test(d_t, test_330);
  tcase_add_test(d_t, test_331);
  tcase_add_test(d_t, test_332);
  tcase_add_test(d_t, test_333);
  tcase_add_test(d_t, test_334);
  tcase_add_test(d_t, test_335);
  tcase_add_test(d_t, test_336);
  tcase_add_test(d_t, test_337);
  tcase_add_test(d_t, test_338);
  tcase_add_test(d_t, test_339);
  tcase_add_test(d_t, test_340);
  tcase_add_test(d_t, test_341);
  tcase_add_test(d_t, test_342);
  tcase_add_test(d_t, test_343);
  tcase_add_test(d_t, test_344);
  tcase_add_test(d_t, test_345);
  tcase_add_test(d_t, test_346);
  tcase_add_test(d_t, test_347);
  tcase_add_test(d_t, test_348);
  tcase_add_test(d_t, test_349);
  tcase_add_test(d_t, test_350);
  tcase_add_test(d_t, test_351);
  tcase_add_test(d_t, test_352);
  tcase_add_test(d_t, test_353);
  tcase_add_test(d_t, test_354);
  tcase_add_test(d_t, test_355);
  tcase_add_test(d_t, test_356);
  tcase_add_test(d_t, test_357);
  tcase_add_test(d_t, test_358);
  tcase_add_test(d_t, test_359);
  tcase_add_test(d_t, test_360);
  tcase_add_test(d_t, test_361);
  tcase_add_test(d_t, test_362);
  tcase_add_test(d_t, test_363);
  tcase_add_test(d_t, test_364);
  tcase_add_test(d_t, test_365);
  tcase_add_test(d_t, test_366);
  tcase_add_test(d_t, test_367);
  tcase_add_test(d_t, test_368);
  tcase_add_test(d_t, test_369);
  return d_t;
}

TCase *unsigned_tests() {
  TCase *u_t = tcase_create("Unsigned tests");
  tcase_add_test(u_t, test_370);
  tcase_add_test(u_t, test_371);
  tcase_add_test(u_t, test_372);
  tcase_add_test(u_t, test_373);
  tcase_add_test(u_t, test_374);
  tcase_add_test(u_t, test_375);
  tcase_add_test(u_t, test_376);
  tcase_add_test(u_t, test_377);
  tcase_add_test(u_t, test_378);
  tcase_add_test(u_t, test_379);
  tcase_add_test(u_t, test_380);
  tcase_add_test(u_t, test_381);
  tcase_add_test(u_t, test_382);
  tcase_add_test(u_t, test_383);
  tcase_add_test(u_t, test_384);
  tcase_add_test(u_t, test_385);
  tcase_add_test(u_t, test_386);
  tcase_add_test(u_t, test_387);
  tcase_add_test(u_t, test_388);
  tcase_add_test(u_t, test_389);
  tcase_add_test(u_t, test_390);
  tcase_add_test(u_t, test_391);
  tcase_add_test(u_t, test_392);
  tcase_add_test(u_t, test_393);
  tcase_add_test(u_t, test_394);
  tcase_add_test(u_t, test_395);
  tcase_add_test(u_t, test_396);
  tcase_add_test(u_t, test_397);
  tcase_add_test(u_t, test_398);
  tcase_add_test(u_t, test_399);
  tcase_add_test(u_t, test_400);
  tcase_add_test(u_t, test_401);
  tcase_add_test(u_t, test_402);
  tcase_add_test(u_t, test_403);
  tcase_add_test(u_t, test_404);
  tcase_add_test(u_t, test_405);
  tcase_add_test(u_t, test_406);
  tcase_add_test(u_t, test_407);
  tcase_add_test(u_t, test_408);
  tcase_add_test(u_t, test_409);
  tcase_add_test(u_t, test_410);
  tcase_add_test(u_t, test_411);
  tcase_add_test(u_t, test_412);
  tcase_add_test(u_t, test_413);
  tcase_add_test(u_t, test_414);
  tcase_add_test(u_t, test_415);
  tcase_add_test(u_t, test_416);
  tcase_add_test(u_t, test_417);
  tcase_add_test(u_t, test_418);
  tcase_add_test(u_t, test_419);
  tcase_add_test(u_t, test_420);
  tcase_add_test(u_t, test_421);
  tcase_add_test(u_t, test_422);
  tcase_add_test(u_t, test_423);
  tcase_add_test(u_t, test_424);
  tcase_add_test(u_t, test_425);
  tcase_add_test(u_t, test_426);
  tcase_add_test(u_t, test_427);
  tcase_add_test(u_t, test_428);
  tcase_add_test(u_t, test_429);
  tcase_add_test(u_t, test_430);
  tcase_add_test(u_t, test_431);
  tcase_add_test(u_t, test_432);
  tcase_add_test(u_t, test_433);
  tcase_add_test(u_t, test_434);
  tcase_add_test(u_t, test_435);
  tcase_add_test(u_t, test_436);
  tcase_add_test(u_t, test_437);
  tcase_add_test(u_t, test_438);
  tcase_add_test(u_t, test_439);
  tcase_add_test(u_t, test_440);
  tcase_add_test(u_t, test_441);
  tcase_add_test(u_t, test_442);
  tcase_add_test(u_t, test_443);
  tcase_add_test(u_t, test_444);
  tcase_add_test(u_t, test_445);
  tcase_add_test(u_t, test_446);
  tcase_add_test(u_t, test_447);
  tcase_add_test(u_t, test_448);
  tcase_add_test(u_t, test_449);
  tcase_add_test(u_t, test_450);
  tcase_add_test(u_t, test_451);
  tcase_add_test(u_t, test_452);
  tcase_add_test(u_t, test_453);
  tcase_add_test(u_t, test_454);
  tcase_add_test(u_t, test_455);
  tcase_add_test(u_t, test_456);
  tcase_add_test(u_t, test_457);
  tcase_add_test(u_t, test_458);
  tcase_add_test(u_t, test_459);
  tcase_add_test(u_t, test_460);
  tcase_add_test(u_t, test_461);
  tcase_add_test(u_t, test_462);
  tcase_add_test(u_t, test_463);
  tcase_add_test(u_t, test_464);
  tcase_add_test(u_t, test_465);
  tcase_add_test(u_t, test_466);
  tcase_add_test(u_t, test_467);
  tcase_add_test(u_t, test_468);
  tcase_add_test(u_t, test_469);
  tcase_add_test(u_t, test_470);
  tcase_add_test(u_t, test_471);
  tcase_add_test(u_t, test_472);
  tcase_add_test(u_t, test_473);
  tcase_add_test(u_t, test_474);
  tcase_add_test(u_t, test_475);
  tcase_add_test(u_t, test_476);
  tcase_add_test(u_t, test_477);
  tcase_add_test(u_t, test_478);
  tcase_add_test(u_t, test_479);
  tcase_add_test(u_t, test_480);
  tcase_add_test(u_t, test_481);
  tcase_add_test(u_t, test_482);
  tcase_add_test(u_t, test_483);
  tcase_add_test(u_t, test_484);
  tcase_add_test(u_t, test_485);
  tcase_add_test(u_t, test_486);
  tcase_add_test(u_t, test_487);
  tcase_add_test(u_t, test_488);
  tcase_add_test(u_t, test_489);
  tcase_add_test(u_t, test_490);
  tcase_add_test(u_t, test_491);
  tcase_add_test(u_t, test_492);
  tcase_add_test(u_t, test_493);
  tcase_add_test(u_t, test_494);
  tcase_add_test(u_t, test_495);
  tcase_add_test(u_t, test_496);
  tcase_add_test(u_t, test_497);
  tcase_add_test(u_t, test_498);
  tcase_add_test(u_t, test_499);
  tcase_add_test(u_t, test_500);
  tcase_add_test(u_t, test_501);
  tcase_add_test(u_t, test_502);
  tcase_add_test(u_t, test_503);
  tcase_add_test(u_t, test_504);
  tcase_add_test(u_t, test_505);
  tcase_add_test(u_t, test_506);
  tcase_add_test(u_t, test_507);
  tcase_add_test(u_t, test_508);
  tcase_add_test(u_t, test_509);
  tcase_add_test(u_t, test_510);
  tcase_add_test(u_t, test_511);
  tcase_add_test(u_t, test_512);
  tcase_add_test(u_t, test_513);
  tcase_add_test(u_t, test_514);
  tcase_add_test(u_t, test_515);
  tcase_add_test(u_t, test_516);
  tcase_add_test(u_t, test_517);
  tcase_add_test(u_t, test_518);
  tcase_add_test(u_t, test_519);
  tcase_add_test(u_t, test_520);
  tcase_add_test(u_t, test_521);
  tcase_add_test(u_t, test_522);
  tcase_add_test(u_t, test_523);
  tcase_add_test(u_t, test_524);
  tcase_add_test(u_t, test_525);
  tcase_add_test(u_t, test_526);
  tcase_add_test(u_t, test_527);
  tcase_add_test(u_t, test_528);
  tcase_add_test(u_t, test_529);
  tcase_add_test(u_t, test_530);
  tcase_add_test(u_t, test_531);
  tcase_add_test(u_t, test_532);
  tcase_add_test(u_t, test_533);
  tcase_add_test(u_t, test_534);
  tcase_add_test(u_t, test_535);
  tcase_add_test(u_t, test_536);
  tcase_add_test(u_t, test_537);
  tcase_add_test(u_t, test_538);
  tcase_add_test(u_t, test_539);
  tcase_add_test(u_t, test_540);
  tcase_add_test(u_t, test_541);
  tcase_add_test(u_t, test_542);
  tcase_add_test(u_t, test_543);
  tcase_add_test(u_t, test_544);
  tcase_add_test(u_t, test_545);
  tcase_add_test(u_t, test_546);
  tcase_add_test(u_t, test_547);
  tcase_add_test(u_t, test_548);
  tcase_add_test(u_t, test_549);
  tcase_add_test(u_t, test_550);
  tcase_add_test(u_t, test_551);
  tcase_add_test(u_t, test_552);
  tcase_add_test(u_t, test_553);
  tcase_add_test(u_t, test_554);
  tcase_add_test(u_t, test_555);
  tcase_add_test(u_t, test_556);
  tcase_add_test(u_t, test_557);
  tcase_add_test(u_t, test_558);
  tcase_add_test(u_t, test_559);
  tcase_add_test(u_t, test_560);
  tcase_add_test(u_t, test_561);
  tcase_add_test(u_t, test_562);
  tcase_add_test(u_t, test_563);
  tcase_add_test(u_t, test_564);
  tcase_add_test(u_t, test_565);
  tcase_add_test(u_t, test_566);
  tcase_add_test(u_t, test_567);
  tcase_add_test(u_t, test_568);
  tcase_add_test(u_t, test_569);
  tcase_add_test(u_t, test_570);
  tcase_add_test(u_t, test_571);
  tcase_add_test(u_t, test_572);
  tcase_add_test(u_t, test_573);
  tcase_add_test(u_t, test_574);
  tcase_add_test(u_t, test_575);
  tcase_add_test(u_t, test_576);
  tcase_add_test(u_t, test_577);
  tcase_add_test(u_t, test_578);
  tcase_add_test(u_t, test_579);
  tcase_add_test(u_t, test_580);
  tcase_add_test(u_t, test_581);
  tcase_add_test(u_t, test_582);
  tcase_add_test(u_t, test_583);
  tcase_add_test(u_t, test_584);
  tcase_add_test(u_t, test_585);
  tcase_add_test(u_t, test_586);
  tcase_add_test(u_t, test_587);
  tcase_add_test(u_t, test_588);
  tcase_add_test(u_t, test_589);
  tcase_add_test(u_t, test_590);
  tcase_add_test(u_t, test_591);
  tcase_add_test(u_t, test_592);
  tcase_add_test(u_t, test_593);
  tcase_add_test(u_t, test_594);
  tcase_add_test(u_t, test_595);
  tcase_add_test(u_t, test_596);
  tcase_add_test(u_t, test_597);
  tcase_add_test(u_t, test_598);
  tcase_add_test(u_t, test_599);
  tcase_add_test(u_t, test_600);
  tcase_add_test(u_t, test_601);
  tcase_add_test(u_t, test_602);
  tcase_add_test(u_t, test_603);
  tcase_add_test(u_t, test_604);
  tcase_add_test(u_t, test_605);
  tcase_add_test(u_t, test_606);
  tcase_add_test(u_t, test_607);
  tcase_add_test(u_t, test_608);
  tcase_add_test(u_t, test_609);
  tcase_add_test(u_t, test_610);
  tcase_add_test(u_t, test_611);
  tcase_add_test(u_t, test_612);
  tcase_add_test(u_t, test_613);
  tcase_add_test(u_t, test_614);
  tcase_add_test(u_t, test_615);
  tcase_add_test(u_t, test_616);
  tcase_add_test(u_t, test_617);
  tcase_add_test(u_t, test_618);
  tcase_add_test(u_t, test_619);

  return u_t;
}

TCase *char_tests() {
  TCase *c_t = tcase_create("Char tests");
  tcase_add_test(c_t, test_620);
  tcase_add_test(c_t, test_621);
  tcase_add_test(c_t, test_622);
  tcase_add_test(c_t, test_623);
  tcase_add_test(c_t, test_624);
  tcase_add_test(c_t, test_625);
  tcase_add_test(c_t, test_626);
  tcase_add_test(c_t, test_627);
  tcase_add_test(c_t, test_628);
  tcase_add_test(c_t, test_629);
  tcase_add_test(c_t, test_630);
  tcase_add_test(c_t, test_631);
  tcase_add_test(c_t, test_632);
  tcase_add_test(c_t, test_633);
  tcase_add_test(c_t, test_634);
  tcase_add_test(c_t, test_635);
  tcase_add_test(c_t, test_636);
  tcase_add_test(c_t, test_637);
  tcase_add_test(c_t, test_638);
  tcase_add_test(c_t, test_639);
  tcase_add_test(c_t, test_640);
  tcase_add_test(c_t, test_641);
  tcase_add_test(c_t, test_642);
  tcase_add_test(c_t, test_643);
  tcase_add_test(c_t, test_644);
  tcase_add_test(c_t, test_645);
  tcase_add_test(c_t, test_646);
  tcase_add_test(c_t, test_647);
  tcase_add_test(c_t, test_648);
  tcase_add_test(c_t, test_649);
  tcase_add_test(c_t, test_650);
  tcase_add_test(c_t, test_651);
  tcase_add_test(c_t, test_652);
  tcase_add_test(c_t, test_653);
  tcase_add_test(c_t, test_654);
  tcase_add_test(c_t, test_655);
  tcase_add_test(c_t, test_656);
  tcase_add_test(c_t, test_657);
  tcase_add_test(c_t, test_658);
  tcase_add_test(c_t, test_659);
  tcase_add_test(c_t, test_660);
  tcase_add_test(c_t, test_661);
  tcase_add_test(c_t, test_662);
  tcase_add_test(c_t, test_663);
  tcase_add_test(c_t, test_664);
  tcase_add_test(c_t, test_665);
  tcase_add_test(c_t, test_666);
  tcase_add_test(c_t, test_667);
  tcase_add_test(c_t, test_668);
  tcase_add_test(c_t, test_669);
  tcase_add_test(c_t, test_670);
  tcase_add_test(c_t, test_671);
  tcase_add_test(c_t, test_672);
  tcase_add_test(c_t, test_673);
  tcase_add_test(c_t, test_674);
  tcase_add_test(c_t, test_675);
  tcase_add_test(c_t, test_676);
  tcase_add_test(c_t, test_677);
  tcase_add_test(c_t, test_678);
  tcase_add_test(c_t, test_679);
  return c_t;
}

TCase *string_tests() {
  TCase *s_t = tcase_create("String tests");

  tcase_add_test(s_t, test_680);
  tcase_add_test(s_t, test_681);
  tcase_add_test(s_t, test_682);
  tcase_add_test(s_t, test_683);
  tcase_add_test(s_t, test_684);
  tcase_add_test(s_t, test_685);
  tcase_add_test(s_t, test_686);
  tcase_add_test(s_t, test_687);
  tcase_add_test(s_t, test_688);
  tcase_add_test(s_t, test_689);
  tcase_add_test(s_t, test_690);
  tcase_add_test(s_t, test_691);
  tcase_add_test(s_t, test_692);
  tcase_add_test(s_t, test_693);
  tcase_add_test(s_t, test_694);
  tcase_add_test(s_t, test_695);
  tcase_add_test(s_t, test_696);
  tcase_add_test(s_t, test_697);
  tcase_add_test(s_t, test_698);
  tcase_add_test(s_t, test_699);
  tcase_add_test(s_t, test_700);
  tcase_add_test(s_t, test_701);
  tcase_add_test(s_t, test_702);
  tcase_add_test(s_t, test_703);
  tcase_add_test(s_t, test_704);
  tcase_add_test(s_t, test_705);
  tcase_add_test(s_t, test_706);
  tcase_add_test(s_t, test_707);
  tcase_add_test(s_t, test_708);
  tcase_add_test(s_t, test_709);
  tcase_add_test(s_t, test_710);
  tcase_add_test(s_t, test_711);
  tcase_add_test(s_t, test_712);
  tcase_add_test(s_t, test_713);
  tcase_add_test(s_t, test_714);
  tcase_add_test(s_t, test_715);
  tcase_add_test(s_t, test_716);
  tcase_add_test(s_t, test_717);
  tcase_add_test(s_t, test_718);
  tcase_add_test(s_t, test_719);
  tcase_add_test(s_t, test_720);
  tcase_add_test(s_t, test_721);
  tcase_add_test(s_t, test_722);
  tcase_add_test(s_t, test_723);
  tcase_add_test(s_t, test_724);
  tcase_add_test(s_t, test_725);
  tcase_add_test(s_t, test_726);
  tcase_add_test(s_t, test_727);
  tcase_add_test(s_t, test_728);
  tcase_add_test(s_t, test_729);
  tcase_add_test(s_t, test_730);
  tcase_add_test(s_t, test_731);
  tcase_add_test(s_t, test_732);
  tcase_add_test(s_t, test_733);
  tcase_add_test(s_t, test_734);
  tcase_add_test(s_t, test_735);
  tcase_add_test(s_t, test_736);
  tcase_add_test(s_t, test_737);
  tcase_add_test(s_t, test_738);
  tcase_add_test(s_t, test_739);
  tcase_add_test(s_t, test_740);
  tcase_add_test(s_t, test_741);
  tcase_add_test(s_t, test_742);
  tcase_add_test(s_t, test_743);
  tcase_add_test(s_t, test_744);
  tcase_add_test(s_t, test_745);
  tcase_add_test(s_t, test_746);
  tcase_add_test(s_t, test_747);
  tcase_add_test(s_t, test_748);
  tcase_add_test(s_t, test_749);
  tcase_add_test(s_t, test_750);
  tcase_add_test(s_t, test_751);
  tcase_add_test(s_t, test_752);
  tcase_add_test(s_t, test_753);
  tcase_add_test(s_t, test_754);
  tcase_add_test(s_t, test_755);
  tcase_add_test(s_t, test_756);
  tcase_add_test(s_t, test_757);
  tcase_add_test(s_t, test_758);
  tcase_add_test(s_t, test_759);
  tcase_add_test(s_t, test_760);
  tcase_add_test(s_t, test_761);
  tcase_add_test(s_t, test_762);
  tcase_add_test(s_t, test_763);
  tcase_add_test(s_t, test_764);
  tcase_add_test(s_t, test_765);
  tcase_add_test(s_t, test_766);
  tcase_add_test(s_t, test_767);
  tcase_add_test(s_t, test_768);
  tcase_add_test(s_t, test_769);
  tcase_add_test(s_t, test_770);
  tcase_add_test(s_t, test_771);
  tcase_add_test(s_t, test_772);
  tcase_add_test(s_t, test_773);
  tcase_add_test(s_t, test_774);
  tcase_add_test(s_t, test_775);
  tcase_add_test(s_t, test_776);
  tcase_add_test(s_t, test_777);
  tcase_add_test(s_t, test_778);
  tcase_add_test(s_t, test_779);

  return s_t;
}

TCase *double_tests() {
  TCase *d_t = tcase_create("Double tests");

  tcase_add_test(d_t, test_780);
  tcase_add_test(d_t, test_781);
  tcase_add_test(d_t, test_782);
  tcase_add_test(d_t, test_783);
  tcase_add_test(d_t, test_784);
  tcase_add_test(d_t, test_785);
  tcase_add_test(d_t, test_786);
  tcase_add_test(d_t, test_787);
  tcase_add_test(d_t, test_788);
  tcase_add_test(d_t, test_789);
  tcase_add_test(d_t, test_790);
  tcase_add_test(d_t, test_791);
  tcase_add_test(d_t, test_792);
  tcase_add_test(d_t, test_793);
  tcase_add_test(d_t, test_794);
  tcase_add_test(d_t, test_795);
  tcase_add_test(d_t, test_796);
  tcase_add_test(d_t, test_797);
  tcase_add_test(d_t, test_798);
  tcase_add_test(d_t, test_799);
  tcase_add_test(d_t, test_800);
  tcase_add_test(d_t, test_801);
  tcase_add_test(d_t, test_802);
  tcase_add_test(d_t, test_803);
  tcase_add_test(d_t, test_804);
  tcase_add_test(d_t, test_805);
  tcase_add_test(d_t, test_806);
  tcase_add_test(d_t, test_807);
  tcase_add_test(d_t, test_808);
  tcase_add_test(d_t, test_809);
  tcase_add_test(d_t, test_810);
  tcase_add_test(d_t, test_811);
  tcase_add_test(d_t, test_812);
  tcase_add_test(d_t, test_813);
  tcase_add_test(d_t, test_814);
  tcase_add_test(d_t, test_815);
  tcase_add_test(d_t, test_816);
  tcase_add_test(d_t, test_817);
  tcase_add_test(d_t, test_818);
  tcase_add_test(d_t, test_819);
  tcase_add_test(d_t, test_820);
  tcase_add_test(d_t, test_821);
  tcase_add_test(d_t, test_822);
  tcase_add_test(d_t, test_823);
  tcase_add_test(d_t, test_824);
  tcase_add_test(d_t, test_825);
  tcase_add_test(d_t, test_826);
  tcase_add_test(d_t, test_827);
  tcase_add_test(d_t, test_828);
  tcase_add_test(d_t, test_829);
  tcase_add_test(d_t, test_830);
  tcase_add_test(d_t, test_831);
  tcase_add_test(d_t, test_832);
  tcase_add_test(d_t, test_833);
  tcase_add_test(d_t, test_834);
  tcase_add_test(d_t, test_835);
  tcase_add_test(d_t, test_836);
  tcase_add_test(d_t, test_837);
  tcase_add_test(d_t, test_838);
  tcase_add_test(d_t, test_839);
  tcase_add_test(d_t, test_840);
  tcase_add_test(d_t, test_841);
  tcase_add_test(d_t, test_842);
  tcase_add_test(d_t, test_843);
  tcase_add_test(d_t, test_844);
  tcase_add_test(d_t, test_845);
  tcase_add_test(d_t, test_846);
  tcase_add_test(d_t, test_847);
  tcase_add_test(d_t, test_848);
  tcase_add_test(d_t, test_849);
  tcase_add_test(d_t, test_850);
  tcase_add_test(d_t, test_851);
  tcase_add_test(d_t, test_852);
  tcase_add_test(d_t, test_853);
  tcase_add_test(d_t, test_854);
  tcase_add_test(d_t, test_855);
  tcase_add_test(d_t, test_856);
  tcase_add_test(d_t, test_857);
  tcase_add_test(d_t, test_858);
  tcase_add_test(d_t, test_859);
  tcase_add_test(d_t, test_860);
  tcase_add_test(d_t, test_861);
  tcase_add_test(d_t, test_862);
  tcase_add_test(d_t, test_863);
  tcase_add_test(d_t, test_864);
  tcase_add_test(d_t, test_865);
  tcase_add_test(d_t, test_866);
  tcase_add_test(d_t, test_867);
  tcase_add_test(d_t, test_868);
  tcase_add_test(d_t, test_869);
  tcase_add_test(d_t, test_870);
  tcase_add_test(d_t, test_871);
  tcase_add_test(d_t, test_872);
  tcase_add_test(d_t, test_873);
  tcase_add_test(d_t, test_874);
  tcase_add_test(d_t, test_875);
  tcase_add_test(d_t, test_876);
  tcase_add_test(d_t, test_877);
  tcase_add_test(d_t, test_878);
  tcase_add_test(d_t, test_879);
  tcase_add_test(d_t, test_880);
  tcase_add_test(d_t, test_881);
  tcase_add_test(d_t, test_882);
  tcase_add_test(d_t, test_883);
  tcase_add_test(d_t, test_884);
  tcase_add_test(d_t, test_885);
  tcase_add_test(d_t, test_886);
  tcase_add_test(d_t, test_887);
  tcase_add_test(d_t, test_888);
  tcase_add_test(d_t, test_889);
  tcase_add_test(d_t, test_890);
  tcase_add_test(d_t, test_891);
  tcase_add_test(d_t, test_892);
  tcase_add_test(d_t, test_893);
  tcase_add_test(d_t, test_894);
  tcase_add_test(d_t, test_895);
  tcase_add_test(d_t, test_896);
  tcase_add_test(d_t, test_897);
  tcase_add_test(d_t, test_898);
  tcase_add_test(d_t, test_899);
  tcase_add_test(d_t, test_900);
  tcase_add_test(d_t, test_901);
  tcase_add_test(d_t, test_902);
  tcase_add_test(d_t, test_903);
  tcase_add_test(d_t, test_904);
  tcase_add_test(d_t, test_905);
  tcase_add_test(d_t, test_906);
  tcase_add_test(d_t, test_907);
  tcase_add_test(d_t, test_908);
  tcase_add_test(d_t, test_909);
  tcase_add_test(d_t, test_910);
  tcase_add_test(d_t, test_911);
  tcase_add_test(d_t, test_912);
  tcase_add_test(d_t, test_913);
  tcase_add_test(d_t, test_914);
  tcase_add_test(d_t, test_915);
  tcase_add_test(d_t, test_916);
  tcase_add_test(d_t, test_917);
  tcase_add_test(d_t, test_918);
  tcase_add_test(d_t, test_919);

  return d_t;
}

Suite *sprintf_suite() {
  Suite *s = suite_create("SPRINTF");
  suite_add_tcase(s, without_specs());
  suite_add_tcase(s, decimal_tests());
  suite_add_tcase(s, unsigned_tests());
  suite_add_tcase(s, char_tests());
  suite_add_tcase(s, string_tests());
  suite_add_tcase(s, double_tests());

  return s;
}