# flow/ test suite
source "$(dirname "${BASH_SOURCE[0]}")/_init.sh"
echo "Running flow tests..."
rebuntu_clip < /dev/null && echo "PASS: rebuntu_clip" || true
rebuntu_pipe_to 'cat' 'true' > /dev/null 2>&1 && echo "PASS: rebuntu_pipe_to"
