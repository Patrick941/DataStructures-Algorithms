#include "t1.c"

// converts an upper case character (A-Z) to a numerical value (between 0 and 25) 
static int char2val ( char c ) {
	if ( c < 'A' || c > 'Z' ) {
		return -1;
	}

	return c-'A';
}

int main(){
    int num_nodes = 6;
    Graph * graph = NULL;
    graph = create_graph(num_nodes);
    
    add_edge(graph, char2val('A'), char2val('E'));
    add_edge(graph, char2val('B'), char2val('D'));
    add_edge(graph, char2val('A'), char2val('D'));
    add_edge(graph, char2val('A'), char2val('B'));
    add_edge(graph, char2val('B'), char2val('C'));
    add_edge(graph, char2val('C'), char2val('B'));
    add_edge(graph, char2val('E'), char2val('D'));
    add_edge(graph, char2val('D'), char2val('F'));
    add_edge(graph, char2val('F'), char2val('C'));
    add_edge(graph, char2val('C'), char2val('D'));

    dfs(graph, char2val('A'));
    printf("\n");
    bfs(graph, char2val('A'));
    printf("\n");

    printGraph(graph);

    delete_graph(graph);

}