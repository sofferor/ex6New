#include <queue>
#include "BFS.h"


/**
 * constructor for BFS.
 */
BFS::BFS() {}

/**
 * finding the path from one node to another using the BFS algorithm.
 * @param environment Environment*
 * @param start Node*
 * @param end Node*
 */
void BFS::findPath(Environment* environment, Node* start, Node* end) {
    queue<Node*> path;
    queue<Node*> toClearAllVisited;
    Node* current = start;
    path.push(current);
    vector<Node*> neighbours;
    start->setDaddy(NULL);
    current->setVisited(true);

    while(*current !=  end) {
        //current->setVisited(true);
        neighbours = (*environment).getNeighbours(current);
        while (neighbours.size() != 0) {
            neighbours.front()->setDaddy(current);
            neighbours.front()->setVisited(true);
            if (*neighbours.front() == end) {
                return;
            }
            path.push(neighbours.front());
            neighbours.erase(neighbours.begin());
        }
        toClearAllVisited.push(path.front());
        path.pop();
        current = path.front();
    }

    //Clear all the nodes' member - visited.
    while (toClearAllVisited.size() > 0) {
        toClearAllVisited.front()->setVisited(false);
        toClearAllVisited.pop();
    }
}