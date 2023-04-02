#!/bin/bash

while [ 1 ]
do
	ls | grep -w yes.sh | cut -c 1-3
	sleep .3
done
