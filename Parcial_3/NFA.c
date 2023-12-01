#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <omp.h>
#include <time.h>

#define MAX_SIZE 100 // Define a maximum size for the input

int row = 0;

// A structure to represent an adjacency list node
struct node
{
	int data;
	struct node* next;
	char edgetype;

}typedef node;

// Adds an edge to an adjacency list
node* push(node* first , char edgetype , int data)
{
	node* new_node = (node*)malloc(sizeof(node));
	new_node->edgetype = edgetype;
	new_node->data = data;
	new_node->next = NULL;
	if (first==NULL)
	{
		first = new_node;
        // printf("(%c, %d)\n", first->edgetype, first->data);
		return new_node;
	}
    // printf("(%c, %d) -> ", first->edgetype, first->data);
	first->next = push(first->next,edgetype,data);
	return first;
}

//Recursive function to check acceptance of input
int nfa(node** graph, int current, char* input,
		int* accept, int start)
{
	if (start==(int)strlen(input))
		return accept[current];

	node* temp = graph[current];
	while (temp != NULL)
	{
	if (input[start]==temp->edgetype)
		if (nfa(graph,temp->data,input,accept,start+1)==1)
			return 1;
	temp=temp->next;
	}
	return 0;
}

//Function to generate binary strings of size n
void generate(char** arr, int size, char *a)
{
	if (size==0)
	{
		strcpy(arr[row], a);
		row++;
		return;
	}
	char b0[MAX_SIZE] = {'\0'};
	char b1[MAX_SIZE] = {'\0'};
	b0[0] = '0';
	b1[0] = '1';

	//Recursively generate the binary string
	generate((char**)arr, size-1, strcat(b0,a)); //Add 0 in front
	generate((char**)arr, size-1, strcat(b1,a)); //Add 1 in front
	return;

}

void freeGraph(node** graph, int n) {
    for (int i = 0; i <= n; i++) {
        node* current = graph[i];
        while (current != NULL) {
            node* temp = current;
            current = current->next;
            free(temp);
        }
    }
}


// Driver program to test above functions
int main()
{
	int n;
	int i, j;
	scanf("%d", &n); //Number of nodes
	node* graph[n+1]; //Create a graph

	for (i=0;i<n+1;i++)
		graph[i]=NULL;


	int accept[n+1]; //Array to store state of vertex

	for (i=0; i<n; ++i)
	{
		//Index of vertex , Acceptance state , Number of edges
        // printf("----- %d / %d ------\n", i + 1, n);
		int index,acc,number_nodes;
		scanf("%d%d%d",&index,&acc,&number_nodes);
		accept[index]=acc; //Store acceptance

		for (j=0;j<number_nodes;j++) //Add all edges
		{
			int node_add;
			int edge;
			scanf("%d%d",&edge,&node_add);
			graph[index] = push(graph[index],'0'+edge,node_add);
		}
        // printf("END!! %d\n", index);
	}

	int size = 1; //Size of input
	int count = 0; //Keep count of output strings

	if (accept[1]==1) //Check for empty string
	{
		printf("e\n");
		count++;
	}

	int n_input;
    printf("Insert the number of inputs to be evaluated: \n");
    scanf("%d", &n_input);

	int stop = 0;
	clock_t start, end;
	start = clock();
	while (count < n_input && !stop)
	{
		char** arr;
		int power = pow(2, size);
		arr = (char**)malloc(power * sizeof(char*));

		for (i = 0; i < power; i++)
			arr[i] = (char*)malloc((size + 1) * sizeof(char));

		char a[MAX_SIZE] = {'\0'};
		generate((char**)arr, size, a); // Generate inputs

		#pragma omp parallel for
		for (i = 0; i < power; i++)
		{
			if(stop) continue;
			char input[MAX_SIZE] = {'\0'};
			
			#pragma omp parallel for
			for (j=0; j<size; j++)
			{
				char foo[2];
				foo[0] = arr[i][size-1-j];
				foo[1] = '\0';
				strcat(input,foo);
								//Copy generated string input
			}

			int result = nfa(graph, 1, input, accept, 0);

			if (result == 1)
			{
				#pragma omp critical
				{
					printf("%s\n", input);
					count++;
				}
			}

			#pragma omp flush(count)
			if (count >= n_input-1)
				stop=1;
		}

		size++; // Increment size of binary string input
		row = 0;

		// Free arrays
		for (int i = 0; i < power; i++)
			free(arr[i]);
		free(arr);

		#pragma omp barrier
		if (count >= n_input-1)
			break;
	}

	end = clock();
	// Calculate the total time used by the program
    double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

    // Print the total time used
    printf("Program executed in: %f seconds\n", cpu_time_used);

    // Free the graph
    freeGraph(graph, n);


	return 0;
}
