
#ifndef EX1_NODE_H
#define EX1_NODE_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>


#include <iostream>
#include <boost/serialization/access.hpp>
#include <boost/serialization/assume_abstract.hpp>
#include <boost/serialization/export.hpp>

using namespace std;

/**
 * class for Node.
 * an abstract class for a node in the world.
 */
class Node {
protected:
    bool visited;
    bool obstacle;
    Node* daddy;

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & visited;
        ar & obstacle;
        ar & daddy;
    }

public:
    /**
     * constructor for Node.
     */
    Node();

    /**
     * Copy constructor for Node.
     */
    Node(Node* node);


    /**
     * setting daddy of a node.
     * @param dad
     */
    virtual void setDaddy(Node* dad);

    /**
     * get the daddy of a node.
     * @return Node*
     */
    Node* getDaddy() const;

    /**
     * return true if the node was already visited.
     * @return bool
     */
    bool isVisited() const;

    //return true if obstacle.
    bool isObstacle() const;

    //set obstacle.
    void setObstacle(bool obstacle);

    /**
     * setting true if the node has been visited.
     * @param visited
     */
    void setVisited(bool visited);

    /**
     * return true if the nodes are equal.
     * @param p
     * @return bool
     */
    virtual inline bool operator==(Node* p) const = 0;

    /**
     * return true if the nodes are not equal.
     * @param p
     * @return
     */
    virtual inline bool operator!=(Node* p) const = 0;

    //operator for +.
    virtual inline Node* operator+(Node* p) const = 0;

    /**
     * function to print nodes.
     * @param output
     */
    virtual void printNode(ostream& output) const = 0;

    /**
     * operator overloading ("<<") to print nodes.
     * @param output
     * @param n
     * @return ostream&
     */
    friend ostream& operator<<(ostream &output, const Node* n);

    /**
     * destructor for node.
     */
    virtual ~Node() {};
};

BOOST_SERIALIZATION_ASSUME_ABSTRACT(Node)


#endif //EX1_NODE_H
