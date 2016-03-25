#!/bin/zsh
zmodload -i zsh/mathfunc

##YOUR SIMILARITY PROG NAME
SIMILARYPROG=./naiveDistance

#nb of source images to test
NBIMGTESTS=10

#nb of noisyfied copies
NBTESTS=20

MAXNOISE=0.7
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
            ./imgRotate -i $IMGNAME -o tmp.pgm -a $ANGLE 2>/dev/null
            ./imgScale -i tmp.pgm -o tmp2.pgm -s $SCALE 2>/dev/null
            ./imgAddNoise -i tmp2.pgm -o tmp.pgm -n $NOISE 2>/dev/null

            DIST=`$SIMILARYPROG $IMGNAME tmp.pgm`
            sum=$(( $sum + $DIST))
            variance=$(( $variance + $DIST*$DIST ))
            echo "Similarity= "$DIST
            cpt=$(($cpt + 1.0))
        done
    fi
done
echo
echo "Average similarity= " $(( $sum / $cpt ))
echo "Variance= " $(( $variance / $cpt - ($sum / $cpt)*($sum / $cpt)  ))
rm tmp.pgm
rm tmp2.pgm
