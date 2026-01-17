#!/bin/bash

read -p "Enter Problem ID: " pid
pid_lower=$(echo "$pid" | tr '[:upper:]' '[:lower:]')

read -p "Enter Problem Name: " pname

read -p "Include IO optimization? (y/n): " io_opt

curr_date=$(date +"%b %d, %Y")

cat <<EOF >"${pid_lower}.cpp"
/* codeforces ${pid_lower} - ${pname}
 * ${curr_date}
 */
#include <bits/stdc++.h>

using namespace std;

int main(void)
{
EOF

if [[ "$io_opt" =~ ^[Yy]$ ]]; then
  cat <<EOF >>"${pid_lower}.cpp"
    ios::sync_with_stdio(false);
    cin.tie(NULL);

EOF
fi

cat <<EOF >>"${pid_lower}.cpp"
    return 0;
}
EOF

echo "File ${pid_lower}.cpp created successfully!"

read -p "Open with which editor? (vim/nvim/code/nano/none): " editor

case $editor in
vim) vim "${pid_lower}.cpp" ;;
code) code "${pid_lower}.cpp" ;;
nano) nano "${pid_lower}.cpp" ;;
nvim) nvim "${pid_lower}.cpp" ;;
*) echo "Done." ;;
esac
