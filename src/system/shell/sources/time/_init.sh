# time/ — Time and duration helpers
rebuntu_time_now() { if [[ -f /proc/uptime ]]; then awk '{print $1 * 1000000000}' /proc/uptime; else date +%s%3N 2>/dev/null || date +%s000; fi; }
rebuntu_time_elapsed() { local s="$1" n=$(rebuntu_time_now); echo $(( (n - s) / 1000000 )); }
rebuntu_time_format() { local ms="$1"; if [[ $ms -lt 1000 ]]; then echo "${ms}ms"; elif [[ $ms -lt 60000 ]]; then echo "$((ms/1000)).$(( (ms%1000)/100 ))s"; else local mins=$((ms/60000)) secs=$(( (ms%60000)/1000 )); echo "${mins}m${secs}s"; fi; }
rebuntu_time_deadline_passed() { local d="$1" n=$(rebuntu_time_now); [[ $n -gt $d ]]; }
