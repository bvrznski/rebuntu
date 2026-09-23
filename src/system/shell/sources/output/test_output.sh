# output/ test suite
source "$(dirname "${BASH_SOURCE[0]}")/_init.sh"
echo "Running output tests..."
rebuntu_output_format 'table' 'a b c' | grep -q '|' && echo "PASS: rebuntu_output_format"
rebuntu_output_error 'test' 2>&1 | grep -q 'ERROR' && echo "PASS: rebuntu_output_error"
