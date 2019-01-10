#!/bin/bash

echo Enter file-name and a number
read file_name number
sed  -i '/'$number'/d' $file_name
