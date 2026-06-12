#include <stdio.h>

/*
	Usage:
	./mycat file1.txt file2.txt
*/
int main(int argc, char *argv[]) {
	char buf[128];

	for (int i = 1; i < argc; ++i) {
		FILE *file = fopen(argv[i], "r");

		if (file == NULL) {
			printf("Cannot open file: %s\n", argv[i]);
			return 1;
		}

		while (1) {
			// We pass a smaller value for the count argument to leave space for the
			// nul terminator.
			int n = fread(buf, 1, 127, file);

			if (n == 0) {
				break;
			}

			// printf works with nul-terminated strings, so we add the nul manually.
			buf[n] = '\0';

			printf("%s", buf);
		}

		fclose(file);
	}

	return 0;
}
