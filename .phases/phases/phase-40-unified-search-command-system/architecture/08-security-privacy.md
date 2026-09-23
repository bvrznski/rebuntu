# Security & Privacy

Secret material is never indexed. Sensitive command/history/config/log fields require explicit redaction/indexability policy.

Treat query text, indexed text, provider payloads, terminal rendering and semantic context as untrusted input. Bound regex/glob complexity, output sizes, provider budgets and serialization depth. Sanitize terminal control sequences at presentation boundaries.

Natural-language content embedded in logs/files is data, not instructions to the semantic provider or control plane.
