
#include "Point.h"

using namespace std;

/**
 * constructor for Point.
 */
Point::Point() {

}

/**
 * constructor for Point.
 * @param x int
 * @param y int
 */
Point::Point(int x, int y) {
    _x = x;
    _y = y;
}

/**
 * constructor for Point.
 * @param p const Point*
 */
Point::Point(const Point* p) {
    _x = p->_x;
    _y = p->_y;
}

/**
 * getting x value.
 * @return int
 */
int Point::getX() const {
    return Point::_x;
}

/**
 * setting x value.
 * @param x int
 */
void Point::setX(int x) {
    _x = x;
}

/**
 * getting the y value.
 * @return int
 */
int Point::getY() const {
    return _y;
}

/**
 * setting the y value.
 * @param y int
 */
void Point::setY(int y) {
    _y = y;
}

/**
 * return true if the nodes are equal.
 * @param p Node*
 * @return bool
 */
bool Point::operator==(Node* p) const {
    Point* p1 = (Point*) p;
    return p1->getX() == _x && p1->getY() == _y;
}

/**
* return true if the nodes are not equal.
* @param p
* @return
*/
bool Point::operator!=(Node* p) const {
    Point* p1 = (Point*)p;
    return !(p1->getX() == _x && p1->getY() == _y);
}

/**
 * function to print nodes.
 * @param output ostream&
 */
void Point::printNode(ostream& output) const {
    const Point *p1 = this;
    output << "(" << p1->getX() << "," << p1->getY() << ")" << endl;
}

//operator for +.
Node *Point::operator+(Node *p) const {
    Point* p1 = (Point*)p;
    return new Point(_x + p1->getX(), _y + p1->getY());
}

BOOST_CLASS_EXPORT(Point)