#include "Environment.h"
#include "Node.h"

#ifndef CABSTATION_MATRIX2D_H
#define CABSTATION_MATRIX2D_H

/**
 * class for Matrix2D.
 * kind of an Environment
 */
class Matrix2D: public Environment {
private:
    int sizeOfX;
    int sizeOfY;
    vector<vector<Node*> > matrix;
public:
    /**
     * constructor for Matrix2D.
     * @param x int
     * @param y int
     */
    Matrix2D(int x, int y);

    /**
     * return a pointer to node in the matrix.
     * @param node Node*
     * @return Node*
     */
    Node* getNodeInMatrix(Node *node);

    /**
     * getting the neighbours of a given node.
     * @param node Node*
     * @return vector<Node*>
     */
    vector<Node*> getNeighbours(Node* node);

    /**
     * return true if a given node exist in the environment.
     * @param node Node*
     * @return bool
     */
    bool isInEnvironment(Node* node);

    /**
     * destructor for Matrix2D.
     */
    virtual ~Matrix2D();

    //Getting the size of x.
    int getSizeOfX() const;

    //Getting the size of y.
    int getSizeOfY() const;

    //initialize the Environment.
    void initializeEnvironment();
};


#endif //CABSTATION_MATRIX2D_H
