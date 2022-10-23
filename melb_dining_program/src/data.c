/* Made by Shenbo Jiang, 1271411 for COMP20003 */

/*-------------------------------------------------------------- 
Project: City of Melbourne
data.c : the interface of helper function of the project
----------------------------------------------------------------*/

//

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#include "data.h"

// Read in one row of data into data and return the data struct
data_t
read_in_one_data(char *line){
	int k = 0;
	char new_line[MAX_LINE_lEN + 3];

	//initialize all buffer
	int footpath_id;
    double deltaz, distance, gradelin, mcc_id, mccid_int, rlmax, rlmin, statusid, streetid, 
		street_group, start_lat, start_lon, end_lat, end_lon;
    char address[MAX_STRING_LEN + 1], 
		clue_sa[MAX_STRING_LEN + 1], 
		asset_type[MAX_STRING_LEN + 1], 
		segside[MAX_STRING_LEN + 1];


	data_t data;

	// Add a space in between two commas right next to each other
	for (int j = 0; line[j] != '\0'; j++){
		new_line[k] = line[j];
		if (line[j] == line [j + 1] && line[j] == ','){	
			new_line[k + 1] = ' ';
			k += 1;
		
		}
		k++;
	} 
	new_line[k] = '\0';

	// If quotation mark exist in the line, process the string further in remove_quot function
	for (int i = 0; i < strlen(new_line); i++){
		if (new_line[i] == '"'){
			remove_quot(new_line);
		}
	}
	
	sscanf(new_line, "%d,%[^,],%[^,],%[^,],%lf,%lf,%lf,%lf,%lf,%lf,%lf,%[^,],%lf,%lf,%lf,%lf,%lf,%lf,%lf",
	&footpath_id, address, clue_sa, asset_type, &deltaz, &distance, &gradelin, &mcc_id, &mccid_int, &rlmax, &rlmin,
	segside, &statusid, &streetid, &street_group, &start_lat, &start_lon, &end_lat, &end_lon);

	data.footpath_id = footpath_id;
	// Replace the space back to null
	if (address[0] == ' '){
		address[0]= '\0';
	}
	data.address = strdup(address);
	// Replace the comma between quotes that have been replaced to full stop in remove_quot back to comma
	for (int i = 0; clue_sa[i] != '\0'; i++){
		if (clue_sa[i] == '.'){
			clue_sa[i] = ',';
		}
	}
	data.clue_sa = strdup(clue_sa);
	data.asset_type = strdup(asset_type);
	data.deltaz = deltaz;
	data.distance = distance;
	data.gradelin = gradelin;
	data.mcc_id = mcc_id;
	data.mccid_int = mccid_int;
	data.rlmax = rlmax;
	data.rlmin = rlmin;
	// Replace the space back to null
	if (segside[0] ==  ' '){
		segside[0]= '\0';
	}
	data.segside = strdup(segside);
	data.statusid = statusid;
	data.streetid = streetid;
	data.street_group = street_group;
	data.start_lat = start_lat;
	data.start_lon = start_lon;
	data.end_lat = end_lat;
	data.end_lon = end_lon;


	return data;
}

// Change the comma in between quotes into full stop for differentiating with comma and remove the quotation marks
void
remove_quot(char *line){
    int loc[2], n = 0, i, j = 0;

	// Remeber the location of quotation marks in the string
	for (i = 0; i < strlen(line); i++){
		if (line[i] == '"'){
			loc[n] = i;
			n++;
		}
	}
	
	// change the comma in between quotation marks into full stop
    for(i = loc[0]; i < loc[1]; i++) {
        if(line[i] == ','){
            line[i] = '.';
        }
    }

	// Remove quotation marks
    for(i = 0; line[i] != '\0'; i++) {
        if(line[i] != '"') {
            line[j] = line[i];
            j++;
        }
    }
    line[j] = '\0';
    return;
}

// Free the memory allocated from strdup in the data struct
void
freestring(data_t *data){
	free(data->address);
    free(data->clue_sa);
    free(data->asset_type);
    free(data->segside);
}



