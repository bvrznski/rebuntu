# input/ test suite
source "$(dirname "${BASH_SOURCE[0]}")/_init.sh"
echo "Running input tests..."
rebuntu_input_is_terminal && echo "PASS: rebuntu_input_is_terminal"
