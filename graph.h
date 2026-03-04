#ifndef GRAPH_H
#define GRAPH_H

#include <string>

class Graph {
public:
    virtual ~Graph() = default;
    virtual void addEdge(std::string node_a_label, std::string edge_label, std::string node_b_label) = 0;
    virtual void readFromFile(std::string filname) = 0;
    virtual void readToFile(std::string filname) = 0;
    virtual void disconnect(std::string node_a_label, std::string node_b_label) = 0;
    virtual void removeNode(std::string node_label) = 0;
};

#endif 