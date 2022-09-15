# Test-Segepar

This is a c++ script used to convert an xml format query to an sql format query, it uses the c++ library RapidXML

the main code is in the StepOne.cpp and StepTwo.cpp file, the other hpp files are used by the RapidXML library

-In order to compile the first step code, we should execute the command `g++ stepOne.cpp  -o exec` in the terminal
And then, we can execute the executable by runing the command `./exec` in the terminal

-In order to compile the second step code, we should execute the command `g++ StepTwo.cpp -o exec2` in the terminal
And then, we can execute the executable by runing the command `./exec2` in the terminal

ps: this code works in linux (visual studio code) and requires a g++ compiler 

