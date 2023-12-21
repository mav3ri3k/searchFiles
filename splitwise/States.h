#include "Groups.h"

using namespace std;

class States {

  string format(string s) {
    for (int i = 0; i < s.length(); i++) {
      s[i] = tolower(s[i]);
    }

    return s;
  }

public:
  Groups groups;

  vector<string> states = {"splitwise", "group"};
  string state;
  string listItem;

  vector<string> nextGroups = {states[1]};
  vector<string> nextGroup = {states[0]};

  vector<string> actionGroups = {"Add", "View"};
  vector<string> actionGroup = {"Add", "View"};

  States() {
    state = states[0];
    groups = Groups();
  }

  string stateName() {
    if (state == states[1]) {
      return listItem;
    } else {
      return state;
    }
  }

  vector<string> &nextViableStates() {
    if (state == states[0]) {
      return nextGroups;
    } else {
      return nextGroup;
    }
  }

  vector<string> &actionsAvailable() {
    if (state == states[0]) {
      return actionGroups;
    } else {
      return actionGroup;
    }
  }

  bool changeStateTo(string nextState) {
    bool allowed = false;
    for (string state : nextViableStates()) {
      if (state == nextState) {
        allowed = true;
      }
    }

    if (allowed) {
      state = nextState;
      return true;
    } else {
      return false;
    }
  }

  bool doAction(string action) {
    action = format(action);

    if (state == states[0]) {
      if (action == format(actionGroups[0])) {
        try {
          groups.addGroup();
        } catch (int i) {
          cout << "\uf256 Please choose a different name! " << endl;
          return false;
        }
        return true;
      } else if (action == format(actionGroups[1])) {
        groups.viewGroups();
        return true;
      }
    } else if (state == states[1]) {
      if (action == format(actionGroup[0])) {
        Group &grp = groups.refGroup(listItem);
        grp.addExpense();
        return true;
      } else if (action == format(actionGroup[1])) {
        Group &grp = groups.refGroup(listItem);

        grp.viewExpenses();
        return true;
      } else {
        return false;
      }
    }

    return false;
  }

  bool moveToList(string item) {
    item = format(item);

    if (state == states[0]) {
      bool present = false;
      for (string name : groups.groupsNames()) {
        if (format(name) == item) {
          present = true;
        }
      }

      if (!present) {
        return false;
      }
      if (changeStateTo(states[1])) {
        listItem = item;
        return true;
      } else {
        return false;
      }
      return false;
    }
    return false;
  }
};
