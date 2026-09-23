# paths/ test suite
source "$(dirname "${BASH_SOURCE[0]}")/_init.sh"
echo "Running paths tests..."
rebuntu_path_normalize '/foo/../bar' | grep -qE '^/bar$' && echo "PASS: rebuntu_path_normalize"
rebuntu_path_canonicalize '.' | grep -qE "^${PWD}$" && echo "PASS: rebuntu_path_canonicalize"
