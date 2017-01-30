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
bool BFS::findPath(Environment* environment, Node* start, Node* end) {
    queue<Node*> path;
    queue<Node*> toClearAllVisited;
    Node* current = start;
    path.push(current);
    vector<Node*> neighbours;
    start->setDaddy(NULL);

    //if the start and the end points are the same.
    if (*current ==  end) {
        return false;
    }

    current->setVisited(true);

    while(*current !=  end) {
        //current->setVisited(true);
        neighbours = (*environment).getNeighbours(current);
        while (neighbours.size() != 0) {
            neighbours.front()->setDaddy(current);
            neighbours.front()->setVisited(true);
            if (*neighbours.front() == end) {
                //delete all
                clean(&neighbours, &path, &toClearAllVisited);//////to see if ok
                return true;
            }
            path.push(neighbours.front());
            neighbours.erase(neighbours.begin());
        }

        //check if the path is empty - means that there is no path.
        if (path.empty()) {
            clean(&neighbours, &path, &toClearAllVisited);//////to see if ok
            return false;
        }

        toClearAllVisited.push(path.front());
        path.pop();
        current = path.front();
    }

    clean(&neighbours, &path, &toClearAllVisited);//////to see if ok
    return true;
}

void BFS::clean(vector<Node *> *nbr, queue<Node *> *path, queue<Node *> *toClearAllVisited) {
    //Clear all the nodes' member - visited.
    while (toClearAllVisited->size() > 0) {
        toClearAllVisited->front()->setVisited(false);
        toClearAllVisited->pop();
    }

    //Clear all the nodes' member - visited.
    while (path->size() > 0) {
        path->front()->setVisited(false);
        path->pop();
    }

    nbr->clear();
}

