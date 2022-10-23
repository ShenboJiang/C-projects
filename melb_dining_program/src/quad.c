/* Made by Shenbo Jiang, 1271411 for COMP20003 */

/*-------------------------------------------------------------- 
Project: City of Melbourne
quad.c : the implementation of helper function for quad tree
----------------------------------------------------------------*/

//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "data.h"
#include "quad.h"


// Return boundry struct pointer using bottom left x, bottom left y, top right x and top right y
boundry_t 
*create_boundry(long double blX, long double blY, long double trX, long double trY){

	boundry_t *boundry;
	boundry = (boundry_t *)malloc(4 * sizeof(long double));
	assert(boundry);

	boundry->BLx = blX;
	boundry->BLy = blY;
	boundry->TRx = trX;
	boundry->TRy = trY;

	return boundry;
}

// Return the root node of the freshly created quadtree node from given boundry
qnode_t 
*createqtree(boundry_t *boundry){
	qnode_t *q;
	q = (qnode_t*)malloc(sizeof(*q));
    assert(q);
    q->tree_boundry = boundry;
    q->d = NULL;
	q->d_array = (data_t **)malloc(SIZE_OF_COLLISION_ARRAY * sizeof(data_t *));
	assert(q->d_array);
	for (int i = 0; i < SIZE_OF_COLLISION_ARRAY; i++){
		q->d_array[i] = NULL;
	}
    q->isInternal = FALSE;
	q->isEnd = UNKNOWN;
    q->sw = NULL;
    q->nw = NULL;
    q->ne = NULL;
	q->se = NULL;
    return q;
}

// Return the root node of the quadtree after data have been inserted with its x y coordinates and Information
// that if it is an end point or a staring point (Recursive)
qnode_t 
*insertqtree(qnode_t *q, data_t *data, double x, double y, int isEnd){
	if (q->d == NULL && q->isInternal == FALSE){
		// Inserting into white node
		q->d = data;
		q->point.x = x;
		q->point.y = y;
		q->isEnd = isEnd;
		q->d_array[0] = NULL;
		return q;
	}

	if (q->d != NULL && q->isInternal == FALSE){
		// Inserting into black node

		long double midX, midY;
		double curX, curY;
		
		
		curX = q->point.x;
		curY = q->point.y;
		int i = 0;
		// Append different data with same coordiantes into d_array
		if (curX == x && curY == y){
			while (q->d_array[i] != NULL){
				i++;
			}
			q->d_array[i] = data;
			return q;
		}
		
		q->isInternal = TRUE;

		// Calculate the boundry coordiantes of the four sub nodes and create the nodes
		midX = (q->tree_boundry->TRx + q->tree_boundry->BLx) / 2;
		midY = (q->tree_boundry->TRy + q->tree_boundry->BLy) / 2;
		boundry_t *boundry = create_boundry(q->tree_boundry->BLx, q->tree_boundry->BLy,
			midX, midY);
		q->sw = createqtree(boundry);

		boundry = create_boundry(q->tree_boundry->BLx, midY,
			midX, q->tree_boundry->TRy);
		q->nw = createqtree(boundry);

		boundry = create_boundry(midX, midY,
			q->tree_boundry->TRx, q->tree_boundry->TRy);
		q->ne = createqtree(boundry);

		boundry = create_boundry(midX, q->tree_boundry->BLy,
			q->tree_boundry->TRx, midY);
		q->se = createqtree(boundry);

		// Store temporary data of the node and empty it
		data_t *cur_data = q->d;
		int cur_isEnd = q->isEnd;
		q->d = NULL;

		// Node navigation and recursivly insert the temp data back into the subnodes
		if(curX > midX){ // NE or SE
			if (curY < midY){ // SE
				q->se = insertqtree(q->se, cur_data, curX, curY, cur_isEnd);
				q->se->d_array = q->d_array;
			}
			else{ // NE
				q->ne = insertqtree(q->ne, cur_data, curX, curY, cur_isEnd);
				q->ne->d_array = q->d_array;
			}
		}
		else { // SW or NW
			if (curY < midY){ // SW
				q->sw = insertqtree(q->sw, cur_data, curX, curY, cur_isEnd);
				q->sw->d_array = q->d_array;
			}
			else{
				q->nw = insertqtree(q->nw, cur_data, curX, curY, cur_isEnd);
				q->nw->d_array = q->d_array;
			}
		}
		
		q = insertqtree(q, data, x, y, isEnd);
		return q;
	}


	else if (q->d == NULL && q->isInternal == TRUE){
		// Inserting data into grey node
		long double midX, midY;
		midX = (q->tree_boundry->TRx + q->tree_boundry->BLx) / 2;
		midY = (q->tree_boundry->TRy + q->tree_boundry->BLy) / 2;

		// Tranverse down further by detecing which direciton it is relative to the current four child node
		// recursivly go down further until the it is at a leaf node.
		if(x > midX){ // NE or SE
			if (y < midY){ // SE
				q->se = insertqtree(q->se, data, x, y, isEnd);
			}
			else{ // NE
				q->ne = insertqtree(q->ne, data, x, y, isEnd);
			}
		}
		else { // SW or NW
			if (y < midY){ // SW
				q->sw = insertqtree(q->sw, data, x, y, isEnd);
			}
			else{
				q->nw = insertqtree(q->nw, data, x, y, isEnd);
			}
		}
		return q;
	}
	return q;	
}

// Find the query x and query y from the quad tree from root node, append all data in the same quadrant of the
// query into result_array. Return amount of data of in result_array.
int 
searchqtree (double queryX, double queryY, qnode_t *q, data_t *result_array[]){
	if(q->isInternal == TRUE){
		// If not a leaf node
		long double midX = (q->tree_boundry->TRx + q->tree_boundry->BLx) / 2;
		long double midY = (q->tree_boundry->TRy + q->tree_boundry->BLy) / 2;

		// Tranverse down further by detecing which direciton query is relative to the current four child node
		// recursivly go down further until the it is a leaf node.
		// Print out the direction to reach node the same time when traversing.
		if(queryX > midX){ // NE or SE
			if (queryY < midY){ // SE
				printf(" SE");
				return searchqtree(queryX, queryY, q->se, result_array);
				
			}
			else{ // NE
				printf(" NE");
				return searchqtree(queryX, queryY, q->ne, result_array);
				
			}
		}
		else { // SW or NW
			if (queryY < midY){ // SW
				printf(" SW");
				return searchqtree(queryX, queryY, q->sw, result_array);
				
			}
			else{ // NW
				printf(" NW");
				return searchqtree(queryX, queryY, q->nw, result_array);
				
			}
		}
		
	}
	// Reaches leaf node
	else{
		// Only one data at that quadrant
		if (q->d_array[0] == NULL){
			int n = 1;
			result_array[0] = q->d;
			return n;
		}
		// More than one data at that quadrant
		else{
			result_array[0] = q->d;
			int n;
			for (n = 1; q->d_array[n - 1] != NULL; n++){
				result_array[n] = q->d_array[n - 1];
			}
			return n;
		}
	}		
}

// Print out the data from result array with n data pointers to outFile
void
printdata(data_t *result_array[], int n, FILE *outFile){
	// Sort the data so it is in order of footpath_id
	insertion_sort(result_array, n);

	// Print out all possible data of result_array
	for (int i = 0; i < n; i++){
		data_t data= *(result_array[i]);
		fprintf(outFile, "--> footpath_id: %d || address: %s || clue_sa: %s || asset_type: %s || deltaz: %.2f || distance: %.2f || grade1in: %.1f || mcc_id: %.0f"
		"|| mccid_int: %.0f || rlmax: %.2f || rlmin: %.2f || segside: %s || statusid: %.0f || streetid: %.0f || street_group: %.0f || start_lat: %.6f || "
		"start_lon: %.6f || end_lat: %.6f || end_lon: %.6f || \n",
				data.footpath_id, data.address, data.clue_sa, data.asset_type
				, data.deltaz, data.distance, data.gradelin, data.mcc_id, data.mccid_int
				, data.rlmax, data.rlmin, data.segside, data.statusid, data.streetid
				, data.street_group, data.start_lat, data.start_lon, data.end_lat, data.end_lon);
	}
	
}

// Sort the array of pointer to structs using footpath_id attribute
void 
insertion_sort(data_t *arr[], int n) { 
    int i, j; 
	data_t *key;
    for (i = 1; i < n; i++){ 
        key = arr[i]; 
        j = i - 1; 
  
        // Move elements of arr that are greater than key one space ahead
        while (j >= 0 && arr[j]->footpath_id > key->footpath_id)
        { 
            arr[j + 1] = arr[j]; 
            j = j - 1; 
        } 
        arr[j + 1] = key; 
    } 
} 

// Recursivly free the memory allocated for the quadtree
void 
freeqtree(qnode_t *q){
	// base case where root node and everything under is freed
	if (! q){
		return;
	}

	// Recursivly free every child node of root node
	freeqtree(q->sw);
	freeqtree(q->nw);
	freeqtree(q->ne);
	freeqtree(q->se);

	//free(q->d_array);

	free(q->tree_boundry);

	// Free root node
	free(q);
}
