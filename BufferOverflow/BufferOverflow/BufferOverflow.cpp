// BufferOverflow.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iomanip>
#include <iostream>
#include <limits>       // std::numeric_limits

int main()
{
  std::cout << "Buffer Overflow Example" << std::endl;

  // TODO: The user can type more than 20 characters and overflow the buffer, resulting in account_number being replaced -
  //  even though it is a constant and the compiler buffer overflow checks are on.
  //  You need to modify this method to prevent buffer overflow without changing the account_order
  //  varaible, and its position in the declaration. It must always be directly before the variable used for input.

  // Declare an input character maximum
  const int INPUT_MAX = 20;
  // declare the account number and the user_input character array
  const std::string account_number = "CharlieBrown42";
  char user_input[INPUT_MAX];

  std::cout << "Enter a value: ";
  // use setw to set the input width to INPUT_MAX. This will prevent any buffer overflows
  std::cin >> std::setw(INPUT_MAX) >> user_input;

  // cin.ignore ignores any characters left in the input buffer
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // ignore anything left in the input buffer

  std::cout << "You entered: " << user_input << std::endl;
  std::cout << "Account Number = " << account_number << std::endl;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu