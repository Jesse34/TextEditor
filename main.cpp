// TextEditor.cpp
//
// This is the main application file

#include "stdafx.h"
#include "Controller.h"

int main(int argc, char *argv[])
{
    Controller textEditor = Controller();

/*    //Takes in case insensitive 'EDIT' and two filepaths seperated by whitespace.
//    const regex inputPattern("^[Ee][Dd][Ii][Tt]\\s\\S*\\s\\S*$");
//
//    string input;
//
//    do
//    {
//        cout << "To begin the program, type 'EDIT <inputFilepath> <outputFilepath>'" << endl;
//        getline(cin, input);
//
//        //If the EDIT command matches correctly against the input regex, begin the program.
//        if (regex_match(input, inputPattern, regex_constants::match_default)) {
//            cout << input;
//        }
//    }
//    while (!regex_match(input, inputPattern, regex_constants::match_default));
*/

    ////Check the args provided for the input and output files.
    //Checks if there are too many arguments provided.
    if(argc > 3) {
        cout << "Too many filename arguments were provided." <<  endl;
    }

    //Checks if there is an argument provided for the source file
    else if(argv[1] == nullptr) {
        cout << "Please enter a filepath for the input file." << endl;
        return 0;
    }

    //Checks if there is an argument provided for the target file
    else if(argv[2] == nullptr) {
        cout << "Please enter a filepath for the output file." << endl;
        return 0;
    }

    //Collect the arguments to be used for the source/target filename
    textEditor.sourceFile = argv[1];
    textEditor.targetFile = argv[2];

    //If the input is valid, attempt to read the source file
    LinkedList linkedList = textEditor.readSourceFile(textEditor.sourceFile);

    //Create var to contain the command entered.
    string inputCommand;

    textEditor.display();

    //Begin listening for user input commands
    while(true)
    {
        cout << endl << endl << "Please enter a command. (Enter 'H' for command options)" << endl;
        getline(cin, inputCommand);
        textEditor.readInput(inputCommand);
    }
}