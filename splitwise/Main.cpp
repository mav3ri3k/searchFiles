#include "Help.h"
#include "States.h"
#include <string>

using namespace std;

string format(string s) {
  for (int i = 0; i < s.length(); i++) {
    if (i == 0) {
      s[i] = toupper(s[i]);
    } else {
      s[i] = tolower(s[i]);
    }
  }

  return s;
}

string lower(string s) {
  for (int i = 0; i < s.length(); i++) {
    s[i] = tolower(s[i]);
  }

  return s;
}

int main() {
  Color::Modifier red(Color::FG_RED);
  Color::Modifier def(Color::FG_DEFAULT);
  Color::Modifier bred(Color::BG_RED);
  Color::Modifier bdef(Color::BG_DEFAULT);
  Color::Modifier blink(Color::BLINK);
  Color::Modifier rblink(Color::RST_BLINK);

  Help h;
  States states = States();
  cout << h.main << endl;
  cout << "Currently in " << red << format(states.stateName()) << def
       << " menu." << endl
       << endl;

  cout << "Commands available: " << endl;
  cout << h.cmdGroups << endl;

  while (true) {
    cout << red << format(states.stateName()) << "> " << def;

    string input;
    cin >> input;
    input = lower(input);

    if (input == "help") {
      cout << "Currently in " << red << format(states.stateName()) << def
           << " menue." << endl
           << endl;

      if (states.state == states.states[0]) {
        if (!states.groups.groups.empty()) {
          cout << "Groups available: " << endl;
          for (Group grp : states.groups.groups) {
            cout << " - " << format(grp.name) << endl;
          }
        } else {
          cout << "You can add groups for managing expenses" << endl;
        }
      } else {
        cout << "Go back: " << endl;
        cout << " - Groups" << endl << endl;

        Group &grp = states.groups.refGroup(states.stateName());
        if (!grp.expenses.empty()) {
          cout << "Expense: " << endl;
          for (Expense expense : grp.expenses) {
            cout << " - "
                 << "Rs " << expense.totalCost << " " << expense.description
                 << endl;

            cout << "   - You: Rs " << expense.myCost << endl;
            for (SplitPerson person : expense.participants) {
              cout << "   - " << format(person.name) << ": Rs "
                   << person.personCost << endl;
            }
          }
        } else {
          cout << "Manage " << red << grp.name << def << " expense here"
               << endl;
          ;
        }
      }

      if (states.state == states.states[0]) {
        cout << endl;
        cout << "Commands available: " << endl;
        cout << h.cmdGroups << endl;
      } else {
        cout << endl;
        cout << "Commands available: " << endl;
        cout << h.cmdGroup << endl;
      }

    } else if (input == "exit") {
      cout << "Thank You" << endl << "Good Bye!!";
      exit(0);
    } else {
      if (states.changeStateTo(input)) {
      } else if (states.doAction(input)) {
      } else if (states.moveToList(input)) {
        cout << h.firstGroup;

        cout << endl;
        cout << "Commands available: " << endl;
        cout << h.cmdGroup << endl;
      } else {

        cout << bred << blink << "Wrong Command!!" << bdef << rblink << endl;
      }
    }
  }
}
