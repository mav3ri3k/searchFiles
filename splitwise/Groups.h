#include "Group.h"

using namespace std;

class Groups {

  static string format(string s) {
    for (int i = 0; i < s.length(); i++) {
      s[i] = tolower(s[i]);
    }

    return s;
  }

  string formatName(string s) {
    for (int i = 0; i < s.length(); i++) {
      s[i] = tolower(s[i]);
    }
    s[0] = toupper(s[0]);

    return s;
  }

  static bool comparator(const Group &a, const Group &b) {
    return format(a.name) < format(b.name);
  }

  void sortList() { sort(groups.begin(), groups.end(), comparator); }

public:
  vector<Group> groups;

  Group &refGroup(string name) {
    bool found = false;
    for (Group &group : groups) {
      if (format(group.name) == format(name)) {
        found = true;
        return group;
      }
    }
    return groups[0];
  }

  vector<string> groupsNames() {
    sortList();
    vector<string> names;
    for (Group group : groups) {
      names.push_back(group.name);
    }

    return names;
  }

  string addGroup() {

    Color::Modifier red(Color::FG_RED);
    Color::Modifier blue(Color::FG_BLUE);
    Color::Modifier green(Color::FG_GREEN);
    Color::Modifier black(Color::FG_BLACK);
    Color::Modifier def(Color::FG_DEFAULT);
    Color::Modifier bred(Color::BG_RED);
    Color::Modifier bgreen(Color::BG_GREEN);
    Color::Modifier bblue(Color::BG_BLUE);
    Color::Modifier bdef(Color::BG_DEFAULT);

    string name;
    cout << green << "Name" << def << " of group: ";
    cout << blue;
    cin >> name;
    cout << def;

    if (name == "group") {
      throw 1;
    }
    name = formatName(name);

    groups.push_back(Group(name));
    cout << endl;
    cout << bgreen << black << "New Group " << formatName(name) << " added!"
         << bdef << def << endl
         << endl;
    cout << "Input name of group to view its expenses\n"
            "Input add command for creating more groups"
         << endl;

    return name;
  }

  void viewGroups() {
    sortList();

    if (!groups.empty()) {
      cout << "Groups created: " << endl;
      for (Group group : groups) {
        cout << " - " << formatName(group.name);
        cout << endl;
      }
    } else {
      cout << "No Groups created yet" << endl;
    }
  }
};
