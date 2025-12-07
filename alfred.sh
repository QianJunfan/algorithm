gcc -D_GNU_SOURCE alfred.c -o alfred 
./alfred 
cat log > README
rm -f log alfred
cat README
