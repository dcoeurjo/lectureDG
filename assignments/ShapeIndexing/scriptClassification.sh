#!/bin/zsh
zmodload -i zsh/mathfunc

##YOUR Classification progname
CLASSIFPROG="./naiveClassification.sh"

#nb of source images to test
NBIMGTESTS=40

#nb of noisyfied copies
NBTESTS=5

#No noise here
MAXNOISE=0.0
sum=0.0
variance=0.0
cpt=0.0

for ((i=0; i < $NBIMGTESTS; i++)); do
    ##Pick a random class
    CLASSID=`expr $RANDOM % 61 + 1`
    CLASSNAME=`head -$CLASSID classes.csv | tail -1 | sed -e 's/,//'`
    echo "Classname: "$CLASSNAME

    ##Pick a random image in this class
    IMGID=`expr $RANDOM % 10 + 1`
    IMGNAME=database/$CLASSNAME-$IMGID.pgm
    echo $IMGNAME

    if [[ -e $IMGNAME ]]; then
        for ((j=0; j < $NBTESTS; j+=1)); do
            ##Random scale+rotation
            ANGLE=$((rand48()*3.1415))
            SCALE=$((rand48()*3))
            NOISE=$((rand48()*MAXNOISE))
            ./imgRotate -i $IMGNAME -o tmp.pgm -a $ANGLE 2> /dev/null
            ./imgScale -i tmp.pgm -o tmp2.pgm -s $SCALE 2> /dev/null
            ./imgAddNoise -i tmp2.pgm -o tmp.pgm -n $NOISE  2> /dev/null

            ##Running the retrieval
            eval `echo $CLASSIFPROG tmp.pgm` >! scores_tmp.txt
            RANK=` ./getRank scores_tmp.txt $CLASSID`
            echo "Rank=$RANK"
            
            ##Number of correct results in the first 10 
            if [[ $RANK -le 10 ]]; then
               correct=$(($correct + 1.0))
            fi
            cpt=$(($cpt + 1.0))
        done
    fi
done
echo
echo "Number of 'correct' classification (first 10 classes)= "$correct
echo "Total number of tests= "$cpt
echo "Final score= " $(( $correct / $cpt ))
rm tmp.pgm
rm tmp2.pgm
rm scores_tmp.txt
