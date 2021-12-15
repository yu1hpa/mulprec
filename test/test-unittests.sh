#! /bin/sh

. ./test-pre.sh

function f(){
    for ut in ${unittests[@]}
    do
        make $ut
        FUNCTION=$ut
        ./${FUNCTION}_test
        . ./test-check.sh
    done
}

$ECHO "$BLUE[*] Execution Unit-Tests $GREY"

unittests=("add" "sub" "multiple" "divide" "power" "fastpower")
f unittests
rm *_test
