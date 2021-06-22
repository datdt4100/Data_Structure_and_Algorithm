#include <sstream>
#include <string>
#include <iostream>
#include <type_traits>
#include <math.h>
#include <bits/stdc++.h>
using namespace std;

class Point
{
private:
    double x, y;
public:
    Point()
    {
         x=0;
         y=0;
    }

    Point(double a, double b)
    {
         x=a;
         y=b;
    }

    void setX(double a)
    {
         x=a;
    }

    void setY(double b)
    {
         y=b;
    }

    double getX() const
    {
         return x;
    }

    double getY() const
    {
         return y;
    }

    double distanceToPoint(const Point& pointA)
    {
         double d;
         d= sqrt(pow(pointA.getX()-this->getX(),2)+pow(pointA.getY()-this->getY(),2));
         return d;
    }

    friend istream &operator >> (istream &in, Point &K)
	{
		in >> K.x;
		in >> K.y;
		return in;
	}
};


class Circle
{
private:
    Point center;
    double radius;

public:
    Circle()
    {
        /*
         * STUDENT ANSWER
         * TODO: set zero center's x-y and radius
         */
         radius = 0;
    }

    Circle(Point I, double R)
    {
        /*
         * STUDENT ANSWER
         */
         center.setX(I.getX());
		 center.setY(I.getY());
         radius = R;
    }

    Circle(const Circle &C)
    {
         center = C.getCenter();
         radius = C.getRadius();
    }

    void setCenter(Point point)
    {
         center.setX(point.getX());
         center.setY(point.getY());

    }

    void setRadius(double R)
    {
         radius=R;
    }

    Point getCenter() const
    {
         return center;
    }

    double getRadius() const
    {
         return radius;
    }


	bool containsPoint(const Point point)
    {
        /*
         * STUDENT ANSWER
         * TODO: check if a given point is entirely within the circle (does not count if the point lies on the circle).
                 If contain, return true.
         */
         if (center.distanceToPoint(point)<radius) return 1;
         return 0;
    }

    bool containsTriangle(Point pointA, Point pointB, Point pointC)
    {
        /*
         * STUDENT ANSWER
         * TODO: check if a given triangle ABC (A, B, C are not on the same line) is entirely within the circle (does not count if any point of the triangle lies on the circle).
                 If contain, return true.
         */
         if (center.distanceToPoint(pointA)>= radius
		 	|| center.distanceToPoint(pointB)>= radius
		 	|| center.distanceToPoint(pointC)>= radius) return 0;

		 double AB,BC,CA;
		 AB= pointA.distanceToPoint(pointB);
		 BC= pointB.distanceToPoint(pointC);
		 CA= pointC.distanceToPoint(pointA);
         if ( AB+BC == CA || AB+CA==BC || BC+CA==AB) return 0;
         return 1;
    }

	void operator=(const Circle &c2)
    {
     	this->setCenter(c2.getCenter());
     	this->setRadius(c2.radius);
    }

    bool operator==(const Circle &c2)
    {
		if (this->getRadius() != c2.getRadius()) return 0;
		if (this->center.getX() != c2.center.getX() && this->center.getY() != c2.center.getY()) return 0;
		return 1;
    }

    friend istream& operator >> (istream &in, Circle &c3)
    {
		in >> c3.center;
		in >> c3.radius;
		return in;
    }

    void printCircle()
    {
        printf("Center: {%.2f, %.2f} and Radius %.2f\n", this->center.getX(), this->center.getY(), this->radius);
    }
};

struct Node{
			Node *next;
			char *name;
		};

class Book
{
private:
    char* title;
    char* authors;
    int publishingYear;
    int numAu=0;

public:
	Node *LAu;
    Book()
    {
    	LAu = nullptr;
        title = nullptr;
        authors = nullptr;
        publishingYear = 0;
    }

    Book(const char* title, const char* authors, int publishingYear)
    {
        this->title = new char[strlen(title)+1];
        this->authors = new char[strlen(authors)+1];
        strcpy(this->title,title);
        strcpy(this->authors,authors);
        this->publishingYear = publishingYear;
        LAu = nullptr;
        makeLs(this->authors);
    }

    Book(const Book &book)
    {
        this->title = new char[strlen(book.getTitle())+1];
        this->authors = new char[strlen(book.getAuthors())+1];
        strcpy(this->title,book.getTitle());
        strcpy(this->authors,book.getAuthors());
        this->publishingYear = book.getPublishingYear();
    }

    void setTitle(const char* title)
    {
        this->title = new char[strlen(title)+1];
        strcpy(this->title,title);
        return;
    }

    void setAuthors(const char* authors)
    {
        this->authors = new char[strlen(authors)+1];
         strcpy(this->authors,authors);
         return;
    }

    void setPublishingYear(int publishingYear)
    {
        this->publishingYear = publishingYear;
        return;
    }

    char* getTitle() const
    {
        return title;
    }

    char* getAuthors() const
    {
        return authors;
    }

    int getPublishingYear() const
    {
        return publishingYear;
    }

    void getList(){
		Node *a = LAu;
		while(a!=nullptr){
			cout << a->name<<endl;
			a=a->next;
		}
	}



    ~Book()
    {
        publishingYear=0;
        delete [] authors;
        delete [] title;
    }

    void printBook(){
        printf("%s\n%s\n%d", this->title, this->authors, this->publishingYear);
    }
	void makeLs(const char* list){
		int len = strlen(list);
		int start = 0;
		int rem=0;
		while (start < len){
        	char* Aname = new char[len+1];
        	while (start < len && list[start] == ' ')
			start ++;
			rem=start;
        	while(start < len && list[start] != ','){
	        	Aname[start-rem] = list[start];
	        	start ++;
	        }
	        Aname[start-rem]='\0';
	        add(Aname);
        	start ++;
		}

	}
	void add(const char* data){
		Node *nE = new Node;
		nE->name = new char[strlen(data)+1];
		nE->next=nullptr;
		strcpy(nE->name, data);
		nE->name[strlen(data)]='\0';

		if (LAu == nullptr){
			LAu = nE;
		} else {
			Node *p = LAu;
			while (p->next != NULL) p=p->next;
			p->next = nE;
		}
	}
	void printName(){
		Node *p = LAu;
		while(p != NULL){
			cout << p->name<<endl;
			p=p->next;
		}
	}

	void printTitle(){
		cout << this->title <<endl;
	}

	void printYear(){
		cout << this->publishingYear;
	}


	Node *takeList(){
		return LAu;
	}

    friend bool checkAuthor(Book book, const char* author){
    	/*
    	char *list=book.getAuthors();
    	int len = strlen(list);
		int start = 0;
		int rem=0;

		int num;
		while (start < len && list[start] == ' ')
		start ++;
		if (start == len) num =0;
		else num = 1;

        for (start; start < len; start++){
			if (list[start] == ',') num++;
        }

        start =0;
        for (int i = 0; i < num; i++){
			bool same = 1;
        	while (start < len && list[start] == ' ')
			start ++;
			rem=start;
        	while(start < len && list[start] != ','){
	        	if(author[start-rem] != list[start]) same = 0;
	        	start ++;
	        }
			if (same) return 1;
        	start ++;
       	}
       	return 0;*/

       	Node *tmp = book.LAu;
    	if (tmp->name == nullptr)
    	    		cout << "di ts day"<<endl;
   		else cout<<"k trong: "<< strlen(tmp->name) << endl;

    	cout << tmp->name;
    	while (tmp != nullptr){

	    	if (strcmp(tmp->name,author)==0) return 1;
	    	tmp = tmp->next;
	    }
	    return 0;
    }

    friend class Printer;

};

class Printer
{
public:
    static void printBook(const Book book)
    {
        cout << book.title<<endl;
		char *list = book.getAuthors();
		int len = strlen(list);
		int start = 0;
		int rem=0;
		while (start < len){
        	char* Aname = new char[len+1];
        	while (start < len && list[start] == ' ')
			start ++;
			rem=start;
        	while(start < len && list[start] != ','){
	        	Aname[start-rem] = list[start];
	        	start ++;
	        }
	        Aname[start-rem]='\0';
	        cout << Aname << endl;
        	start ++;
		}
		cout << book.getPublishingYear();
	}
};
