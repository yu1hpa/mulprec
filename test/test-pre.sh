ECHO="printf %b\\n"
$ECHO \\101 2>&1 | grep -qE '^A' || {
  ECHO=
  test -e /bin/printf && {
    ECHO="/bin/printf %b\\n"
    $ECHO "\\101" 2>&1 | grep -qE '^A' || ECHO=
  }
}

SYS=`uname -m`

GREY="\\033[1;90m"
BLUE="\\033[1;94m"
GREEN="\\033[0;32m"
RED="\\033[0;31m"
YELLOW="\\033[1;93m"
RESET="\\033[0m"

$ECHO "${RESET}${GREY}[*] starting ..."

CODE=0
INCOMPLETE=0
