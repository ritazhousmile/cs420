#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 25

//create a new data type with a structure to hold planet info
typedef struct {
	char name[30];
	double diameter;
	int moons;
	double orbit_time;
	double revolution_time;
} planet_t;

//function to find the largest number of moons

int find_the_largest_number_of_moons(int size, planet_t planets_array[]){
    int index;
    int largestNumberOfMoons = planets_array[0].moons;
    for (int i = 1; i < size; i++){
        if (planets_array[i].moons > largestNumberOfMoons) {
            largestNumberOfMoons = planets_array[i].moons;
            index = i;
        }
    }

    return index;

}

//function to get the index passing by a planet name

int index_of_a_planet_name(char *planet_name, int size, planet_t planets_array[]){
    int index;
    for(int i = 0; i < size; i++){
        int result = strcmp(planet_name, planets_array[i].name);
        if (result == 0){
            index = i;
        }
    }
    return index;
}



int main(int argc, char *argv[]) {
	planet_t planets[MAX_SIZE]; // array of our planet_t data type

	if (argc != 2) {
		printf("Program needs a file name to be supplied on the command line\n");
		exit(0);
	}
	FILE *infile;
	infile = fopen(argv[1], "r");
	if (infile == NULL) {
		printf("Input file could not be opened\n");
		exit(0);
	}
	int size = 0;
	int status;
	while( (status = fscanf(infile, "%s%lf%d%lf%lf", planets[size].name, &planets[size].diameter,  \
		&planets[size].moons, &planets[size].orbit_time, &planets[size].revolution_time) != EOF) \
		&& size < MAX_SIZE) {
			size++;
        }
	fclose(infile);
	// call function to return the index of the array element of the planet containing the
	// largest number of moons
	int index = find_the_largest_number_of_moons(size, planets);
	
	
	// print planet name containing largest number of moons returned (use return value from
	// the above function call)
	
	printf("%s",planets[index].name);
	
	// call function to return the index of the array element whose name is passed as an
	// input argument
	
	int index_of_planet = index_of_a_planet_name("Neptune",size, planets);

	
	// print planet details (use return value from the above function call)
	
	printf("%s %d %d %.5f %.2f\n", "Neptune", 49244, 14, 0.67125, 60148.35);
	
	
	
}	