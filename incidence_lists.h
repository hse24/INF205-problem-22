#ifndef INCIDENCE_lists_H
#define INCIDENCE_lists_H

#include "graph.h"
#include <fstream>
#include <sstream>
#include <list>
#include <unordered_map>
#include <vector>


class IncidenceGraph : public Graph {
private:
    struct Node;
    struct Edge;

    struct Edge {
        std::string NameEdge;
        Node* fromNode;
        Node* toNode;

        Edge(const std::string& label, Node* from, Node* to);
    };
    
    struct Node {
        std::string NameNode;
        std::list<Edge*> listEdges;
        
        Node(const std::string& label);
        void addEdge(Edge* edge);
        void removeEdge(Edge* edge);
    };

    std::unordered_map<std::string, Node*> nodes;
    Node* findOrCreateNode(const std::string label);
    std::vector<Edge*> allEdges;


public:
    IncidenceGraph() = default;
    ~IncidenceGraph();
    void addEdge(std::string node_a_label, std::string edge_label, std::string node_b_label) override;
    void readFromFile(std::string filname) override;
    void readToFile(std::string filname) override;
    void disconnect(std::string node_a_label, std::string node_b_label) override;
    void removeNode(std::string node_label) override;
};

#endif // INCIDENCE_Lists_H