/* Utilitaires de lecture pour les fichiers PBM, PGM, PPM
 * E.B.  12/98
 */

#ifndef _Util_h
#define _Util_h


typedef unsigned char bit;
typedef unsigned char gray;



// Returns the next bit (0 or 1) of "file". Takes into account the following separation char: ' ', '\t', '\n', '\r'
bit pm_getbit(FILE* file);

// Returns the next char of "file". Takes into account the following separation char: '\n', '\r' and the lines starting by #
char pm_getc(FILE* file);

// Returns the next integer of "file". Takes into account the following separation char: ' ', '\t', '\n' and '\r'
int pm_getint( FILE* file);

// Returns the next Byte (octet) of "file" - do not ignore separation char
unsigned char pm_getrawbyte(FILE* file);

// Throws an exception whose error message is "texte"
void pm_erreur(char *texte);

#endif

