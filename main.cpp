#include <iostream>
#include <stdio.h>
#include "Empirical/include/emp/math/Random.hpp"
using namespace std;

// Organism class w instance variable double behvior

class Organism
{
public:
  Organism() : behavior(0.0) {}
  Organism(double b) : behavior(b) {}
  double GetBehavior() const { return behavior; }
  void SetBehavior(double b) { behavior = b; }

  void Print() const
  {
    std::cout << "Organism behavior: " << behavior << std::endl;
  }
  // Create a reproduce function in your Organism class that returns a pointer to an Organism and takes no arguments currently.
  // We probably want to use our new-found power in several places. The most critical is in reproduce. Add an argument to reproduce that is of type emp::Random and pass the random that you made in main to reproduce when you call it.
  Organism *Reproduce(emp::Random &random)
  {
    Organism *child = new Organism(this->behavior); // Copy behavior
    // Within reproduce, mutate the offspring after you create it and before returning it. Remember that in C++, you use the -> syntax to call the functions of pointers:
    child->mutate(random);
    return child;
  }

  // Now create a function in your Organism class called mutate that doesn’t return anything but receives an emp::Random as input. (Why do you think we are passing it instead of just making another one?)

  void mutate(emp::Random &random)
  {
    // There are a whole lot of ways of mutating organisms and whole dissertations have been devoted to what the ‘best’ way is. A generally good way to mutate a value that is of type double is to pull a random number from a normal distribution/bell curve that is centered at 0. This means that you are just as likely to mutate up as down and mutations will generally be small but have the chance at being large, which is fairly biologically accurate.

    // This is such a common task that Empirical provides a function for it:
    behavior += random.GetRandNormal(0.0, 0.02); // pull a random number from a normal
    // distribution with a mean of 0 and a standard deviation of 0.002.
    //  Add the random number you get to the organism’s behavior value.
  }

private:
  double behavior;
};

int main()
{
  // create an emp::vector<Organism> called population.
  emp::vector<Organism> population;

  // To mutate organisms, you’ll need access to randomness. C++ has built-in randomness of course, but Empirical provides useful tools for this as well. In main, create a random number generator like so:
  emp::Random random(1); // create an object of type emp::Random called random
  // and pass 1 as an argument to its constructor
  // this is c++ shorthand for emp::Random random = *new emp::Random(1);

  // create 10 organisms with a fixed behavior and add them to the population.
  for (int i = 0; i < 100; ++i)
  {
    population.push_back(*new Organism(0.5));
  }
  // print the behavior of each organism in the population.
  // for (const auto & org : population) {
  //     org.Print();
  // }

  // print the behavior of one organism in the population
  population[0].Print();

  // Verify that your reproduction function works by calling it on an Organism in your population in main and printing the parent and offspring’s addresses and behaviors. Compile and run your code at this point.
  Organism *child = population[0].Reproduce(random);
  cout << "Parent address: " << &population[0] << ", behavior: " << population[0].GetBehavior() << endl;
  cout << "Child address: " << child << ", behavior: " << child->GetBehavior() << endl;

  // In main create a for-loop that loops 100 times, which we’ll call ‘updates’. In more complicated programs, organisms would do some behavior every update, but currently they don’t actually do anything.
  for (int i = 0; i < 100; ++i)
  {
    // population.push_back(*new Organism(0.5));
  }

  // To create competition, we need to compare the organisms’ behavior values and find the best. You can loop through Empirical vectors easily like so:
  // Loop through every organism in the population and find the organism with the maximum behavior. You’ll want to start by declaring a variable to hold the organism with the current maximum that you can then compare to in the loop.
  Organism best = population[0];
  for (Organism j : population)
  {
    if (best.GetBehavior() > j.GetBehavior())
    {
      best = j;
    }
  }

  // Once you find the organism with the maximum behavior value, call its reproduce method and save that new organism.
  Organism *new_org = best.Reproduce(random);

  // We don’t want to just add the offspring to the end of the vector since then the population would just grow and there wouldn’t actually be competition. For evolution to occur, organisms must die. You could go through again and find the minimum behavior value organism, but the first organism in the population will be fine for the moment:
  population[0] = *new_org;

  // Print out the size of your population using the .size() method after running your updates to see that it stays the same. Compile and run your code at this point.
  cout << "New population size: " << population.size() << endl;

  // Outside of your for-loop in main, again trace through your population to find the organism with the maximum behavior value and print it out. Compile and run your code to see what max you reach. It probably won’t be very high since we don’t have a whole lot of variation being introduced and are only running for 100 updates. Increase the number of updates to 10,000 and see what you get.
  population[0].SetBehavior(0.5);
  best = population[0];
  int updates = 100000;
  for (int i = 0; i < updates; ++i)
  {
    Organism *offspring = best.Reproduce(random);
    int overwrite = random.GetUInt(0,population.size());
    population[overwrite] = *offspring;
    if (offspring->GetBehavior() > best.GetBehavior())
    {
      best = *offspring;
    }
  }

  cout << "Max behavior: " << best.GetBehavior() << endl;
}
