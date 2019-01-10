#!/bin/bash
for file in *
do
	changed_name=$(echo $file | tr 'A-Za-z' 'a-zA-Z')
    	mv $file $changed_name
done
