#include <iostream>

using namespace std;

// Base class
class Shape {
public:
    void setWidth(int w) {
        width = w;
    }
    void setHeight(int h) {
        height = h;
    }

protected:
    int width;
    int height;
};

// Derived class
class Rectangle : public Shape {
public:
    int getArea() {
        return (width * height);
    }
private:
    int s;
};

int main(void) {
    Rectangle Rect;

    Rect.setWidth(5);
    Rect.setHeight(7);

    // protected data have changed to Rectangle's private data members
    // so it cannot be accessed
    // Rect.width = 1;


    // protected data is as well private data (in Shape)
/*
    Shape ap;
    ap.width = 1;*/

    //private data will not be inherite

/*
    Access	            public	protected	private
    Same    class	    yes	    yes	        yes
    Derived classes	    yes	    yes	        no
    Outside classes	    yes	    no	        no
*/
    // Print the area of the object.
    cout << "Total area: " << Rect.getArea() << endl;

    return 0;
}
