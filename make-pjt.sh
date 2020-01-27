 #!/bin/zsh

TARGET=$PWD/$1

mkdir -p $TARGET/src $TARGET/file $TARGET/test

cp $PWD/dbg/dbg.h $PWD/dbg/common.h $TARGET/src
cp $PWD/dbg/Makefile $TARGET
cp run.sh $TARGET



#cp $PWD/dbg/dbg.h


