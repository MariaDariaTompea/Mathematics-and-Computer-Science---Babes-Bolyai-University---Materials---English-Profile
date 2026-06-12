#include <stdio.h>
#include <stdlib.h>

/*
	Usage:
	./matrix 3 2

	Expected output:
	0 1 2
	3 4 5
*/
int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Wrong argument count\n");

		// Non-zero return codes are used to signal errors.
		return 1;
	}

	// sscanf is similar to scanf, but parses the string provieded as the first
	// argument instead of reading from the keyboard.
	int w, h;
	sscanf(argv[1], "%d", &w);
	sscanf(argv[2], "%d", &h);
	
	// Allocate space for the row pointers. 
	int **matrix = malloc(h * sizeof(int*));

	for (int i = 0; i < h; ++i) {
		// Allocate space for the elements in the row.
		matrix[i] = malloc(w * sizeof(int));
	}

	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			matrix[i][j] = i * w + j; 
		}
	}

	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			printf("%d ", matrix[i][j]);
		}

		printf("\n");
	}

	for (int i = 0; i < h; ++i) {
		// Free the elements in the row.
		free(matrix[i]);
	}

	// Free the row pointers. 
	free(matrix);

	return 0;
}
