# REBUNTU WIKI — REPEATABLE KNOWLEDGE COMPILATION PASS

Repository:

```
/home/bvrznski/rebuntu
```

Canonical wiki root:

```
/home/bvrznski/rebuntu/wiki
```

This is a REPEATABLE task.

It may be executed after implementation passes, architectural changes, refactors,
new phases, incident investigations, documentation changes, or simply as a
periodic knowledge-maintenance pass.

Its purpose is to build and continuously maintain an encyclopedic,
interconnected knowledge base describing Rebuntu.

The wiki should gradually become the best human-readable map of the project.

It is inspired by the persistent LLM-maintained wiki model:

```
raw sources
    ↓
extraction
    ↓
synthesis
    ↓
persistent interlinked wiki
    ↓
future ingestion updates the existing knowledge
```

Do NOT recreate knowledge from scratch on every execution.

Knowledge must ACCUMULATE.

The wiki is a maintained project artifact.

======================================================================

1. FUNDAMENTAL AUTHORITY RULE
   ======================================================================

THE WIKI IS NOT THE SOURCE OF TRUTH FOR IMPLEMENTATION STATE.

For implementation facts, authority remains with the relevant primary source:

```
source code
tests
build configuration
native Linux behavior
configuration
schemas/contracts
repository architecture
applicable AGENTS.md
phase requirements
verified runtime evidence
```

The wiki is a DERIVED KNOWLEDGE LAYER.

Conceptually:

```
authoritative repository evidence
            ↓
    Rebuntu Wiki compiler
            ↓
  structured knowledge graph
            ↓
    Markdown encyclopedia
            ↓
     generated HTML site
```

Never modify implementation merely to make it agree with the wiki.

If:

```
CODE != WIKI
```

investigate which source is authoritative for the disputed statement.

If the implementation changed:

```
UPDATE THE WIKI.
```

Never silently change code to restore an obsolete wiki description.

======================================================================
2. CORE PRINCIPLE
=================

The wiki is not merely a collection of generated summaries.

It is a persistent, cumulative synthesis of Rebuntu knowledge.

A new source should not normally produce only:

```
one new summary file.
```

Instead it may require:

```
creating one article
updating several existing articles
adding cross-links
updating architecture descriptions
recording a contradiction
updating terminology
updating an index
adding provenance
recording the maintenance operation
```

Knowledge should be integrated into the existing encyclopedia.

======================================================================
3. DIRECTORY STRUCTURE
======================

Create and maintain:

```
wiki/
├── AGENTS.md
├── README.md
├── index.md
├── log.md
│
├── overview/
├── architecture/
├── concepts/
├── components/
├── runtime/
├── semantics/
├── observation/
├── knowledge/
├── planning/
├── control/
├── providers/
├── integration/
├── automation/
├── operator/
│
├── linux/
├── hardware/
├── protocols/
├── security/
├── persistence/
├── recovery/
├── testing/
│
├── decisions/
├── incidents/
├── glossary/
├── guides/
├── development/
│
├── sources/
├── generated/
│   └── html/
│
└── tools/
```

This is an initial taxonomy, not an immutable ontology.

Before creating a category, inspect the existing wiki.

Prefer extending an existing coherent taxonomy over endlessly creating new
directories.

The wiki taxonomy should follow Rebuntu's actual architecture where useful,
but it MUST NOT simply mirror src/ one directory per page.

The wiki is CONCEPT-ORIENTED, not merely FILE-ORIENTED.

======================================================================
4. WIKI AGENTS.md — SCHEMA
==========================

Create:

```
wiki/AGENTS.md
```

This is the canonical schema/instruction document for maintaining the wiki.

It must define:

* article format;
* naming;
* linking;
* provenance;
* source hierarchy;
* update rules;
* contradiction handling;
* stale-information handling;
* index maintenance;
* log maintenance;
* HTML generation;
* linting;
* query workflow;
* synchronization workflow.

Future agents MUST read:

```
/home/bvrznski/rebuntu/AGENTS.md
```

and:

```
/home/bvrznski/rebuntu/wiki/AGENTS.md
```

before modifying the wiki.

======================================================================
5. INITIAL REPOSITORY ARCHAEOLOGY
=================================

Before creating or updating articles, inspect the repository.

Read applicable:

```
AGENTS.md
TASK.md
README*
STRUCTURE*
__tree__
__base__
__meta__
__load__
architecture documents
phase specifications
tests
CMake/build files
configuration
important implementation
```

Search by concepts and behavior, not merely filenames.

Do not assume directory names fully describe architectural responsibility.

======================================================================
6. SOURCE CLASSES
=================

The wiki may compile knowledge from:

A. PRIMARY IMPLEMENTATION SOURCES

```
C++ source
headers
tests
CMake
schemas
service definitions
configuration
scripts that remain authoritative
native integration
```

B. ARCHITECTURAL SOURCES

```
AGENTS.md
architecture specifications
structural metadata
design documents
accepted decisions
```

C. REQUIREMENT SOURCES

```
.phases/
TASK.md
project specifications
```

D. EMPIRICAL SOURCES

```
incident reports
diagnostic logs
verified runtime observations
benchmarks
hardware investigations
```

E. HISTORICAL SOURCES

```
obsolete implementation
previous designs
migrations
deprecated mechanisms
```

Historical information must be clearly identified as historical.

Do not describe historical architecture as current architecture.

======================================================================
7. SOURCE PROVENANCE
====================

Important factual statements should be recoverable to repository evidence.

Each article should contain a Sources / Evidence section where appropriate.

Prefer repository-relative references such as:

```
src/runtime/...
src/observation/...
tests/...
.phases/phases/...
AGENTS.md
```

For important implementation claims, include relevant symbols where useful.

Example:

```
Source:
  - src/runtime/service_registry.hpp — ServiceRegistry
  - src/runtime/service_registry.cpp — ServiceRegistry::register_service()
  - tests/runtime/service_registry_test.cpp
```

Do not manufacture provenance.

======================================================================
8. ARTICLE FORMAT
=================

Use a consistent article structure where appropriate.

Suggested template:

```
---
title: Desired State
category: concept
status: current
updated: YYYY-MM-DD
---

# Desired State

## Summary

Concise explanation.

## Role in Rebuntu

Why this concept exists.

## Semantics

Precise meaning.

## Architecture

Where it participates.

## Relationships

Links to related concepts/components.

## Invariants

Important rules that must remain true.

## Authority boundaries

What is authoritative and what is merely derived.

## Lifecycle / data flow

Where applicable.

## Failure semantics

Where applicable.

## Implementation

Important implementation locations and symbols.

## Examples

Where useful.

## Historical notes

Only where supported.

## Open questions / limitations

Where appropriate.

## Sources

Repository evidence.
```

Do NOT mechanically create empty sections.

Use only sections that add value.

======================================================================
9. WIKIPEDIA-LIKE WRITING STYLE
===============================

Articles should resemble a high-quality technical encyclopedia.

Prefer:

```
definition
context
relationships
architecture
behavior
constraints
implementation references
```

over:

```
task-oriented prose
changelog prose
marketing prose
conversation-style prose.
```

Avoid:

```
"We implemented..."
"You should..."
"This amazing system..."
```

Prefer:

```
"The reconciliation subsystem compares observed state with desired state..."
```

Articles describe Rebuntu.

Guides may use instructional prose when appropriate.

======================================================================
10. CROSS-LINKING
=================

Cross-link aggressively but meaningfully.

Use relative Markdown links.

Example:

```
[Desired State](../concepts/desired-state.md)
```

A concept should link to related:

```
components
concepts
native mechanisms
providers
decisions
incidents
tests
architecture pages
```

Do not create links merely to maximize graph density.

Links should represent useful semantic relationships.

======================================================================
11. KNOWLEDGE GRAPH MENTAL MODEL
================================

Treat the wiki as a graph:

```
article = knowledge node
hyperlink = semantic edge
```

Useful edges include:

```
implements
depends on
observes
controls
verifies
provides
consumes
supersedes
constrains
authorizes
persists
derives from
recovers
integrates with
related to
```

Markdown remains canonical.

No graph database is required initially.

======================================================================
12. INDEX
=========

Maintain:

```
wiki/index.md
```

The index is CONTENT-ORIENTED.

It should provide:

* major categories;
* article links;
* concise descriptions;
* important hub pages;
* useful navigation paths.

Do not make it merely an alphabetical filename dump.

An engineer unfamiliar with Rebuntu should be able to begin at index.md and
progressively discover the system.

======================================================================
13. LOG
=======

Maintain:

```
wiki/log.md
```

The log is chronological and APPEND-ONLY except for correcting malformed entries.

Use machine-searchable headings:

```
## [YYYY-MM-DD HH:MM] ingest | ...
## [YYYY-MM-DD HH:MM] sync | ...
## [YYYY-MM-DD HH:MM] lint | ...
## [YYYY-MM-DD HH:MM] query | ...
## [YYYY-MM-DD HH:MM] rebuild | ...
```

Record:

* operation;
* scope;
* major articles created;
* major articles changed;
* contradictions found;
* stale information corrected;
* important unresolved questions.

Do not turn log.md into another encyclopedia.

======================================================================
14. CORE OPERATIONS
===================

The wiki supports five primary operations:

```
INGEST
SYNCHRONIZE
QUERY
LINT
BUILD
```

Every invocation of this reusable task should determine which operations are
appropriate.

======================================================================
15. INGEST
==========

INGEST incorporates new knowledge sources.

For each new source:

```
inspect source
    ↓
extract factual/architectural knowledge
    ↓
identify affected existing wiki concepts
    ↓
update existing articles
    ↓
create missing articles
    ↓
add cross-links
    ↓
update index
    ↓
append log entry
```

Do not automatically create:

```
sources/foo-summary.md
```

and stop there.

The goal is INTEGRATION, not accumulation of disconnected summaries.

A single source may update many articles.

======================================================================
16. SYNCHRONIZE
===============

SYNCHRONIZE is especially important for Rebuntu.

Compare wiki knowledge against current repository state.

Detect:

```
changed implementation
renamed concepts
moved components
removed components
new components
changed contracts
changed state machines
changed authority boundaries
changed tests
changed configuration
changed native integration
```

Update affected wiki articles.

Never assume a previously generated page remains correct.

The repository evolves.

The wiki must follow it.

======================================================================
17. INCREMENTAL SYNCHRONIZATION
===============================

Use Git to avoid rescanning everything unnecessarily.

Inspect where useful:

```
git status
git diff
git log
git diff <previous-wiki-sync>..HEAD
```

Maintain enough metadata to identify the repository revision used during the
last successful synchronization.

However:

```
Git commit ID is synchronization metadata,
NOT proof that individual claims remain correct.
```

When necessary inspect implementation directly.

======================================================================
18. QUERY
=========

When asked a substantial question about Rebuntu:

1. read wiki/index.md;
2. locate relevant articles;
3. inspect them;
4. inspect primary repository sources when freshness or precision requires it;
5. answer the question;
6. determine whether the answer contains durable knowledge not yet represented
   in the wiki.

If yes:

```
integrate that knowledge into the wiki.
```

Thus useful investigation compounds over time instead of disappearing into chat
history.

Do NOT automatically persist speculation.

======================================================================
19. LINT
========

Periodically perform a WIKI LINT PASS.

Detect:

```
broken links
orphan pages
duplicate concepts
near-duplicate pages
stale implementation references
missing source references
contradictory claims
historical claims presented as current
pages without useful inbound links
concepts heavily referenced but lacking an article
dead categories
missing index entries
stale index descriptions
malformed frontmatter
invalid HTML generation
missing backlinks where useful
terminology drift
```

Also detect architectural contradictions.

Example:

```
article A:
    component X owns Y

article B:
    component Z owns Y
```

Do not arbitrarily choose one.

Inspect authoritative repository evidence and reconcile.

If authority cannot be established:

```
mark the uncertainty explicitly.
```

======================================================================
20. CONTRADICTION HANDLING
==========================

Never silently blend incompatible claims.

When sources disagree:

1. identify source class;
2. determine freshness;
3. determine authority;
4. inspect implementation/tests;
5. determine whether one source superseded another.

Possible outcomes:

```
CURRENT
HISTORICAL
SUPERSEDED
PROPOSED
CONTRADICTED
UNRESOLVED
```

Represent uncertainty explicitly.

Do not manufacture consensus.

======================================================================
21. CURRENT VS PROPOSED ARCHITECTURE
====================================

This distinction is mandatory.

Rebuntu contains:

```
implemented architecture
partially implemented architecture
planned architecture
phase requirements
historical architecture
```

Never collapse these into one description.

Articles must make clear whether something is:

```
implemented
partial
planned
experimental
deprecated
historical
```

A phase specification does NOT prove implementation.

A header declaration does NOT prove working behavior.

A TODO does NOT prove capability.

======================================================================
22. IMPLEMENTATION DEPTH
========================

Where useful, articles may explicitly distinguish:

```
specification exists
interface exists
skeleton exists
partial implementation exists
operational implementation exists
tests exist
integration verified
```

Do not turn the wiki into a progress dashboard.

Use this distinction only when necessary to prevent misleading descriptions.

======================================================================
23. NATIVE LINUX RELATIONSHIP
=============================

The wiki must preserve Rebuntu's architectural rule:

Rebuntu is not a Linux reimplementation, simulation, shadow OS, or replica.

Native Linux mechanisms remain authoritative.

Articles should explain how Rebuntu composes semantics ABOVE/ACROSS:

```
kernel
systemd
cgroups
namespaces
procfs/sysfs
udev
D-Bus
Netlink
NetworkManager
nftables
PAM/NSS
polkit/sudo
package managers
filesystems/mounts
process/service management
scheduling
hardware/driver interfaces
```

Do not describe Rebuntu abstractions as replacing native mechanisms unless the
implementation genuinely does so.

======================================================================
24. ARCHITECTURE HUB PAGES
==========================

Create high-value hub articles such as appropriate:

```
Rebuntu
Architecture
Runtime
Semantic Model
Observation
Desired State
Evidence
Identity
Providers
Planning
Control
Operations
Reconciliation
Automation
Security Model
Persistence
Recovery
Native Linux Integration
Testing Architecture
```

Exact pages should emerge from repository evidence.

Do not create fictional subsystems merely to fill this list.

======================================================================
25. COMPONENT ARTICLES
======================

Important components should receive their own pages when enough knowledge exists.

A component article should answer:

```
What is it?
Why does it exist?
Where is it?
What owns it?
What does it consume?
What does it produce?
What native authority does it depend on?
What invariants does it maintain?
What can fail?
What depends on it?
Where is it tested?
```

Avoid creating one wiki page for every C++ class.

Articles should correspond to meaningful engineering concepts.

======================================================================
26. DECISION ARTICLES
=====================

Maintain important architectural decisions under:

```
wiki/decisions/
```

These are not necessarily formal ADRs, though existing ADRs should be reused if
present.

Record decisions such as:

```
why durable identity is separate from runtime handles;
why native Linux remains authoritative;
why observation is separate from authorization;
why execution requires verification;
why certain recovery behavior is deliberately bounded.
```

Only record decisions supported by repository/task/history evidence.

Do not invent rationale.

======================================================================
27. INCIDENT ARTICLES
=====================

Important real-world failures may receive articles under:

```
wiki/incidents/
```

An incident article may document:

```
symptoms
evidence
affected subsystem
investigation
established findings
unresolved hypotheses
architectural implications
resulting implementation changes
```

Keep:

```
observation
inference
hypothesis
conclusion
```

explicitly separated.

Incidents can become valuable engineering knowledge.

======================================================================
28. GLOSSARY
============

Maintain a canonical Rebuntu glossary.

Important terms should have ONE canonical definition.

Examples may include:

```
observation
evidence
assertion
desired state
operation
capability
permission
provider
identity
runtime instance
verification
reconciliation
```

Cross-link glossary terms to full articles.

Detect terminology drift during lint passes.

======================================================================
29. GUIDES
==========

The encyclopedia may include practical guides:

```
building Rebuntu
running tests
adding a provider
adding an operation
debugging a service
inspecting runtime state
tracing evidence
understanding repository structure
```

Guides should link back to conceptual articles.

Do not duplicate architecture explanations wholesale.

======================================================================
30. HTML VERSION
================

Generate a browsable HTML projection of the wiki.

Canonical content remains:

```
wiki/**/*.md
```

Generated HTML goes to:

```
wiki/generated/html/
```

HTML MUST NOT become a second independently maintained documentation tree.

Pipeline:

```
Markdown wiki
    ↓
deterministic builder
    ↓
static HTML
    ↓
local browser
```

Provide a build command/tool under:

```
wiki/tools/
```

or the repository's existing tooling location if architecture requires it.

Prefer a static site requiring no server-side database.

======================================================================
31. HTML NAVIGATION
===================

The generated site should provide:

```
clickable hyperlinks
category navigation
article navigation
index/home page
breadcrumbs where useful
source links
backlinks
table of contents
search
```

The site should remain usable from localhost.

Where practical also make relative-link output usable directly from disk.

======================================================================
32. HTML VISUAL STYLE
=====================

Use a restrained technical encyclopedia aesthetic.

Priorities:

```
readability
information density
navigation
code readability
diagrams
links
source provenance
```

Avoid turning documentation into a marketing landing page.

A subtle Rebuntu retro-tech character is acceptable if it does not reduce
readability.

The HTML renderer should support:

```
Markdown headings
tables
fenced code
syntax highlighting where practical
ASCII diagrams
callouts
internal links
external links
source references
```

======================================================================
33. HTML SEARCH
===============

Provide local full-text search if practical.

Start simple.

Prefer deterministic local indexing.

Do not introduce a vector database merely because one exists.

At moderate scale:

```
index + textual search
```

is sufficient.

Architecture should permit more sophisticated search later if needed.

======================================================================
34. BACKLINKS
=============

Generate backlinks where practical.

At the bottom or side of an article show:

```
Referenced by
```

with pages linking to the current article.

This makes the wiki graph navigable in both directions.

Backlinks may be derived during HTML generation rather than manually maintained.

======================================================================
35. GRAPH VIEW — OPTIONAL BUT DESIRABLE
=======================================

If reasonably implementable without a heavy dependency stack, generate a
knowledge graph view from Markdown links.

Nodes:

```
articles
```

Edges:

```
hyperlinks
```

This is a derived visualization.

Do not manually maintain a second graph representation unless required.

======================================================================
36. SOURCE CODE LINKS
=====================

Where useful, HTML articles should make repository source references clickable.

For local browsing this may resolve to repository-relative paths or generated
source-browser links.

Do not hardcode developer-specific absolute paths into canonical article text
unless unavoidable.

Canonical references should normally be repository-relative.

======================================================================
37. SEARCH / RETRIEVAL FOR AGENTS
=================================

The Markdown wiki should remain easily searchable with ordinary Unix tools:

```
rg
grep
find
```

Optionally provide:

```
wiki/tools/search
```

A future BM25/hybrid search layer may be added if corpus size justifies it.

Do not prematurely build a complex RAG stack.

The wiki itself is the compiled knowledge layer.

======================================================================
38. MACHINE-READABLE METADATA
=============================

Use minimal YAML frontmatter where useful.

Potential fields:

```
title
category
status
updated
tags
```

Optionally:

```
aliases
source_count
```

Do not put volatile data into frontmatter merely because it can be measured.

Avoid metadata that agents will constantly fail to keep synchronized.

Prefer derivable state to duplicated state.

======================================================================
39. NO KNOWLEDGE POISONING
==========================

LLM-generated synthesis must not silently become unquestionable authority.

Never use an unsupported wiki claim as sufficient evidence to create another
"fact".

When updating factual implementation knowledge:

```
wiki
  -> navigate
  -> primary source
  -> verify
  -> update wiki
```

For stable conceptual synthesis, existing wiki pages may be used as navigation
and context, but important changed/current implementation claims should be
checked against authoritative repository evidence.

======================================================================
40. NO COPY-PASTE ENCYCLOPEDIA
==============================

Do not fill the wiki by copying:

```
headers
source files
TASK.md
AGENTS.md
```

verbatim.

Synthesize them.

The wiki should reduce cognitive load.

Source remains available for exact details.

======================================================================
41. NO ARTICLE EXPLOSION
========================

Before creating a page:

```
search the wiki.
```

Determine whether:

```
an article already exists;
an alias exists;
the concept belongs as a section of an existing article.
```

Prefer:

```
one strong article
```

over:

```
five overlapping articles.
```

Split an article when it becomes genuinely conceptually overloaded.

======================================================================
42. NO SUMMARY GRAVEYARD
========================

Do not create a directory containing hundreds of disconnected source summaries.

Source-oriented pages are allowed when intrinsically useful, but every ingest
should ask:

```
What existing knowledge changes because of this source?
```

Update that knowledge.

This is the central compounding behavior of the wiki.

======================================================================
43. WIKI SATURATION PASS
========================

During a general wiki-building invocation:

1. inspect index;
2. inspect recent log;
3. inspect repository changes;
4. identify documentation gaps;
5. rank them by architectural importance;
6. create/update high-value articles;
7. cross-link them;
8. lint affected graph;
9. regenerate HTML;
10. append log entry.

Prioritize:

P0:
architecture
authority boundaries
runtime
security
identity
state/evidence semantics
execution/verification
persistence/recovery

P1:
major subsystems
providers
integration
automation
native Linux boundaries

P2:
individual components
development guides
testing knowledge

P3:
minor utilities and implementation details.

======================================================================
44. CONVERGENCE
===============

This task is intentionally repeatable.

A later run must NOT rewrite every article merely to sound different.

Before editing ask:

```
Is this knowledge already represented accurately?
```

If yes:

```
leave it alone.
```

Prefer small evidence-backed updates.

The wiki should converge toward a stable representation while continuing to
evolve with the project.

======================================================================
45. WIKI ↔ SOURCE COMMENT RELATIONSHIP
======================================

Source comments and Rebuntu Wiki have different responsibilities.

SOURCE COMMENTS:

```
local WHY
local invariants
local concurrency
local failure semantics
local platform behavior
dangerous simplifications
```

WIKI:

```
global architecture
concepts
relationships
cross-component behavior
historical evolution
incidents
navigational knowledge
aggregated synthesis
```

Do not move essential local correctness knowledge out of source comments merely
because the wiki exists.

Do not paste entire wiki articles into source comments.

They complement each other.

======================================================================
46. VALIDATION
==============

Before finishing:

Validate Markdown links.

Check:

```
broken internal links
duplicate pages
orphan pages
index completeness
source references
frontmatter
HTML generation
HTML internal links
search index if present
```

If tooling exists, automate these checks.

Prefer deterministic linting over asking the LLM to eyeball everything.

======================================================================
47. IMPLEMENT SUPPORT TOOLING
=============================

If missing, implement small maintainable tools for:

```
wiki build
link checking
index generation assistance
backlink generation
orphan detection
HTML generation
textual search
```

Prefer using the repository's primary implementation/tooling conventions.

Do not introduce a giant documentation framework unnecessarily.

Generated artifacts must be reproducible.

======================================================================
48. GIT
=======

Inspect:

```
git status
git diff
git diff --check
```

Do not include unrelated working-tree changes.

Wiki source and wiki tooling should be version-controlled.

Generated HTML policy must be decided explicitly:

Either:

```
commit generated HTML
```

if Rebuntu intentionally wants immediately browsable artifacts in Git;

or:

```
generate on demand and ignore generated output.
```

Record the decision in wiki/AGENTS.md.

Do not accidentally commit caches or temporary build files.

======================================================================
49. COMMIT
==========

If useful changes were produced, create one dedicated commit for the wiki pass.

Examples:

```
Build Rebuntu architectural knowledge wiki

Expand Rebuntu wiki with runtime and integration knowledge

Synchronize Rebuntu wiki with current implementation

Lint and reconcile Rebuntu knowledge base
```

Do not create an empty commit when nothing changed.

======================================================================
50. FINAL REPORT
================

Report:

```
operation(s) performed
repository revision inspected
wiki pages inspected
wiki pages created
wiki pages updated
pages removed/merged, if any
cross-links added
contradictions found
stale claims corrected
unresolved contradictions
orphan pages
missing high-value topics
source areas inspected
HTML build result
link-check result
wiki lint result
commit hash
```

Also provide:

```
NEXT HIGH-VALUE WIKI TARGETS
```

with the most important remaining knowledge gaps.

======================================================================
51. REPEATABILITY CONTRACT
==========================

Every future invocation of this prompt must begin from the existing wiki.

NEVER regenerate the wiki from scratch unless explicitly instructed.

The normal operation is:

```
existing knowledge
       +
new repository evidence
       +
new investigation
       ↓
reconciliation
       ↓
improved persistent knowledge
```

The desired long-term result is:

```
/home/bvrznski/rebuntu/wiki
```

becoming an encyclopedic, interlinked, evidence-backed map of Rebuntu that is
simultaneously:

```
human-readable;
agent-readable;
grep-friendly;
Git-versioned;
locally browsable;
hyperlinked;
incrementally maintained;
synchronized with implementation.
```

The wiki should become MORE valuable as the project grows, not merely larger.
