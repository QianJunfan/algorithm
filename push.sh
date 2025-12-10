gcc -D_GNU_SOURCE alfred.c -o alfred 
./alfred 
cat log > README
rm -f log alfred a.out
cat README
git add .
git commit -m "new"
git push
