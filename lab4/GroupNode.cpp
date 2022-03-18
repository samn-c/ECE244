//
//  GroupNode.cpp
//  Lab4
//
//  Created by Tarek Abdelrahman on 2020-10-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student:
//  Write the implementation (and only the implementation) of the GroupNode class below

#include "GroupNode.h"
#include "ShapeList.h"
#include "ShapeNode.h"
#include "Shape.h"
#include <iostream>
#include <string>

GroupNode::GroupNode(string n) {
    name = n;
    myShapeList = new ShapeList(); //VALGRIND
    next = NULL;
}

GroupNode::~GroupNode() {
    delete myShapeList;
    myShapeList = NULL;
    next = NULL;
}

string GroupNode::getName() const {
    return name;
}

ShapeList* GroupNode::getShapeList() const {
    return myShapeList;
}

void GroupNode::setShapeList(ShapeList* ptr) {
    myShapeList = ptr;
}

GroupNode* GroupNode::getNext() const {
    return next;
}

void GroupNode::setNext(GroupNode* ptr) {
    next = ptr;
}

void GroupNode::print() const {
    cout << name << ":" << endl;

    myShapeList -> print();
}