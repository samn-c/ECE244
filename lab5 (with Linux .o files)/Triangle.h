//
//  Triangle.h
//  Lab5
//
//  Created by Tarek Abdelrahman on 2020-11-25.
//  Copyright © 2020 Tarek Abdelrahman.
//
//  Permission is hereby granted to use this code in ECE244 at
//  the University of Toronto. It is prohibited to distribute
//  this code, either publicly or to third parties.

#ifndef Triangle_h
#define Triangle_h

#include <iostream>
#include <string>
using namespace std;


// This class implements the triangle Shape objects.
// ECE244 Student: Write the definition of the class here.
#include "Shape.h"

class Triangle : Shape {
    private:
        float xp1, yp1, xp2, yp2, xp3, yp3;

    public:
        //Constructor
        Triangle (string n, float xcent, float ycent, float x1, float y1, float x2, float y2, float x3, float y3);

        //Destructor
        virtual ~Triangle();

        //Accessors
        float getx1() const;
        float getx2() const;
        float getx3() const;
        float gety1() const;
        float gety2() const;
        float gety3() const;

        //Mutators
        void setx1(float x);
        void setx2(float x);
        void setx3(float x);
        void sety1(float y);
        void sety2(float y);
        void sety3(float y);

        //Utility Methods
        virtual void draw() const;

        virtual float computeArea() const;

        virtual Shape* clone() const;
};

#endif /* Triangle_h */


