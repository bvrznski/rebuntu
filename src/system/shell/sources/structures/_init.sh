# structures/ — Data structure helpers
rebuntu_array_push() { local n="$1" v="$2"; declare -n arr_ref="$n"; arr_ref+=("$v"); }
rebuntu_array_pop() { local n="$1"; declare -n arr_ref="$n"; local len=${#arr_ref[@]}; if [[ $len -gt 0 ]]; then echo "${arr_ref[$((len-1))]}"; unset 'arr_ref[$((len-1))]'; fi; }
rebuntu_map_set() { local n="$1" k="$2"; shift 2; declare -n map_ref="$n"; map_ref["$k"]="$*"; }
rebuntu_map_get() { local n="$1" k="$2"; declare -n map_ref="$n"; echo "${map_ref[$k]:-}"; }
