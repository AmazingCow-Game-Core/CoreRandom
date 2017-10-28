#!/bin/bash
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
##  Copyright : AmazingCow - 2016, 2017                                       ##
##                                                                            ##
##  Description :                                                             ##
## This will update the ProjectName (HEADER_FILE) and the                     ##
## Doxyfile (DOXY_FILE) version strings.                                      ##
## Very dirty, but does the job - We were forgeting to update the version     ##
## string before each release.                                                ##
## Today it is local to this project (but if it become too complex) it        ##
## will be placed into a separate project.                                    ##
##---------------------------------------------------------------------------~##

################################################################################
## CONFIG                                                                     ##
################################################################################
PROJECT_NAME="CORERANDOM"
HEADER_FILE=./include/CoreRandom_Utils.h
DOXY_FILE=Doxyfile


################################################################################
## Vars                                                                       ##
################################################################################
MAJOR=$(echo $@ | cut -d. -f1);
MINOR=$(echo $@ | cut -d. -f2);
REVISION=$(echo $@ | cut -d. -f3);


################################################################################
## Sanity                                                                     ##
################################################################################
#Thanks to Charles Duffy in SO.
#http://stackoverflow.com/questions/806906/how-do-i-test-if-a-variable-is-a-number-in-bash
re='^[0-9]+$' #Check if is number.

if ! [[ $MAJOR =~ $re ]] ; then
   echo "MAJOR Not a number" >&2;
   exit 1
fi

if ! [[ $MINOR =~ $re ]] ; then
   echo "MINOR Not a number" >&2;
   exit 1
fi

if ! [[ $REVISION =~ $re ]] ; then
   echo "REVISION Not a number" >&2;
   exit 1
fi


################################################################################
## Update HEADER FILE                                                         ##
################################################################################
MAJOR_STR="#define COW_${PROJECT_NAME}_VERSION_MAJOR    ";
MINOR_STR="#define COW_${PROJECT_NAME}_VERSION_MINOR    ";
REVISION_STR="#define COW_${PROJECT_NAME}_VERSION_REVISION ";

cat $HEADER_FILE \
    | sed -e s/"$MAJOR_STR\".*\""/"$MAJOR_STR\"$MAJOR\""/g          \
    | sed -e s/"$MINOR_STR\".*\""/"$MINOR_STR\"$MINOR\""/g          \
    | sed -e s/"$REVISION_STR\".*\""/"$REVISION_STR\"$REVISION\""/g \
    > $HEADER_FILE.new;

################################################################################
## Update DOXY FILE                                                           ##
################################################################################
PROJECT_NUMBER_STR="PROJECT_NUMBER         ="
PROJECT_NUMBER_STR_REPLACE="PROJECT_NUMBER         = v$MAJOR.$MINOR.$REVISION";

cat $DOXY_FILE \
    | sed -e s/"$PROJECT_NUMBER_STR.*"/"$PROJECT_NUMBER_STR_REPLACE"/g \
    > $DOXY_FILE.new;



################################################################################
## CHECKING                                                                   ##
################################################################################
## CHECK IF OPERATION WAS OK ##
cat $HEADER_FILE.new;

echo "Is this correct?[y/n]";
read CORRECT;

if [ "$CORRECT" = "y" ]; then
    echo "Updating the files..."
    mv $DOXY_FILE.new  $DOXY_FILE;
    mv $HEADER_FILE.new  $HEADER_FILE;
else
  rm $DOXY_FILE.new
  rm $HEADER_FILE.new
fi;

