#include "graph.h"
#include "incidence_lists.h"

#include <fstream>
#include <sstream>


int main() {
	IncidenceGraph graph;
	graph.readFromFile("test.txt");
	graph.addEdge("skole", "sti", "skogen");
	graph.removeNode("skogen");
	graph.readToFile("fårviutput.txt");
}
