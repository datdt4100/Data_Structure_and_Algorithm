#include <sstream>
#include <string>
#include <iostream>
#include <type_traits>
#include <math.h>
#include <bits/stdc++.h>
using namespace std;

#ifndef _TOY_H_
#define _TOY_H_

enum Color
{
    red,
    green,
    blue
};

enum Size
{
    small,
    medium,
    big
};
class Toy
{
protected:
    double price;
public:
    Toy(double price)
    {
        this->price = price;
    }
    virtual void printType() = 0;
    friend class ToyBox;
};

class CarToy : public Toy
{
private:
    Color color;
public:
    CarToy(double price, Color color) : Toy(price)
    {
        /*
         * STUDENT ANSWER
         */
         this->color = color;
    }
    void printType()
    {
        cout << "This is a car toy\n";
    }
    friend class ToyBox;
};
class PuzzleToy : public Toy
{
private:
    Size size;
public:
    PuzzleToy(double price, Size size) : Toy(price)
    {
        /*
         * STUDENT ANSWER
         */
         this->size = size;
    }
    void printType()
    {
        cout << "This is a puzzle toy\n";
    }
    friend class ToyBox;
};
class ToyBox
{
private:
    Toy *toyBox[5];
    int numberOfItems;
public:
    ToyBox()
    {
        /*
         * STUDENT ANSWER
         * TODO: set zero numberOfItems and nullptr toyBox
         */
         this->numberOfItems = 0;
         for (int i=0;i<5;i++){
            toyBox[i]=nullptr;
         }
    }
    int addItem(const CarToy &carToy)
    {
        /*
         * STUDENT ANSWER
         * TODO: function add a new Car toy to the box.
                 If successfully added, the function returns the current number of toys in the box.
                 If the box is full, return -1.
         */
         int i=0;
         while (toyBox[i]){
            i++;
         }
         if (i<5) {
            toyBox[i] = new CarToy(carToy.price, carToy.color);
            numberOfItems++;
            return numberOfItems;
         }
         cout << i<<endl;
         return -1;
    }
    int addItem(const PuzzleToy &puzzleToy)
    {
        /*
         * STUDENT ANSWER
         * TODO: function add a new Puzzle toy to the box.
                 If successfully added, the function returns the current number of toys in the box.
                 If the box is full, return -1.
         */
        int i=0;
         while (toyBox[i]){
            i++;
         }
         if (i<5) {
            toyBox[i] = new PuzzleToy(puzzleToy.price,puzzleToy.size);
            numberOfItems++;
            return numberOfItems;
         }
         return -1;
    }
    void printBox()
    {
        for (int i = 0; i < numberOfItems; i++)
            toyBox[i]->printType();
    }
};

#endif // _TOY_H_
