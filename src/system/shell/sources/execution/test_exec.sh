# execution/ test suite
source "$(dirname "${BASH_SOURCE[0]}")/_init.sh"

echo "Running execution tests..."
rebuntu_exec_with_timeout 5 'true' > /dev/null && echo "PASS: rebuntu_exec_with_timeout"
rebuntu_exec_validate 'true' 'echo ok' > /dev/null && echo "PASS: rebuntu_exec_validate"
rebuntu_exec_verify 'true' > /dev/null && echo "PASS: rebuntu_exec_verify"
