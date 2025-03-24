#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <ctime> // Include ctime for time() function
#include <fstream>
using namespace std;

//colors for the cout statements
const string WHITE = "\033[97m";
const string RESET = "\033[0m";
const string GRAY = "\033[90m";
const string RED = "\033[31m";
const string GREEN = "\033[32m";
const string YELLOW = "\033[33m";
const string OFFSET = "    ";

//loading words txt file
extern const char *wordsArray[];
static vector<string> wordList;

void loadWords() {
    for (int i = 0; wordsArray[i] != NULL; i++) {
        wordList.push_back(wordsArray[i]);
    }
}

//keyboard
static vector<char> keyboard = {'q', 'w', 'e', 'r', 't', 'y', 'u', 'i', 'o', 'p',
                                'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l',
                                'z', 'x', 'c', 'v', 'b', 'n', 'm'};

                         //Function Prototypes
void displayGuesses(vector<string> guesses);
void displayKeyboard(vector<char> usedChars, vector<char> yellowChars, vector<char> greenChars, vector<char> keyboard);
void updateLetterColors(vector<char>* grayChars, vector<char>* yellowChars, vector<char>* greenChars, 
                        vector<string> guesses, string word, vector<string>* coloredGuesses);
vector<char> getUsedChars(vector<string> guesses);
//small function to choose a word from the wordlist
string chooseWord(vector<string> wordList);
bool isValidGuess(string word, string* errorMessage);


int main() {
                        //setup
    // Seed the random number generator
    srand(time(0));
    //load words into wordList
    loadWords();
    //clear the screen
    system("CLS");
    //create variables
    bool playing = true;
    int playAgain = 0;
    string errorMessage;
    string guess;
    
    cout << WHITE << OFFSET << "Welcome to Wordle!" << RESET << endl;

    //playloop
    while(playing) {
        //Reset
        playAgain = 0;
        bool win = false;
        vector<char> guessedLetters = {};
        vector<char> yellowLetters = {};
        vector<char> greenLetters = {};
        vector<string> guesses {};
        vector<string> coloredGuesses = {};
        int guessesLeft = 6;

        //Choose a word
        string word = chooseWord(wordList);


        //Play loop
        while (guessesLeft > 0 && !win) {
            //Display the gamescreen
            system("CLS");
            displayGuesses(coloredGuesses);
            displayKeyboard(guessedLetters, yellowLetters, greenLetters, keyboard);
            //Display errorMessage if there is any, then reset
            cout << OFFSET << "  " << errorMessage;
            errorMessage = "";
            //Get the guess
            cout << endl << OFFSET << OFFSET << "Guess: ";
            cin >> guess;
            cout << endl;
            
            if (!isValidGuess(guess, &errorMessage)) {
                continue;
            }

            guesses.push_back(guess);
            guessesLeft--;

            //Game logic, coloring the keyboard and the guesses to print
            updateLetterColors(&guessedLetters, &yellowLetters, &greenLetters, guesses, word, &coloredGuesses);

            //Displaying the game
            system("CLS");
            displayGuesses(coloredGuesses);
            displayKeyboard(guessedLetters, yellowLetters, greenLetters, keyboard);
            
            //check for win condition
            win = word == guess;
            if (win) cout << endl << OFFSET << GREEN << "CONGRATULATIONS!" << RESET << endl << endl;
            if (!win && guessesLeft == 0) cout << endl << OFFSET <<"The word was " << GREEN << word << RESET << endl << endl;
        }
        
        cout << WHITE << OFFSET << " 1 for Play Again" << endl << OFFSET << "    0 for Quit" << endl << OFFSET << OFFSET << OFFSET << RESET;
        cin >> playAgain;
        cout << endl;
        
        if (playAgain != 1)
            playing = false;
    }

    //done
    return 69;
}


//Function Implementations
string chooseWord(vector<string> wordList) {
    int wordIndex = rand() % wordList.size();
    return wordList[wordIndex];
}

vector<char> getUsedChars(vector<string> guesses) {
    vector<char> usedChars = {};
    for (string guess : guesses) {
        for (char c : guess) {
            if (find(usedChars.begin(), usedChars.end(), c) == usedChars.end()) {
                usedChars.push_back(c);
            }
        }
    } 
    return usedChars;
}

//Temporary implementation without colors
void displayGuesses(vector<string> guesses) {
    int guessCount = 6;
    for (string guess : guesses) {
        cout << OFFSET << OFFSET << "   " << guess << endl;
        guessCount--;
    }
    while (guessCount != 0) {
        cout << GRAY << OFFSET << OFFSET << "   " << "GUESS" << RESET << endl;
        guessCount--;
    }
}

void displayKeyboard(vector<char> grayChars, vector<char> yellowChars, vector<char> greenChars, vector<char> keyboard) {
    cout << endl << OFFSET;
    for (int i = 0; i < keyboard.size(); ++i) {
        char c = keyboard[i];
        if (find(greenChars.begin(), greenChars.end(), c) != greenChars.end()) {
            cout << GREEN << c << RESET << " ";
        } else if (find(yellowChars.begin(), yellowChars.end(), c) != yellowChars.end()) {
            cout << YELLOW << c << RESET << " ";
        } else if (find(grayChars.begin(), grayChars.end(), c) != grayChars.end()) {
            cout << GRAY << c << RESET << " ";
        } else 
            cout << c << " ";

        // Print a new line after each row of the keyboard
        if (i == 9 ) {
            cout << endl << OFFSET << " ";
        } else if (i == 18) {
            cout << endl << OFFSET << "   ";
        }
    }
    cout << endl;
}

//helper functions for updateLetterColor
vector<char> getGrayChars(vector<string> guesses) {
    vector<char> grayChars;
    for (string guess : guesses) {
        for (char c : guess) {
            if (find(grayChars.begin(), grayChars.end(), c) == grayChars.end()) {
                grayChars.push_back(c);
            }
        }
    } 
    return grayChars;
}

void updateLetterColors(vector<char>* usedChars, vector<char>* yellowChars, vector<char>* greenChars, 
                        vector<string> guesses, string word, vector<string>* coloredGuesses) {
    //all used letters are added to grayChars.
    vector<char> grayChars = getGrayChars(guesses);

    //The current guess is colored in, and added to the back of the coloredGuesses vector
    string coloredGuess;
    string guess = guesses.back(); // Get the latest guess

    for (int i = 0; i < guess.size(); ++i) {
        char c = guess[i];
        if (word[i] == c) {
            // correct character in correct place
            coloredGuess += GREEN + c + RESET;
            greenChars->push_back(c);
            // Remove from yellowChars if it was there before
            yellowChars->erase(remove(yellowChars->begin(), yellowChars->end(), c), yellowChars->end());
        } else if (word.find(c) != string::npos) {
            // correct character in incorrect place
            coloredGuess += YELLOW + c + RESET;
            if (find(yellowChars->begin(), yellowChars->end(), c) == yellowChars->end()) {
                yellowChars->push_back(c);
            }
        } else {
            // incorrect character
            coloredGuess += c;
        }
        // Add to usedChars if not already present
        if (find(usedChars->begin(), usedChars->end(), c) == usedChars->end()) {
            usedChars->push_back(c);
        }
    }

    // Add the colored guess to the list of colored guesses
    coloredGuesses->emplace_back(coloredGuess);
}

bool isValidGuess(string word, string* errorMessage) {
    if (word.length() != 5) {
        *errorMessage = RED + "MUST BE 5 LETTERS" + RESET;
        return false;
    }
    if (find(wordList.begin(), wordList.end(), word) == wordList.end()) {
        *errorMessage = RED + "NOT IN WORDLIST" + RESET;
        return false;
    }
    return true;
}