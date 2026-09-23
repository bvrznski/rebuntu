# text/ — Text transformation utilities
#
# Shell-native text transformations that work line-by-line or character-by-character,
# respecting Unix composition and pipeline semantics.

# Trim leading and trailing whitespace
# INPUT:  String to trim
# OUTPUT: Trimmed string to stdout
rebuntu_text_trim() {
    local input="$1"
    
    # Remove leading whitespace
    input="${input#"${input%%[![:space:]]*}"}"
    
    # Remove trailing whitespace
    input="${input%"${input##*[![:space:]]}"}"
    
    echo "$input"
}

# Convert string to uppercase
# INPUT:  String to convert
# OUTPUT: Uppercase string to stdout
rebuntu_text_uppercase() {
    local input="$1"
    # Use tr for portability
    echo "$input" | tr '[:lower:]' '[:upper:]'
}

# Convert string to lowercase
# INPUT:  String to convert
# OUTPUT: Lowercase string to stdout
rebuntu_text_lowercase() {
    local input="$1"
    # Use tr for portability
    echo "$input" | tr '[:upper:]' '[:lower:]'
}

# Join array elements with a delimiter
# INPUT:  Delimiter, then array elements
# OUTPUT: Joined string to stdout
# EXAMPLE: rebuntu_text_join "," a b c => "a,b,c"
rebuntu_text_join() {
    local delimiter="$1"
    shift
    
    local result=""
    local first=1
    
    for element in "$@"; do
        if [[ $first -eq 1 ]]; then
            result="$element"
            first=0
        else
            result="$result$delimiter$element"
        fi
    done
    
    echo "$result"
}

# Split string by delimiter into array (outputs each element on a new line)
# INPUT:  Delimiter, then string to split
# OUTPUT: Elements one per line to stdout
rebuntu_text_split() {
    local delimiter="$1"
    local input="$2"
    
    # Use tr to replace delimiter with newline
    echo "$input" | tr "$delimiter" '\n'
}

# Get string length
# INPUT:  String
# OUTPUT: Character count to stdout
rebuntu_text_length() {
    local input="$1"
    echo "${#input}"
}

# Check if string starts with prefix
# INPUT:  String, prefix
# OUTPUT: 0 if starts with, non-zero otherwise
rebuntu_text_starts_with() {
    local string="$1"
    local prefix="$2"
    
    [[ "$string" == "$prefix"* ]]
}

# Check if string ends with suffix
# INPUT:  String, suffix
# OUTPUT: 0 if ends with, non-zero otherwise
rebuntu_text_ends_with() {
    local string="$1"
    local suffix="$2"
    
    [[ "$string" == *"$suffix" ]]
}