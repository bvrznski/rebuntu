# administration/ — System administration helpers
#
# System administration operations that need shell-native execution.

# Query service status using systemd
rebuntu_admin_service_status() {
    local service="$1"
    
    if command -v systemctl &>/dev/null; then
        systemctl is-active "$service" 2>/dev/null || echo "unknown"
    else
        # Fallback: check if process exists
        if pgrep -x "$service" >/dev/null 2>&1; then
            echo "active"
        else
            echo "inactive"
        fi
    fi
}

# Check if user exists
rebuntu_admin_user_exists() {
    local username="$1"
    
    id "$username" >/dev/null 2>&1
}

# Get group members
rebuntu_admin_group_members() {
    local groupname="$1"
    
    getent group "$groupname" | cut -d: -f4 | tr ',' ' '
}