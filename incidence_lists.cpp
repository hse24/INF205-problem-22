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

// add lists to Node->listEdges
void IncidenceGraph::Node::addEdge(Edge* edge){
    listEdges.push_back(edge);
}

// removes lists from Node->listEdges
void IncidenceGraph::Node::removeEdge(Edge* edge){
    listEdges.remove(edge);
}

// checks if Node are in nodes. if so returns pointer to node else create new Node, and add label and pointer to nodes
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
    // creates new Edge object and add the Edge pointer to vector allEdges
    Edge* newEdge = new Edge(edge_label, fromNode, toNode);
    allEdges.push_back(newEdge);
    // add the edges to Node->listEdges
    fromNode->addEdge(newEdge);
    toNode->addEdge(newEdge);
}

void IncidenceGraph::readFromFile(std::string filname){
    // checks if could open or find file
    std::ifstream file(filname);
    if (!file.is_open()) {
        throw std::runtime_error("could not find fil: " + filname);
    }
    
    std::string line;
    while (std::getline(file, line)){
        // removes . at end of fileline
        line.pop_back();

        std::istringstream iss(line);
        std::string fromNode, edge, toNode;
        
        // returns true of iss has tree string and has no error
        if (iss >> fromNode >> edge >> toNode) {
            addEdge(fromNode, edge, toNode);
        }
    }
    file.close();
}

void IncidenceGraph::readToFile(std::string filname){
    // checks if could open or find file
    std::ofstream file(filname);
    if (!file.is_open()) {
        throw std::runtime_error("could not create file: " + filname);
    }
    // wright to file.
    for (Edge* edge : allEdges){
        file << edge->fromNode->NameNode << " " << edge->NameEdge << " " << edge->toNode->NameNode << ".\n";
    }
    file.close();
}

void IncidenceGraph::checkAndDelete(){
    // first make a copy of all pointers for node
    std::vector<Node*> vectorNodes;
    for (auto node : nodes){
        vectorNodes.push_back(node.second);
    }
    // loop trough the copy pointers and delete
    for (Node* node : vectorNodes){
        if (node->listEdges.size() == 0){
            nodes.erase(node->NameNode);
            delete node;
        }
    }
}

void IncidenceGraph::removeNode(std::string nodeName){
    // if could not find Node with matching string read out that it does not and do nothing
    if (nodes.find(nodeName) == nodes.end()){
        std::cout << "The node does not exist: " + nodeName << std::endl;
        return;
    }
    // finds pointer to nodeName
    Node* node = findOrCreateNode(nodeName);
    // creates copy of pointers Edges needed to be deleted.
    std::vector<Edge*> edgesToDelete(node->listEdges.begin(), node->listEdges.end());
    for (Edge* edge : edgesToDelete){
        //identifies which Node the Edge is connected to
        Node* nodeA = edge->fromNode;
        Node* nodeB = edge->toNode;
        //remove edge from the list of all edges
        allEdges.erase(std::find(allEdges.begin(), allEdges.end(), edge));
        //remove edge from Node->listEdges
        nodeA->removeEdge(edge);
        nodeB->removeEdge(edge);
        delete edge;
    }
    // runs check to see if there are any empty nodes
    checkAndDelete();
} 

void IncidenceGraph::disconnect(std::string nameNodeA, std::string nameNodeB){
    // check if NodeA and Node B is legit Nodes, if they does not exist do nothing.
    if (nodes.find(nameNodeA)  == nodes.end() || nodes.find(nameNodeB) == nodes.end()){
        std::cout << "Method disconnect: The nodeA: " + nameNodeA + " or the nodeB: " + nameNodeB + " does not exist" << std::endl;
        return;
    }
    // find pointer to nodeA and B
    Node* nodeA = findOrCreateNode(nameNodeA);
    Node* nodeB = findOrCreateNode(nameNodeB);
    // create empty vector for Edge pointers to be deleted
    std::vector<Edge*> edgesToDelete;
    // loops trough Edges from nodeA and checks if they connect to NodeB
    for (Edge* edge : nodeA->listEdges){
        if (edge->toNode == nodeB){
            edgesToDelete.push_back(edge);
        }
    }
    // Delete all Edges going from Node A to B    
    for (Edge* edge : edgesToDelete){
        nodeA->removeEdge(edge);
        nodeB->removeEdge(edge);
        allEdges.erase(std::find(allEdges.begin(), allEdges.end(), edge));
        delete edge;
    }
    // checks if any Node is without Edges if so Deletes them
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

IncidenceGraph::IncidenceGraph(IncidenceGraph& nodeToCopy){
    std::unordered_map<Node*, Node*> nodeMapping;
    // need to create new copy for nodes 
    for (auto& nodeEdge : nodeToCopy.nodes){
        Node* newNode = new Node(nodeEdge.first);
        nodes[nodeEdge.first] = newNode;
        nodeMapping[nodeEdge.second] = newNode;
    }
    // creates new edges and combine them with pointers to new nodes
    for (Edge* oldEdge : nodeToCopy.allEdges){
        // gets pointers to new Nodes
        Node* newNodeFrom = nodeMapping[oldEdge->fromNode];
        Node* newNodeTo = nodeMapping[oldEdge->toNode];
        Edge* newEdge = new Edge(oldEdge->NameEdge, newNodeFrom, newNodeTo);
        allEdges.push_back(newEdge);
        newNodeFrom->addEdge(newEdge);
        newNodeTo->addEdge(newEdge);
    }
}

IncidenceGraph& IncidenceGraph::operator=(IncidenceGraph& nodeToCopy) {
    // check if it tries to assign itself to itself. forexample: graph = graph
    if (this == &nodeToCopy) {
        return *this;
    }
    // delete all old edges and clears list of allEdges
    for (Edge* edge : allEdges) {
        delete edge;
    }
    allEdges.clear();
    // Same for Nodes
    for (auto& pair : nodes) {
        delete pair.second;
    }
    nodes.clear();

    //repeat what we did in copy constructor
    std::unordered_map<Node*, Node*> nodeMapping;
    // need to create new copy for nodes 
    for (auto& nodeEdge : nodeToCopy.nodes){
        Node* newNode = new Node(nodeEdge.first);
        nodes[nodeEdge.first] = newNode;
        nodeMapping[nodeEdge.second] = newNode;
    }
    // creates new edges and combine them with pointers to new nodes
    for (Edge* oldEdge : nodeToCopy.allEdges){
        Node* newNodeFrom = nodeMapping[oldEdge->fromNode];
        Node* newNodeTo = nodeMapping[oldEdge->toNode];
        Edge* newEdge = new Edge(oldEdge->NameEdge, newNodeFrom, newNodeTo);
        allEdges.push_back(newEdge);
        newNodeFrom->addEdge(newEdge);
        newNodeTo->addEdge(newEdge);
    }
    return *this;
}

IncidenceGraph::IncidenceGraph(IncidenceGraph&& nodeToMoved) noexcept
    // just moves all nodes and allEdges and leave the old ones empty
    : nodes(std::move(nodeToMoved.nodes)) , allEdges(std::move(nodeToMoved.allEdges)) {}


IncidenceGraph& IncidenceGraph::operator=(IncidenceGraph&& nodeToMove) noexcept {
    // check if it tries to assign itself to itself. forexample: graph = graph
    if (this == &nodeToMove) {
        return *this;
    }
    // Deletes data from orginal IncidenceGraph
    for (Edge* edge : allEdges){
        delete edge;
    }
    for (auto node : nodes){
        delete node.second;
    }
    // move pointers to nodeToMoved 
    nodes = std::move(nodeToMove.nodes);
    allEdges = std::move(nodeToMove.allEdges);
    
    return *this;
}