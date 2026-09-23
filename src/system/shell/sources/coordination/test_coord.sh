# coordination/ test suite
source "$(dirname "${BASH_SOURCE[0]}")/_init.sh"

echo "Running coordination tests..."
test_count=0; pass_count=0

check_test() {
    "$@" > /dev/null 2>&1 && { echo "PASS: $*"; pass_count=$((pass_count + 1)); }
    test_count=$((test_count + 1))
}

rebuntu_coord_atomic_group 'true' > /dev/null 2>&1 && check_test rebuntu_coord_atomic_group
echo "$pass_count/$test_count tests passed"
