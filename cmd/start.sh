#!/bin/bash

if ! figlet SDNTT -w 200 -f slant  &> /dev/null
then
	sudo dnf install figlet -y
else
	figlet SDNTT -w 200 -f slant	
fi
