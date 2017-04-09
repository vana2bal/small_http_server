#!/bin/bash
# Author:       fgautier
# Description:  A simple script checking if both pid got from 'top'
# and 'littleserver.pid' matches

SCRIPT=$(readlink -f "$BASH_SOURCE")
BASEDIR=$(dirname "$SCRIPT")

source $BASEDIR/setenv.sh

PGREP_CMD="pgrep $EXEC"
PGREP_PID=$($PGREP_CMD)

if [ -e "$PIDSTORAGE" ]; then
  STORED_PID=$(<"$PIDSTORAGE")
else
  STORED_PID=""
fi


if [ $PGREP_PID -eq $STORED_PID ]; then
  echo Everything is fine;
  echo Pgrep cmd deamon PID: $PGREP_PID;
  echo Stored deamon PID: $STORED_PID
else
  echo "Oups server is down in a badway";
  echo Pgrep cmd deamon PID: $PGREP_PID;
  echo Stored deamon PID: $STORED_PID
fi
