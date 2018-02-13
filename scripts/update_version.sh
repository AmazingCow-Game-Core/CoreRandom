#!/usr/bin/env sh
##~---------------------------------------------------------------------------##
##                     _______  _______  _______  _     _                     ##
##                    |   _   ||       ||       || | _ | |                    ##
##                    |  |_|  ||       ||   _   || || || |                    ##
##                    |       ||       ||  | |  ||       |                    ##
##                    |       ||      _||  |_|  ||       |                    ##
##                    |   _   ||     |_ |       ||   _   |                    ##
##                    |__| |__||_______||_______||__| |__|                    ##
##                             www.amazingcow.com                             ##
##  File      : update_version.sh                                             ##
##  Project   : CoreRandom                                                    ##
##  Date      : May 27, 2016                                                  ##
##  License   : GPLv3                                                         ##
##  Author    : n2omatt <n2omatt@amazingcow.com>                              ##
##  Copyright : AmazingCow - 2016 - 2018                                      ##
##                                                                            ##
##  Description :                                                             ##
##    Updates the version of the project in the header and doxy files.        ##
##    This scipts relies that Amazing Cow's update_version program to         ##
##    be already installed.                                                   ##
##---------------------------------------------------------------------------~##

##----------------------------------------------------------------------------##
## Vars                                                                       ##
##----------------------------------------------------------------------------##
PROJECT_NAME="CORERANDOM"
HEADER_FILE=../CoreRandom/include/CoreRandom_Utils.h
DOXY_FILE=../docs/Doxyfile

##----------------------------------------------------------------------------##
## Script                                                                     ##
##----------------------------------------------------------------------------##
## Since we're using relative paths, make sure that we are
## in the correct working directory.
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)";
cd "$SCRIPT_DIR";

## Update.
update_version $PROJECT_NAME $1 $HEADER_FILE $DOXY_FILE