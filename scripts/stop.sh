#!/bin/bash
# Author:       fgautier
# Description:  A simple scrpt stopping correctly the littleserver

# this should'nt be necessary as the rights to this file
# should be along the lines 100.

if [ ! $( id -u ) -eq 0 ]; then
     echo "Please run $0 as root" ;
     exit 2
fi

echo "--------------------------------"
echo "--- Shutting down the server ---"
echo "--------------------------------"
echo ""
echo "Setting up the environment"

SCRIPT=$(readlink -f "$BASH_SOURCE")
BASEDIR=$(dirname "$SCRIPT")

source $BASEDIR/setenv.sh

if [ ! -e "$PIDSTORAGE" ]; then
    echo "Server hasn't been started yet...";
    exit 2
fi

curPID=$(<"$PIDSTORAGE")
stopCMD="kill -2 $curPID"
rmCMD="rm -f $PIDSTORAGE"

if [ $curPID -ne 0 ]; then
  echo "Stopping process $curPID (sending interruption signal)";
  echo ""
  eval $stopCMD;
  eval $rmCMD
else
  echo "Problem reading the deamon pid, aborting $0...";
  exit 2
fi
