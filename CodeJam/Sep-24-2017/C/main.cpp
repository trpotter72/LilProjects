#include <iostream>
//#include "min_distance_search.h"
#include <math.h>
#include <string>

int** generate_permutations(int locations, int codejamon);

void p(std::string message) {
  std::cout << message << std::endl;
}

int main() {
  int test_cases;
  std::cin >> test_cases;

  for (int test = 0; test < test_cases; test++)  {
    int locations, roads, codejamon;
    std::cin >> locations, roads, codejamon;

    int permutations = pow((locations - 1), codejamon);

    p("generating permutations");
    int** spawn_combinations = generate_permutations(locations, codejamon);
    for (int i = 0; i < permutations; i++) {
      std::cout << "(";
      for (int j = 0; j < codejamon; j++) {
        std::cout << spawn_combinations[i][j] << ", ";
      }
      std::cout << ")\n";
    }

    }
  }


int** generate_permutations(int locations, int codejamon) {

  int permutations = pow((locations - 1), codejamon);
  int** combinations = new int*[permutations];
  for (int i = 0; i < permutations; i++) {
    combinations[i] = new int[locations];
  }
  p("created grid");
  int latest_val = 1;
  for(int index = 0; index < locations; locations++) {
    int current_p = 0;
    for(int p = 0; p < permutations; p++) {
      if ((p / (pow((locations-1),(codejamon-1-index)))) > current_p) {
        latest_val = ((latest_val % 4) + 1);
      }
      combinations[p][index] = latest_val + 1;
    }
  }
  p("retruning combos");
  return combinations;
}
