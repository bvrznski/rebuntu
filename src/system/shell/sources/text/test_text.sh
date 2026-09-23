# text/ test suite
source "$(dirname "${BASH_SOURCE[0]}")/_init.sh"
echo "Running text tests..."
rebuntu_text_trim '  hello world  ' | grep -qE '^hello world$' && echo "PASS: rebuntu_text_trim"
rebuntu_text_upper 'hello' | grep -qE '^HELLO$' && echo "PASS: rebuntu_text_upper"
