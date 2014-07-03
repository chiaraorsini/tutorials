

#include "boost/random.hpp" 
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/random/uniform_real.hpp>

#include <iostream> 


typedef boost::mt19937 RandomGenerator_t;

/* "Mersenne Twister: A 623-dimensionally equidistributed uniform pseudo-random number generator", 
 * Makoto Matsumoto and Takuji Nishimura, ACM Transactions on Modeling and Computer Simulation: 
 * Special Issue on Uniform Random Number Generation, Vol. 8, No. 1, January 1998, pp. 3-30.
 */

class Random {
public:
    static void init(unsigned int s) {
      RandomGenerator_t generator(s);
      Random::random_generator = generator;
    }
    static double get_random_value() {
      // Define a uniform random number distribution which produces "double"
      // values between 0 and 1 (0 inclusive, 1 exclusive).
      boost::uniform_real<> uni_dist(0,1);
      boost::variate_generator<RandomGenerator_t&, boost::uniform_real<> > uni(Random::random_generator, 
									       uni_dist);
      return uni();
    }
private:
    static RandomGenerator_t random_generator;
    static int seed;
};


RandomGenerator_t Random::random_generator(1);
