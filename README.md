# WordleCloneCpp

Wordle clone written for the terminal in cpp

![alt text](images/Screenshot1.png)

![alt text](images/Screenshot2.png)

## words.txt

The file of words is taken from this repository:

[Wordle Words List by dracos](https://gist.github.com/dracos/dd0668f281e685bad51479e5acaadb93)

As of right now to play the game you need to compile the .cpp to an .exe with a command such as this:

g++ wordle.cpp -o wordle.exe

The game will need to be played from the folder, or a shortcut has to be made to the executable. This is because the executable still depends in the words.txt. I have plans to make a script to convert it to a .cpp file so it can be compiled together so the .exe is completely standalone.
