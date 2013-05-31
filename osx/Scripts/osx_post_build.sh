#! /bin/bash

BUILD_SUFFIX="build/Release Shared"
AUDACITY_OSX_PATH=${HOME}/src/audacity-read-only/mac
AURORA_OSX_PATH=${HOME}/src/aurora/osx

CURRENT_PATH=`pwd`

cd "${AURORA_OSX_PATH}/${BUILD_SUFFIX}"

if [[ "$#" -lt 1 ]]
then
   # if there isn't arguments on the command line, then
   # process all modules
   for MODULE in *.so
   do
      echo "Copying  ${MODULE} to ${AUDACITY_OSX_PATH}/${BUILD_SUFFIX}/modules"
      cp  ${MODULE} "${AUDACITY_OSX_PATH}/${BUILD_SUFFIX}/modules" 
   done
   
   cd ${AUDACITY_OSX_PATH}
   ./update_modules_link
   
else
   MODULE=$1
   echo "Copying  ${MODULE} to ${AUDACITY_OSX_PATH}/${BUILD_SUFFIX}/modules"
   cp  ${MODULE} "${AUDACITY_OSX_PATH}/${BUILD_SUFFIX}/modules" 

   cd ${AUDACITY_OSX_PATH}
   ./update_modules_link ${MODULE}
fi


echo "done."

cd ${CURRENT_PATH}

exit 0