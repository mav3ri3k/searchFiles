#include <iostream>

using namespace std;

class Help {
public:
  string main =
      "Welcome to expense sharing application\n"
      "You can add groups for managing expenses\n"
      "When in doubt, input 'help' for instructions on how to proceed\n";

  string cmdGroups = " - Add: Make new groups\n"
                     " - View: List groups\n"
                     " - Exit: Leave the application\n";

  string firstGroup = "Manage group expense here\n";
  string cmdGroup = " - Add: Make new expense\n"
                    " - View: List expenses\n"
                    " - Splitwise: Go back to main menu\n"
                    " - Exit: Leave the application\n";
};
