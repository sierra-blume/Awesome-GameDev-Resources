// add your imports here
#include <fstream>
#include <iostream>
#include <istream>
// tree based data structures
#include <map>
#include <set>
// hashtable based data structures
#include <unordered_map>
#include <unordered_set>
// other includes
#include <ctime>
#include <iostream>
#include <random>

const std::string TEST_FOLDER = "\\test\\";

using namespace std;

struct State {
  int min;
  int max;
  int output;
  bool operator==(const State&) const {
    return min == min && max == max && output == output;
  }
};

// teach the compiler how to hash the State struct
// hashing function
namespace std {
  template<>
  struct hash<State> {
    std::size_t operator()(const State &state) const {
      return hash<int>()(state.min) ^ hash<int>()(state.max) ^ hash<int>()(state.output);
    }
  };
}

int main() {
  std::unordered_map<State, int> hashMap;

  State state;
  state.min = 0;
  state.max = 1000;
  int id = 0;
  int warmupPhase = 0;
  int periodicPhase = 0;

  std::mt19937 generator(std::random_device{}());

  std::uniform_int_distribution<int> distribution(state.min, state.max);

  while (true) {
    state.output = distribution(generator);
    if(hashMap.contains(state)) {
      warmupPhase = hashMap[state];
      periodicPhase = id - warmupPhase;
      break;
    }
    std::cout << id << ": " << state.output << std::endl;
    hashMap.emplace(state, id);
    id++;
  }
  std::cout << "Warmup Phase Length: " << warmupPhase << std::endl;
  std::cout << "Period Phase Length: " << periodicPhase << std::endl;

  return 0;
}