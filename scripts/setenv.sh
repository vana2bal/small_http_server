#!/bin/bash
# Author:       fgautier
# Description:  A simple script setting common environment variables

export EXEC="littleserver"
export BIN_DIR=/home/florian/work/fun/CBasics/server/bin
export RUN_DIR_LITTLESERVER=/run/$EXEC/
export PIDSTORAGE=$RUN_DIR_LITTLESERVER/$EXEC.pid
