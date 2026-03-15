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

echo ${CYAN}INSTALL.SH BEGIN${RESET}

starting_dir=$PWD

cd "$HOME"


if [ ! -e .profile ] ; then
	echo Creating $HOME/.profile
	touch .profile
fi

# Check if this script hasn't run before, prevents duplicate lines
# It should be noted that the comments are not to be removed, otherwise the uninstall script won't work.
if ! grep -q '# BEGIN ARENA_INSTALL' ".profile" ; then
	cat << 'EOF' >> .profile

# BEGIN ARENA_INSTALL
if [ -d "$HOME/.local/lib" ] ; then
	case ":$LD_LIBRARY_PATH:" in
		*":$HOME/.local/lib:"*) ;;
		*) LD_LIBRARY_PATH="$HOME/.local/lib${LD_LIBRARY_PATH:+:$LD_LIBRARY_PATH}" ;;
	esac
	case ":$LIBRARY_PATH:" in
		*":$HOME/.local/lib:"*) ;;
		*) LIBRARY_PATH="$HOME/.local/lib${LIBRARY_PATH:+:$LIBRARY_PATH}" ;;
	esac
fi

if [ -d "$HOME/.local/include" ] ; then
	case ":$CPATH:" in
		*":$HOME/.local/include:"*) ;;
		*) CPATH="$HOME/.local/include${CPATH:+:$CPATH}" ;;
	esac
fi
export CPATH LD_LIBRARY_PATH LIBRARY_PATH
# END ARENA_INSTALL
EOF
fi

cd "$starting_dir"

echo ${CYAN}INSTALL.SH END${RESET}