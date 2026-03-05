#include "graph.h"
#include "incidence_lists.h"
#include "adjacency_matrix.h"

#include <fstream>
#include <sstream>


int main() {
	IncidenceGraph graph;
	graph.readFromFile("test.txt");
	graph.addEdge("skole", "sti", "skogen");
	graph.removeNode("skogen");
	graph.addEdge("ulykke", "sykebil", "sykehus");
	graph.readToFile("OutputGraph.txt");
	graph.removeNode("sykehus");
	graph.readToFile("OutputGraph2.txt");
	AdjMatrix matrix;
	matrix.readFromFile("test.txt");
	matrix.addEdge("skole", "sti", "skogen");
	matrix.removeNode("skogen");
	matrix.addEdge("ulykke", "sykebil", "sykehus");
	matrix.readToFile("OutputMatrix.txt");
	matrix.removeNode("sykehus");
	matrix.readToFile("OutputMatrix2.txt");
}
