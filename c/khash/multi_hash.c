

#include "khash.h"
#include <stdio.h>


typedef struct struct_route_info {
  int type_info; // 0 rib, 1 updates
  int timestamp;
} route_info;

KHASH_MAP_INIT_STR(route, route_info*)

typedef struct struct_peer_info {
  int num_updates;
  int timestamp;
  khash_t(route) * route_table;
} peer_info;


KHASH_MAP_INIT_STR(peer, peer_info*)


// -------------------------------------------------------


/* route info functions */
route_info * create_route_info(int type_info, int timestamp) {
  route_info *ri = (route_info*) malloc(sizeof(route_info));
  ri->type_info = type_info;
  ri->timestamp = timestamp;
  return ri;
}

void destroy_route_info(route_info *ri) {
  free(ri);
  return;
}


/* peer_info (i.e. info + ribs) functions */
peer_info * create_peer_info(int num_updates, int timestamp) {
  peer_info *pi = (peer_info*) malloc(sizeof(peer_info));  
  pi->num_updates = num_updates;
  pi->timestamp = timestamp;
  pi->route_table = kh_init(route);
  return pi;
}

void destroy_peer_info(peer_info * pi) {
  khiter_t k;
  route_info * ri; 
  for (k = kh_begin(pi->route_table); k != kh_end(pi->route_table); ++k) {
    if (kh_exist(pi->route_table, k)){
      ri = kh_value(pi->route_table, k);
      destroy_route_info(ri);
    }
  }
  kh_destroy(route, pi->route_table);
  return;
}


/* peer table functions */
khash_t(peer) * create_peer_table() {
  khash_t(peer) *peer_table = kh_init(peer);
  return peer_table;
}


void destroy_peer_table(khash_t(peer) * peer_table) {
  khiter_t k;
  peer_info * pi; 
  for (k = kh_begin(peer_table); k != kh_end(peer_table); ++k) {
    if (kh_exist(peer_table, k)){
      pi = kh_value(peer_table, k);
      destroy_peer_info(pi);
    }
  }
  kh_destroy(peer, peer_table);
  return;
}


void insert_new_route_info(khash_t(peer) * peer_table, char * peer_name,
			   char * prefix, int type_info, int timestamp ) {  
  int r;
  khiter_t peer_it;
  peer_info * pi;
  khiter_t route_it;
  route_info * ri;
  // insert new peer 
  peer_it = kh_put(peer, peer_table, peer_name, &r);  
  // if value does not exists, create and insert value
  if( r!=0 ) { 
    pi = create_peer_info(0,timestamp);
    kh_value(peer_table, peer_it) = pi; 
  }
  pi = kh_value(peer_table, peer_it); 
  // update peer info:
  if(type_info == 1) {
    pi->num_updates++;
  }
  pi->timestamp = timestamp;
  // insert new prefix in peer
  route_it = kh_put(route, pi->route_table, prefix, &r);  
  // if value does not exists, create and insert values
  if( r!=0 ) { 
    ri = create_route_info(type_info, timestamp);
    kh_value(pi->route_table, route_it) = ri; 
  }
  else { // just update values
    ri = kh_value(pi->route_table, route_it); 
    ri->type_info = type_info;
    ri->timestamp = timestamp;
  }
}



void print_route_table(khash_t(route) * route_table) {  
  khiter_t k;
  route_info * ri;
  for (k = kh_begin(route_table); k != kh_end(route_table); ++k){  // traverse
    if (kh_exist(route_table, k)){          // test if a bucket contains data
      ri = kh_value(route_table,k);
      printf("\t%s -> (type) %d - (ts) %d \n", kh_key(route_table,k), ri->type_info, ri->timestamp);      
    }
  }
}

void print_peer_table(khash_t(peer) * peer_table) {  
  khiter_t k;
  peer_info * pi;
  for (k = kh_begin(peer_table); k != kh_end(peer_table); ++k){  // traverse
    if (kh_exist(peer_table, k)){          // test if a bucket contains data
      pi = kh_value(peer_table,k);
      printf("%s  (last ts: %d - Num Up: %d) \n", kh_key(peer_table,k), pi->timestamp, pi->num_updates);      
      print_route_table(pi->route_table);
      printf("\n");
    }
  }
}


int main() {
  int ret, is_missing;
  khiter_t k;
  khash_t(peer) *peer_table = create_peer_table();
  insert_new_route_info(peer_table, "P1", "1.0.1.3/3", 1, 2);
  insert_new_route_info(peer_table, "P2", "1.0.1.3/3", 1, 2);
  insert_new_route_info(peer_table, "P1", "1.0.11.3/3", 1, 2);
  insert_new_route_info(peer_table, "2P1", "1.0.1.3/3", 0, 2);
  insert_new_route_info(peer_table, "2P1", "1.0.1.3/3", 0, 2);
  insert_new_route_info(peer_table, "2P1", "1.0.1.3/3", 0, 2);
  insert_new_route_info(peer_table, "2P1", "1.0.1.3/3", 0, 2);
  insert_new_route_info(peer_table, "2P1", "1.0.1.3/3", 0, 2);
  insert_new_route_info(peer_table, "P1", "1.0.1.3/3", 1, 2);
  insert_new_route_info(peer_table, "P1", "1.0.1.3/3", 1, 2);
  insert_new_route_info(peer_table, "P1", "1.0.1.3/3", 1, 2);
  insert_new_route_info(peer_table, "P1", "1.0.1.3/3", 1, 2);
  insert_new_route_info(peer_table, "P1", "1.0.1.3/3", 1, 2);
  insert_new_route_info(peer_table, "P1", "1.0.1.3/3", 1, 2);
  insert_new_route_info(peer_table, "P1", "1.0.1.3/3", 1, 2);

  print_peer_table(peer_table);
  destroy_peer_table(peer_table);
  return 0;
}

