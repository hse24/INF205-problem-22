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

void IncidenceGraph::readFromFile(std::string filname){
    std::ifstream file(filname);
    if (!file.is_open()) {
        throw std::runtime_error("could not find fil: " + filname);
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

void IncidenceGraph::readToFile(std::string filname){
    std::ofstream file(filname);
    if (!file.is_open()) {
        throw std::runtime_error("could not create file: " + filname);
    }

    for (Edge* edge : allEdges){
        file << edge->fromNode->NameNode << " " << edge->NameEdge << " " << edge->toNode->NameNode << ".\n";
    }
    file.close();
}

void IncidenceGraph::checkAndDelete(){
    std::vector<Node*> vectorNodes;
    for (auto node : nodes){
        vectorNodes.push_back(node.second);
    }
    for (Node* node : vectorNodes){
        if (node->listEdges.size() == 0){
            nodes.erase(node->NameNode);
            delete node;
        }
    }
}

void IncidenceGraph::removeNode(std::string nodeName){
    if (nodes.find(nodeName) == nodes.end()){
        std::cout << "The node does not exist: " + nodeName << std::endl;
        return;
    }

    Node* node = findOrCreateNode(nodeName);
    std::vector<Edge*> edgesToDelete(node->listEdges.begin(), node->listEdges.end());
    for (Edge* edge : edgesToDelete){
        Node* nodeA = edge->fromNode;
        Node* nodeB = edge->toNode;
        allEdges.erase(std::find(allEdges.begin(), allEdges.end(), edge));
        nodeA->removeEdge(edge);
        nodeB->removeEdge(edge);
        delete edge;
    }
    checkAndDelete();
} 

void IncidenceGraph::disconnect(std::string nameNodeA, std::string nameNodeB){
    if (nodes.find(nameNodeA)  == nodes.end() || nodes.find(nameNodeB) == nodes.end()){
        std::cout << "Method disconnect: The nodeA: " + nameNodeA + " or the nodeB: " + nameNodeB + " does not exist" << std::endl;
        return;
    }
    Node* nodeA = findOrCreateNode(nameNodeA);
    Node* nodeB = findOrCreateNode(nameNodeB);
    std::vector<Edge*> edgesToDelete;
    for (Edge* edge : nodeA->listEdges){
        if (edge->toNode == nodeB){
            edgesToDelete.push_back(edge);
        }
    }    
    for (Edge* edge : edgesToDelete){
        nodeA->removeEdge(edge);
        nodeB->removeEdge(edge);
        allEdges.erase(std::find(allEdges.begin(), allEdges.end(), edge));
        delete edge;
    }
    checkAndDelete();
}

IncidenceGraph::~IncidenceGraph(){
    for (Edge* edge : allEdges){
        delete edge;
    }
    for (auto node : nodes){
        delete node.second;
    }
}