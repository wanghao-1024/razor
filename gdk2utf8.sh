#!/bin/bash

base_dir=$1

echo $base_dir

function read_dir() {
    cd ${base_dir}
        files=`ls *.c *.h *.cpp`
        echo $files
        for file in $files
        do
            bak_file="${file}.bak"
            iconv -f GB2312 -t UTF-8 $file >$bak_file
            mv $bak_file $file
        done
    cd -
}

read_dir $base_dir