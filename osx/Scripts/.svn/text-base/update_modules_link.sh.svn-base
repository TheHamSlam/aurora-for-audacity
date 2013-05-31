#! /bin/bash

cd build/Release\ Shared

# Handy build tools for Applications on OSX
APP_NAME=Audacity
BUNDLE_NAME=Audacity
BINARY_PATH=${BUNDLE_NAME}.app/Contents/MacOS
FRAMEWORKS_PATH=${BUNDLE_NAME}.app/Contents/Frameworks
MODULES_PATH=modules
LIBS_SRC_PATH=/usr/local/lib


WXLIBS_SRC_PATH=${LIBS_SRC_PATH}
WXLIBS_DEST_PATH=libs
WXLIBS=( "libwx_macu_html-2.8.0.dylib" "libwx_macu_adv-2.8.0.dylib" "libwx_macu_core-2.8.0.dylib" "libwx_base_carbonu_xml-2.8.0.dylib" "libwx_base_carbonu_net-2.8.0.dylib" "libwx_base_carbonu-2.8.0.dylib" )
WXLIBS_ARRAY_SIZE=${#WXLIBS[@]}


if [[ "$#" -lt 1 ]]
then
    for MODULE_NAME in ${MODULES_PATH}/*.so
    do
        IDX=0
        echo "Updating link for module ${MODULE_NAME}"
        while [[ "$IDX" -lt "$WXLIBS_ARRAY_SIZE" ]]
        do
            # ...update libraries links...
            echo " -> ${LIBS_SRC_PATH}/${WXLIBS[$IDX]}  to @executable_path/../../../${WXLIBS_DEST_PATH}/${WXLIBS[$IDX]}"
            install_name_tool -change ${LIBS_SRC_PATH}/${WXLIBS[$IDX]}  @executable_path/../../../${WXLIBS_DEST_PATH}/${WXLIBS[$IDX]} "${MODULE_NAME}"

            let "IDX = $IDX + 1"
        done
    # ...and show changes.
    #    otool -L ${MODULES_PATH}/${MODULE_NAME}

    done
else
    MODULE_NAME="$1 $2"
    echo "Updating link for module ${MODULE_NAME}"
    while [[ "$IDX" -lt "$WXLIBS_ARRAY_SIZE" ]]
    do
        # ...update libraries links...
        echo " -> ${LIBS_SRC_PATH}/${WXLIBS[$IDX]}  to @executable_path/../../../${WXLIBS_DEST_PATH}/${WXLIBS[$IDX]}"
        install_name_tool -change ${LIBS_SRC_PATH}/${WXLIBS[$IDX]}  @executable_path/../../../${WXLIBS_DEST_PATH}/${WXLIBS[$IDX]} "${MODULE_NAME}"

        let "IDX = $IDX + 1"
    done
fi

# Go out.
cd ../..
