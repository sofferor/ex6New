
#include <stack>
#include "Environment.h"

/**
 * operator overloading ("<<") for printing.
 * @param p Node*
 */
void Environment::operator<<(Node *p) const {
    stack<Node*> path;
    while (p != NULL) {
        path.push(p);
        p = p->getDaddy();
    }
    while (path.size() > 0) {
        cout << path.top();
        path.pop();
    }
}

//Get the path of the trip as a vector.
vector<Node *> Environment::getPath(Node *p) const {
    vector<Node*> path;
    //Node* temp;
    while (p != NULL) {
        path.push_back(p);
        //temp = p;
        p = p->getDaddy();
        //temp->setDaddy(NULL);
        //temp->setVisited(false);
    }
    return path;
}

