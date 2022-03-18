//
//  parser.cpp
//  lab3
//
//  Modified by Tarek Abdelrahman on 2020-10-04.
//  Created by Tarek Abdelrahman on 2018-08-25.
//  Copyright © 2018-2020 Tarek Abdelrahman.
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

// This is the shape array, to be dynamically allocated
Shape** shapesArray;

// The number of shapes in the database, to be incremented 
int shapeCount = 0;

// The value of the argument to the maxShapes command
int max_shapes;

// ECE244 Student: you may want to add the prototype of
// helper functions you write here
void deleteArray();
string errorResponse(int errorCode, string name);
Shape* search(string name);

int main() {

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
        
        //if proper input
        if (!lineStream.fail()) {
            //maxShapes
            if (command == keyWordsList[1]) {
                // take next command
                int value;
                
                lineStream >> value;

                //success
                if (!lineStream.fail() && (lineStream.peek() == 32 || lineStream.peek() == -1)) {
                    string extra;

                    lineStream >> extra;
                    //if right amount of args
                    if (lineStream.eof() && lineStream.fail()) {
                        //if already exists
                        if (shapesArray != NULL) {
                            //delete the old array and old shapeCount
                            deleteArray();
                        }

                        //after deleting, set max shapes
                        max_shapes = value;

                        //new array
                        shapesArray = new Shape*[max_shapes];

                        //output message
                        cout << "New database: max shapes is " << max_shapes << endl;
                    }
                    else {
                        cout << errorResponse(7, "beep") << endl;
                    }
                }
                //fail
                else {
                    //notify error
                    if (lineStream.eof()) {
                        //too few arguments
                        cout << errorResponse(8, "beep") << endl;    
                    }
                    else {
                        //invalid argument
                        cout << errorResponse(1, "beep") << endl;
                    }
                }
            }
            
            //create
            else if (command == keyWordsList[2]) {
                string name;
                //get name
                lineStream >> name;

                if (!lineStream.fail()) {
                    //name taken check
                    bool nameTaken = false;
                    for (int i = 0; i < shapeCount; i++) {
                        if (shapesArray != NULL) {
                            if (shapesArray[i] != NULL) {
                                if (name == (shapesArray[i])->getName()) {
                                    nameTaken = true;
                                    //notify name taken
                                    cout << errorResponse(3, name) << endl;
                                    break;
                                }
                            }
                        }
                    }

                    //check in keyword list for name
                    for (int i = 0; i < NUM_KEYWORDS; i++) {
                        if (name == keyWordsList[i]) {
                            nameTaken = true;
                            cout << errorResponse(2, name) << endl;
                            break;
                        }
                    }
                    
                    //check in shape type list for name
                    for (int i = 0; i < NUM_TYPES; i++) {
                        if (name == shapeTypesList[i]) {
                            nameTaken = true;
                            cout << errorResponse(2, name) << endl;
                            break;
                        }
                    }
                    
                    //if available name
                    if (!nameTaken) {
                        string type;
                        //get type
                        lineStream >> type;

                        if (!lineStream.fail()) {
                            //if shape exists
                            bool realShape = false;

                            for (int i = 0; i < NUM_TYPES; i++) {
                                if (type == shapeTypesList[i]){
                                    realShape = true;
                                    break;
                                }
                            }

                            //continue to locations
                            if (realShape) {
                                int x_loc;

                                lineStream >> x_loc;

                                //if valid argument
                                if (!lineStream.fail() && x_loc >= 0 && (lineStream.peek() == 32 || lineStream.peek() == -1)) {
                                    int y_loc;

                                    lineStream >> y_loc;

                                    //if valid argument
                                    if (!lineStream.fail() && y_loc >= 0 && (lineStream.peek() == 32 || lineStream.peek() == -1)) {
                                        int x_sz;

                                        lineStream >> x_sz;

                                        if (!lineStream.fail() && x_sz >= 0 && (lineStream.peek() == 32 || lineStream.peek() == -1)) {
                                            int y_sz;

                                            lineStream >> y_sz;

                                            if (!lineStream.fail() && y_sz >= 0 && (lineStream.peek() == 32 || lineStream.peek() == -1)) {
                                                string extra;

                                                lineStream >> extra;

                                                //if right amount of args
                                                if (lineStream.eof() && lineStream.fail()) {
                                                    bool validCircle = true;

                                                    if (type == shapeTypesList[0] && y_sz != x_sz) {
                                                        validCircle = false;
                                                    }

                                                    if (validCircle) {
                                                        if (shapeCount != max_shapes) {
                                                            Shape* newShape;

                                                            newShape = new Shape(name, type, x_loc, x_sz, y_loc, y_sz);

                                                            shapesArray[shapeCount] = newShape;
                                                            
                                                            shapeCount++;

                                                            cout << "Created ";
                                                            newShape->draw();
                                                            cout << endl;
                                                        }
                                                        else {
                                                            cout << errorResponse(9, "beep") << endl;
                                                        }
                                                    }
                                                    else {
                                                        //invalid value
                                                        cout << errorResponse(6, "beep") << endl;
                                                    }
                                                } 
                                                //too many args                    
                                                else {
                                                    cout << errorResponse(7, "beep") << endl;
                                                }
                                            }
                                            //if y_size not right
                                            else {
                                                if (lineStream.fail()) {
                                                    if (lineStream.eof()) {
                                                        //too few arguments
                                                        cout << errorResponse(8, "beep") << endl;
                                                    }
                                                    else {
                                                        //invalid argument
                                                        cout << errorResponse(1, "beep") << endl;
                                                    }
                                                }
                                                else if (y_sz < 0) {
                                                    //invalid value
                                                    cout << errorResponse(6, "beep") << endl;
                                                }
                                                else {
                                                    //invalid argument
                                                    cout << errorResponse(1, "beep") << endl;
                                                }
                                            }
                                        }
                                        //if x_size not right
                                        else {
                                            if (lineStream.fail()) {
                                                if (lineStream.eof()) {
                                                    //too few arguments
                                                    cout << errorResponse(8, "beep") << endl;
                                                }
                                                else {
                                                    //invalid argument
                                                    cout << errorResponse(1, "beep") << endl;
                                                }
                                            }
                                            else if (x_sz < 0) {
                                                //invalid value
                                                cout << errorResponse(6, "beep") << endl;
                                            }
                                            else {
                                                //invalid argument
                                                cout << errorResponse(1, "beep") << endl;
                                            }
                                        }
                                    }
                                    //if y_loc fails
                                    else {
                                        if (lineStream.fail()) {
                                            if (lineStream.eof()) {
                                                //too few arguments
                                                cout << errorResponse(8, "beep") << endl;
                                            }
                                            else {
                                                //invalid argument
                                                cout << errorResponse(1, "beep") << endl;
                                            }
                                        }
                                        else if (y_loc < 0) {
                                            //invalid value
                                            cout << errorResponse(6, "beep") << endl;
                                        }
                                        else {
                                            //invalid argument
                                            cout << errorResponse(1, "beep") << endl;
                                        }
                                    }
                                }
                                //if x_loc fails
                                else {
                                    if (lineStream.fail()) {
                                        if (lineStream.eof()) {
                                            //too few arguments
                                            cout << errorResponse(8, "beep") << endl;
                                        }
                                        else {
                                            //invalid argument
                                            cout << errorResponse(1, "beep") << endl;
                                        }
                                    }
                                    else if (x_loc < 0) {
                                        //invalid value
                                        cout << errorResponse(6, "beep") << endl;
                                    }
                                    else {
                                        //invalid argument
                                        cout << errorResponse(1, "beep") << endl;
                                    }
                                }
                            }
                            //if shape doesnt exist
                            else {
                                //invalid shape type
                                cout << errorResponse(5, "beep") << endl;    
                            }
                        }
                        //if type cant be extracted
                        else {
                            //notify error
                            if (lineStream.eof()) {
                                //too few arguments
                                cout << errorResponse(8, "beep") << endl;   
                            }
                            else {
                                cout << errorResponse(100, "beep") << endl;
                            }
                        }
                    }
                }
                //if name cant be extracted
                else {
                    //notify error
                    if (lineStream.eof()) {
                        //too few arguments
                        cout << errorResponse(8, "beep") << endl;    
                    }
                }
            }   
            
            //move
            else if (command == keyWordsList[3]) {
                string name;

                lineStream >> name;

                //if works
                if (!lineStream.fail()) {
                    //search for the shape
                    Shape* found = search(name);

                    //if shape found
                    if (found != NULL) {
                        int x_loc;

                        lineStream >> x_loc;
                        
                        //if valid argument 
                        if (!lineStream.fail() && x_loc >= 0 && (lineStream.peek() == 32 || lineStream.peek() == -1)) {
                            int y_loc;

                            lineStream >> y_loc;

                            //if valid argument
                            if (!lineStream.fail() && y_loc >= 0 && (lineStream.peek() == 32 || lineStream.peek() == -1)) {
                                string extra;

                                lineStream >> extra;

                                //if right amount of args
                                if (lineStream.eof() && lineStream.fail()) {
                                    found->setXlocation(x_loc);
                                    found->setYlocation(y_loc);
                                    
                                    cout << "Moved " << found->getName() << " to " << found->getXlocation() << " " << found->getYlocation() << endl;
                                }
                                //too many args              
                                else {
                                    cout << errorResponse(7, "beep") << endl;
                                }
                            }
                            //if y_loc fails
                            else {
                                if (lineStream.fail()) {
                                    if (lineStream.eof()) {
                                        //too few arguments
                                        cout << errorResponse(8, "beep") << endl;
                                    }
                                    else {
                                        //invalid argument
                                        cout << errorResponse(1, "beep") << endl;
                                    }
                                }
                                else if (y_loc < 0) {
                                    //invalid value
                                    cout << errorResponse(6, "beep") << endl;
                                }
                                else {
                                    //invalid argument
                                    cout << errorResponse(1, "beep") << endl;
                                }
                            }
                        }
                        //if x_loc fails
                        else {
                            if (lineStream.fail()) {
                                if (lineStream.eof()) {
                                    //too few arguments
                                    cout << errorResponse(8, "beep") << endl;
                                }
                                else {
                                    //invalid argument
                                    cout << errorResponse(1, "beep") << endl;
                                }
                            }
                            else if (x_loc < 0) {
                                //invalid value
                                cout << errorResponse(6, "beep") << endl;
                            }
                            else {
                                //invalid argument
                                cout << errorResponse(1, "beep") << endl;
                            }
                        }

                    }
                    else {
                        //shape not found 
                        cout << errorResponse(4, name) << endl;  
                    }
                }
                //if cant extract name
                else {
                    //notify error
                    if (lineStream.eof()) {
                        //too few arguments
                        cout << errorResponse(8, "beep") << endl;    
                    }
                }
            }   
            
            //rotate
            else if (command == keyWordsList[4]) {
                string name;

                lineStream >> name;

                //if works
                if (!lineStream.fail()) {
                    //search for the shape
                    Shape* found = search(name);

                    //if shape found
                    if (found != NULL) {
                        int rotate;

                        lineStream >> rotate;
                        
                        //if valid argument 
                        if (!lineStream.fail() && rotate >= 0 && rotate <= 360 && (lineStream.peek() == 32 || lineStream.peek() == -1)) {
                            string extra;

                            lineStream >> extra;

                            //if right amount of args
                            if (lineStream.eof() && lineStream.fail()) {
                                found->setRotate(rotate);
                                
                                cout << "Rotated " << found->getName() << " by " << rotate << " degrees" << endl;
                            }
                            //too many args              
                            else {
                                cout << errorResponse(7, "beep") << endl;
                            }
                        }
                        //if rotate fails
                        else {
                            if (lineStream.fail()) {
                                if (lineStream.eof()) {
                                    //too few arguments
                                    cout << errorResponse(8, "beep") << endl;
                                }
                                else {
                                    //invalid argument
                                    cout << errorResponse(1, "beep") << endl;
                                }
                            }
                            else if (rotate < 0 || rotate > 360) {
                                //invalid value
                                cout << errorResponse(6, "beep") << endl;
                            }
                            else {
                                //invalid argument
                                cout << errorResponse(1, "beep") << endl;
                            }
                        }

                    }
                    else {
                        //shape not found 
                        cout << errorResponse(4, name) << endl;  
                    }
                }
                //if cant extract name
                else {
                    //notify error
                    if (lineStream.eof()) {
                        //too few arguments
                        cout << errorResponse(8, "beep") << endl;    
                    }
                }
            }   
            
            //draw
            else if (command == keyWordsList[5]) {
                string name;
                
                lineStream >> name;

                //if works
                if (!lineStream.fail()) {
                    string extra;

                    lineStream >> extra;
                    
                    //search for the shape
                    Shape* found = search(name);

                    //if shape found
                    if (found != NULL) {
                        //if right amount of args
                        if (lineStream.eof() && lineStream.fail()) {
                            cout << "Drew ";
                            found->draw();
                            cout << endl;
                        }
                        else {
                            //too many args
                            cout << errorResponse(7, "beep") << endl;
                        }
                    }
                    //if not found
                    else {
                        //all?
                        if (name == keyWordsList[0]) {
                            //if right amount of args
                            if (lineStream.eof() && lineStream.fail()) {
                                cout << "Drew all shapes" << endl;
                                for (int i = 0; i < shapeCount; i++) {
                                    if (shapesArray[i] != NULL) {
                                        shapesArray[i]->draw();
                                        cout << endl; 
                                    }
                                }
                            }
                            else {
                                //too many args
                                cout << errorResponse(7, "beep") << endl;
                            }
                        }
                        else {
                            //shape not found 
                            cout << errorResponse(4, name) << endl;
                        }
                    }
                }
                else {
                    //too few arguments
                    cout << errorResponse(8, "beep") << endl;    
                }
            }   
            
            //delete
            else if (command == keyWordsList[6]) {
                string name;
                
                lineStream >> name;

                //if works
                if (!lineStream.fail()) {
                    string extra;

                    lineStream >> extra;

                    //search for the shape
                    Shape* found = search(name);

                    //if shape found
                    if (found != NULL) {
                        //if right amount of args
                        if (lineStream.eof() && lineStream.fail()) {
                            for (int i = 0; i < shapeCount; i++) {
                                if (name == shapesArray[i]->getName()) {
                                    cout << "Deleted shape " << name << endl;
                                    delete shapesArray[i];
                                    shapesArray[i] = NULL;
                                    break;
                                }
                            }
                        }
                        else {
                            //too many args
                            cout << errorResponse(7, "beep") << endl;
                        }
                    }
                    //if not found
                    else {
                        //all?
                        if (name == keyWordsList[0]) {
                            //if right amount of args
                            if (lineStream.eof() && lineStream.fail()) {
                                //DELETE ALL SHAPES
                                for (int i = 0; i < shapeCount; i++) {
                                    delete shapesArray[i];
                                    shapesArray[i] = NULL;
                                }
                                cout << "Deleted: all shapes" << endl; 
                            }
                            else {
                                //too many args
                                cout << errorResponse(7, "beep") << endl;
                            }
                        }
                        else {
                            //shape not found 
                            cout << errorResponse(4, name) << endl;
                        }
                    }
                }
                else {
                    //too few arguments
                    cout << errorResponse(8, "beep") << endl;    
                }
            }  
            
            //if nothing works
            else {
                cout << errorResponse(0, "beep") << endl;
            } 
        }
        
        //make sure linestream is cleared, even tho it does get cleared on its own
        lineStream.clear();

        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.
    
    return 0;
}

//delete all shapes
void deleteArray() {
    //delete each shape
    for (int i = 0; i < shapeCount; i++) {
        delete shapesArray[i];

        //no more dangling pointer
        shapesArray[i] = NULL;
    }

    //deletes the pointers
    delete [] shapesArray;

    //no more dangling pointer to the start of the deleted shape array
    shapesArray = NULL;

    //reset shape count to zero
    shapeCount = 0;
}

string errorResponse(int errorCode, string name) {
    string output = "Error: ";

    //codes for each error
    switch (errorCode) {
        case 0: 
            output += "invalid command";
            break;
        case 1:
            output += "invalid argument";
            break;
        case 2: 
            output += "invalid shape name";
            break;
        case 3: 
            output += "shape " + name + " exists";
            break;
        case 4: 
            output += "shape " + name + " not found";
            break;
        case 5: 
            output += "invalid shape type";
            break;
        case 6: 
            output += "invalid value";
            break;
        case 7: 
            output += "too many arguments";
            break;
        case 8: 
            output += "too few arguments";
            break;
        case 9: 
            output += "shape array is full";
            break;
        default:
            output = "~function broke";
            break;
    }

    return output;
}

Shape* search(string name) {
    for (int i = 0; i < shapeCount; i++) {
        if (shapesArray[i] != NULL) {
            if (((shapesArray[i])->getName()) == name) {
                return shapesArray[i];
            }
        }
    }
    return NULL;
}