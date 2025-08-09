#include <iostream>

#include <stopwatch.h>
#include "arraydyn.h"

int main() {
  const size_t d1c = 8;
  const size_t d2c = 9;
  const size_t d3c = 10;
  typedef int D3Array[d1c][d2c][d3c];

  size_t d1 = d1c;
  size_t d2 = d2c;
  size_t d3 = d3c;
  ArrayDyn<int, 3> arr_dyn(d1,d2,d3);

  D3Array& arr_stat = * (D3Array*) &arr_dyn[0][0][0];
  //D3Array& arr_stat = * (D3Array*) (void*) arr_dyn;

  // Test 1: Funktion
  for (int i1 = 0; i1 < d1; ++i1) {
    for (int i2 = 0; i2 < d2; ++i2) {
      for (int i3 = 0; i3 < d3; ++i3) {
        if (&arr_dyn[i1][i2][i3] != &arr_stat[i1][i2][i3]) {
          std::cout <<   "i1 = " << i1
                    << ", i2 = " << i2
                    << ", i3 = " << i3 << std::endl;
          return 1;
        }
      }
    }
  }
  printf("Test 1: check\n");

  // Test 2: Performance
  StopWatch s;
  memset(arr_stat, 0, sizeof(D3Array));
  s.start();
  for (int n = 0; n < 1000000; ++n) {
    for (int i1 = 0; i1 < d1; ++i1) {
      for (int i2 = 0; i2 < d2; ++i2) {
        for (int i3 = 0; i3 < d3; ++i3) {
          arr_stat[i1][i2][i3] += 1;
        }
      }
    }
  }
  s.stop();
  printf("Laufzeit statisches Array: %f sec\n", s.getElapsedTimeSecs());

  memset(arr_stat, 0, sizeof(D3Array));
  s.start();
  for (int n = 0; n < 1000000; ++n) {
    for (int i1 = 0; i1 < d1; ++i1) {
      for (int i2 = 0; i2 < d2; ++i2) {
        for (int i3 = 0; i3 < d3; ++i3) {
          arr_dyn[i1][i2][i3] += 1;
        }
      }
    }
  }
  s.stop();
  printf("Laufzeit dynamisches Array: %f sec\n", s.getElapsedTimeSecs());

  {
    ArrayDyn<int,4> a4(4,5,6,7);
    int* a4_base = a4;
    std::cout << "a4_base = " << a4_base << std::endl;
    std::cout << "&a4[0][0][0][0] = " << &a4[0][0][0][0] << std::endl;
    std::cout << "&a4[0][0][0][1] = " << &a4[0][0][0][1] << std::endl;
    std::cout << "&a4[0][0][0][5] = " << &a4[0][0][0][5] << std::endl;
    std::cout << "&a4[0][0][0][6] = " << &a4[0][0][0][6] << std::endl;
    std::cout << "-----" << std::endl;
    std::cout << "&a4[0][0][1][0] = " << &a4[0][0][1][0] << std::endl;
    std::cout << "&a4[0][0][1][1] = " << &a4[0][0][1][1] << std::endl;
    std::cout << "&a4[0][0][1][5] = " << &a4[0][0][1][5] << std::endl;
    std::cout << "&a4[0][0][1][6] = " << &a4[0][0][1][6] << std::endl;
  }

  std::cout << "----------------------------------------" << std::endl;
  
  {
    ArrayDyn<char,4> a4(4,5,6,7);
    std::cout << "&a4[0][0][0][0] = " << (void*) &a4[0][0][0][0] << std::endl;
    std::cout << "&a4[0][0][0][1] = " << (void*) &a4[0][0][0][1] << std::endl;
    std::cout << "&a4[0][0][0][5] = " << (void*) &a4[0][0][0][5] << std::endl;
    std::cout << "&a4[0][0][0][6] = " << (void*) &a4[0][0][0][6] << std::endl;
    std::cout << "-----" << std::endl;
    std::cout << "&a4[0][0][1][0] = " << (void*) &a4[0][0][1][0] << std::endl;
    std::cout << "&a4[0][0][1][1] = " << (void*) &a4[0][0][1][1] << std::endl;
    std::cout << "&a4[0][0][1][5] = " << (void*) &a4[0][0][1][5] << std::endl;
    std::cout << "&a4[0][0][1][6] = " << (void*) &a4[0][0][1][6] << std::endl;
  }

  std::cout << "----------------------------------------" << std::endl;

  {
    size_t d1 = 4;

    ArrayDyn<char, 1> a1(d1);
    for (int i = 0; i < d1; ++i) {
      printf("&a1[%d] = %p\n", i, &a1[i]);
    }
  }

  std::cout << "----------------------------------------" << std::endl;

  {
    size_t d21 = 3;
    size_t d22 = 3;

    ArrayDyn<int, 2> a2(d21, d22);
    for (int i = 0; i < d21; ++i) {
      for (int j = 0; j < d22; ++j) {
        printf("&a2[%d][%d] = %p\n", i, j, &a2[i][j]);
      }
    }
  }

  return 0;
}

