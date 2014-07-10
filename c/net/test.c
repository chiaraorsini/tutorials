

#include <stdio.h>
#include <limits.h>
#include <inttypes.h>


#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h> /* superset of previous */



/* void print_bits(unsigned int x){ */
/*   unsigned int size = sizeof(unsigned int); */
/*   printf("%u\n", size); */
/*   unsigned int maxPow = 1<<(size*CHAR_BIT-1); */
/*   printf("MAX POW : %u\n",maxPow); */
/*   int i=0; */
/*   int j=1; */
/*   const int group_size = 4; */
/*   for(;i<size*8;++i, j++){ */
/*     // print last bit and shift left. */
/*     printf("%u",x&maxPow ? 1 : 0); */
/*     x = x<<1; */
/*     if(j==group_size){ */
/*       j = 0; */
/*       printf(" "); */
/*     } */
/*   } */
/*   printf("\n"); */
/* } */





/* void print_bits(unsigned int x){ */
/*   unsigned int size = sizeof(unsigned int); */
/*   printf("%u\n", size); */
/*   unsigned int maxPow = 1<<(size*CHAR_BIT-1); */
/*   printf("MAX POW : %u\n",maxPow); */
/*   int i=0; */
/*   int j=1; */
/*   const int group_size = 4; */
/*   for(;i<size*8;++i, j++){ */
/*     // print last bit and shift left. */
/*     printf("%u",x&maxPow ? 1 : 0); */
/*     x = x<<1; */
/*     if(j==group_size){ */
/*       j = 0; */
/*       printf(" "); */
/*     } */
/*   } */
/*   printf("\n"); */
/* } */

/* void print_64_bits(unsigned long x){ */
/*   unsigned long size = sizeof(unsigned long); */
/*   printf("%lu\n", size); */
/*   unsigned long maxPow = 1<<(size*CHAR_BIT-1); */
/*   printf("MAX POW : %lu\n",maxPow); */
/*   int i=0; */
/*   int j=1; */
/*   const int group_size = 4; */
/*   for(;i<size*8;++i, j++){ */
/*     // print last bit and shift left. */
/*     printf("%u",x&maxPow ? 1 : 0); */
/*     x = x<<1; */
/*     if(j==group_size){ */
/*       j = 0; */
/*       printf(" "); */
/*     } */
/*   } */
/*   printf("\n"); */
/* } */

/* void show_mem_rep(char *start, int n)  */
/* { */
/*     int i; */
/*     for (i = 0; i < n; i++) { */
/*       //         printf(" %.2x", start[i]); */
/*       printf(" %02X", (int)start[i]); */
/*     } */
/*     printf("\n"); */

/*     uint8_t x;  */
/*     uint8_t k; */
/*     for (i = 0; i < n; i++) { */
/*       x = start[i]; */
/*       for(k =0; k<8; k++){ */
/* 	printf("%u",x&128 ? 1 : 0); */
/*       	x = x<<1; */
/*       } */
/*       printf(" "); */
/*     } */
/*     printf("\n"); */
/* } */



void printbinary(uint32_t n) {
  const int numbits = CHAR_BIT * sizeof( uint32_t );
  printf("%d\n", (int)CHAR_BIT);

  for(int i=numbits-1; i>= 0; --i) {
    printf("%s", ( ( 1 << i ) & n ? "1" : "0" ));
    if(i % CHAR_BIT == 0) {
      printf(" ");
    }
  }
  printf("\n");

}

/* uint32_t get_hash_v4(uint32_t n, uint8_t m) { */

/*   uint32_t m32 = m << 24; */
/*   uint32_t test = n | m32; */
/*   printf("%"PRIu32"\n", n); */
/*   printf("%"PRIu32"\n", test); */
/*   return test; */
/* } */



uint32_t get_hash_v4(struct in_addr * inp, uint8_t mask) {
  uint32_t n = inp->s_addr;
  uint32_t m32 = mask << 24;
  uint32_t test = n | m32;
  printf("%"PRIu32"\n", n);
  printf("%"PRIu32"\n", test);
  return test;
}





// Big-endian is the most common convention in data networking (including IPv6),
// hence its pseudo-synonym network byte order


int main() {
  int ret;
  const char *cp = "1.0.0.0";
  struct in_addr inp;
  ret = inet_aton(cp, &inp);
  printf("%s\n", inet_ntoa(inp));
  uint32_t ipv4 = inp.s_addr;
  uint8_t netmask = 5;
  uint32_t test = get_hash_v4(&inp, netmask);



  struct in_addr inp_mod;
  inp_mod.s_addr = test;
  printf("%s\n", inet_ntoa(inp_mod));


  // http://linux.die.net/man/7/ipv6
  const char *cp6 = "2001:48d0:101:501:4523:3fde:a880:4909";
  struct in6_addr inp6;

  ret = inet_pton(AF_INET6, cp6, &inp6);
  


  // int inet_aton(const char *cp, struct in_addr *inp);  
  // char *inet_ntoa(struct in_addr in);

  /* const char *cp = "127.12.12.16"; */
  /* struct in_addr inp; */
  /* int ret = inet_aton(cp, &inp); */
  /* uint32_t no_ipv4 = inp.s_addr; */
  /* uint64_t test =  no_ipv4;   */
  /* uint8_t nm = 32; */

  /* //  int i = 0x01234567; */
  /* show_mem_rep((char *)&no_ipv4, sizeof(no_ipv4)); */
  /* show_mem_rep((char *)&nm, sizeof(nm)); */
  /* uint32_t netmask = nm << 24; */
  /* uint32_t res = no_ipv4 | netmask; */

  /* show_mem_rep((char *)&netmask, sizeof(netmask)); */
  /* show_mem_rep((char *)&res, sizeof(res)); */

  /* return 0; */


  /* printf("%s\n", cp); */
  /* printf("%s\n", inet_ntoa(inp)); */
  /* printf("%u\n", inp.s_addr); */
  /* printf("%u\n", no_ipv4); */
  /* printf("%llu\n", test); */

  /* print_bits(no_ipv4);  */
  /* print_64_bits(test);  */

  /* print_bits(no_ipv4);  */
  /* printf("%llu\n", test); */
  /* print_64_bits(test);  */

  return 0;
}

