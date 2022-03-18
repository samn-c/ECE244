//
//  ShapeList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the ShapeList class below

#include "ShapeList.h"
#include "ShapeNode.h"
#include "Shape.h"
#include <iostream>
#include <string>

ShapeList::ShapeList() {
    head = NULL;
}

ShapeList::~ShapeList() {
    //to delete
    ShapeNode* ptr;

    while (head != NULL) {
        //set next node to current node
        ptr = head;
        
        //traverse to next node
        head = ptr -> getNext();

        //delete current
        delete ptr;
    }
    //set deletion pointer to null
    ptr = NULL;
}

ShapeNode* ShapeList::getHead() const {
    return head;
}

void ShapeList::setHead(ShapeNode* ptr) {
    head = ptr;
}

ShapeNode* ShapeList::find(string name) const {
    //to traverse
    ShapeNode* ptr = head;
    
    while (ptr != NULL) {
        if (ptr -> getShape() -> getName() == name) {
            return ptr;
        }
        else {
            ptr = ptr -> getNext();
        }
    }
    //if none found
    return NULL;
}

void ShapeList::insert(ShapeNode* s) {
    //if no head
    if (head == NULL) {
        head = s;
    }
    else {
        //to traverse
        ShapeNode* ptr = head;

        //until the end of list is found
        while (ptr -> getNext() != NULL) {
            ptr = ptr -> getNext();
        }

        //append to end of list
        ptr -> setNext(s);
    }
}

ShapeNode* ShapeList::remove(string name) {
    ShapeNode* previous = NULL;
    ShapeNode* current = head;
    
    //while there is a node to look at
    while (current != NULL) {
        //set next since there is node to look at
        ShapeNode* next = current -> getNext();

        if (current -> getShape() -> getName() == name) {
            //if remove head
            if (previous == NULL) {
                head = next;
            }
            else {
                previous -> setNext(next);
            }

            current -> setNext(NULL);
            return current;
        }
        else {
            //shift pointers
            previous = current;
            current = next;
            //only if next exists
            next = (next != NULL) ? next -> getNext() : NULL;
        }
    }

    //if no node found
    return NULL;
}

void ShapeList::print() const {
    //to traverse nodes
    ShapeNode* ptr = head;

    while (ptr != NULL) {
        //output
        ptr -> print();

        //onto next node
        ptr = ptr -> getNext();
    }
}
