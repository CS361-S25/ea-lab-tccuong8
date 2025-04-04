#include <iostream>
#include "Empirical/include/emp/math/Random.hpp"

// Organism class w instance variable double behvior

class Organism {
public:
  Organism() : behavior(0.0) { }
  Organism(double b) : behavior(b) { }
  double GetBehavior() const { return behavior; }
  void SetBehavior(double b) { behavior = b; }
//   void MutateBehavior(emp::Random & random) {
//     behavior += random.GetUniform(-0.1, 0.1);
//     if (behavior < 0) behavior = 0;
//     if (behavior > 1) behavior = 1;
//   }
  void Print() const {
    std::cout << "Organism behavior: " << behavior << std::endl;
  }
private:
  double behavior;
};

int main() {
    // create an emp::vector<Organism> called population.
    emp::vector<Organism> population;
    emp::Random random;
    // create 10 organisms with random behavior and add them to the population.
    for (int i = 0; i < 100; ++i) {
        population.push_back(*new Organism(0.5));
    }
    // print the behavior of each organism in the population.
    for (const auto & org : population) {
        org.Print();
    }

    // print the behavior of one organism in the population
    population[0].Print();
    // mutate the behavior of each organism in the population.
    // for (auto & org : population) {
    //     org.MutateBehavior(random);
    // }
    // print the behavior of one organism in the population after mutation.
    // for (const auto & org : population) {
    //     org.Print();
    // }
    // print the behavior of the new organism.
    // new_org.Print();
    // // mutate the behavior of the new organism.
    // new_org.MutateBehavior(random);
    // print the behavior of the new organism after mutation.
    // new_org.Print();
    // remove the new organism from the population.
    // population.pop_back();
    // print the behavior of each organism in the population after removing the new organism.

}