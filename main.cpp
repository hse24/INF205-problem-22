#include "graph.h"
#include "incidence_lists.h"
#include "adjacency_matrix.h"

#include <fstream>
#include <sstream>


int main() {
	// tests Incidence Graph
	IncidenceGraph graph;
	graph.readFromFile("test.txt");
	graph.addEdge("skole", "sti", "skogen");
	graph.disconnect("skole", "skogen");
	graph.addEdge("ulykke", "sykebil", "sykehus");
	graph.readToFile("testGraph.txt");
	graph.removeNode("sykehus");
	graph.readToFile("testGraph2.txt");
	// test copy constructor
	IncidenceGraph copy1(graph);
	copy1.readToFile("copytest1.txt");
	// test opy Assignment opperator
	IncidenceGraph copy2 = graph;
	copy2.addEdge("ulykke", "sykebil", "sykehus");
	copy2.readToFile("copytest2.txt");
	// check if graph now is same
	graph.readToFile("copytest3.txt");
	// checking move
	IncidenceGraph moved = std::move(graph);
	moved.readToFile("moved.txt");
	graph.readToFile("movedEmpty");
	IncidenceGraph moved2(std::move(copy2));
	moved2.readToFile("moved2.txt");
	copy2.readToFile("movedEmpty2");



	AdjMatrix matrix;
	matrix.readFromFile("test.txt");
	matrix.addEdge("skole", "sti", "skogen");
	matrix.disconnect("skole", "skogen");
	matrix.addEdge("ulykke", "sykebil", "sykehus");
	matrix.readToFile("testMatrix.txt");
	matrix.removeNode("sykehus");
	matrix.readToFile("testMatrix2.txt");
	
}
