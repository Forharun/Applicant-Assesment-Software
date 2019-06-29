#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
//Instead of line 1 to 4, #include<bits/stdc++.h> also can be written.
using namespace std;
#define PLAYER_1 1
#define PLAYER_2 2

vector<string> computerGuess;

/*
Given a number as a string, this function check if the number contains duplicate digit.

For example:
checkDuplicateDigit("1234") returns false, because 1234 doesn't have duplicate digit.
checkDuplicateDigit("1123") returns true, because digit 1 is duplicated.
*/
bool checkDuplicateDigit(string number) {
    bool duplicateExist = false;

    // Check all pairs of digits.
    for (int i = 0; i < number.length(); i++) {
        for (int j = i + 1; j < number.length(); j++) {
            if (number[i] == number[j])
                duplicateExist = true;
        }
    }

    return duplicateExist;
}

/*
Check if a string is a number string.

For example:
isNumber("1234") returns true, because it is a number string.
isNumber("Turkey") returns false, because it is not a number string.
*/
bool isNumber(string s) {
    bool allNumber = true;

    for (int i = 0; i < s.length(); i++) {
        if (s[i] < '0' || s[i] > '9')
            allNumber = false;
    }

    return allNumber && s[0] != '0';
}

/*
Check if a string is a four digit number string.

For example:
isFourDigitNumber("1234") returns true, because it is a four digit number string.
isFourDigitNumber("123a") returns false, because it is not a number string.
*/
bool isFourDigitNumber(string s) {
    return isNumber(s) && s.length() == 4;
}

/*
Convert a number to 4-digit number string.
*/
string toNumberString(int number) {
    string numberString = "";
    while (number > 0) {
        numberString = (char) ('0' + (number%10)) + numberString;
        number /= 10;
    }

    while (numberString.length() < 4)
        numberString = "0" + numberString;

    return numberString;
}

/*
Returns a random 4-digit number where all it's digits are different.
*/
string generateRandomFourDigitNumber() {
    srand(time(0));
    while (true) {
        int number = 1000 + rand()%9000;

        string numberString = toNumberString(number);

        if (!checkDuplicateDigit(numberString))
            return numberString;
    }
}

/*
Given a number and a guess, count how many digits in guess match the digits in number.

For example:
countCorrectDigitAndPosition("1234", "1567") returns 1, because digit 1 is correct (value and position).
countCorrectDigitAndPosition("1234", "4321") returns 0, because no digits is correct (in terms of value and position).
*/
int countCorrectDigitAndPosition(string number, string guess) {
    int result = 0;

    for (int i = 0; i < number.length(); i++) {
        if (number[i] == guess[i])
            result += 1;
    }

    return result;
}

/*
Given a number and a guess, count how many digits in guess match which is in number but in the wrong position.

For example:
countCorrectDigitAndWrongPosition("1234", "1425") returns 2, because digit 2 and 4 exists in number but in wrong position.
countCorrectDigitAndWrongPosition("1234", "4321") returns 4, all digits exist but in wrong position.
*/
int countCorrectDigitAndWrongPosition(string number, string guess) {
    int result = 0;

    for (int i = 0; i < guess.length(); i++) {
        for (int j = 0; j < number.length(); j++) {
            if (i != j && guess[i] == number[j])
                result += 1;
        }
    }

    return result;
}

//###############################################
//Computer strategy
//###############################################

/*
Generate all valid computer guess
*/
void generateComputerGuess() {
    for (int i = 1000; i <= 9999; i++) {
        string numberString = toNumberString(i);

        if (!checkDuplicateDigit(numberString))
            computerGuess.push_back(numberString);
    }
}

/*
Get a computer's guess
*/
string getComputerGuess() {
    for (int i = 0; i < computerGuess.size(); i++) {
        if (computerGuess[i] != "")
            return computerGuess[i];
    }
}

/*
Remove all guesses that is not valid.
A guess is valid means that it is possible true. A guess is invalid means that the number can't be the answer.
*/
void removeInvalidComputerGuess(string guess, int targetCorrectDigitAndPosition, int targetCorrectDigitAndWrongPosition) {
    for (int i = 0; i < computerGuess.size(); i++) {
        int correctDigitAndPosition = countCorrectDigitAndPosition(computerGuess[i], guess);
        int correctDigitAndWrongPosition = countCorrectDigitAndWrongPosition(computerGuess[i], guess);

        if (correctDigitAndPosition != targetCorrectDigitAndPosition || correctDigitAndWrongPosition != targetCorrectDigitAndWrongPosition)
            computerGuess[i] = "";
    }
}

//###############################################
//Helper functions
//###############################################
int getUserResponse() {
    cout << "> ";

    string line;
    getline(cin, line);

    int result = 0;
    for (int i = 0; i < line.length(); i++) {
        if (line[i] >= '0' && line[i] <= '9')
            result = 10 * result + (line[i] - '0');
    }

    return result;
}

int main() {
    generateComputerGuess();

    cout << endl;
    cout << "\t\t\t=============================================" << endl;
    cout << "\t\t\t| CS-TECH Applicant Assesment Software v1.0 |" << endl;
    cout << "\t\t\t=============================================" << endl;
    cout << endl;

    int currentPlayer = PLAYER_1;
    string computerNumber = generateRandomFourDigitNumber();

    cout << "\tComputer has generated 4-digit number with different digits that the user will " << endl<<"estimate the number of,make sure you have too.           " << endl;
    cout << "\tThe Computer will try to find the number predicted by the user and the user    " << endl<<"will try to find the number predicted by the computer.   " << endl;
    cout << "\tIf the given number is correct and the digit value is correct,'+'value will be " << endl<<"hinted,and if the digit value is wrong,'-'will be hinted." << endl;
	cout << "\tAccording to this estimated number,you must give to the software same hints!   " << endl;
	cout << "\tLet's start the game!" << endl;
    while (true) {
        if (currentPlayer == PLAYER_1) {
            cout << "\nYour turn, what would be your guess?" << endl;
            cout << "> ";

            string guess;

            getline(cin, guess);
            while (!isFourDigitNumber(guess) || checkDuplicateDigit(guess)) {
                cout << "You should input 4-digit number that doesn't have duplicate digits." << endl;
                cout << "> ";

                getline(cin, guess);
            }

            int correctDigitAndPosition = countCorrectDigitAndPosition(computerNumber, guess);
            int correctDigitAndWrongPosition = countCorrectDigitAndWrongPosition(computerNumber, guess);

            if (correctDigitAndPosition == 4) {
                cout << "\nYour guess is right! Computer's number is " << guess << ". You win!" << endl;
                return 0;
            } else {
                cout << "Number of correct digits and correct position: ";
                if (correctDigitAndPosition > 0)
                    cout << "+";
                
                cout << correctDigitAndPosition << endl;

                cout << "Number of correct digits but wrong position: ";
                if (correctDigitAndWrongPosition > 0)
                    cout << "-";
                
                cout << correctDigitAndWrongPosition << endl;
            }
        } else {
            string computerGuess = getComputerGuess();
            cout << "\nComputer's turn, it guesses " << computerGuess << endl;

            cout << "How many digits which value and position is correct?" << endl;
            int correctDigitAndPosition = getUserResponse();

            if (correctDigitAndPosition == 4) {
                cout << "\nComputer's guess is right! Computer wins!" << endl;
                return 0;
            }

            cout << "How many digits which value is correct but the position is wrong?" << endl;
            int correctDigitAndWrongPosition = getUserResponse();

            removeInvalidComputerGuess(computerGuess, correctDigitAndPosition, correctDigitAndWrongPosition);
        }

        currentPlayer = (currentPlayer == PLAYER_1 ? PLAYER_2 : PLAYER_1);
    }
}
