

#include <iostream>
#include "boost_random.h"

using namespace std;


int main(int argc, char** argv) {
  
  const int my_seed = 18;

  Random::init(my_seed);

  for(int i =0; i<10; i++) {
    cout << "Got: " << Random::get_random_value() << endl;
  }
  return 0;
}



