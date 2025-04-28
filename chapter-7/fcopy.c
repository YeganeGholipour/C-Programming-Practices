#include <stdio.h>
#include <stdlib.h>


/*****************
 * first open file1
 * open file2 
 * get each character from file1 and add it to file2
 * then close both files
*******************/

int main(int argc , char *argv[]) {
    FILE *source_fp, *dest_fp;
    int c;

    if (argc != 3) {
        printf("Usage: You need to specify the files' names");
        exit(EXIT_FAILURE);
    }


    if ((source_fp = fopen(argv[1], "rb")) == NULL) {
        fprintf(stderr, "Can't open %s\n", argv[1]);
        exit(EXIT_FAILURE);
    }

    if ((dest_fp = fopen(argv[2], "wb")) == NULL) {
        fprintf(stderr, "Can't open %s\n", argv[2]);
        exit(EXIT_FAILURE);
    }

    while ((c = fgetc(source_fp)) != EOF)
        fputc(c, dest_fp);

    fclose(source_fp);
    fclose(dest_fp);
    return 0;
}