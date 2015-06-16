#!/bin/bash

usage() {
    echo "usage: $0 your-wc209-bin"
    exit -1
}

WC209_BIN=$1

if [[ -z "${WC209_BIN}" ]]; then
    usage
fi

if [[ ! -f "${WC209_BIN}" ]]; then
    echo "ERROR: ${WC209_BIN} does not exist"
    usage
fi

if [[ ! -x "${WC209_BIN}" ]]; then
    echo "ERROR: ${WC209_BIN} is NOT an executable file!"
    usage
fi

cd inputs/

echo description-0_x1
$WC209_BIN -l description.txt | diff -uw ../gnu-wc-outputs/description-0_x1.l.out -
echo

echo description-0_x3
$WC209_BIN -l description.txt description.txt description.txt | diff -uw ../gnu-wc-outputs/description-0_x3.l.out -
echo

echo description-0_stdin
cat description.txt | $WC209_BIN -l | diff -uw ../gnu-wc-outputs/description-0_stdin.l.out -
echo

echo quick-0_x1
$WC209_BIN -l quick.txt | diff -uw ../gnu-wc-outputs/quick-0_x1.l.out -
echo

echo quick-0_x3
$WC209_BIN -l quick.txt quick.txt quick.txt | diff -uw ../gnu-wc-outputs/quick-0_x3.l.out -
echo

echo quick-0_stdin
cat quick.txt | $WC209_BIN -l | diff -uw ../gnu-wc-outputs/quick-0_stdin.l.out -
echo

echo quick3-0_x1
$WC209_BIN -l quick3.txt | diff -uw ../gnu-wc-outputs/quick3-0_x1.l.out -
echo

echo quick3-0_x3
$WC209_BIN -l quick3.txt quick3.txt quick3.txt | diff -uw ../gnu-wc-outputs/quick3-0_x3.l.out -
echo

echo quick3-0_stdin
cat quick3.txt | $WC209_BIN -l | diff -uw ../gnu-wc-outputs/quick3-0_stdin.l.out -
echo

echo syllabus-0_x1
$WC209_BIN -l syllabus.txt | diff -uw ../gnu-wc-outputs/syllabus-0_x1.l.out -
echo

echo syllabus-0_x3
$WC209_BIN -l syllabus.txt syllabus.txt syllabus.txt | diff -uw ../gnu-wc-outputs/syllabus-0_x3.l.out -
echo

echo syllabus-0_stdin
cat syllabus.txt | $WC209_BIN -l | diff -uw ../gnu-wc-outputs/syllabus-0_stdin.l.out -
echo

echo ulysses-0_x1
$WC209_BIN -l ulysses.txt | diff -uw ../gnu-wc-outputs/ulysses-0_x1.l.out -
echo

echo ulysses-0_x3
$WC209_BIN -l ulysses.txt ulysses.txt ulysses.txt | diff -uw ../gnu-wc-outputs/ulysses-0_x3.l.out -
echo

echo ulysses-0_stdin
cat ulysses.txt | $WC209_BIN -l | diff -uw ../gnu-wc-outputs/ulysses-0_stdin.l.out -
echo

echo manpage-0_x1
$WC209_BIN -l manpage.txt | diff -uw ../gnu-wc-outputs/manpage-0_x1.l.out -
echo

echo manpage-0_x3
$WC209_BIN -l manpage.txt manpage.txt manpage.txt | diff -uw ../gnu-wc-outputs/manpage-0_x3.l.out -
echo

echo manpage-0_stdin
cat manpage.txt | $WC209_BIN -l | diff -uw ../gnu-wc-outputs/manpage-0_stdin.l.out -
echo

echo description-1_x1
$WC209_BIN -w description.txt | diff -uw ../gnu-wc-outputs/description-1_x1.w.out -
echo

echo description-1_x3
$WC209_BIN -w description.txt description.txt description.txt | diff -uw ../gnu-wc-outputs/description-1_x3.w.out -
echo

echo description-1_stdin
cat description.txt | $WC209_BIN -w | diff -uw ../gnu-wc-outputs/description-1_stdin.w.out -
echo

echo quick-1_x1
$WC209_BIN -w quick.txt | diff -uw ../gnu-wc-outputs/quick-1_x1.w.out -
echo

echo quick-1_x3
$WC209_BIN -w quick.txt quick.txt quick.txt | diff -uw ../gnu-wc-outputs/quick-1_x3.w.out -
echo

echo quick-1_stdin
cat quick.txt | $WC209_BIN -w | diff -uw ../gnu-wc-outputs/quick-1_stdin.w.out -
echo

echo quick3-1_x1
$WC209_BIN -w quick3.txt | diff -uw ../gnu-wc-outputs/quick3-1_x1.w.out -
echo

echo quick3-1_x3
$WC209_BIN -w quick3.txt quick3.txt quick3.txt | diff -uw ../gnu-wc-outputs/quick3-1_x3.w.out -
echo

echo quick3-1_stdin
cat quick3.txt | $WC209_BIN -w | diff -uw ../gnu-wc-outputs/quick3-1_stdin.w.out -
echo

echo syllabus-1_x1
$WC209_BIN -w syllabus.txt | diff -uw ../gnu-wc-outputs/syllabus-1_x1.w.out -
echo

echo syllabus-1_x3
$WC209_BIN -w syllabus.txt syllabus.txt syllabus.txt | diff -uw ../gnu-wc-outputs/syllabus-1_x3.w.out -
echo

echo syllabus-1_stdin
cat syllabus.txt | $WC209_BIN -w | diff -uw ../gnu-wc-outputs/syllabus-1_stdin.w.out -
echo

echo ulysses-1_x1
$WC209_BIN -w ulysses.txt | diff -uw ../gnu-wc-outputs/ulysses-1_x1.w.out -
echo

echo ulysses-1_x3
$WC209_BIN -w ulysses.txt ulysses.txt ulysses.txt | diff -uw ../gnu-wc-outputs/ulysses-1_x3.w.out -
echo

echo ulysses-1_stdin
cat ulysses.txt | $WC209_BIN -w | diff -uw ../gnu-wc-outputs/ulysses-1_stdin.w.out -
echo

echo manpage-1_x1
$WC209_BIN -w manpage.txt | diff -uw ../gnu-wc-outputs/manpage-1_x1.w.out -
echo

echo manpage-1_x3
$WC209_BIN -w manpage.txt manpage.txt manpage.txt | diff -uw ../gnu-wc-outputs/manpage-1_x3.w.out -
echo

echo manpage-1_stdin
cat manpage.txt | $WC209_BIN -w | diff -uw ../gnu-wc-outputs/manpage-1_stdin.w.out -
echo

echo description-2_x1
$WC209_BIN -c description.txt | diff -uw ../gnu-wc-outputs/description-2_x1.c.out -
echo

echo description-2_x3
$WC209_BIN -c description.txt description.txt description.txt | diff -uw ../gnu-wc-outputs/description-2_x3.c.out -
echo

echo description-2_stdin
cat description.txt | $WC209_BIN -c | diff -uw ../gnu-wc-outputs/description-2_stdin.c.out -
echo

echo quick-2_x1
$WC209_BIN -c quick.txt | diff -uw ../gnu-wc-outputs/quick-2_x1.c.out -
echo

echo quick-2_x3
$WC209_BIN -c quick.txt quick.txt quick.txt | diff -uw ../gnu-wc-outputs/quick-2_x3.c.out -
echo

echo quick-2_stdin
cat quick.txt | $WC209_BIN -c | diff -uw ../gnu-wc-outputs/quick-2_stdin.c.out -
echo

echo quick3-2_x1
$WC209_BIN -c quick3.txt | diff -uw ../gnu-wc-outputs/quick3-2_x1.c.out -
echo

echo quick3-2_x3
$WC209_BIN -c quick3.txt quick3.txt quick3.txt | diff -uw ../gnu-wc-outputs/quick3-2_x3.c.out -
echo

echo quick3-2_stdin
cat quick3.txt | $WC209_BIN -c | diff -uw ../gnu-wc-outputs/quick3-2_stdin.c.out -
echo

echo syllabus-2_x1
$WC209_BIN -c syllabus.txt | diff -uw ../gnu-wc-outputs/syllabus-2_x1.c.out -
echo

echo syllabus-2_x3
$WC209_BIN -c syllabus.txt syllabus.txt syllabus.txt | diff -uw ../gnu-wc-outputs/syllabus-2_x3.c.out -
echo

echo syllabus-2_stdin
cat syllabus.txt | $WC209_BIN -c | diff -uw ../gnu-wc-outputs/syllabus-2_stdin.c.out -
echo

echo ulysses-2_x1
$WC209_BIN -c ulysses.txt | diff -uw ../gnu-wc-outputs/ulysses-2_x1.c.out -
echo

echo ulysses-2_x3
$WC209_BIN -c ulysses.txt ulysses.txt ulysses.txt | diff -uw ../gnu-wc-outputs/ulysses-2_x3.c.out -
echo

echo ulysses-2_stdin
cat ulysses.txt | $WC209_BIN -c | diff -uw ../gnu-wc-outputs/ulysses-2_stdin.c.out -
echo

echo manpage-2_x1
$WC209_BIN -c manpage.txt | diff -uw ../gnu-wc-outputs/manpage-2_x1.c.out -
echo

echo manpage-2_x3
$WC209_BIN -c manpage.txt manpage.txt manpage.txt | diff -uw ../gnu-wc-outputs/manpage-2_x3.c.out -
echo

echo manpage-2_stdin
cat manpage.txt | $WC209_BIN -c | diff -uw ../gnu-wc-outputs/manpage-2_stdin.c.out -
echo

echo description-3_x1
$WC209_BIN -l -w description.txt | diff -uw ../gnu-wc-outputs/description-3_x1.l_w.out -
echo

echo description-3_x3
$WC209_BIN -l -w description.txt description.txt description.txt | diff -uw ../gnu-wc-outputs/description-3_x3.l_w.out -
echo

echo description-3_stdin
cat description.txt | $WC209_BIN -l -w | diff -uw ../gnu-wc-outputs/description-3_stdin.l_w.out -
echo

echo quick-3_x1
$WC209_BIN -l -w quick.txt | diff -uw ../gnu-wc-outputs/quick-3_x1.l_w.out -
echo

echo quick-3_x3
$WC209_BIN -l -w quick.txt quick.txt quick.txt | diff -uw ../gnu-wc-outputs/quick-3_x3.l_w.out -
echo

echo quick-3_stdin
cat quick.txt | $WC209_BIN -l -w | diff -uw ../gnu-wc-outputs/quick-3_stdin.l_w.out -
echo

echo quick3-3_x1
$WC209_BIN -l -w quick3.txt | diff -uw ../gnu-wc-outputs/quick3-3_x1.l_w.out -
echo

echo quick3-3_x3
$WC209_BIN -l -w quick3.txt quick3.txt quick3.txt | diff -uw ../gnu-wc-outputs/quick3-3_x3.l_w.out -
echo

echo quick3-3_stdin
cat quick3.txt | $WC209_BIN -l -w | diff -uw ../gnu-wc-outputs/quick3-3_stdin.l_w.out -
echo

echo syllabus-3_x1
$WC209_BIN -l -w syllabus.txt | diff -uw ../gnu-wc-outputs/syllabus-3_x1.l_w.out -
echo

echo syllabus-3_x3
$WC209_BIN -l -w syllabus.txt syllabus.txt syllabus.txt | diff -uw ../gnu-wc-outputs/syllabus-3_x3.l_w.out -
echo

echo syllabus-3_stdin
cat syllabus.txt | $WC209_BIN -l -w | diff -uw ../gnu-wc-outputs/syllabus-3_stdin.l_w.out -
echo

echo ulysses-3_x1
$WC209_BIN -l -w ulysses.txt | diff -uw ../gnu-wc-outputs/ulysses-3_x1.l_w.out -
echo

echo ulysses-3_x3
$WC209_BIN -l -w ulysses.txt ulysses.txt ulysses.txt | diff -uw ../gnu-wc-outputs/ulysses-3_x3.l_w.out -
echo

echo ulysses-3_stdin
cat ulysses.txt | $WC209_BIN -l -w | diff -uw ../gnu-wc-outputs/ulysses-3_stdin.l_w.out -
echo

echo manpage-3_x1
$WC209_BIN -l -w manpage.txt | diff -uw ../gnu-wc-outputs/manpage-3_x1.l_w.out -
echo

echo manpage-3_x3
$WC209_BIN -l -w manpage.txt manpage.txt manpage.txt | diff -uw ../gnu-wc-outputs/manpage-3_x3.l_w.out -
echo

echo manpage-3_stdin
cat manpage.txt | $WC209_BIN -l -w | diff -uw ../gnu-wc-outputs/manpage-3_stdin.l_w.out -
echo

echo description-4_x1
$WC209_BIN -c -w description.txt | diff -uw ../gnu-wc-outputs/description-4_x1.c_w.out -
echo

echo description-4_x3
$WC209_BIN -c -w description.txt description.txt description.txt | diff -uw ../gnu-wc-outputs/description-4_x3.c_w.out -
echo

echo description-4_stdin
cat description.txt | $WC209_BIN -c -w | diff -uw ../gnu-wc-outputs/description-4_stdin.c_w.out -
echo

echo quick-4_x1
$WC209_BIN -c -w quick.txt | diff -uw ../gnu-wc-outputs/quick-4_x1.c_w.out -
echo

echo quick-4_x3
$WC209_BIN -c -w quick.txt quick.txt quick.txt | diff -uw ../gnu-wc-outputs/quick-4_x3.c_w.out -
echo

echo quick-4_stdin
cat quick.txt | $WC209_BIN -c -w | diff -uw ../gnu-wc-outputs/quick-4_stdin.c_w.out -
echo

echo quick3-4_x1
$WC209_BIN -c -w quick3.txt | diff -uw ../gnu-wc-outputs/quick3-4_x1.c_w.out -
echo

echo quick3-4_x3
$WC209_BIN -c -w quick3.txt quick3.txt quick3.txt | diff -uw ../gnu-wc-outputs/quick3-4_x3.c_w.out -
echo

echo quick3-4_stdin
cat quick3.txt | $WC209_BIN -c -w | diff -uw ../gnu-wc-outputs/quick3-4_stdin.c_w.out -
echo

echo syllabus-4_x1
$WC209_BIN -c -w syllabus.txt | diff -uw ../gnu-wc-outputs/syllabus-4_x1.c_w.out -
echo

echo syllabus-4_x3
$WC209_BIN -c -w syllabus.txt syllabus.txt syllabus.txt | diff -uw ../gnu-wc-outputs/syllabus-4_x3.c_w.out -
echo

echo syllabus-4_stdin
cat syllabus.txt | $WC209_BIN -c -w | diff -uw ../gnu-wc-outputs/syllabus-4_stdin.c_w.out -
echo

echo ulysses-4_x1
$WC209_BIN -c -w ulysses.txt | diff -uw ../gnu-wc-outputs/ulysses-4_x1.c_w.out -
echo

echo ulysses-4_x3
$WC209_BIN -c -w ulysses.txt ulysses.txt ulysses.txt | diff -uw ../gnu-wc-outputs/ulysses-4_x3.c_w.out -
echo

echo ulysses-4_stdin
cat ulysses.txt | $WC209_BIN -c -w | diff -uw ../gnu-wc-outputs/ulysses-4_stdin.c_w.out -
echo

echo manpage-4_x1
$WC209_BIN -c -w manpage.txt | diff -uw ../gnu-wc-outputs/manpage-4_x1.c_w.out -
echo

echo manpage-4_x3
$WC209_BIN -c -w manpage.txt manpage.txt manpage.txt | diff -uw ../gnu-wc-outputs/manpage-4_x3.c_w.out -
echo

echo manpage-4_stdin
cat manpage.txt | $WC209_BIN -c -w | diff -uw ../gnu-wc-outputs/manpage-4_stdin.c_w.out -
echo

echo description-5_x1
$WC209_BIN -lwc description.txt | diff -uw ../gnu-wc-outputs/description-5_x1.lwc.out -
echo

echo description-5_x3
$WC209_BIN -lwc description.txt description.txt description.txt | diff -uw ../gnu-wc-outputs/description-5_x3.lwc.out -
echo

echo description-5_stdin
cat description.txt | $WC209_BIN -lwc | diff -uw ../gnu-wc-outputs/description-5_stdin.lwc.out -
echo

echo quick-5_x1
$WC209_BIN -lwc quick.txt | diff -uw ../gnu-wc-outputs/quick-5_x1.lwc.out -
echo

echo quick-5_x3
$WC209_BIN -lwc quick.txt quick.txt quick.txt | diff -uw ../gnu-wc-outputs/quick-5_x3.lwc.out -
echo

echo quick-5_stdin
cat quick.txt | $WC209_BIN -lwc | diff -uw ../gnu-wc-outputs/quick-5_stdin.lwc.out -
echo

echo quick3-5_x1
$WC209_BIN -lwc quick3.txt | diff -uw ../gnu-wc-outputs/quick3-5_x1.lwc.out -
echo

echo quick3-5_x3
$WC209_BIN -lwc quick3.txt quick3.txt quick3.txt | diff -uw ../gnu-wc-outputs/quick3-5_x3.lwc.out -
echo

echo quick3-5_stdin
cat quick3.txt | $WC209_BIN -lwc | diff -uw ../gnu-wc-outputs/quick3-5_stdin.lwc.out -
echo

echo syllabus-5_x1
$WC209_BIN -lwc syllabus.txt | diff -uw ../gnu-wc-outputs/syllabus-5_x1.lwc.out -
echo

echo syllabus-5_x3
$WC209_BIN -lwc syllabus.txt syllabus.txt syllabus.txt | diff -uw ../gnu-wc-outputs/syllabus-5_x3.lwc.out -
echo

echo syllabus-5_stdin
cat syllabus.txt | $WC209_BIN -lwc | diff -uw ../gnu-wc-outputs/syllabus-5_stdin.lwc.out -
echo

echo ulysses-5_x1
$WC209_BIN -lwc ulysses.txt | diff -uw ../gnu-wc-outputs/ulysses-5_x1.lwc.out -
echo

echo ulysses-5_x3
$WC209_BIN -lwc ulysses.txt ulysses.txt ulysses.txt | diff -uw ../gnu-wc-outputs/ulysses-5_x3.lwc.out -
echo

echo ulysses-5_stdin
cat ulysses.txt | $WC209_BIN -lwc | diff -uw ../gnu-wc-outputs/ulysses-5_stdin.lwc.out -
echo

echo manpage-5_x1
$WC209_BIN -lwc manpage.txt | diff -uw ../gnu-wc-outputs/manpage-5_x1.lwc.out -
echo

echo manpage-5_x3
$WC209_BIN -lwc manpage.txt manpage.txt manpage.txt | diff -uw ../gnu-wc-outputs/manpage-5_x3.lwc.out -
echo

echo manpage-5_stdin
cat manpage.txt | $WC209_BIN -lwc | diff -uw ../gnu-wc-outputs/manpage-5_stdin.lwc.out -
echo

echo all-newlines-0_x1
$WC209_BIN -l all-newlines.txt | diff -uw ../gnu-wc-outputs/all-newlines-0_x1.l.out -
echo

echo all-newlines-0_x3
$WC209_BIN -l all-newlines.txt all-newlines.txt all-newlines.txt | diff -uw ../gnu-wc-outputs/all-newlines-0_x3.l.out -
echo

echo all-spaces-0_x1
$WC209_BIN -l all-spaces.txt | diff -uw ../gnu-wc-outputs/all-spaces-0_x1.l.out -
echo

echo all-spaces-0_x3
$WC209_BIN -l all-spaces.txt all-spaces.txt all-spaces.txt | diff -uw ../gnu-wc-outputs/all-spaces-0_x3.l.out -
echo

echo all-whitespace-0_x1
$WC209_BIN -l all-whitespace.txt | diff -uw ../gnu-wc-outputs/all-whitespace-0_x1.l.out -
echo

echo all-whitespace-0_x3
$WC209_BIN -l all-whitespace.txt all-whitespace.txt all-whitespace.txt | diff -uw ../gnu-wc-outputs/all-whitespace-0_x3.l.out -
echo

echo no-whitespace-2-0_x1
$WC209_BIN -l no-whitespace-2.txt | diff -uw ../gnu-wc-outputs/no-whitespace-2-0_x1.l.out -
echo

echo no-whitespace-2-0_x3
$WC209_BIN -l no-whitespace-2.txt no-whitespace-2.txt no-whitespace-2.txt | diff -uw ../gnu-wc-outputs/no-whitespace-2-0_x3.l.out -
echo

echo no-whitespace-0_x1
$WC209_BIN -l no-whitespace.txt | diff -uw ../gnu-wc-outputs/no-whitespace-0_x1.l.out -
echo

echo no-whitespace-0_x3
$WC209_BIN -l no-whitespace.txt no-whitespace.txt no-whitespace.txt | diff -uw ../gnu-wc-outputs/no-whitespace-0_x3.l.out -
echo

echo all-newlines-1_x1
$WC209_BIN -w all-newlines.txt | diff -uw ../gnu-wc-outputs/all-newlines-1_x1.w.out -
echo

echo all-newlines-1_x3
$WC209_BIN -w all-newlines.txt all-newlines.txt all-newlines.txt | diff -uw ../gnu-wc-outputs/all-newlines-1_x3.w.out -
echo

echo all-spaces-1_x1
$WC209_BIN -w all-spaces.txt | diff -uw ../gnu-wc-outputs/all-spaces-1_x1.w.out -
echo

echo all-spaces-1_x3
$WC209_BIN -w all-spaces.txt all-spaces.txt all-spaces.txt | diff -uw ../gnu-wc-outputs/all-spaces-1_x3.w.out -
echo

echo all-whitespace-1_x1
$WC209_BIN -w all-whitespace.txt | diff -uw ../gnu-wc-outputs/all-whitespace-1_x1.w.out -
echo

echo all-whitespace-1_x3
$WC209_BIN -w all-whitespace.txt all-whitespace.txt all-whitespace.txt | diff -uw ../gnu-wc-outputs/all-whitespace-1_x3.w.out -
echo

echo no-whitespace-2-1_x1
$WC209_BIN -w no-whitespace-2.txt | diff -uw ../gnu-wc-outputs/no-whitespace-2-1_x1.w.out -
echo

echo no-whitespace-2-1_x3
$WC209_BIN -w no-whitespace-2.txt no-whitespace-2.txt no-whitespace-2.txt | diff -uw ../gnu-wc-outputs/no-whitespace-2-1_x3.w.out -
echo

echo no-whitespace-1_x1
$WC209_BIN -w no-whitespace.txt | diff -uw ../gnu-wc-outputs/no-whitespace-1_x1.w.out -
echo

echo no-whitespace-1_x3
$WC209_BIN -w no-whitespace.txt no-whitespace.txt no-whitespace.txt | diff -uw ../gnu-wc-outputs/no-whitespace-1_x3.w.out -
echo

echo all-newlines-2_x1
$WC209_BIN -c all-newlines.txt | diff -uw ../gnu-wc-outputs/all-newlines-2_x1.c.out -
echo

echo all-newlines-2_x3
$WC209_BIN -c all-newlines.txt all-newlines.txt all-newlines.txt | diff -uw ../gnu-wc-outputs/all-newlines-2_x3.c.out -
echo

echo all-spaces-2_x1
$WC209_BIN -c all-spaces.txt | diff -uw ../gnu-wc-outputs/all-spaces-2_x1.c.out -
echo

echo all-spaces-2_x3
$WC209_BIN -c all-spaces.txt all-spaces.txt all-spaces.txt | diff -uw ../gnu-wc-outputs/all-spaces-2_x3.c.out -
echo

echo all-whitespace-2_x1
$WC209_BIN -c all-whitespace.txt | diff -uw ../gnu-wc-outputs/all-whitespace-2_x1.c.out -
echo

echo all-whitespace-2_x3
$WC209_BIN -c all-whitespace.txt all-whitespace.txt all-whitespace.txt | diff -uw ../gnu-wc-outputs/all-whitespace-2_x3.c.out -
echo

echo no-whitespace-2-2_x1
$WC209_BIN -c no-whitespace-2.txt | diff -uw ../gnu-wc-outputs/no-whitespace-2-2_x1.c.out -
echo

echo no-whitespace-2-2_x3
$WC209_BIN -c no-whitespace-2.txt no-whitespace-2.txt no-whitespace-2.txt | diff -uw ../gnu-wc-outputs/no-whitespace-2-2_x3.c.out -
echo

echo no-whitespace-2_x1
$WC209_BIN -c no-whitespace.txt | diff -uw ../gnu-wc-outputs/no-whitespace-2_x1.c.out -
echo

echo no-whitespace-2_x3
$WC209_BIN -c no-whitespace.txt no-whitespace.txt no-whitespace.txt | diff -uw ../gnu-wc-outputs/no-whitespace-2_x3.c.out -
echo

echo all-newlines-3_x1
$WC209_BIN -l -w all-newlines.txt | diff -uw ../gnu-wc-outputs/all-newlines-3_x1.l_w.out -
echo

echo all-newlines-3_x3
$WC209_BIN -l -w all-newlines.txt all-newlines.txt all-newlines.txt | diff -uw ../gnu-wc-outputs/all-newlines-3_x3.l_w.out -
echo

echo all-spaces-3_x1
$WC209_BIN -l -w all-spaces.txt | diff -uw ../gnu-wc-outputs/all-spaces-3_x1.l_w.out -
echo

echo all-spaces-3_x3
$WC209_BIN -l -w all-spaces.txt all-spaces.txt all-spaces.txt | diff -uw ../gnu-wc-outputs/all-spaces-3_x3.l_w.out -
echo

echo all-whitespace-3_x1
$WC209_BIN -l -w all-whitespace.txt | diff -uw ../gnu-wc-outputs/all-whitespace-3_x1.l_w.out -
echo

echo all-whitespace-3_x3
$WC209_BIN -l -w all-whitespace.txt all-whitespace.txt all-whitespace.txt | diff -uw ../gnu-wc-outputs/all-whitespace-3_x3.l_w.out -
echo

echo no-whitespace-2-3_x1
$WC209_BIN -l -w no-whitespace-2.txt | diff -uw ../gnu-wc-outputs/no-whitespace-2-3_x1.l_w.out -
echo

echo no-whitespace-2-3_x3
$WC209_BIN -l -w no-whitespace-2.txt no-whitespace-2.txt no-whitespace-2.txt | diff -uw ../gnu-wc-outputs/no-whitespace-2-3_x3.l_w.out -
echo

echo no-whitespace-3_x1
$WC209_BIN -l -w no-whitespace.txt | diff -uw ../gnu-wc-outputs/no-whitespace-3_x1.l_w.out -
echo

echo no-whitespace-3_x3
$WC209_BIN -l -w no-whitespace.txt no-whitespace.txt no-whitespace.txt | diff -uw ../gnu-wc-outputs/no-whitespace-3_x3.l_w.out -
echo

echo all-newlines-4_x1
$WC209_BIN -c -w all-newlines.txt | diff -uw ../gnu-wc-outputs/all-newlines-4_x1.c_w.out -
echo

echo all-newlines-4_x3
$WC209_BIN -c -w all-newlines.txt all-newlines.txt all-newlines.txt | diff -uw ../gnu-wc-outputs/all-newlines-4_x3.c_w.out -
echo

echo all-spaces-4_x1
$WC209_BIN -c -w all-spaces.txt | diff -uw ../gnu-wc-outputs/all-spaces-4_x1.c_w.out -
echo

echo all-spaces-4_x3
$WC209_BIN -c -w all-spaces.txt all-spaces.txt all-spaces.txt | diff -uw ../gnu-wc-outputs/all-spaces-4_x3.c_w.out -
echo

echo all-whitespace-4_x1
$WC209_BIN -c -w all-whitespace.txt | diff -uw ../gnu-wc-outputs/all-whitespace-4_x1.c_w.out -
echo

echo all-whitespace-4_x3
$WC209_BIN -c -w all-whitespace.txt all-whitespace.txt all-whitespace.txt | diff -uw ../gnu-wc-outputs/all-whitespace-4_x3.c_w.out -
echo

echo no-whitespace-2-4_x1
$WC209_BIN -c -w no-whitespace-2.txt | diff -uw ../gnu-wc-outputs/no-whitespace-2-4_x1.c_w.out -
echo

echo no-whitespace-2-4_x3
$WC209_BIN -c -w no-whitespace-2.txt no-whitespace-2.txt no-whitespace-2.txt | diff -uw ../gnu-wc-outputs/no-whitespace-2-4_x3.c_w.out -
echo

echo no-whitespace-4_x1
$WC209_BIN -c -w no-whitespace.txt | diff -uw ../gnu-wc-outputs/no-whitespace-4_x1.c_w.out -
echo

echo no-whitespace-4_x3
$WC209_BIN -c -w no-whitespace.txt no-whitespace.txt no-whitespace.txt | diff -uw ../gnu-wc-outputs/no-whitespace-4_x3.c_w.out -
echo

echo all-newlines-5_x1
$WC209_BIN -lwc all-newlines.txt | diff -uw ../gnu-wc-outputs/all-newlines-5_x1.lwc.out -
echo

echo all-newlines-5_x3
$WC209_BIN -lwc all-newlines.txt all-newlines.txt all-newlines.txt | diff -uw ../gnu-wc-outputs/all-newlines-5_x3.lwc.out -
echo

echo all-spaces-5_x1
$WC209_BIN -lwc all-spaces.txt | diff -uw ../gnu-wc-outputs/all-spaces-5_x1.lwc.out -
echo

echo all-spaces-5_x3
$WC209_BIN -lwc all-spaces.txt all-spaces.txt all-spaces.txt | diff -uw ../gnu-wc-outputs/all-spaces-5_x3.lwc.out -
echo

echo all-whitespace-5_x1
$WC209_BIN -lwc all-whitespace.txt | diff -uw ../gnu-wc-outputs/all-whitespace-5_x1.lwc.out -
echo

echo all-whitespace-5_x3
$WC209_BIN -lwc all-whitespace.txt all-whitespace.txt all-whitespace.txt | diff -uw ../gnu-wc-outputs/all-whitespace-5_x3.lwc.out -
echo

echo no-whitespace-2-5_x1
$WC209_BIN -lwc no-whitespace-2.txt | diff -uw ../gnu-wc-outputs/no-whitespace-2-5_x1.lwc.out -
echo

echo no-whitespace-2-5_x3
$WC209_BIN -lwc no-whitespace-2.txt no-whitespace-2.txt no-whitespace-2.txt | diff -uw ../gnu-wc-outputs/no-whitespace-2-5_x3.lwc.out -
echo

echo no-whitespace-5_x1
$WC209_BIN -lwc no-whitespace.txt | diff -uw ../gnu-wc-outputs/no-whitespace-5_x1.lwc.out -
echo

echo no-whitespace-5_x3
$WC209_BIN -lwc no-whitespace.txt no-whitespace.txt no-whitespace.txt | diff -uw ../gnu-wc-outputs/no-whitespace-5_x3.lwc.out -
echo

echo "Self test completed."
