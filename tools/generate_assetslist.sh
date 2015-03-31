#!/bin/bash

echo "Assets list generator - fix for Android platform"
SCRIPTDIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )
CURDIR=`pwd`

cd $SCRIPTDIR

rm -f assets_list
rm -f assets_dir_list
rm -f assets_zip_list

find . -type f | cut -c 3- | grep -v generate_assets | grep -v assets_list >> assets_list
echo "Listed `wc -l assets_list` files"
#cat assets_list

find . -type d | cut -c 3- | grep -v generate_assets | grep . --color=no >> assets_dir_list
echo "Listed `wc -l assets_dir_list` directories"

find . -type f | cut -c 3- | grep -v generate_assets | egrep -i '\.zip$' >> assets_zip_list
echo "Listed `wc -l assets_zip_list` ZIP files"

cd $CURDIR
