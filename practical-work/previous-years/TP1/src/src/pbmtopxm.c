#include <stdlib.h>
#include <stdio.h>
#include "Util.h"


void pxmtopbm(char* filename) {
    FILE* ifp;
    bit* bitmap;
    int ich1, ich2, rows, cols ;
    int i,j ;
    
    /* We open the file we want to read */
    ifp = fopen(filename,"r");
    
    /* Reading the "Magic number" */
    ich1 = getc( ifp );
    if (ich1 == EOF)
        pm_erreur( "Error: EOF encountered while reading the header" );
    if (ich1 !='P')
        pm_erreur("Error: the file must start by the character P");
    
    ich2 = getc(ifp);
    if (ich2 == EOF)
        pm_erreur( "Error: EOF encountered while reading the header" );
    if(ich2 != '1')
      pm_erreur(" Wrong ifp format: P1 is the only one supported ");
    
    /* Reading the dimensions of the image */
    cols = pm_getint(ifp);
    rows = pm_getint(ifp);

    /* Reading the image */
    bitmap = (bit *) malloc(cols * rows * sizeof(bit));
    
    for(i=0; i < rows; i++)
      for(j=0; j < cols ; j++)
        bitmap[i * cols + j] = pm_getbit(ifp);
    
    /* Closing the file */
    fclose(ifp);
    
    /* Writting the new image */
    printf("P2\n");
    printf("%d %d \n", cols, rows);
    printf("1\n");
    for(i=0; i < rows; i++)
      for(j=0; j < cols ; j++)
        printf("%u ",bitmap[i * cols + j] );
    printf("\n");
    
    return;
}

void pgmtopgm(char* filename) {
    // TODO: Complete here for exercice 2
    
}

void pgmtopbm(char* filename) {
    // TODO: Complete here for exercice 3
    
}

void ppmtopgm(char* filename) {
    // TODO: Complete here for exercice 4
    
}

int main(int argc, char* argv[]) {
    /* We test the arguments */
    if (argc != 2) {
      printf("\nUsage : pbmtopgm file \n\n");
      exit(0);
    }
    
    // TODO: remember to modify here...
    pxmtopbm(argv[1]);
    
    return 0;
}

