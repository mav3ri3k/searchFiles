#include <string>

using namespace std;

class SplitPerson {
public:
  string name;
  float personCost;

  SplitPerson(string name, float personCost) {
    this->name = name;
    this->personCost = personCost;
  }

  SplitPerson(string name) { this->name = name; }
};
