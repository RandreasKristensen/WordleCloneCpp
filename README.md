# WordleCloneCpp

Wordle clone written for the terminal in cpp

![alt text](images/Screenshot1.png)

![alt text](images/Screenshot2.png)

## words.txt

The list of words used is taken from this repository:

[Wordle Words List by dracos](https://gist.github.com/dracos/dd0668f281e685bad51479e5acaadb93)

The .txt file is in the "words folder" and has been "translated" to a .cpp file with just the array, with a python script. The .cpp file with the array is then included in the wordle.cpp and compiled together as below

## compilation for Windows

As of right now to play the game on windows you need to compile the .cpp to an .exe with a command such as this:

g++ -o WORDLE.exe wordle.cpp words_array.cpp

This can be done with mingw.
