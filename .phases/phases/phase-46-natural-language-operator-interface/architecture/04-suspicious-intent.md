# Suspicious Intent and Effect Analysis

Detect suspicious requests by intended effects and capability combinations, not by blacklisting strings.

Examples of high-risk effects include unbounded process creation, destructive storage mutation, disabling safeguards, persistence creation, privilege escalation, exposing services, new external destinations, bulk/sensitive data export, credential access, secret material movement, monitoring/surveillance changes and combinations that create exfiltration or loss-of-control paths.

Benign legitimate administration remains possible through explicit context, policy and authorization; anomaly detection must not become a simplistic command blacklist.
