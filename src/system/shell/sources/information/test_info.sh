# information/ test suite
source "$(dirname "${BASH_SOURCE[0]}")/_init.sh"
echo "Running information tests..."
rebuntu_info_available_tools 'true' | grep -q true && echo "PASS: rebuntu_info_available_tools"
rebuntu_info_current_state 'hostname' > /dev/null && echo "PASS: rebuntu_info_current_state"
