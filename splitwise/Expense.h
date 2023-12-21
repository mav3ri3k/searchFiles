#include "Color.h"
#include "SplitPerson.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Expense {
private:
  static bool comparator(const SplitPerson &a, const SplitPerson &b) {
    return a.name < b.name;
  }

  string format(string s) {
    for (int i = 0; i < s.length(); i++) {
      s[i] = tolower(s[i]);
    }

    s[0] = toupper(s[0]);

    return s;
  }

public:
  float myCost;
  float totalCost;
  string description;
  vector<SplitPerson> participants = {};

  Expense() {}

  void addExpense() {

    Color::Modifier red(Color::FG_RED);
    Color::Modifier black(Color::FG_BLACK);
    Color::Modifier blue(Color::FG_BLUE);
    Color::Modifier green(Color::FG_GREEN);
    Color::Modifier def(Color::FG_DEFAULT);
    Color::Modifier bred(Color::BG_RED);
    Color::Modifier bgreen(Color::BG_GREEN);
    Color::Modifier bblue(Color::BG_BLUE);
    Color::Modifier bdef(Color::BG_DEFAULT);

    cout << "Add" << green << " names" << def << " of members and their "
         << green << "contribution" << def << endl
         << endl;
    cout << "Add your contribution: Rs " << blue;
    float myCost;
    cin >> myCost;
    cout << def;
    this->myCost = myCost;
    totalCost += myCost;

    cout << endl;
    cout << "Input " << bred << "'n' to stop" << bdef << " adding member"
         << endl
         << endl;
    while (true) {
      string name;
      cout << "Name of member: " << blue;
      getchar(); // idk what hidden input is there ????
      getline(cin, name);
      cout << def;

      if (name == "n" || name == "N") {
        break;
      } else {
        float split;
        cout << blue << format(name) << "'s" << def << " contribution: Rs "
             << blue;
        cin >> split;
        cout << def;
        totalCost += split;

        participants.push_back(SplitPerson(name, split));
      }
    }
    cout << "\nAdd " << green << "expense" << def << " description: " << blue;
    string des;
    getline(cin, this->description);
    cout << def;

    cout << endl
         << bgreen << black << "Expense Added" << bdef << def << endl
         << endl;
    cout << "Input View to see all expense summaries" << endl;
    cout << "Input Add command for adding more expenses" << endl;

    sortList();
  }
  void sortList() {
    sort(participants.begin(), participants.end(), comparator);
  }
};
