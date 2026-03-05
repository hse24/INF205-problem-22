#include "adjacency_matrix.h"

#include <list>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

void AdjMatrix::addNode(std::string node){
    allNodes.emplace_back(node);
    size_t newSize = allNodes.size();

    matrix.resize(newSize);
    for (auto& row : matrix){
        row.resize(newSize);
    }
}

void AdjMatrix::addEdge(std::string node_a_label, std::string edge_label, std::string node_b_label){
    auto nodeA = std::find(allNodes.begin(), allNodes.end(), node_a_label);
    if (nodeA == allNodes.end()){
        addNode(node_a_label);
    }
    auto nodeB = std::find(allNodes.begin(), allNodes.end(), node_b_label);
    if (nodeB == allNodes.end()){
        addNode(node_b_label);
    }

    auto updateNodeA = std::find(allNodes.begin(), allNodes.end(), node_a_label);
    auto updateNodeB = std::find(allNodes.begin(), allNodes.end(), node_b_label);

    if (updateNodeA == allNodes.end() || updateNodeB == allNodes.end()) {
        std::cerr << "Something went wrong with adding Node A or B" << std::endl;
        return;
    }

    int NodeA = std::distance(allNodes.begin(), updateNodeA);
    int NodeB = std::distance(allNodes.begin(), updateNodeB);
    matrix[NodeA][NodeB].push_back(edge_label);    
 }

void AdjMatrix::readFromFile(std::string filname){
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
void AdjMatrix::readToFile(std::string filname){
    std::ofstream file(filname);
    if (!file.is_open()) {
        throw std::runtime_error("could not create file: " + filname);
    }
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
    auto nodeA = std::find(allNodes.begin(), allNodes.end(), node_a_label);
    auto nodeB = std::find(allNodes.begin(), allNodes.end(), node_b_label);

    if (nodeA == allNodes.end() || nodeB == allNodes.end()) {
        std::cout << "Could not found NodeA or B to disconnect" << std::endl;
        return;
    }

    int NodeA = std::distance(allNodes.begin(), nodeA);
    int NodeB = std::distance(allNodes.begin(), nodeB);
    matrix[NodeA][NodeB].clear();
    if (cleanup){
    checkAndDelete();
    }
}

void AdjMatrix::removeNode(std::string node_label){
    auto node = std::find(allNodes.begin(), allNodes.end(), node_label);

    if (node == allNodes.end()){
        std::cout << "Could not found the Node you wanted to remove" << std::endl;
    }

    int indexNode = std::distance(allNodes.begin(), node);
    allNodes.erase(node);

    matrix.erase(matrix.begin() + indexNode);
    for (auto& row : matrix){
        row.erase(row.begin() + indexNode);
    }
    if (cleanup){
    checkAndDelete();
    }
}

void AdjMatrix::checkAndDelete(){
    cleanup = false;
    size_t numNodes = allNodes.size();
    std::vector<std::string> NodesToBeDeleted;

    for (size_t i = 0; i < numNodes; i++){
        bool hasEdge = true;
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
    for (std::string deleteNode : NodesToBeDeleted){
        removeNode(deleteNode);
    cleanup = true;
    }

}

AdjMatrix::~AdjMatrix(){
    return;
}