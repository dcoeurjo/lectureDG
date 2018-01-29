#######################################
# Makefile PBM                        #  
#                                     #
# E.B.                                #
#######################################
 

PROG = pbmtopxm

# Variables pour la compilation des fichiers
CC        =  gcc
CFLAGS    =  -g -Wall
CPPFLAGS  =  -DDEBUG -I$(INCDIR)
LDFLAGS   =  -g 


all : $(PROG) 

%.o : %.c Util.h
	$(CC) -c $(CPPFLAGS) $(CFLAGS) $< -o $@ 

$(PROG): % : %.o Util.o 
	$(CC) $(LDFLAGS) -o $@ $< Util.o -lm
 
cleanall : clean
	rm  pbmtopgm pgmtopgm pgmtopbm ppmtopgm pxmtopxm

clean :
	rm *.o

