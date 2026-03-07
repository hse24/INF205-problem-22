#ifndef ADJACENCY_MATRIX_H
#define ADJACENCY_MATRIX_H

#include "graph.h"
#include <fstream>
#include <sstream>
#include <list>
#include <unordered_map>
#include <vector>

class AdjMatrix : public Graph{
private:
    // stores string with all nodes
    std::vector<std::string> allNodes;
    // create a 3dmatrix with vector with strings of edges in z direction
    std::vector<std::vector<std::vector<std::string>>> matrix;
    // needed for checkAndDelete
    bool cleanup = true;

public:
    AdjMatrix() = default;
    ~AdjMatrix();
    void addNode(std::string node);
    void addEdge(std::string node_a_label, std::string edge_label, std::string node_b_label) override;
    void checkAndDelete();
    void readFromFile(std::string filname) override;
    void readToFile(std::string filname) override;
    void disconnect(std::string node_a_label, std::string node_b_label) override;
    void removeNode(std::string node_label) override;
};

#endif