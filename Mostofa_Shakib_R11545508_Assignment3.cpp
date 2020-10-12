#include <iostream>
#include <fstream>
#include <string.h>
#include <stdio.h>

using namespace std;

// A helper function that converts from a char dataType to a string dataType

string getString(char x) 
{
    string s(1, x); 
    return s;    
}

// A helper function that checks to is if the current character is anyone of the special characters if not the function returns false

bool isSpecial(char character) 
{  
  if ( ':' == character || '<' == character || '>' == character || '=' == character || '+' == character || '-' == character || '*' == character  || '/' == character || '('  == character || ')' == character || ';' == character ) {
    return true;
  }
  return false;
}

// A helper function that checks if a given string is a special character of length 2 or not

bool isTwoCharSpecial(string word)
{
  if ( ":=" == word || "<>" == word || ">=" == word || "<=" == word ) {
    return true;
  }
  return false;
}

// A helper function that returns the index of a specific word

int getSpecialCharIndex(string word)
{
  if (word == ":=") {
    return 0;
  }
  else if (word == "<>") {
    return 1;
  }
  else if (word == ">=") {
    return 2;
  } 
  else {
    return 3;
  }
}

// a helper function that returns the index of a specific word or 100 if the word is not found

int getReservedKeywordIndex(string word)
{
  if (word == "read") {
    return 0;
  }
  else if (word == "write") {
    return 1;
  }
  else if (word == "while") {
    return 2;
  } 
  else if (word == "do") {
    return 3;
  } 
  else if (word == "od") {
    return 4;
  }
  return 100;
}


// A helper function that checks if all the characters of a string is lower cased if not the function returns false

bool isAllLower(string word)
{
  int length = word.length();

  for (int i = 0; i < length; i++){
    if (islower(word[i])) {
      continue;
    } else {
      return false;
    }
  }
  return true;
}
  
int main(int argc, char ** argv) 
{

  // This line checks if the number if arguments executed by the program is two or not

  if (argc == 2) {

    string line;

    // A build in method that is used to read text files
    
    ifstream myfile (argv[1]);   // this line opens the text file that is passed through the command line
    
    // This line checks if the file change be opened of not

    if (myfile.is_open()) {
      cout << "DanC Analyzer :: R11545508" << endl;

      while ( getline (myfile, line) ) {    // This line reads the file line by line

        int pointer = 0;                    // initialize a pointer for the given line
        int lineLength = line.length();

        // Walks all the characters in a given line

        while (pointer < lineLength) {
          char sub_string = line[pointer];   // gets the character at a specific index in the line

          // this checks to see if the current character is a digit or not

          if ( isdigit(sub_string) ) {
            int digitCounter = 0;
            int digitNumber = 0;          // pointer to count how many digits does the integer have

            // If the current character is a digit we run a while look in order to handle cases where the integer is more than one character long. Example 100

            while ( isdigit(line[pointer + digitCounter]) ) {
              int num = (int) (line[pointer + digitCounter]) - 48;     // The ASCII value for 0 is 48 hence it is subtracted in order to get the actual digit value
              digitNumber = digitNumber*10 + num;
              digitCounter ++;
            }
            cout << digitNumber << "      " << "INT_LIT" << endl;
            pointer += digitCounter;
          }

          // This checks to see if the current character is an alphabet or not

          else if ( isalpha(sub_string) ) {
            string currentString = "";
            int stringCounter = 0;    // pointer to count how many characters does the string have

            // This is done in order to read continue characters as one string

            while ( isalpha(line[pointer + stringCounter]) ) {
              currentString += line[pointer + stringCounter];
              stringCounter ++;
            }

            // this checks if the string contains all lower cased characters or not

            if ( isAllLower(currentString) == false) {
              cout << currentString << "      " << "UNKNOWN" << endl; 
            }

            // This checks if the string is any of the reserved keywords or not

            int reservedKeywordIndex = getReservedKeywordIndex(currentString);

            switch (reservedKeywordIndex) {
                case 0:
                    cout <<  currentString << "      " << "KEY_READ" << endl;
                    break;
                case 1:
                    cout <<  currentString << "      " << "KEY_WRITE" << endl;
                    break;
                case 2:
                    cout <<  currentString << "      " << "KEY_WHILE" << endl;
                    break;
                case 3:
                    cout <<  currentString << "      " << "KEY_DO" << endl;
                    break;
                case 4:
                    cout << currentString << "      " << "KEY_OD" << endl;
                    break;
                default:
                    cout << currentString << "      " << "IDENT" << endl;
                    break;
            }
            pointer += stringCounter;
          }

          // This checks if the character is a special character or not by calling the isSpecial helper function

          else if ( isSpecial(sub_string) == true ) {
              string specialString = "";
              specialString += line[pointer];
              specialString += line[pointer+1];         

              // If the first character is a special character we also check the next character to see if both the characters together forms one special character or not
              // If the second character is not a special character then we check if the first character is one of the recognized lexeme
              // If the first character is a special character, the second character is not a special character and the first character is not a recognized lexeme then we return UNKNOWN

              if ( isTwoCharSpecial(specialString) == true ) {

                int specialStringIndex = getSpecialCharIndex(specialString);

                switch (specialStringIndex) {
                    case 0:
                        cout <<  specialString << "      " << "ASSIGN_OP" << endl;
                        break;
                    case 1:
                        cout <<  specialString << "      " << "NEQUAL_OP" << endl;
                        break;
                    case 2:
                        cout <<  specialString << "      " << "GEQUAL_OP" << endl;
                        break;
                    case 3:
                        cout <<  specialString << "      " << "LEQUAL_OP" << endl;
                        break;
                }
                pointer += 2;
              } 
              else {

                  switch (sub_string) {
                    case '<':
                        cout <<  sub_string << "      " << "LESSER_OP" << endl;
                        break;
                    case '>':
                        cout <<  sub_string << "      " << "GREATER_OP" << endl;
                        break;
                    case '=':
                        cout <<  sub_string << "      " << "EQUAL_OP" << endl;
                        break;
                    case '+':
                        cout <<  sub_string << "      " << "ADD_OP" << endl;
                        break;
                    case '-':
                        cout <<  sub_string << "      " << "LESSER_OP" << endl;
                        break;
                    case '*':
                        cout <<  sub_string << "      " << "MULT_OP" << endl;
                        break;
                    case '/':
                        cout <<  sub_string << "      " << "DIV_OP" << endl;
                        break;
                    case '(':
                        cout <<  sub_string << "      " << "LEFT_PAREN" << endl;
                        break;
                    case ')':
                        cout <<  sub_string << "      " << "RIGHT_PAREN" << endl;
                        break;
                    case ';':
                        cout <<  sub_string << "      " << "SEMICOLON" << endl;
                        break;
                    default:
                        cout << sub_string << "      " << "UNKNOWN" << endl;
                        break;
                      }
                pointer++;
              }
          }
          else if ( sub_string == '\t' || sub_string == '\n' || sub_string == ' ' || sub_string == '\v' || sub_string == '\f' || sub_string == '\r' ) {
            pointer++;
          }
          else {
            cout << sub_string << "      " << "UNKNOWN" << endl;
            pointer++;
            }
          }
        }
      myfile.close();    // After we have read all the lines from the text file we simply close the file reader
    }

    // We return the appropriate error message if the file either cannot be opened or not enough arguments have been passed

    else {
      cout << "Unable to open file" << endl;
    }
  }
  else {
    cout << "Not enough arguments passed" << endl;
  }
  return 0;
}
