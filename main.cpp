//
//  main.cpp
//  Chapter_5
//
//  Created by Hayden Crabb on 10/22/18.
//  Copyright  2018 Coconut Productions. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include <ctype.h>
#include "Stack.h"
#include "StackNode.h"

using namespace std;

void readInFile(ifstream&, char * &, int &, int &);
void printOutGrid(ofstream &, bool, int * &, int, int);
void printOutInputGrid(char * &, int, int);
void detectTreeStands(char * &, int * &, int, int);
void extractIntegersFromString(string, int &, int &);

int main(int argc, const char * argv[]) {
    
    ifstream inputfile;
    ofstream outputfile;
    
    bool weHaveAnOutputfile = false;
    string fileToOpen;
    if (argc > 1)
    {
        fileToOpen = argv[1];
        if (argc == 3)
        {
            outputfile.open(argv[2]);
            weHaveAnOutputfile = true;
        }
    }
    else {
        cout << "Enter a filepath to open a file." << endl;
        getline(cin, fileToOpen);
    }
    inputfile.open(fileToOpen);
    if (inputfile.is_open())
    {
        cout << "Working..." << endl;
        //file has been opened. //begin reading.
        char * first = nullptr;
        int rowSize = 0, columnSize = 0;
        
        //deal with the first line
        string firstLine;
        getline(inputfile, firstLine);
        extractIntegersFromString(firstLine, rowSize, columnSize);
        //initialize a 2d array
        first= new char[rowSize * columnSize];
        
        //initialize the second.
        int * results = nullptr;
        results = new int[rowSize * columnSize];
        
        //fill up the first array
        readInFile(inputfile, first, rowSize, columnSize);
        
        if (!weHaveAnOutputfile)
        {
            //if we don't have a output file the output the input to the screen.
            printOutInputGrid(first, rowSize, columnSize);
        }
        
        //fill up the second array.
        detectTreeStands(first, results, rowSize, columnSize);
        
        if (weHaveAnOutputfile)
        {
            printOutGrid(outputfile, true, results, rowSize, columnSize);
        }
        else
        {
            printOutGrid(outputfile, false, results, rowSize, columnSize);
        }
        
        //delete our crazy array;
        delete [] results;
        delete [] first;
        
    }
    else {
        cout << "Unable to open file: " << fileToOpen << " exiting program." << endl;
    }
    return 0;
    
}
void iterativeFollowTrees(Stack<stackNode> &mainStack, char * &first, int * &results, int columnSize, int rowSize, int treeStands)
{
    /*
     This is an iterative method of solving the problem, where I manage my own stack. Works fantastic.
     */
    stackNode * tempNode = nullptr;
    while (mainStack.size() > 0) {
        bool foundT = false;
        tempNode = mainStack.getTop();
        if (tempNode->setFirstAsT == false)
        {
            tempNode->setFirstAsT = true;
            first[(columnSize * tempNode->row) + tempNode->column] = 'x';
            results[(columnSize * tempNode->row) + tempNode->column] = treeStands;
        }
        
        //check the top.
        if (tempNode->row - 1 >= 0 && tempNode->checkedTop == false)
        {
            if (first[(columnSize * (tempNode->row - 1)) + tempNode->column] == 't')
            {
                tempNode->checkedTop = true;
                foundT = true;
                stackNode * newNode = new stackNode;
                newNode->row = tempNode->row - 1;
                newNode->column = tempNode->column;
                mainStack.push(newNode);
            }
        }

        
        //Check the right.
        if (tempNode->column + 1 < columnSize && tempNode->checkedRight == false && foundT == false)
        {
            if (first[(columnSize * tempNode->row) + tempNode->column + 1] == 't')
            {
                tempNode->checkedRight = true;
                foundT = true;
                stackNode * newNode = new stackNode;
                newNode->row = tempNode->row;
                newNode->column = tempNode->column + 1;
                mainStack.push(newNode);
            }
        }
        
        //check down
        if (tempNode->row + 1 < rowSize && tempNode->checkedDown == false && foundT == false)
        {
            if (first[(columnSize * (tempNode->row + 1)) + tempNode->column] == 't')
            {
                tempNode->checkedDown = true;
                foundT = true;
                stackNode * newNode = new stackNode;
                newNode->row = tempNode->row + 1;
                newNode->column = tempNode->column;
                mainStack.push(newNode);
            }
        }
        
        
        //check left
        if (tempNode->column - 1 >= 0 && tempNode->checkedLeft == false && foundT == false)
        {
            if (first[(columnSize * tempNode->row) + tempNode->column - 1] == 't')
            {
                tempNode->checkedLeft = true;
                foundT = true;
                stackNode * newNode = new stackNode;
                newNode->row = tempNode->row;
                newNode->column = tempNode->column - 1;
                mainStack.push(newNode);
            }
        }
        
        if (foundT == false)
        {
            mainStack.pop();
        }
    }
}

void followTrees(char * &first, int * &results, int &rowSize, int &columnSize, int x, int i, int &treeStands)
{
    /*
     This is a recursive method at solving this problem. It works great but takes up a lot of Stack.
     Also I am not using it.
     */
    
    //check if x and i are still in the array
    if ((x >= 0 && i >= 0) && (x < columnSize && i < rowSize))
    {
        if (first[(columnSize * i) + x] == 't')
        {
            //this is a tree, lets mark it as checked, and as a tree
            first[(columnSize * i) + x] = 'x';
            results[(columnSize * i) + x] = treeStands;
            
            //lets see if there are tree's around it.
            followTrees(first, results, rowSize, columnSize, x, i - 1, treeStands);
            followTrees(first, results, rowSize, columnSize, x + 1, i, treeStands);
            followTrees(first, results, rowSize, columnSize, x, i + 1, treeStands);
            followTrees(first, results, rowSize, columnSize, x - 1, i, treeStands);
        }
    }
}
void detectTreeStands(char * &first, int * &results, int rowSize, int columnSize)
{
    Stack<stackNode> mainStack;
    int treeStands = 1;
    for (int i = 0; i < rowSize; i++)
    {
        for (int x = 0; x < columnSize; x++)
        {
            if (first[(columnSize * i) + x] == 't')
            {
                //followTrees(first, results, rowSize, columnSize, x, i, treeStands);
                
                //if we were using the recursion method we would not push the object to the stack here.
                stackNode * newNode = new stackNode;
                newNode->row = i;
                newNode->column = x;
                mainStack.push(newNode);
                
                iterativeFollowTrees(mainStack, first, results, columnSize, rowSize, treeStands);
                
                treeStands++;
            }
            else if (first[(columnSize * i) + x] != 'x')
            {
                results[(columnSize * i) + x] = 0;
            }
        }
    }
}
void printOutGrid(ofstream & outputfile, bool printTofile, int * & array, int rowSize, int columnSize)
{
    for (int i = 0; i < rowSize; i++)
    {
        for (int x = 0; x < columnSize; x++)
        {
            if (printTofile && outputfile.is_open())
            {
                outputfile << array[(columnSize * i) + x] << " ";
            }
            else
            {
                cout << array[(columnSize * i) + x] << " ";
            }
        }
        (printTofile && outputfile.is_open() ? outputfile << "\n" : cout << "\n");
    }
    (printTofile && outputfile.is_open() ? cout << "Output file Generated.\n" : cout << "\nDone.");
}

void printOutInputGrid(char * &array, int rowSize, int columnSize)
{
    for (int i = 0; i < rowSize; i++)
    {
        for (int x = 0; x < columnSize; x++)
        {
            cout << array[(columnSize * i) + x] << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void extractIntegersFromString(string stringToExtractFrom, int &first, int &second)
{
    string temp = "";
    for (int i = 0; i < stringToExtractFrom.length(); i++)
    {
        if (isdigit(stringToExtractFrom[i]))
        {
            // if the item is a digit lets add it to a string, which will later be converted to int
            temp = temp + stringToExtractFrom[i];
        }
        else if (stringToExtractFrom[i] == ',') {
            //middle found, lets set the first to it's integer form
            first = stoi(temp);
            temp = "";
        }
    }
    //if the line has run out of characters then we have read in the whole number, lets set it.
    second = stoi(temp);
}
void readInFile(ifstream &infile, char * &firstArray, int & rows, int & columns)
{
    //read in the data
    for (int rowCounter = 0; rowCounter < rows; rowCounter++)
    {
        for (int columnCounter = 0; columnCounter < columns; columnCounter++)
        {
            infile >> firstArray[rowCounter * columns + columnCounter];
        }
    }
}



