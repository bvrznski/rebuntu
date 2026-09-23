# filesystem/ test suite
source "$(dirname "${BASH_SOURCE[0]}")/_init.sh"
echo "Running filesystem tests..."
rebuntu_fs_exists_type '.' 'd' && echo "PASS: rebuntu_fs_exists_type"
tmpfile=$(mktemp); echo "test" > "$tmpfile"; rebuntu_fs_read "$tmpfile" | grep -q test && echo "PASS: rebuntu_fs_read"; rm -f "$tmpfile"
