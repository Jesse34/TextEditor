//
// Created by nscc on 1/26/18.
//

#ifndef ASS1_TEXTEDITOR_CONTROLLER_H
#define ASS1_TEXTEDITOR_CONTROLLER_H


#include "LinkedList.h"
#include "stdafx.h"

////Command Regex Patterns
const regex helpRegex   ("^\\s*[Hh]\\s*$");
const regex viewRegex   ("^\\s*[Vv]\\s*$");
const regex rangeRegex  ("^([Ll]|([Ll])(\\s)(\\d*)(\\s*)|([Ll])(\\s)(\\d*)(\\s)(\\d*)\\s*)$");
const regex deleteRegex ("^([Dd]|([Dd])(\\s)(\\d*)(\\s*)|([Dd])(\\s)(\\d*)(\\s)(\\d*)\\s*)$");
const regex insertRegex ("^([Ii]|([Ii])(\\s)(\\d*)\\s*)$");
const regex replaceRegex("^([Ss]|([Ss])(\\s)(\\d*)\\s*)$");
const regex goToRegex   ("^([Gg]|([Gg])(\\s)(\\d*)\\s*)$");
const regex exitRegex   ("^\\s*[Ee]\\s*$");
const regex quitRegex   ("^\\s*[Qq]\\s*$");

class Controller
{

public:
    int currentLine;
    char* sourceFile;
    char* targetFile;

    ifstream inputFile;
    ofstream outputFile;
    LinkedList list;

    LinkedList readSourceFile(string fileName);
    void readInput(string inputCommand);
    void display();

private:
    void insertLine(string inputText);
    void replaceLine(string inputText);
    void goToLine(string inputText);
    void deleteRange(string inputText);
    void displayRange(string inputText);
    void displayHelp();
    void saveAndExit();
    void quitWithoutSaving();
};


#endif //ASS1_TEXTEDITOR_CONTROLLER_H
