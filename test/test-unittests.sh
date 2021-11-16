#! /bin/sh

. ./test-pre.sh

$ECHO "$BLUE[*] Execution Unit-Tests $GREY"

make -C .. unittest
time ./a.out 2> test-comp.log | 2> /dev/null 2>&1
rm a.out
test -e test-comp.log && {
    grep -E 'Assertion failed' test-comp.log > /dev/null 2>&1 && {
        $ECHO "$RED[!] Failed"
        CODE=1
    }
}
rm test-comp.log

. ./test-post.sh
