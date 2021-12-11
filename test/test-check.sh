#!/bin/bash

if [ $? -eq 0 ]; then
    $ECHO "$GREEN[+] ${FUNCTION}_test Success!!!${GREY}"
else
    $ECHO "$RED[!] ${FUNCTION}_test failed!!!${GREY}"
fi

