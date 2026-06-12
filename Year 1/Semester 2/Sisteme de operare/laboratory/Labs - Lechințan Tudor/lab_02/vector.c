#include <stdio.h>
#include <stdlib.h>

/*
	Usage:
	./vector 1 2 3 4 5

	Expected output:
	5 4 3 2 1
*/
int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Wrong argument count");
		return 1;
	}

	int n;
	sscanf(argv[1], "%d", &n);

	int *num = malloc(n * sizeof(int));

	for (int i = 0; i < n; ++i) {
		scanf("%d", &num[i]);
	}

	printf("Numbers in reverse order:\n");
	for (int i = n - 1; i >= 0; --i) {
		printf("%d\n", num[i]);
	}

	free(num);
	return 0;
}
