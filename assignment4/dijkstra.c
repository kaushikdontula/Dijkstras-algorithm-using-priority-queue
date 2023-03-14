/*
 * In this file, you'll implement Dijkstra's algorithm to find the least
 * expensive paths in the graph defined in `airports.dat`.  Don't forget to
 * include your name and @oregonstate.edu email address below.
 *
 * Name: Kaushik Dontula
 * Email: dontulak@oregonstate.edu
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pq.h"


#define DATA_FILE "airports.dat"
#define START_NODE 0

struct path{
	int N;
	int prev;
	//int cost;
};



int main(int argc, char const *argv[]) {

	/*
	 * Open file and read the first two int: num of nodes, num of edges
	 */
	int n_nodes;
	int n_edges;
	int matrix[100][100] = {0};

	FILE* file = fopen(DATA_FILE, "r");
	fscanf(file, " %d %d ", &n_nodes, &n_edges);

	//gets number of nodes and edges and stores it into the variables
	printf("nodes = %d \n edges = %d \n", n_nodes, n_edges);
	

	//initialize the price and prev arrays to size of n_nodes
	int* price = malloc(sizeof(int) * n_nodes);
	int* prev = malloc(sizeof(int) * n_nodes);
	
	//Read edge data and store in adjacency matrix
	for (int i = 0; i < n_nodes; i++) {
		for (int j = 0; j < n_nodes; j++) {
			matrix[i][j] = 0;
		}
	}
	for (int i = 0; i < n_edges; i++) {
		int from;
		int to;
		int cost;
		fscanf(file, " %d %d %d ", &from, &to, &cost);
		matrix[from][to] = cost;
	}

	
	//prints out adjency matrix for reference
	for(int k = 0; k< n_nodes; k++){
		printf("  %d ", k);
	}
	printf("\n");
	for (int i = 0; i < n_nodes; i++) {
		printf(" %d ", i);
		for (int j = 0; j < n_nodes; j++) {
			printf(" %d ", matrix[i][j]);
		}
		printf(" \n");
	}
	


	//initializing the price array to infinite and prev array to undefined
	for(int i=0; i<n_nodes; i++){
		price[i] = 99999;
		prev[i] = -1;
	}


	//create path struct and initialize the start node
	struct path* start = malloc(sizeof(struct path));
	start->N = START_NODE;
	start->prev = 0;

	
	//create priority queue and insert start node
	struct pq* q = pq_create();
	pq_insert(q, start, 0);

	//while the priority queue is not empty
	while (pq_isempty(q) != 1) {

		//int c is the cost/priority of the first element in the queue
		int c = pq_first_priority(q);
		
		//remove first priority nide and set it to struct path, store struct values into int N and int N_prev then free(Node)
		struct path* Node = pq_remove_first(q);
		int N = Node->N;
		int N_prev = Node->prev;
		free(Node);

		//if the elements cost is less than the cost of the price array at N index
		if( c < price[N]){

			//update the price and prev arrays to c and N_prev
			price[N] = c;
			prev[N] = N_prev;

			//for the amount of neighbors that node N has
			for(int N_i =0; N_i <n_nodes; N_i++){

				//if the node is a neighbor update the prev and N index in a new struct and insert it into priority queue
				if(matrix[N][N_i] != 0){
					int c_i = matrix[N][N_i];
					struct path* tempo = malloc(sizeof(struct path));
					tempo->prev = N;
					tempo->N = N_i;
					pq_insert(q, tempo, c+c_i);
				}
            }
		}
	}
	pq_free(q);



//Print the shortest path from the start node to each node
    printf("\n \nLeast cost paths from Start Node %d:\n", START_NODE);

	//prints the cost of the path
    for (int i = 0; i < n_nodes; i++) {
		printf("Node %d cost: %d 	Path:", i, price[i]);

		int previous = i;
		int arr[n_nodes];
		int size=0;
		int j=0;
		printf(" 0 ");

		//prints the path and nodes of the path
		while(previous != 0){
			arr[j] = previous;
			j++;
			size++;
			previous = prev[previous];		
		}
		for(int k=size-1; k>=0; k--){
			printf("-> %d ", arr[k]);
		}

		printf("\n");
        
    }
	free(price);
	free(prev);
	fclose(file);

	return 0;
}
