#!/bin/sh

NITRO_ENGINE=$BLOCKSDS../../external/nitro-engine
ASSETS="assets"
TOOLS=$NITRO_ENGINE/tools
OBJ2DL=$TOOLS/obj2dl/obj2dl.py
BLOCKSDS="${BLOCKSDS:-/opt/blocksds/core/}"
GRIT=$BLOCKSDS/tools/grit/grit

mkdir nitrofiles

#rm -rf nitrofiles/model
mkdir -p nitrofiles/model

#rm -rf nitrofiles/model/cars
mkdir -p nitrofiles/model/cars

#rm -rf nitrofiles/model/cars/car
mkdir -p nitrofiles/model/cars/car

#rm -rf nitrofiles/model/cars/car
mkdir -p nitrofiles/model/nature

mkdir -p nitrofiles/model/nature/tree

python $OBJ2DL \
    --input $ASSETS/model/car/car.obj \
    --output nitrofiles/model/cars/car/car.bin \
    --texture 128 128

python $OBJ2DL \
    --input $ASSETS/model/nature/trees/tree/tree01.obj \
    --output nitrofiles/model/nature/tree/tree01.bin \
    --texture 256 256

python $OBJ2DL \
    --input $ASSETS/cube.obj \
    --output nitrofiles/cube.bin \
    --texture 128 128
$GRIT \
    $ASSETS/model/nature/trees/tree/tree01_spring.png \
    -gx -gb -gB16 -gT! -ftb -fh! -W1\
    -o nitrofiles/model/nature/tree/tree01_spring

$GRIT \
    $ASSETS/model/car/texture/car_blue.png \
    -gx -gb -gB16 -gT! -ftb -fh! -W1\
    -o nitrofiles/model/cars/car/car_blue

$GRIT \
    $ASSETS/terrain/grass.png \
    -gx -gb -gB16 -gT! -ftb -fh! -W1\
    -o nitrofiles/grass
