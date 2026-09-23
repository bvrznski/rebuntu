# parsing/ — Parsing utilities
rebuntu_parse_keyvalue() { local i="${1:-}"; [[ -n "$i" && -f "$i" ]] && cat "$i" || cat; }
rebuntu_parse_get_value() { local key="$1"; while IFS='=' read -r k v; do [[ "$k" == "$key" ]] && { echo "$v"; return 0; }; done; return 1; }
rebuntu_csv_to_array() { local csv="$1"; echo "$csv" | tr ',' '\n' | while read -r item; do echo "${item#"${item%%[![:space:]]*}"}"; done
