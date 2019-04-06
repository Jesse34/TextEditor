//
// Created by nscc on 1/26/18.
//

#include "Controller.h"
#include "stdafx.h"

//Open, read, and append the src files contents to the LinkedList
LinkedList Controller::readSourceFile(string fileName)
{
    string line = "";

    try
    {
        inputFile.open(fileName);
    }
    catch (const char* e) {
        cerr << "Unable to open the input file, file not found or file path is incorrect." << endl;
        exit(EXIT_FAILURE);
    }

    if(inputFile.is_open()) {

        //If the file successfully opens, loop through the file and add each line to the LinkedList
        while (!inputFile.eof()) {
            //Extract the current line and save it as a string the to 'line' variable
            getline(inputFile, line);

            //Add the current line to the LinkedList
            list.Add(line);
        }
        inputFile.close();

        //After collecting all sourcefile data
        //Reset the current line to the first node by default
        currentLine = 1;

        return list;
    }
    else
    {
        cerr << "Error occurred when opening the source file." << endl;
        exit(EXIT_FAILURE);
    }
}

//Read command input and match against proper regex
void Controller::readInput(string inputCommand)
{
    if(regex_match(inputCommand, helpRegex, regex_constants::match_default))
    {
        displayHelp();
        return;
    }
    else if(regex_match(inputCommand, viewRegex, regex_constants::match_default))
    {
        display();
        return;
    }
    else if(regex_match(inputCommand, rangeRegex, regex_constants::match_default))
    {
        displayRange(inputCommand);
        return;
    }
    else if(regex_match(inputCommand, insertRegex, regex_constants::match_default))
    {
        insertLine(inputCommand);
        return;
    }
    else if(regex_match(inputCommand, replaceRegex, regex_constants::match_default))
    {
        replaceLine(inputCommand);
        return;
    }
    else if(regex_match(inputCommand, deleteRegex, regex_constants::match_default))
    {
        deleteRange(inputCommand);
        return;
    }
    else if(regex_match(inputCommand, goToRegex, regex_constants::match_default))
    {
        goToLine(inputCommand);
        return;
    }
    else if(regex_match(inputCommand, quitRegex, regex_constants::match_default))
    {
        quitWithoutSaving();
        return;
    }
    else if(regex_match(inputCommand, exitRegex, regex_constants::match_default))
    {
        saveAndExit();
        return;
    }
}

//Display the LinkedList's contents currently in the buffer
void Controller::display()
{
    cout << endl << "Linked List contents: " << endl << list;
}

//Display the lines between a specified range
void Controller::displayRange(string inputText)
{
    int startLine;
    int endLine;

    //If the input contains a line number, eg: 'L 5' or 'L 5 6'.
    if (inputText.size() > 2) {
        string indexParameters;
        indexParameters = inputText.substr(2);

        //Method to tokenize the index parameters from the string
        /*
         * Referenced this method from @kev
         * https://stackoverflow.com/questions/236129/the-most-elegant-way-to-iterate-the-words-of-a-string?page=1&tab=votes#tab-top
         */
        string buffer;
        stringstream ss(indexParameters); //Insert the line num parameters into a string stream
        vector<string> parameters;

        while(ss >> buffer)
            parameters.push_back(buffer);

        //Handle a single line parameter
        if(parameters.size() == 1 && stoi(parameters[0]) > 0 && stoi(parameters[0]) <= list.size())
        {
            cout << "[" << stoi(parameters[0]) << "] " << list.GetNodeById(stoi(parameters[0]))->data << endl;
        }
        else
        {
            if(stoi(parameters[0]) <= 0 || stoi(parameters[0]) > list.size()+1 || stoi(parameters[1]) <= 0 || stoi(parameters[1]) > list.size()+1)
            {
                cout << "The provided line id is out of range." << endl;
                return;
            }
            else
            {
                if(stoi(parameters[0]) < stoi(parameters[1]))
                {
                    startLine = stoi(parameters[0]);
                    endLine = stoi(parameters[1]);
                }
                else
                {
                    startLine = stoi(parameters[1]);
                    endLine = stoi(parameters[0]);
                }

                int totalLines = endLine - startLine + 1;
                for(int i=startLine; i<totalLines + startLine; i++)
                {
                    cout << "[" << i << "] " << list.GetNodeById(i)->data << endl;
                }
            }
        }

    }
    else
    {
        cout << "[" << currentLine << "] " << list.GetNodeById(currentLine)->data << endl;
    }
}

//Inserts a line of text into the specified line number.
void Controller::insertLine(string inputText)
{
    //If the input contains a line number, eg: 'i 5'.
    if (inputText.size() > 2)
    {
        string indexParameter;
        indexParameter = inputText.substr(2);

        int lineNum = stoi(indexParameter);
        if(lineNum <= 0 || lineNum > list.size()+1)
        {
            cout << "The provided line id is out of range." << endl;
            return;
        }
        else
        {
            string insertText;
            cout << "Please enter the text you would like to replace line " << lineNum << " with." << endl;
            getline(cin, insertText);
            if(!insertText.empty())
            {
                list.InsertBeforeNode(lineNum-1, insertText);
                display();
                return;
            }
        }
    }
    //If the input is only 'I' or 'i'.
    else
    {
        string insertText;
        cout << "Please enter the text you would like to insert into the current line." << endl;
        getline(cin, insertText);
        if(!insertText.empty())
        {
            list.InsertBeforeNode(currentLine-1, insertText);
            display();
            return;
        }
    }
}

void Controller::replaceLine(string inputText)
{
    //If the input contains a line number, eg: 'S 3'.
    if (inputText.size() > 2) {
        string indexParameter;
        indexParameter = inputText.substr(2);

        int lineNum = stoi(indexParameter);
        if (lineNum <= 0 || lineNum > list.size() + 1) {
            cout << "The provided line id is out of range." << endl;
            return;
        }
        else
        {
            string insertText;
            cout << "Please enter the text you would like to substitute into line " << lineNum << "." << endl;
            getline(cin, insertText);
            if(!insertText.empty())
            {
                list.GetNodeById(lineNum)->data = insertText;
                display();
                return;
            }
        }
    }
    //If the input is only 'S' or 's'.
    else
    {
        string insertText;
        cout << "Please enter the text you would like to substitute into the current line." << endl;
        getline(cin, insertText);
        if(!insertText.empty())
        {
            list.InsertBeforeNode(currentLine-1, insertText);
            display();
            return;
        }
    }
}

//Display the lines between a specified range
void Controller::deleteRange(string inputText)
{
    int startLine;
    int endLine;

    //If the input contains a line number, eg: 'D 5' or 'D 5 6'.
    if (inputText.size() > 2) {
        string indexParameters;
        indexParameters = inputText.substr(2);

        //Method to tokenize the index parameters from the string
        /*
         * Referenced this method from @kev
         * https://stackoverflow.com/questions/236129/the-most-elegant-way-to-iterate-the-words-of-a-string?page=1&tab=votes#tab-top
         */
        string buffer;
        stringstream ss(indexParameters); //Insert the line num parameters into a string stream
        vector<string> parameters;

        while(ss >> buffer)
            parameters.push_back(buffer);

        //Handle a single line parameter
        if(parameters.size() == 1 && stoi(parameters[0]) > 0 && stoi(parameters[0]) <= list.size())
        {
            list.DeleteNode(stoi(parameters[0]));
        }
        else
        {
            if(stoi(parameters[0]) <= 0 || stoi(parameters[0]) > list.size()+1 || stoi(parameters[1]) <= 0 || stoi(parameters[1]) > list.size()+1)
            {
                cout << "The provided line id is out of range." << endl;
                return;
            }
            else
            {
                if(stoi(parameters[0]) < stoi(parameters[1]))
                {
                    startLine = stoi(parameters[0]);
                    endLine = stoi(parameters[1]);
                }
                else
                {
                    startLine = stoi(parameters[1]);
                    endLine = stoi(parameters[0]);
                }

                int totalLines = endLine - startLine + 1;
                for(int i=startLine; i<totalLines + startLine; i++)
                {
                    list.DeleteNode(startLine);
                }
            }
        }

    }
    else
    {
        cout << "Current Line: " << currentLine << endl;
        list.DeleteNode(currentLine);
    }
    display();
}

//Set the currentLine of the text editor. If no line number was provided, default to the first line.
void Controller::goToLine(string inputText)
{
    //If the input contains a line number, eg: 'g 5'.
    if (inputText.size() > 2)
    {
        string indexParameter;
        indexParameter = inputText.substr(2);

        int lineNum = stoi(indexParameter);
        if(lineNum <= 0 || lineNum > list.size())
        {
            cout << "The provided line id is out of range." << endl;
        }
        else
        {
            currentLine = lineNum;
            cout << "Current line is now set to: " << currentLine << endl;
        }
    }
    //If the input is only 'G' or 'g'.
    else
    {
        currentLine = 1;
        cout << "Current line is now set to: " << currentLine << endl;
    }
}

//Display all available commands and the description for each
void Controller::displayHelp()
{
    cout << endl << "Commands: "
         << endl << "I <line number>.............. - Inserts text before the selected line. If no line number is entered, enter before the current line."
         << endl << "D <line number> <line number> - Delete all lines between the selected lines. If no line numbers are entered, delete the current line."
         << endl << "V............................ - Display the contents of the text in the buffer."
         << endl << "G <line number>.............. - Set the current line to the selected line. If no line number is entered, select the first line."
         << endl << "L <line number> <line number> - Display all lines between the selected lines. If no line numbers are entered, display the current line."
         << endl << "S <line number>.............. - Replace the selected line (or current line) with input text. Then display the contents of the text."
         << endl << "E............................ - Exit and save the text file to the specified output file."
         << endl << "Q............................ - Exit without saving." << endl << endl;
}

//Save the LinkedList's contents to the new file and exit the application
void Controller::saveAndExit()
{
    //Try to open the target file to save to
    try
    {
        outputFile.open(targetFile);
    }
    catch (const char* e) {
        cerr << "Unable to open the output file, file not found or file path is incorrect." << endl;
    }

    //Check if file is open
    if(outputFile.is_open())
    {
        //Attempt to save the contents of the LinkedList buffer to the target file
        try
        {
            string line;

            cout << "Saving...." << endl;
            for(int i=1;i<list.size()+1;i++)
            {
                //Collect the value of of the current node and append to the new file.
                line = list.GetNodeById(i)->data;
                outputFile << line << endl;
            }
            cout << "File saved." << endl;
        }
        catch (exception e)
        {

        }
        outputFile.close();
    }
    else
    {
        cerr << "Error when opening the target output file." << endl;
    }
    cout << "Exiting program..." << endl;
    exit(0);
}

//Exit the application without creating/saving the file.
void Controller::quitWithoutSaving()
{
    cout << "Exiting program..." << endl;
    exit(0);
}





