/*
 * File:   MiniUloha8.cpp
 * Author: Petr Kuška
 *
 * Created on 14. prosince 2015, 17:21
 */

#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <sstream>

using namespace std;

/*
Obsah souboru Drawing.txt ve formatu:
shapeId x y polomer/strana
1 1 1 3
2 3 3 4
 */
#define DRAWING_FILE "Drawing.txt"

static const int circleShape = 1;
static const int squareShape = 2;

int actualPosition = 0;

class Shape {
    int shapeId;
public:
    virtual void draw() = 0;
    virtual void load(ifstream &file) = 0;
    virtual void save(ofstream &file) = 0;

    virtual ~Shape() {
    }
};

class ShapeCircle : public Shape {
    double x;
    double y;
    double r;
    static const int shapeId = circleShape;
public:

    ShapeCircle() {
    }

    ShapeCircle(double _x, double _y, double _r) : x(_x), y(_y), r(_r) {
    }

    virtual void draw() {
        cout << "Circle:" << " " << x << " " << y << " " << r << endl;
    }

    virtual void load(ifstream &file) {
        string line;
        int tmp;
        int lineCounter = 1;
        if (file.is_open()) {
            while (getline(file, line)) {
                if (actualPosition > lineCounter) {
                    continue;
                } else {
                    istringstream ss(line);
                    ss >> tmp >> x >> y >> r;
                    break;
                }
                lineCounter++;
            }
        }
        file.close();
    }

    virtual void save(ofstream &file) {
        file << shapeId << " " << x << " " << y << " " << r << endl;
    }

    virtual ~ShapeCircle() {
    }
};

class ShapeSquare : public Shape {
    double x;
    double y;
    double a;
    static const int shapeId = squareShape;
public:

    ShapeSquare() {
    }

    ShapeSquare(double _x, double _y, double _a) : x(_x), y(_y), a(_a) {
    }

    virtual void draw() {
        cout << "Square:" << " " << x << " " << y << " " << a << endl;
    }

    virtual void load(ifstream &file) {
        string line;
        int tmp;
        int lineCounter = 1;
        if (file.is_open()) {
            while (getline(file, line)) {
                if (actualPosition > lineCounter) {
                    continue;
                } else {
                    istringstream ss(line);
                    ss >> tmp >> x >> y >> a;
                    break;
                }
                lineCounter++;
            }
        }
        file.close();
    }

    virtual void save(ofstream &file) {
        file << shapeId << " " << x << " " << y << " " << a << endl;
    }

    virtual ~ShapeSquare() {
    }
};

class ShapeFactory {
public:

    Shape *createShape(int shapeId) {
        if (shapeId == circleShape) {
            return new ShapeCircle();
        } else if (shapeId == squareShape) {
            return new ShapeSquare();
        }
    }
};

class Drawing {
public:
    typedef vector<Shape *> Shapes;
private:
    Shapes shapes;
public:

    void addShape(Shape *shape) {
        shapes.push_back(shape);
    }

    void draw() {
        for (Shapes::iterator i = shapes.begin(); i != shapes.end(); i++) {
            (*i)->draw();
        }
    }

    void load(const char *fileName) {
    	int shapeId;
    	Shape* shape;
        ifstream file(fileName);
        string line;
        actualPosition = 1;
        if (file.is_open()) {
            ShapeFactory* factory = new ShapeFactory();
            while (getline(file, line)) {
                istringstream ss(line);
                ss >> shapeId;
                shape = factory->createShape(shapeId);
                ifstream tmpFile(fileName);
                shape->load(tmpFile);
                this->addShape(shape);
                actualPosition++;
            }
            file.close();
        }
    }

    void save(const char *fileName) {
        ofstream file(fileName);
        if (file.is_open()) {
            for (Shapes::iterator i = shapes.begin(); i != shapes.end(); ++i) {
                (*i)->save(file);
            }
            file.close();
        }
    }
};

/**
 *
 * @return
 */
int main() {
    Drawing drawing;

    drawing.addShape(new ShapeCircle(1, 1, 2));
    drawing.addShape(new ShapeSquare(2, 2, 4));
    drawing.draw();
    // Circle: 1 1 2
    // Square: 2 2 4
    drawing.load(DRAWING_FILE);
    drawing.draw();
    // Circle: 1 1 2
    // Square: 2 2 4
    // Circle: 1 1 3
    // Square: 3 3 4
    drawing.save(DRAWING_FILE); //ulozi navic shapeId
    // 1 1 1 2
    // 2 2 2 4
    // 1 1 1 3
    // 2 3 3 4

    getchar();
    return 0;
}