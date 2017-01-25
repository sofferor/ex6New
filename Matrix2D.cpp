
#include "Matrix2D.h"
#include "Point.h"

/**
 * constructor for Matrix2D.
 * @param x int
 * @param y int
 */
Matrix2D::Matrix2D(int x, int y) {
    sizeOfX = x;
    sizeOfY = y;
    //Resize the matrix.
    matrix.resize(x);
    for (int i = 0; i < x; i++) {
        matrix.at(i).resize(y);
    }
    for (int i = 0; i < x; i++) {
        for (int j = 0; j < y; j++) {
            Point* p = new Point(i, j);
            matrix.at(i).at(j) = p;
        }
    }
}

/**
 * destructor for Matrix2D.
 */
Matrix2D::~Matrix2D() {
    for (int i = 0; i < sizeOfX; i++) {
        for (int j = 0; j < sizeOfY; j++) {
            if (matrix.at(i).at(j) != NULL) {
                delete matrix.at(i).at(j);
            }
        }
        matrix.at(i).clear();
    }
    matrix.clear();
}

/**
 * getting the neighbours of a given node.
 * @param node Node *
 * @return vector<Node *>
 */
vector<Node *> Matrix2D::getNeighbours(Node *node) {
    vector<Node*> neighbours;
    Point* nodePoint = (Point*)node;

    int x = nodePoint->getX();
    int y = nodePoint->getY();
    if (x - 1 > -1) {
        neighbours.push_back(matrix.at(x - 1).at(y));
    }
    if (y < sizeOfY - 1) {
        neighbours.push_back(matrix.at(x).at(y + 1));
    }
    if (x + 1 < sizeOfX) {
        neighbours.push_back(matrix.at(x + 1).at(y));
    }
    if (y - 1 > -1) {
        neighbours.push_back(matrix.at(x).at(y - 1));
    }

    for (int j = 0; j < neighbours.size(); j++) {
        if (neighbours.at(j) != NULL) {
            if (neighbours.at(j)->isVisited() || neighbours.at(j)->isObstacle()) {
                neighbours.erase(neighbours.begin() + j);
                j--;
            }
        }
    }

    return neighbours;
}

/**
 * return true if a given node exist in the environment.
 * @param node Node *
 * @return bool
 */
bool Matrix2D::isInEnvironment(Node *node) {
    Point* pNode = (Point*) node;
    return pNode->getX() >= 0 && pNode->getX() < sizeOfX
           && pNode->getY() >= 0 && pNode->getY() < sizeOfY;
}

/**
 * return a pointer to node in the matrix.
 * @param node Node*
 * @return Node*
 */
Node* Matrix2D::getNodeInMatrix(Node* node) {
    Point* pNode = (Point*) node;
    if (this->isInEnvironment(node)) {
        return matrix[pNode->getX()][pNode->getY()];
    }
    return NULL;
}

//Getting the size of x.
int Matrix2D::getSizeOfX() const {
    return sizeOfX;
}

//Getting the size of y.
int Matrix2D::getSizeOfY() const {
    return sizeOfY;
}

//initialize the Environment.
void Matrix2D::initializeEnvironment() {
    for (int i = 0; i < sizeOfX; i++) {
        for (int j = 0; j < sizeOfY; j++) {
            matrix.at(i).at(j)->setDaddy(NULL);
            matrix.at(i).at(j)->setVisited(false);
        }
    }
}
