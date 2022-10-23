/* Made by Shenbo Jiang, 1271411 for COMP20003 */

/*-------------------------------------------------------------- 
Project: City of Melbourne
data.h : the header file of data.c
----------------------------------------------------------------*/

//

#ifndef _DATA_H_
#define _DATA_H_

#define MAX_LINE_lEN 512
#define MAX_STRING_LEN 128

// Type definitions
typedef struct{
	int footpath_id;
    char *address;
    char *clue_sa;
    char *asset_type;
    double deltaz;
    double distance;
    double gradelin;
    double mcc_id;
    double mccid_int;
    double rlmax;
    double rlmin;
    char *segside;
    double statusid;
    double streetid;
    double street_group;
    double start_lat;
    double start_lon;
    double end_lat;
    double end_lon;
} data_t;


// Read in one row of data into data and return the data struct
data_t read_in_one_data(char *line);

// Change the comma in between quotes into full stop for differentiating with comma and remove the quotation marks
void remove_quot(char *line);

// Free the strings that is allocated by strdup
void freestring(data_t *data);

#endif

