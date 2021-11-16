$ECHO "$GREY[*] test cases completed.$RESET"
test "$INCOMPLETE" = "0" && $ECHO "$GREEN[+] all test cases executed"
test "$INCOMPLETE" = "1" && $ECHO "$YELLOW[-] not all test cases were executed"
test "$CODE" = "0" && $ECHO "$GREEN[+] all tests were successful :-)$RESET"
test "$CODE" = "0" || $ECHO "$RED[!] failure in tests :-($RESET"
exit $CODE
