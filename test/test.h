/* 2016-12-02 */

#ifdef ZTEST_PRINT
#include <iostream>
#endif  // ZTEST_PRINT

namespace ztest {

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void colored_print(int attr, int fore_color, int back_color, 
                   const char* fmt, ...) {
  va_list args;
  va_start(args, fmt);
  printf("%c[%d;%d;%dm", 0x1B, attr, 30 + fore_color, 40 + back_color);
  printf("%s", fmt);
  printf("%c[%d;%d;%dm", 0x1B, 1, 7, 0);
  va_end(args);
}

void expect(bool expr, const char* expr_str, 
            const char* file, int line) {
  if (!expr) {
    colored_print(1, 3, 0, "[ WARNING ]");
    printf(" %s [%d]: %s\n", file, line, expr_str);
  }
}

void require(bool expr, const char* expr_str, 
             const char* file, int line) {
  if (!expr) {
    colored_print(1, 1, 0, "[  ERROR  ]");
    printf(" %s [%d]: %s\n", file, line, expr_str);
    exit(1);
  }
}

template <typename, typename>
struct is_same {
  static void expect(const char* Tp1_str, const char* Tp2_str, 
                     const char* file, int line) {
    colored_print(1, 3, 0, "[ WARNING ]");
    print(Tp1_str, Tp2_str, file, line);
  }
  static void require(const char* Tp1_str, const char* Tp2_str, 
                      const char* file, int line) {
    colored_print(1, 1, 0, "[  ERROR  ]");
    print(Tp1_str, Tp2_str, file, line);
    exit(1);
  }

private:
  static void print(const char* Tp1_str, const char* Tp2_str, 
                    const char* file, int line) {
    printf(" %s [%d]: %s is not the same type as %s\n", 
           file, line, Tp1_str, Tp2_str);
  }
};

template <typename Tp>
struct is_same<Tp, Tp> {
   static void expect(const char*, const char*, const char*, int) {}
  static void require(const char*, const char*, const char*, int) {}
};


template <typename Base, typename Derived, 
          bool = __is_base_of(Base, Derived)>
struct is_base_of;

template <typename Base, typename Derived>
struct is_base_of<Base, Derived, false> {
  static void expect(const char* Base_str, const char* Derived_str,
                     const char* file, int line) {
    colored_print(1, 3, 0, "[ WARNING ]");
    print(Base_str, Derived_str, file, line);
  }
  static void require(const char* Base_str, const char* Derived_str,
                      const char* file, int line) {
    colored_print(1, 1, 0, "[  ERROR  ]");
    print(Base_str, Derived_str, file, line);
    exit(1);
  }

private:
  static void print(const char* Base_str, const char* Derived_str,
                    const char* file, int line) {
    printf(" %s [%d]: %s is not the base of %s\n",
           file, line, Base_str, Derived_str);
  }
};

template <typename Base, typename Derived>
struct is_base_of<Base, Derived, true> {
  static void expect(const char*, const char*, const char*, int) {}
  static void require(const char*, const char*, const char*, int) {}
};

}  // namespace ztest

#define EXPECT(expr) ztest::expect(expr, #expr, __FILE__, __LINE__)
#define REQUIRE(expr) ztest::require(expr, #expr, __FILE__, __LINE__)

#define EXPECT_SAME(Tp1, Tp2) \
  ztest::is_same<Tp1, Tp2>::expect(#Tp1, #Tp2, __FILE__, __LINE__)
#define REQUIRE_SAME(Tp1, Tp2) \
  ztest::is_same<Tp1, Tp2>::require(#Tp1, #Tp2, __FILE__, __LINE__)

#define EXPECT_BASE_OF(Base, Derived) \
  ztest::is_base_of<Base, Derived>::expect(#Base, #Derived, __FILE__, __LINE__)
#define REQUIRE_BASE_OF(Base, Derived) \
  ztest::is_base_of<Base, Derived>::require( \
    #Base, #Derived, __FILE__, __LINE__)
