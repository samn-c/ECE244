//
//  Triangle.cpp
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

//  ECE244 Student: Write the implementation of the class Rectangle here


#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

#include "Shape.h"
#include "Triangle.h"


//Constructor
Triangle::Triangle (string n, float xcent, float ycent, float x1, float y1, float x2, float y2, float x3, float y3) : Shape(n, xcent, ycent) {
    xp1 = x1;
    xp2 = x2;
    xp3 = x3;
    yp1 = y1;
    yp2 = y2;
    yp3 = y3;
}

//Destructor
Triangle::~Triangle() {
    //Nothing
}

//Accessors
float Triangle::getx1() const {
    return xp1;
}
float Triangle::getx2() const {
    return xp2;
}
float Triangle::getx3() const {
    return xp3;
}
float Triangle::gety1() const {
    return yp1;
}
float Triangle::gety2() const {
    return yp2;
}
float Triangle::gety3() const {
    return yp3;
}

//Mutators
void Triangle::setx1(float x) {
    xp1 = x;
}
void Triangle::setx2(float x) {
    xp2 = x;
}
void Triangle::setx3(float x) {
    xp3 = x;
}
void Triangle::sety1(float y) {
    yp1 = y;
}
void Triangle::sety2(float y) {
    yp2 = y;
}
void Triangle::sety3(float y) {
    yp3 = y;
}

//Utility Methods
void Triangle::draw() const {
    cout << std::fixed;
    cout << std::setprecision(2);

    cout << "triangle: " << name << " "
         << x_centre << " " << y_centre
         << " " << xp1 << " " << yp1
         << " " << xp2 << " " << yp2
         << " " << xp3 << " " << yp3
         << " " << computeArea() << endl;
}

float Triangle::computeArea() const {
    float area = 0.5 * (xp1 * (yp2 - yp3) + xp2 * (yp3 - yp1) + xp3 * (yp1 - yp2));

    return (area >= 0.0) ? area : -area;
}

Shape* Triangle::clone() const {
    return (new Triangle(*this));
}