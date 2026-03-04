#include "incidence_lists.h"

#include <list>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

IncidenceGraph::Edge::Edge(const std::string& label, Node* from, Node* to)
    : NameEdge(label), fromNode(from), toNode(to) {}

IncidenceGraph::Node::Node(const std::string& label) : NameNode(label) {}

void IncidenceGraph::Node::addEdge(Edge* edge){
    listEdges.push_back(edge);
}

void IncidenceGraph::Node::removeEdge(Edge* edge){
    listEdges.remove(edge);
}

IncidenceGraph::Node* IncidenceGraph::findOrCreateNode(const std::string label){
    auto nameNode = nodes.find(label);
    if (nameNode != nodes.end()){
        return nameNode->second;
    }
    Node* newNode = new Node(label);
    nodes[label] = newNode;
    return newNode;
}

void IncidenceGraph::addEdge(std::string node_a_label, std::string edge_label, std::string node_b_label){
    Node* fromNode = findOrCreateNode(node_a_label);
    Node* toNode = findOrCreateNode(node_b_label);

    Edge* newEdge = new Edge(edge_label, fromNode, toNode);
    allEdges.push_back(newEdge);
    
    fromNode->addEdge(newEdge);
    toNode->addEdge(newEdge);
}

void IncidenceGraph::readFromFile(std::string filename){
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("could not find fil: " + filename);
    }
    
    std::string line;
    while (std::getline(file, line)){
        line.pop_back();

        std::istringstream iss(line);
        std::string fromNode, edge, toNode;
        
        if (iss >> fromNode >> edge >> toNode) {
            addEdge(fromNode, edge, toNode);
        }
    }
    file.close();
}

void IncidenceGraph::readToFile(std::string filename){
    std::ofstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("could not create file: " + filename);
    }

    for (Edge* edge : allEdges){
        file << edge->fromNode->NameNode << " " << edge->NameEdge << " " << edge->toNode->NameNode << ".\n";
    }
    file.close();
}

void IncidenceGraph::removeNode(std::string nodeName){
    if (nodes.find(nodeName) == nodes.end()){
        std::cout << "The node does not exist: " + nodeName << std::endl;
        return;
    }

    Node* node = findOrCreateNode(nodeName);
    for (Edge* edge : node->listEdges){
        Node* nodeA = edge->fromNode;
        Node* nodeB = edge->toNode;
        allEdges.erase(std::find(allEdges.begin(), allEdges.end(), edge));
        nodeA->removeEdge(edge);
        nodeB->removeEdge(edge);
        delete edge;
    }
} 

void IncidenceGraph::disconnect(std::string nameNodeA, std::string nameNodeB){
    if (nodes.find(nameNodeA)  == nodes.end() || nodes.find(nameNodeB) == nodes.end()){
        std::cout << "Method disconnect: The nodeA: " + nameNodeA + " or the nodeB: " + nameNodeB + " does not exist" << std::endl;
    }
    else {
        Node* nodeA = findOrCreateNode(nameNodeA);
        Node* nodeB = findOrCreateNode(nameNodeB);
        for (Edge* edge : nodeA->listEdges){
            if (edge->toNode == nodeB){
                nodeA->removeEdge(edge);
            }
        }
    }
}

IncidenceGraph::~IncidenceGraph(){
    for (Edge* edge : allEdges){
        delete edge;
    }
    for (auto node : nodes){
        delete node.second;
    }
}