//
//  GroupList.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the GroupList class below

#include "GroupList.h"
#include "GroupNode.h"
#include "ShapeList.h"
#include "ShapeNode.h"
#include "Shape.h"
#include <iostream>
#include <string>

GroupList::GroupList() {
    head = NULL;
}

GroupList::~GroupList() {
    //to delete
    GroupNode* ptr;

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

GroupNode* GroupList::getHead() const {
    return head;
}

void GroupList::setHead(GroupNode* ptr) {
    head = ptr;
}

void GroupList::insert(GroupNode* s) {
    //if no head
    if (head == NULL) {
        head = s;
    }
    else {
        //to traverse
        GroupNode* ptr = head;

        //until the end of list is found
        while (ptr -> getNext() != NULL) {
            ptr = ptr -> getNext();
        }

        //append to end of list
        ptr -> setNext(s);
    }
}

GroupNode* GroupList::remove(string name) {
    GroupNode* previous = NULL;
    GroupNode* current = head;
    
    //while there is a node to look at
    while (current != NULL) {
        //set next since there is node to look at
        GroupNode* next = current -> getNext();

        if (current -> getName() == name) {
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

void GroupList::print() const {
    
    //to traverse nodes
    GroupNode* ptr = head;

    while (ptr != NULL) {
        //output
        ptr -> print();

        //onto next node
        ptr = ptr -> getNext();
    }
}