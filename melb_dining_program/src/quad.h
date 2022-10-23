/* Made by Shenbo Jiang, 1271411 for COMP20003 */

/*-------------------------------------------------------------- 
Project: City of Melbourne
quad.h : the header file of quad.c
----------------------------------------------------------------*/

//

#ifndef _QUAD_H_
#define _QUAD_H_

#include "data.h"
#include "linked.h"

#include <stdio.h>

#define UNKNOWN -1
#define TRUE 1
#define FALSE 2
#define SIZE_OF_COLLISION_ARRAY 50

// Typedef

// Struct for storing boundry of the node
typedef struct {
    long double BLx;
    long double BLy;
    long double TRx;
    long double TRy;
} boundry_t;

// Struct for storing point of the current node
typedef struct {
    double x;
    double y;
} point_t;


// Quad tree node
typedef struct qnode qnode_t;
struct qnode {
    // Information of current node
    boundry_t *tree_boundry;    // Boundry of the current node
	int isInternal;    // Detect if current node is a leaf
    int isEnd;      // Detect if current point is a end point or a starting point

    // Data
    data_t *d;
    data_t **d_array;     // Data array if collision happen

    point_t point; // Point of the data

    // Children of tree
    qnode_t *sw;   // SW Quadrant of this Node
    qnode_t *nw;   // NW Quadrant of this Node
    qnode_t *ne;   // NE Quadrant of this Node
    qnode_t *se;   // SE Quadrant of this Node

};


// Return boundry struct pointer using bottom left x, bottom left y, top right x and top right y
boundry_t *create_boundry(long double blX, long double blY, long double trX, long double trY);

// Return the root node of the freshly created quadtree node from given boundry
qnode_t *createqtree(boundry_t *boundry);

// Return the root node of the quadtree after data have been inserted with its x y coordinates and Information
// that if it is an end point or a staring point (Recursive)
qnode_t *insertqtree(qnode_t *q, data_t *data, double x, double y, int isEnd);

// Find the query x and query y from the quad tree from root node, append all data in the same quadrant of the
// query into result_array. Return amount of data of in result_array.
int searchqtree(double queryX, double queryY, qnode_t *q, data_t *result_array[]);

// Print out the data from result array with n data pointers to outFile
void printdata(data_t *result_array[], int n, FILE *outFile);

// Sort the data in array of n data by footpath_id 
void insertion_sort(data_t *arr[], int n);

// Recursivly free the memory allocated for the quadtree
void freeqtree(qnode_t *q);

#endif
