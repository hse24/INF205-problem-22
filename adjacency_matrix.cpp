#include "adjacency_matrix.h"

#include <list>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

void AdjMatrix::addNode(std::string node){
    // adds new node and resizes the 3d vector in the first 2 dementions
    allNodes.emplace_back(node);
    size_t newSize = allNodes.size();

    matrix.resize(newSize);
    for (auto& row : matrix){
        row.resize(newSize);
    }
}

void AdjMatrix::addEdge(std::string node_a_label, std::string edge_label, std::string node_b_label){
    // if nodeA is not in allNodes create a new Node
    auto nodeA = std::find(allNodes.begin(), allNodes.end(), node_a_label);
    if (nodeA == allNodes.end()){
        addNode(node_a_label);
    }
    // same for nodeB
    auto nodeB = std::find(allNodes.begin(), allNodes.end(), node_b_label);
    if (nodeB == allNodes.end()){
        addNode(node_b_label);
    }
    // updates the itterator to find the right position
    auto updateNodeA = std::find(allNodes.begin(), allNodes.end(), node_a_label);
    auto updateNodeB = std::find(allNodes.begin(), allNodes.end(), node_b_label);
    // if it now could not find NodeA or NodeB something wrong throws an error
    if (updateNodeA == allNodes.end() || updateNodeB == allNodes.end()) {
        std::cerr << "Something went wrong with adding Node A or B" << std::endl;
        return;
    }
    // finds the index for NodeA and Node B in matrix and adds the Edge
    int NodeA = std::distance(allNodes.begin(), updateNodeA);
    int NodeB = std::distance(allNodes.begin(), updateNodeB);
    matrix[NodeA][NodeB].push_back(edge_label);    
 }

void AdjMatrix::readFromFile(std::string filname){
    // check if could open file or could read if not throw an error
    std::ifstream file(filname);
    if (!file.is_open()) {
        throw std::runtime_error("could not find fil: " + filname);
    }
    // add all edges
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

void AdjMatrix::readToFile(std::string filname){
    // check if can open create file, else throw error
    std::ofstream file(filname);
    if (!file.is_open()) {
        throw std::runtime_error("could not create file: " + filname);
    }
    // loops through the matrix and find all edges and corresponding Nodes and write it to file
    size_t numberNodes = allNodes.size();
    for (size_t i = 0; i < numberNodes; i++){
        for (size_t j = 0; j < numberNodes; j++){
            auto& edges = matrix[i][j];
            if (!edges.empty()){
                for (std::string edge : edges){
                    file << allNodes[i] << " " << edge << " " << allNodes[j] << ".\n";
                }
            }
        }
    }
    file.close();
}

void AdjMatrix::disconnect(std::string node_a_label, std::string node_b_label){
    // find node A and B
    auto nodeA = std::find(allNodes.begin(), allNodes.end(), node_a_label);
    auto nodeB = std::find(allNodes.begin(), allNodes.end(), node_b_label);
    // checks if could find node A and B else does nothing.
    if (nodeA == allNodes.end() || nodeB == allNodes.end()) {
        std::cout << "Could not found NodeA or B to disconnect" << std::endl;
        return;
    }
    // find index for NodeA and B
    int NodeA = std::distance(allNodes.begin(), nodeA);
    int NodeB = std::distance(allNodes.begin(), nodeB);
    // removes all Edges going from A to B
    matrix[NodeA][NodeB].clear();
    // checks if cleanup is true if it is check for stand alone Nodes and removes them
    if (cleanup){
    checkAndDelete();
    }
}

void AdjMatrix::removeNode(std::string node_label){
    // finds node A
    auto node = std::find(allNodes.begin(), allNodes.end(), node_label);
    // return error if it could not found
    if (node == allNodes.end()){
        std::cout << "Could not found the Node you wanted to remove" << std::endl;
        return;
    }
    // find index node
    int indexNode = std::distance(allNodes.begin(), node);
    // removes the node from all nodes
    allNodes.erase(node);
    // removes row and columb that link to Node
    matrix.erase(matrix.begin() + indexNode);
    for (auto& row : matrix){
        row.erase(row.begin() + indexNode);
    }
    // if cleanup true checks if any stand alone Nodes has been created and removes them
    if (cleanup){
    checkAndDelete();
    }
}

void AdjMatrix::checkAndDelete(){
    // set cleanup to false to not make it removeNode and disconnect call for 
    // checkAndDelte more than once
    cleanup = false;
    // create size of all nodes and nodes to be deleted
    size_t numNodes = allNodes.size();
    std::vector<std::string> NodesToBeDeleted;
    // a dobble loop going through matrix to identify if a Node has a Edge
    // if not break the inner loop and set hasEdges to true
    for (size_t i = 0; i < numNodes; i++){
        bool hasEdge = false;
        for (size_t j = 0; j < numNodes; j++){
            if (!matrix[i][j].empty()){
                hasEdge = true;
                break;
            }
            if (!matrix[j][i].empty()){
                hasEdge = true;
                break;
            }
        }
        if (!hasEdge){
            NodesToBeDeleted.push_back(allNodes[i]);
        }
    }
    // call for deletion of all Nodes with no Edges.
    for (std::string deleteNode : NodesToBeDeleted){
        removeNode(deleteNode);
    // set to true only after it loops through
    cleanup = true;
    }

}

AdjMatrix::~AdjMatrix(){
    return;
}