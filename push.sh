#!/bin/bash
git add .
current_date=$(date +"%b %d, %Y")

file_list=$(git status --porcelain | grep '^[AMDR]' | awk '{
    status = substr($1,1,1);
    if (status == "A") s = "add";
    else if (status == "M") s = "mod";
    else if (status == "D") s = "del";
    else if (status == "R") s = "ren";
    else s = "upd";
    print s " " $2;
}')

if [ -z "$file_list" ]; then
  echo "Error: No files staged."
  exit 1
fi

commit_message="$current_date

$file_list"
rm -f README
cat HEAD >>README
python sc.py >>README
git commit -m "$commit_message"
current_branch=$(git rev-parse --abbrev-ref HEAD)
git push origin "$current_branch"

cat README
rm -f a.out
