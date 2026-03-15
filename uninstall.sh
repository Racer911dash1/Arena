#!/bin/sh

# Colors
BLACK='\033[0;30m'
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[0;33m'
BLUE='\033[0;34m'
PURPLE='\033[0;35m'
CYAN='\033[0;36m'
WHITE='\033[0;37m'

BRIGHT_RED='\033[0;91m'
BRIGHT_BLUE='\033[0;94m'

RESET='\033[0m'

echo ${CYAN}UNINSTALL.SH BEGIN${RESET}

starting_dir=$PWD

cd "$HOME"

if grep -q '# BEGIN ARENA_INSTALL' ".profile" ; then
	echo ${BRIGHT_RED}Removing relevant targets in $HOME/.profile${RESET}
	sed -i '/# BEGIN ARENA_INSTALL/,/# END ARENA_INSTALL/d' ".profile"
fi

cd "$starting_dir"

echo ${CYAN}UNINSTALL.SH END${RESET}