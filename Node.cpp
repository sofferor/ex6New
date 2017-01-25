#include <iostream>
#include "Node.h"


/**
 * constructor for Node.
 */
Node::Node() {
    Node::daddy = NULL;
    Node::visited = false;
    Node::obstacle = false;
}

/**
 * constructor for Node.
 */
Node::Node(Node* node) {
    Node::daddy = NULL;
    Node::visited = node->isVisited();
    Node::obstacle = node->isObstacle();
}

/**
 * setting daddy of a node.
 * @param dad
 */
void Node::setDaddy(Node* dad) {
    Node::daddy = dad;
}

/**
 * get the daddy of a node.
 * @return Node*
 */
Node* Node::getDaddy() const {
    return daddy;
}

/**
 * return true if the node was already visited.
 * @return bool
 */
bool Node::isVisited() const {
    return visited;
}

/**
 * setting true if the node has been visited.
 * @param visited
 */
void Node::setVisited(bool visited) {
    Node::visited = visited;
}

/**
 * function to print nodes.
 * @param output
 */
ostream &operator<<(ostream &output, const Node* n) {
    n->printNode(output);
    return output;
}

//return true if obstacle.
bool Node::isObstacle() const {
    return obstacle;
}

//set obstacle.
void Node::setObstacle(bool obstacle) {
    Node::obstacle = obstacle;
}

