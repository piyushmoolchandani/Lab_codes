#!/bin/bash
copyit () {
    if [ -f "$1" ]
    then
	cat $1 > $2
    else
        echo 'File does not exists!.'
    fi
}
copyit $@
