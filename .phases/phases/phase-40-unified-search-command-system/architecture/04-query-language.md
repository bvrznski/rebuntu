# Unified Query Language

The language should support operator-friendly free text plus structured selectors without becoming a shell.

Examples are conceptual:
`service:sshd state:failed`
`gpu pci:44:00.0`
`events boot:current severity>=warning`
`package:nvidia* installed:true`
`project:Gordon runtime:python`

The parser must retain source spans and diagnostics. Unsupported fields/scopes are explicit errors or UNKNOWN-capability states, never silently ignored.
