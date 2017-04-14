#!/bin/bash
# Author:       fgautier
# Description:  A simple script launching correctly the littleserver

# this should'nt be necessary as the rights to this file
# should be along the lines 100.

if [ ! $( id -u ) -eq 0 ]; then
     echo "Please run $0 as root" ;
     exit 2
fi

echo "--------------------------------"
echo "---   Starting the server    ---"
echo "--------------------------------"
echo ""
echo "Setting up the environment"

SCRIPT=$(readlink -f "$BASH_SOURCE")
BASEDIR=$(dirname "$SCRIPT")

source $BASEDIR/setenv.sh

if [ ! -d $RUN_DIR_LITTLESERVER ]; then
  echo "$RUN_DIR_LITTLESERVER does not exist creating it";
  mkdir $RUN_DIR_LITTLESERVER;
  chmod 700 $RUN_DIR_LITTLESERVER
fi

if [ -e "$PIDSTORAGE" ]; then
    echo "Server already started...";
    exit 2
fi

echo "Launching the server"
echo""
start_cmd="valgrind --leak-check=full --track-origins=yes --trace-children=yes $BIN_DIR/$EXEC"
eval $start_cmd
