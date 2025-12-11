#!/bin/bash

gcc -D_GNU_SOURCE alfred.c -o alfred
./alfred

cat log > README
cat README
rm -f log alfred a.out

COMMIT_MESSAGE=$(date +"%b %d, %Y")

git add .
git commit -m "$COMMIT_MESSAGE"

git push
