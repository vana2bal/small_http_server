#!/bin/bash
# Author:       fgautier
# Description:  A simple script restarting properly the server

if [ ! $( id -u ) -eq 0 ]; then
     echo "Please run $0 as root" ;
     exit 2
fi

SCRIPT=$(readlink -f "$BASH_SOURCE")
BASEDIR=$(dirname "$SCRIPT")

stop="$BASEDIR/stop.sh"
eval $stop

start="$BASEDIR/start.sh"
eval $start
