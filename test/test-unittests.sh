#! /bin/sh

. ./test-pre.sh

$ECHO "$BLUE[*] Execution Unit-Tests $GREY"

FUNCTION="add"
make $FUNCTION
./${FUNCTION}_test
. ./test-check.sh

FUNCTION="sub"
make $FUNCTION
./${FUNCTION}_test
. ./test-check.sh

FUNCTION="multiple"
make $FUNCTION
./${FUNCTION}_test
. ./test-check.sh

FUNCTION="divide"
make $FUNCTION
./${FUNCTION}_test
. ./test-check.sh

rm *_test
