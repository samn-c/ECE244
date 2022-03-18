//
//  parser.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"
#include "ShapeNode.h"
#include "GroupNode.h"
#include "ShapeList.h"
#include "GroupList.h"

// This is a pointer to the groups list
// The list itseld must be allocated
GroupList* gList;

int nameExists(string name);
void errorResponse(int errorCode, string name);
// ECE244 Student: you may want to add the prototype of
// helper functions you write here

int main() {
    // Create the groups list
    gList = new GroupList();
    
    // Create the pool group and add it to the group list
    GroupNode* poolGroup = new GroupNode(keyWordsList[NUM_KEYWORDS-1]);
    gList->insert(poolGroup);
    
    string line;
    string command;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while ( !cin.eof () ) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;

        // Check for the command and act accordingly
        // ECE244 Student: Insert your code here
        //########################################
        //SHAPE name type loc loc size size
        if (command == keyWordsList[0]) {
            lineStream >> command;
            
            int existion = nameExists(command);
            
            if (existion == 0) {
                //take the rest of input
                string type;
                int x_loc, y_loc, x_sz, y_sz;
                lineStream >> type;
                lineStream >> x_loc;
                lineStream >> y_loc;
                lineStream >> x_sz;
                lineStream >> y_sz;

                //create the shape
                Shape* newShape = new Shape(command, type, x_loc, y_loc, x_sz, y_sz);
                //create the shape node
                ShapeNode* newSNode = new ShapeNode;
                //set the shape in the shape node
                newSNode->setShape(newShape);
                //insert into pool
                gList->getHead()->getShapeList()->insert(newSNode);
                //output created shape
                newShape->draw();
            }
            else {
                //invalid name
                if (existion == 3) errorResponse(0, command);
                //name exists
                else errorResponse(1, command);
            }
        }
        //GROUP name
        else if (command == keyWordsList[1]) {
            lineStream >> command;
            
            int existion = nameExists(command);
            
            if (existion == 0) {
                GroupNode* newGNode = new GroupNode(command); //VALGRIND

                gList->insert(newGNode);

                cout << command << ": group" << endl;
            }
            else {
                //invalid name
                if (existion == 3) errorResponse(0, command);
                //name exists
                else errorResponse(1, command);
            }
        }
        //MOVE name name
        else if (command == keyWordsList[2]) {
            lineStream >> command;
            
            int existion = nameExists(command);

            //if shape exists
            if (existion == 1) {
                string name = command;

                lineStream >> command;

                int existion = nameExists(command);

                //if group exists
                if (existion == 2) {
                    string group = command;

                    //FIND SHAPE AND GROUP
                    //traverse groups
                    GroupNode* traverseG = gList -> getHead();
                    //shape search trigger
                    bool shapeFound = false;

                    //storage of group and shape
                    GroupNode* newGroup;
                    ShapeNode* moveShape;

                    while (traverseG != NULL) {
                        //search for group
                        if (traverseG -> getName() == group) {
                            newGroup = traverseG;
                        }

                        //traverse shape lists
                        ShapeList* sList = traverseG->getShapeList();

                        //search for shape
                        if (sList != NULL && !shapeFound) {
                            //find and remove the shape
                            moveShape = sList->remove(name);

                            //stop searching if found
                            if (moveShape != NULL) {
                                shapeFound = true;
                            }
                        }

                        traverseG = traverseG -> getNext();
                    }

                    newGroup->getShapeList()->insert(moveShape);

                    cout << "moved " << name << " to " << group << endl;
                }
                else {
                    //invalid name
                    if (existion == 3) errorResponse(0, command);
                    //group name doesnt exist
                    else errorResponse(3, command);
                }
            }
            else {
                //invalid name
                if (existion == 3) errorResponse(0, command);
                //shape name doesnt exist
                else errorResponse(2, command);
            }
        }
        //DELETE name
        else if (command == keyWordsList[3]) {
            lineStream >> command;
            
            int existion = nameExists(command);

            //name is keyword
            if (existion == 3) {
                //invalid name
                errorResponse(0, command);
            }
            //group delete command
            else if (existion == 2) {
                //group to delete
                GroupNode* deletion = gList->remove(command);

                //insert full list to end of pool
                gList->getHead()->getShapeList()->insert(deletion->getShapeList()->getHead());

                //loop until deletion head points to null (trick valgrind)
                while (deletion->getShapeList()->getHead() != NULL) {
                    deletion->getShapeList()->setHead(deletion->getShapeList()->getHead()->getNext());
                }
                
                //delete group
                delete deletion;
                deletion = NULL;

                //output
                cout << command << ": deleted" << endl;
            }
            //shape delete command
            else if (existion == 1) {
                //traverse groups
                GroupNode* traverseG = gList -> getHead();

                while (traverseG != NULL) {
                    //traverse shape lists
                    ShapeList* sList = traverseG->getShapeList();

                    if (sList != NULL) {
                        //find and remove the shape
                        ShapeNode* deletion = sList->remove(command);

                        //if up for deletion
                        if (deletion != NULL) {
                            //output message and delete
                            cout << deletion->getShape()->getName() << ": deleted" << endl;
                            delete deletion;
                        }
                    }

                    traverseG = traverseG -> getNext();
                }
            }
            //name doesnt exist
            else if (existion == 0) {
                //invalid shape name (hierarchy)
                errorResponse(2, command);
            }
        }
        //DRAW
        else if (command == keyWordsList[4]) {
            cout << "drawing:" << endl;
            gList -> print();
        }
        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.

    return 0;
}

// 3 for keyword, 2 for group, 1 for shape, 0 for available
int nameExists(string name) {
    //check key words
    for (int i = 0; i < NUM_KEYWORDS; i++) {
        if (name == keyWordsList[i]) {
            return 3;
        }
    }

    //check type words
    for (int i = 0; i < NUM_TYPES; i++) {
        if (name == shapeTypesList[i]) {
            return 3;
        }
    }

    //check group names
    GroupNode* traverseG = gList -> getHead();

    while (traverseG != NULL) {
        if (name == traverseG -> getName()) {
            return 2;
        }
        else {
            //check shape names
            ShapeList* sList = traverseG->getShapeList();

            if (sList != NULL) {
                if (sList->find(name) != NULL) {
                    return 1;
                }
            }

            traverseG = traverseG -> getNext();
        }
    }

    return 0;
}

// 0 invalid name, 1 name exists, 2 shape not found, 3 group not found
void errorResponse(int errorCode, string name) {
    string output = "error: ";

    //codes for each error
    switch (errorCode) {
        case 0: 
            output += "invalid name";
            break;
        case 1:
            output += "name " + name + " exists";
            break;
        case 2: 
            output += "shape " + name + " not found";
            break;
        case 3: 
            output += "group " + name + " not found";
            break;
        default:
            output = "~FUNCTION BROKE";
            break;
    }

    cout << output << endl;
}