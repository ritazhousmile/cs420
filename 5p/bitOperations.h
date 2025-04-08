#define INVALID_INPUT_FILE -1
#define MAX_DATES 100

typedef struct {
	char startDateStr[12];
	unsigned short int binaryDate;
	unsigned short int reverseDate;
	unsigned short int shiftedDate;
	char endDateStr[12];
	int endDateValid;
} date_t;

/* First argument is input file name, second argument is an array */
/* Function return value is an integer for size of array filled in */
int convertDate(char [], date_t []);
