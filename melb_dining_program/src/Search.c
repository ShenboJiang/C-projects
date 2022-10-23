/* Made by Shenbo Jiang, 1271411 for COMP20003 */

/*-------------------------------------------------------------- 
Project: City of Melbourne
dict3.c : the main driver of stage 3 point query
----------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "data.h"
#include "linked.h"
#include "quad.h"


int main(int argc, char *argv[]){
	// Value initialization
	char* endptr;
	list_t *list;
	char line[MAX_LINE_lEN + 1];
	data_t data;

	// Opening read and write file
	FILE *inFile = fopen(argv[2], "r");
	assert(inFile);
	FILE *outFile = fopen(argv[3], "w");
	assert(outFile);

	// Create empty list
	list = make_empty_list();

	// Skip the header in the .csv and read in rest of the lines into linked list
	fscanf(inFile, "%*[^\n]\n");
	while (fscanf(inFile, "%[^\n]\n", line) == 1){
		data = read_in_one_data(line);
		list = insert_at_foot(list, data);
	}
	
	// Create the boundry from stdin inputs
	boundry_t *boundry = create_boundry(strtold(argv[4], &endptr), strtold(argv[5], &endptr), strtold(argv[6], &endptr), 
		strtold(argv[7], &endptr));

	// Create new empty quad tree
	qnode_t *qtree = createqtree(boundry);
	
	// Insert all data in linked list into qtree
	for (node_t *curr = list->head; curr != NULL; curr = curr->next){
		qtree = insertqtree(qtree, &(curr->data), curr->data.start_lon, curr->data.start_lat, FALSE);
		qtree = insertqtree(qtree, &(curr->data), curr->data.end_lon, curr->data.end_lat, TRUE);
	}

	char queryX_str[MAX_STRING_LEN];
	char queryY_str[MAX_STRING_LEN];

	// For all query input, find all matching points and print out the associated data and direction
	while (scanf("%s", queryX_str) == 1 && scanf("%s\n", queryY_str) == 1){
		printf("%s %s -->", queryX_str, queryY_str);
		fprintf(outFile, "%s %s\n", queryX_str, queryY_str);

		double queryX = strtod(queryX_str, &endptr);
		double queryY = strtod(queryY_str, &endptr);
		data_t *result_array[SIZE_OF_COLLISION_ARRAY];
		int n = searchqtree(queryX, queryY, qtree, result_array);
		printf("\n");

		printdata(result_array, n, outFile);
		
		
	}


	// Close read and write file
	fclose(inFile);
	fclose(outFile);

	// Free memory allocated to linked list and quad tree
	free_list(list);
	freeqtree(qtree);


	return 0;
}
