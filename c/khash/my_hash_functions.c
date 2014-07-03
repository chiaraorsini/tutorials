

#include "khash.h"
#include <stdio.h>
#include <stdint.h>




typedef struct struct_ipv4_prefix {
  uint32_t address;
  uint8_t length; // max = /32 = 2**5
} ipv4_prefix;

typedef struct struct_ipv6_prefix {
  unsigned __int128 address;
  uint8_t length; // max = /128 = 2**7
} ipv_prefix;



typedef struct struct_prova {
  int a;
  int b;
} prova;

KHASH_MAP_INIT_STR(test_prova, prova*)



int main() {
  printf("%lu\n", sizeof(unsigned __int128));
  printf("%lu\n",UINTMAX_MAX);

  int ret, is_missing;
  khiter_t k;
  khash_t(test_prova) *h = kh_init(test_prova);
  prova * p;

  printf("Size: %d\n", kh_size(h));
  // inserting values  
  k = kh_put(test_prova, h, "provatest_prova", &ret);
  p = (prova*) malloc(sizeof(prova));
  p->a = 1;
  p->b = 2;
  kh_value(h, k) = p; 
  printf("Size: %d\n", kh_size(h));

  k = kh_put(test_prova, h, "provatest_prova3", &ret);
  p = (prova*) malloc(sizeof(prova));
  p->a = 2;
  p->b = 1;
  kh_value(h, k) = p; 
  printf("Size: %d\n", kh_size(h));

  // printing current content
  for (k = kh_begin(h); k != kh_end(h); ++k) {
    if (kh_exist(h, k)){
      p = kh_value(h, k);
      printf("%d -> %d %d\n", k, p->a, p->b);
    }
  }

  // requesting existing content
  k = kh_get(test_prova, h, "provatest_prova");
  is_missing = (k == kh_end(h));
  if (is_missing) {
    printf("missing\n");
  }
  else {
    printf("not missing\n");
  }

  // requesting non existing content
  k = kh_get(test_prova, h, "proafmvatest_prova");
  is_missing = (k == kh_end(h));
  if (is_missing) {
    printf("missing\n");
  }
  else {
    printf("not missing\n");
  }

  // deleting content
  printf("deleting content\n");
  k = kh_get(test_prova, h, "provatest_prova");
  p = kh_value(h, k);
  free(p);
  kh_del(test_prova, h, k);
  printf("Size: %d\n", kh_size(h));


  // printing current content
  for (k = kh_begin(h); k != kh_end(h); ++k) {
    if (kh_exist(h, k)){
      p = kh_value(h, k);
      printf("%d -> %d %d\n", k, p->a, p->b);
    }
  }
  printf("Size: %d\n", kh_size(h));

  // free values
  printf("destroying hash values - because they are malloc'd\n");
  for (k = kh_begin(h); k != kh_end(h); ++k) {
    if (kh_exist(h, k)){
      p = kh_value(h, k);
      free(p);
    }
  }
  printf("Size: %d\n", kh_size(h));

  // free hash  
  printf("destroying hash\n");
  kh_destroy(test_prova, h);
  return 0;
}

