#include <iostream>
#include <vector>
#include "Node.h"
#include "Environment.h"

#ifndef CABSTATION_BFS_H
#define CABSTATION_BFS_H

using namespace std;

/**
 * BFS class.
 * for finding the pass between 2 nodes using the BFS algorithm.
 */
class BFS {
public:
    /**
     * constructor for BFS.
     */
    BFS();

    /**
     * finding the path from one node to another using the BFS algorithm.
     * @param environment Environment*
     * @param start Node*
     * @param end Node*
     */
    void findPath(Environment* environment, Node* start, Node* end);
};


#endif //CABSTATION_BFS_H
