#include <stdio.h>
#include <limits.h>
#include <string.h>

#include <stdlib.h> 
#include <arpa/inet.h>
#include <sys/socket.h>
// #include <netinet/ip.h> /* superset of previous */

#define _BSD_SOURCE	       /* See feature_test_macros(7) */
//#include <machine/endian.h>


#include <sys/types.h>
#include <netinet/in.h>
#include <inttypes.h>


uint64_t ntoh64(const uint64_t *input) {
    uint64_t rval;
    uint8_t *data = (uint8_t *)&rval;
    data[0] = *input >> 56;
    data[1] = *input >> 48;
    data[2] = *input >> 40;
    data[3] = *input >> 32;
    data[4] = *input >> 24;
    data[5] = *input >> 16;
    data[6] = *input >> 8;
    data[7] = *input >> 0;
    return rval;
}

uint64_t hton64(const uint64_t *input) {
    return (ntoh64(input));
}



void printbinary_32(uint32_t n) {
  const int numbits = CHAR_BIT * sizeof( uint32_t );
  for(int i=numbits-1; i>= 0; --i) {
    printf("%s", ( ( 1 << i ) & n ? "1" : "0" ));
    if(i % CHAR_BIT == 0) {
      printf(" ");
    }
  }
  printf("\n");

}


void printbinary_64(uint64_t n) {
  const int numbits = CHAR_BIT * sizeof( uint64_t );
  for(int i=numbits-1; i>= 0; --i) {
    printf("%s", ( ( (uint64_t) 1 << i ) & n ? "1" : "0" ));
    if(i % CHAR_BIT == 0) {
      printf(" ");
    }
  }
  printf("\n");

}



// IPv4

/* struct sockaddr_in { */
/*     sa_family_t    sin_family; /\\* address family: AF_INET *\/ */
/*     in_port_t      sin_port;   /\* port in network byte order *\/ */
/*     struct in_addr sin_addr;   /\* internet address *\/ */
/* }; */

/* /\* Internet address. *\/ */
/* struct in_addr { */
/*     uint32_t       s_addr;     /\* address in network byte order *\/ */
/* }; */

uint32_t get_hash_v4(struct in_addr * ip_addr_v4, uint8_t netmask) {
  // check netmask is acceptable
  if(netmask < 0 || netmask >32) {
    return 0;
  }
  // convert network byte order to host byte order
  uint32_t address = ntohl(ip_addr_v4->s_addr);  
  printf("address:\t");
  printbinary_32(address);
  uint32_t wildcard = ((1 << (netmask)) -1) << (32-netmask);
  printf("wildcard:\t");
  printbinary_32(wildcard);
  // make sure mask has been applied correctly
  uint32_t net_address = address & wildcard;
  printf("net_address:\t");
  printbinary_32(net_address);
  // embed network mask in network address
  uint32_t netmask_32 = netmask;
  printf("netmask_32:\t");
  printbinary_32(netmask_32);
  uint32_t hash = net_address | netmask_32;
  printf("hash:\t\t");
  printbinary_32(hash);
  return hash;
}


// IPv6 

/* struct sockaddr_in6 { */
/*     sa_family_t     sin6_family;   /\* AF_INET6 *\/ */
/*     in_port_t       sin6_port;     /\* port number *\/ */
/*     uint32_t        sin6_flowinfo; /\* IPv6 flow information *\/ */
/*     struct in6_addr sin6_addr;     /\* IPv6 address *\/ */
/*     uint32_t        sin6_scope_id; /\* Scope ID (new in 2.4) *\/ */
/* }; */

/* struct in6_addr { */
/*     unsigned char   s6_addr[16];   /\* IPv6 address *\/ */
/* }; */

uint64_t get_hash_v6(struct in6_addr * ip_addr_v6, uint8_t netmask) {
  int i = 0;
  if(netmask < 0 || netmask > 64) {
    return 0;
  }
  printf("address:\t");
  uint64_t address = *((uint64_t *) &(ip_addr_v6->s6_addr[0]));
  address = ntoh64(&address);
  printbinary_64(address);
  uint64_t wildcard = ((1 << (netmask)) -1) << (64-netmask);
  printf("wildcard:\t");
  printbinary_64(wildcard);
  // make sure mask has been applied correctly
  uint64_t net_address = address & wildcard;
  printf("net_address:\t");
  printbinary_64(net_address);
  // embed network mask in network address
  uint64_t netmask_64 = netmask;
  printf("netmask_64:\t");
  printbinary_64(netmask_64);
  uint64_t hash = net_address | netmask_64;
  printf("hash:\t\t");
  printbinary_64(hash);
  return hash;
  return 0;
}



int main() {
  int ret;
  // buffers to print ipvX prefixes
  char ipv4[INET_ADDRSTRLEN];
  char ipv6[INET6_ADDRSTRLEN];
  struct in_addr ip_addr_v4;
  struct in6_addr ip_addr_v6;

  const char *cp4 = "2.114.3.27";
  uint8_t netmask_v4 = 12;
  //  const char *cp6 = "2001:48d0:101:501:4523:3fde:a880:4909";
  const char *cp6 = "0102:0304:0506:0708:0:0:0:02";
  uint8_t netmask_v6 = 60;
  printf("\n");


  // IPv4 to hash
  // convert text to ip_addr_v4
  ret = inet_pton(AF_INET, cp4, &ip_addr_v4);
  printf("IPv4: %s\n", cp4);
  uint32_t hash = get_hash_v4(&ip_addr_v4, netmask_v4);
  printf("\n");

  // IPv6 to hash
  // convert text to ip_addr_v6
  ret = inet_pton(AF_INET6, cp6, &ip_addr_v6);
  printf("IPv6: %s\n", cp6);
  uint64_t hash64 = get_hash_v6(&ip_addr_v6, netmask_v6);
  printf("\n");


  return 0;
}
