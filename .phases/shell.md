# Phase SHELL — Unified Fish Interactive Cockpit, Oh My Fish UX & Bash Compatibility

## Mission

Implement the COMPLETE Rebuntu human-facing shell environment as one coherent
phase.

This phase SUPERSEDES the previous separate SHELL and SHELL.2 implementations.

Do not treat previous shell work as architecture that must be preserved
verbatim. Treat the current machine as a migration source: inspect what exists,
preserve useful user configuration, back it up, and normalize the final system
onto one clean implementation.

The desired architecture is:

    HUMAN
      │
      ▼
    graphical terminal
      │
      ▼
     Fish
      │
      ├── console ──> Bash
      │                 │
      │              exit / Ctrl-D
      │                 │
      │                 └──────────> Fish
      │
      └── panel ───> Rebuntu System Control Panel


    AUTOMATION / DEVELOPMENT

    scripts ─────────────> shebang interpreter
    Cline / Codex ───────> Bash/POSIX-compatible execution
    VS Code tasks ───────> Bash/POSIX-compatible execution
    Docker / systemd ────> unchanged


Core rule:

    Fish = human-facing interactive cockpit
    Bash = conservative UNIX maintenance / scripting / automation console

The final Fish environment should be:

    beautiful
    fast
    technical
    highly usable
    information-rich when appropriate
    visually restrained when idle
    retro-futuristic / workstation-like
    recognizably Rebuntu

Do NOT build a large bespoke shell framework if mature existing tools already
solve the problem.

Use existing software aggressively and configure/integrate it well.

===============================================================================
1. DISCOVERY BEFORE MODIFICATION
===============================================================================

Before changing anything, inspect the current system.

At minimum inspect:

- current login shell
- `$SHELL`
- `/etc/shells`
- installed Fish version
- installed Bash version
- `~/.bashrc`
- `~/.profile`
- `~/.bash_profile`
- `~/.bash_login`
- `~/.config/fish/`
- Fish functions
- Fish conf.d files
- aliases
- environment exports
- PATH construction
- existing prompt implementation
- existing `fish_prompt`
- existing `fish_right_prompt`
- installed Fish plugins
- Fisher, if present
- Tide, if present (legacy/conflict discovery only)
- Starship, if present (legacy/conflict discovery only)
- Oh My Posh or other prompt engines, if present (legacy/conflict discovery only)
- eza, if present (rejected-tool residue discovery only)
- bat, fzf, zoxide and similar CLI enhancements, if present
- `LS_COLORS`
- `dircolors`
- GNOME Terminal configuration
- terminal profile custom command
- terminal font
- presence of obsolete Powerline configuration/residue
- rendering of the approved glyph whitelist
- VS Code integrated terminal configuration
- locally inspectable Cline/Codex shell execution configuration
- `TERM`
- `COLORTERM`
- locale
- relevant terminal capabilities

Determine what previous SHELL/SHELL.2 work has already changed.

Do not assume that an existing implementation is correct merely because it
exists.

Do not blindly overwrite configuration either.

Understand it first.

===============================================================================
2. EXISTING IMPLEMENTATION — NORMALIZE / REINSTALL
===============================================================================

IMPORTANT:

An earlier implementation attempt may already have installed or configured:

- Fish
- custom Fish prompt functions
- `fish_right_prompt`
- obsolete handcrafted prompt rendering
- Nerd Font icons
- Git prompt functions
- aliases
- helper functions
- terminal fonts
- plugins
- prompt engines
- enhanced `ls` functions
- other shell tooling

This phase explicitly replaces the previous fragmented implementation with ONE
canonical implementation.

Use the following migration lifecycle:

    inspect
      ↓
    classify
      ↓
    preserve useful user configuration
      ↓
    backup
      ↓
    remove/retire conflicting implementation
      ↓
    reinstall/reconfigure selected tools if useful
      ↓
    integrate
      ↓
    verify
      ↓
    leave ONE canonical implementation

If a selected tool is already installed but the installation/configuration is:

- incomplete
- inconsistent
- manually patched
- partially broken
- duplicated
- polluted by the previous attempt
- configured in conflict with the new architecture

then it is explicitly permitted to REINSTALL or RECONFIGURE that tool cleanly.

This may include:

- Fish
- Oh My Fish
- Zephyr theme
- Fish
- selected CLI enhancement packages
- related user-level integrations

However:

DO NOT delete unrelated user data.

DO NOT remove unrelated shell configuration.

DO NOT destroy the previous configuration before backing it up.

Create timestamped backups before replacing materially relevant configuration.

Preserve useful user-authored functionality where appropriate.

Do NOT leave competing prompt frameworks active. In particular, back up and retire
legacy Starship, Tide, Oh My Posh, custom fish_prompt/fish_right_prompt, and old
Powerline helpers if they conflict with the canonical OMF + Zephyr stack.

There must be ONE canonical prompt implementation:

    Fish -> Oh My Fish -> Zephyr

===============================================================================
3. HARD COMPATIBILITY BOUNDARY
===============================================================================

Fish is intended for HUMAN INTERACTIVE USE.

It must NOT become an accidental compatibility boundary for:

- Bash scripts
- POSIX scripts
- Cline
- Codex
- other coding agents
- VS Code tasks
- subprocess automation
- Docker
- systemd
- cron
- system tooling

Do NOT modify:

    /bin/sh
    /bin/bash

Do NOT change global shell semantics.

Do NOT introduce Fish syntax into Bash/POSIX scripts.

Do NOT run:

    chsh

Do NOT make Fish the account login shell in this phase.

Preserve:

    graphical human terminal -> Fish

while:

    scripts              -> shebang-selected interpreter
    coding agents        -> Bash/POSIX-compatible shell
    system services      -> unchanged
    Docker               -> unchanged

Prefer configuring the intended GNOME Terminal profile to launch Fish
explicitly.

Do not globally force Fish onto processes that expect Bash/POSIX semantics.

If a compatibility condition cannot be conclusively verified:

    UNKNOWN != PASS

Preserve the conservative behavior and report the uncertainty.

===============================================================================
4. USE MATURE EXISTING TOOLS — DO NOT REINVENT THEM
===============================================================================

This is a strong architectural requirement.

Do NOT write hundreds of lines of handcrafted Fish code for capabilities already
provided cleanly by mature tools.

Prefer:

    integration + configuration

over:

    custom reimplementation

The desired stack should conceptually resemble:

    GNOME Terminal
          │
         Fish
          │
          ├── Oh My Fish
          │    └── Zephyr
          ├── Fish native features
          ├── grc / fzf / bat / fd-find / ripgrep
          ├── zoxide / btop / direnv / tldr
          └── small Rebuntu-specific glue only where useful

-------------------------------------------------------------------------------
4.1 Fish
-------------------------------------------------------------------------------

Use Fish-native functionality for:

- autosuggestions
- syntax highlighting
- completions
- command history
- directory navigation
- interactive functions
- shell ergonomics

Do not replace good Fish-native functionality unnecessarily.

-------------------------------------------------------------------------------
4.2 Prompt Framework and Theme
-------------------------------------------------------------------------------

Use the already selected mature stack:

    Fish
      -> Oh My Fish
           -> Zephyr

Oh My Fish is the canonical Fish framework for this phase.

Zephyr is the selected prompt/theme baseline:

    https://github.com/komarnitskyi/theme-zephyr

Do NOT install or layer Starship, Tide, Oh My Posh, or another prompt engine on
top of it. If remnants of competing prompt implementations exist from earlier
experiments, back them up and retire them.

Do NOT handcraft a replacement prompt framework. Configure or minimally patch
Zephyr only where necessary.

IMPORTANT: Powerline chevrons/separators (the previously desired "krawaty")
are explicitly abandoned because they do not render correctly in the actual
terminal environment. Do not attempt to repair, emulate, reintroduce, or depend
on:

          

The design must work without them.

-------------------------------------------------------------------------------
4.3 File Listing
-------------------------------------------------------------------------------

Keep GNU `ls` as the canonical file-listing command.

`eza` has been tested in this environment and intentionally rejected because it
did not behave correctly. It is NOT part of the Rebuntu shell stack.

Do NOT reinstall eza in this phase.

Enhance human readability through Fish colors, GNU `LS_COLORS`/`dircolors`, and
other non-invasive tooling where useful, while preserving normal GNU `ls`
semantics.

-------------------------------------------------------------------------------
4.4 Canonical CLI Enhancement Stack
-------------------------------------------------------------------------------

The selected enhancement stack is:

    grc       generic output colourisation
    fzf       fuzzy search / interactive selection
    bat       syntax-highlighted file viewing
    fd-find   ergonomic file discovery
    ripgrep   fast recursive text search
    zoxide    frecency-based directory navigation
    btop      interactive system monitor
    direnv    per-directory environment activation
    tldr      concise command examples

Install/repair these through Ubuntu packages where available. On Ubuntu, retain
distribution binary naming where applicable (for example `batcat` or `fdfind`)
unless a small human-facing Fish abbreviation is useful. Do not break scripts by
shadowing canonical commands globally.

Do not reinstall eza.

===============================================================================
5. VERIFIED GLYPH POLICY
===============================================================================

Do NOT assume general Nerd Font compatibility. The actual terminal/font has been
tested and only a restricted glyph set is approved for Rebuntu shell UI.

Approved glyphs:

    FILES
        

    NAVIGATION
                    ➜  ❯

    SHELL / STATUS
              

    SYSTEM
                  

    DEV
        

    GIT / STATE
    ↑  ↓  +  !  ?  ✘

Use ONLY these verified glyphs unless another glyph is explicitly tested in the
actual terminal and added to the approved set.

Explicitly forbidden/abandoned Powerline separators:

          

They do not render correctly and must not be used.

Do not spend implementation time trying to fix them.

===============================================================================
6. VISUAL LANGUAGE
===============================================================================

Desired aesthetic:

    operator workstation
          +
    UNIX power-user environment
          +
    modern terminal ergonomics
          +
    subtle retro computing
          +
    restrained HUD

NOT:

    generic default Fish

NOT:

    enormous prompt prefix

NOT:

    rainbow Christmas tree

NOT:

    frontend dashboard transplanted into a terminal

The prompt should feel intentionally designed.

===============================================================================
7. CORE PROMPT GEOMETRY
===============================================================================

Use a clean text/icon geometry WITHOUT Powerline wedges.

The command workspace remains the visual center. Context should be compact and
status information should be visually separated using spacing, restrained
color, punctuation, and approved glyphs.

Representative direction:

     DIABLO   ~/Gordon  ❯ make test

or, when contextual Git/status information is shown:

     DIABLO   ~/Gordon   main  ↑3 !2 ?1  ❯ make test

Do not force an elaborate right prompt if Zephyr's existing layout is cleaner.
Prefer the stock theme's proven rendering and small maintainable adjustments.

No Powerline geometry is required or desired.

===============================================================================
8. LEFT CONTEXT
===============================================================================

Keep the left prompt compact.

Primary information:

    host
    working directory

Example:

     DIABLO   ~/Gordon  ❯

Prefer:

    DIABLO

over permanent verbose:

    username@hostname

unless user identity becomes operationally relevant.

The current directory must remain immediately recognizable.

Abbreviate intelligently when paths become long.

Do not sacrifice useful path context merely for symmetry.

===============================================================================
9. COMMAND WORKSPACE IS SACRED
===============================================================================

The command-entry area must remain the visual center of the shell.

It must:

- have ample horizontal space;
- work naturally with Fish autosuggestions;
- preserve Fish syntax highlighting;
- preserve completions;
- remain readable for long commands;
- not be crowded by decorative modules.

The user should perceive:

    context | COMMAND WORKSPACE | telemetry

not:

    GIANT PROMPT PREFIX | tiny command area

Right-side information must gracefully disappear or compress when terminal
width becomes insufficient.

===============================================================================
10. RIGHT-SIDE HUD
===============================================================================

Use the selected mature prompt engine's right-prompt/right-format capability
where practical.

The right side acts as a contextual HUD.

Potential information:

- Git branch
- Git ahead/behind
- staged changes
- modified files
- untracked files
- conflicts
- previous command failure
- meaningful command duration
- active Python environment
- jobs
- other genuinely useful context

Everything is DYNAMIC.

Do not display information simply because it is available.

===============================================================================
11. GIT COMPACT STATUS TOKENS
===============================================================================

Git should remain compact and scannable without Powerline separators.

Do NOT render Git as one verbose flat string.

Example:

     main  ↑3 ↓1 +4 !2 ?1

Suggested semantics:

     main     branch
    ↑3         commits ahead
    ↓1         commits behind
    +4         staged
    !2         modified
    ?1         untracked
    ✘1         conflicts

Only show non-zero/relevant state.

Clean repository:

     main

Active repository:

     main ↑3 !2 ?1

Diverged repository:

     main ↑3 ↓2

Prefer capabilities already provided by the selected prompt engine.

Do not implement a complex Git parser if the prompt engine already provides
equivalent information.

Git status collection must remain fast enough that large repositories do not
make the shell feel sluggish.

===============================================================================
12. SEMANTIC ICONS
===============================================================================

Use small icons as semantic landmarks.

Examples:

      host / terminal
      directory
      Git branch
      Python
      compute/hardware
      duration
      success
      warning
      failure

Icons should help recognition BEFORE text is consciously read.

Good:

     ~/Gordon
     main
     gordon
     3.2s
     ERR:127

Bad:

    five decorative icons around every word

Use icons dynamically.

Do not turn the prompt into an icon showcase.

Do not replace important information with ambiguous glyphs.

===============================================================================
13. DYNAMIC INFORMATION
===============================================================================

The idle prompt should remain calm.

Examples:

Outside Git:

     DIABLO   ~/Downloads  ❯

Inside clean repository:

     DIABLO   ~/Gordon  ❯                      main

Busy repository:

     DIABLO   ~/Gordon  ❯ command     main ↑3 !2 ?1

Failed command:

     DIABLO   ~/Gordon  ❯ command        main  ERR:127

Long-running command:

     DIABLO   ~/Gordon   main   4.2s  ❯ command

Rules:

- Git only inside Git repositories.
- Python environment only when active.
- failure prominently shown after failure.
- exit code 0 should normally not create noise.
- duration shown only when useful.
- jobs shown only when jobs exist.
- other modules shown only when materially relevant.

===============================================================================
14. COMMAND DURATION
===============================================================================

Use the prompt engine/Fish-provided duration information.

Do not display meaningless durations for trivial commands.

Establish a sensible threshold.

For example:

    1.8s
    14s
    2m13s

Prefer omission for extremely fast commands.

===============================================================================
15. FAILURE STATE
===============================================================================

A failed command should be immediately recognizable.

Example:

     ERR:1
     ERR:127

Choose one coherent notation.

Do not make successful exit code 0 equally visually loud.

Failure is exceptional telemetry.

Success is normal.

===============================================================================
16. SEMANTIC COLOR SYSTEM
===============================================================================

Create ONE restrained semantic color vocabulary shared across:

- Fish prompt
- Git status
- GNU ls/file listing
- future Rebuntu Panel

Colors communicate meaning.

Suggested roles:

    CONTEXT
    PATH
    ACCENT
    READ / INFORMATION
    WRITE / MUTATION
    EXECUTE / ACTION
    SUCCESS / HEALTHY
    WARNING
    ERROR / CONFLICT
    SECONDARY / DIM

Do not assign unrelated arbitrary colors to every module.

Avoid excessive saturation.

Avoid displaying too many saturated colors simultaneously.

Color should reinforce meaning rather than replace it.

The interface should remain understandable through:

    shape
    position
    glyph
    text
    color

rather than color alone.

===============================================================================
17. RWX / FILE PERMISSION VISUALIZATION
===============================================================================

The enhanced human-facing file listing should make UNIX permissions immediately
scannable.

Use standard GNU listing semantics. Enhance readability through LS_COLORS/dircolors where practical; do not create a bespoke permission parser merely for decoration.

Desired semantic concept:

    r = read
    w = write / mutation
    x = execute / action
    - = absent / dim

Example permission strings remain conventional:

    -rwxr-xr--
    drwxr-x---
    -rw-r-----

Preserve exact UNIX ordering:

    [type][user:rwx][group:rwx][other:rwx]

Never rearrange permissions for visual reasons.

Correctly preserve:

    s
    S
    t
    T

for:

- setuid
- setgid
- sticky bit

Preserve ACL/extended attribute indicators where applicable.

Do NOT write a bespoke parser merely to color individual characters unless no
mature installed tool can reasonably provide the desired result.

Do NOT replace GNU `ls`.

===============================================================================
18. FILE TYPE COLOR HARMONY
===============================================================================

Directories, symlinks, executables, sockets, pipes, devices and ordinary files
should remain distinguishable.

Inspect existing:

    LS_COLORS
    dircolors
    Fish colors

before modifying anything.

Prefer harmonization over wholesale replacement.

The result should feel like one environment:

    prompt
      +
    Git
      +
    listings
      +
    completions
      +
    future panel

rather than five unrelated themes.

===============================================================================
18.1 CLI OUTPUT COLOR INTEGRATION & GNU LISTING NORMALIZATION
===============================================================================

The current shell implementation must ensure that ordinary command output feels
like part of the same Rebuntu visual environment as Fish + Oh My Fish + Zephyr.

This is NOT a request to replace standard UNIX tools.

The objective is:

    native mature color support
        +
    coherent LS_COLORS / dircolors
        +
    selective grc integration
        +
    small Fish-facing aliases/abbreviations/functions where appropriate

NOT:

    custom reimplementation of ls/tree/grep/etc.

-------------------------------------------------------------------------------
18.1.1 DISCOVER THE CURRENT COLOR PATH FIRST
-------------------------------------------------------------------------------

Before changing anything, inspect the actual active configuration.

At minimum inspect:

    type -a ls
    type -a ll
    type -a tree
    type -a grep
    type -a rg
    type -a grc

and in Fish:

    functions ls
    functions ll
    alias
    set -q LS_COLORS; and echo $LS_COLORS

Also inspect:

    LS_COLORS
    dircolors configuration
    ~/.dircolors
    ~/.config/fish/config.fish
    ~/.config/fish/conf.d/
    ~/.config/fish/functions/
    Oh My Fish initialization
    Zephyr initialization
    existing grc integration

Determine WHY colors are currently missing before adding configuration.

In particular verify whether:

    command ls --color=always

actually produces colored output.

If it does, then the underlying GNU ls color support works and the problem is
likely Fish configuration / alias / function / environment integration.

Do not build another listing implementation to solve a configuration problem.

-------------------------------------------------------------------------------
18.1.2 GNU LS REMAINS CANONICAL
-------------------------------------------------------------------------------

GNU ls remains the canonical listing implementation.

Do NOT install or restore eza.

Do NOT replace ls with a custom parser.

Ensure that human-interactive Fish usage enables GNU ls colors automatically.

Desired conceptual behavior:

    ls  -> GNU ls with --color=auto
    ll  -> GNU ls long human-readable listing with --color=auto
    la  -> GNU ls including hidden entries with --color=auto
    l   -> compact GNU ls listing with --color=auto

Exact aliases/functions may be adapted to existing configuration after
discovery.

Representative semantics:

    ls='command ls --color=auto'
    ll='command ls -lah --color=auto'
    la='command ls -A --color=auto'
    l='command ls -CF --color=auto'

Do not blindly install these definitions if equivalent good definitions already
exist.

Prefer ONE canonical owner.

Do not create competing aliases + functions + conf.d definitions for the same
command.

-------------------------------------------------------------------------------
18.1.3 LS_COLORS / DIRCOLORS
-------------------------------------------------------------------------------

Inspect the existing LS_COLORS before replacing it.

If the current LS_COLORS is missing, malformed, incomplete, or visually
incoherent, normalize it through the standard GNU dircolors mechanism.

Prefer:

    dircolors
        ->
    LS_COLORS
        ->
    GNU ls / tree / compatible tools

over hardcoding file-type logic into Fish.

Preserve standard distinctions for at least:

    directories
    symlinks
    broken symlinks
    executables
    regular files
    sockets
    FIFOs
    block devices
    character devices
    archives
    common source/config file types where supported

Do not make every extension a different saturated color.

The result should remain restrained and workstation-like.

The color grammar should harmonize with the semantic roles already established
for Rebuntu:

    CONTEXT
    PATH
    ACCENT
    READ / INFORMATION
    WRITE / MUTATION
    EXECUTE / ACTION
    SUCCESS / HEALTHY
    WARNING
    ERROR / CONFLICT
    SECONDARY / DIM

File type remains the primary semantic dimension for ordinary ls output.

Do NOT attempt to encode Git modification state into LS_COLORS.

Git state belongs to Git-aware components such as Zephyr, git status, Phase 26,
and future Panel integration.

-------------------------------------------------------------------------------
18.1.4 GIT DIRECTORIES MUST NOT LOSE FILE COLORS
-------------------------------------------------------------------------------

Explicitly test GNU ls inside:

    ordinary directories
    clean Git repositories
    dirty Git repositories
    repositories with staged files
    repositories with untracked files

Entering a Git repository MUST NOT cause ordinary GNU ls file-type colors to
disappear.

This is an important regression test.

If colors disappear only inside Git repositories, investigate:

    Fish functions
    directory hooks
    direnv
    Git-related Fish/OMF plugins
    Zephyr hooks
    environment mutation
    LS_COLORS mutation
    aliases/functions shadowing ls

before implementing a workaround.

Git repository detection must remain orthogonal to ordinary file-type coloring.

Conceptually:

    FILE TYPE COLOR
         +
    GIT CONTEXT

not:

    Git repository
         ->
    disable/replace ls coloring

-------------------------------------------------------------------------------
18.1.5 TREE COLOR INTEGRATION
-------------------------------------------------------------------------------

If `tree` is installed, preserve the mature upstream implementation.

Do NOT implement a custom tree renderer.

Inspect its current behavior first.

Configure the HUMAN Fish environment so that interactive tree output uses
colors when appropriate.

Representative desired behavior:

    tree -> tree -C

provided that this is compatible with the installed implementation and actual
terminal behavior.

The tree color vocabulary should derive from / harmonize with LS_COLORS where
supported.

Verify:

    tree
    tree -L 2
    tree inside Git repository
    tree with executable files
    tree with symlinks
    tree with hidden files when explicitly requested

Do not force ANSI color codes into redirected/scripted output unless explicitly
requested.

Interactive beautification must not corrupt machine-readable output.

-------------------------------------------------------------------------------
18.1.6 NATIVE COLOR FIRST
-------------------------------------------------------------------------------

Use the following priority:

    1. native program color support
    2. shared standard color configuration
    3. grc where genuinely useful
    4. minimal Fish glue
    5. custom implementation only as a last resort

Examples:

    ls          -> native GNU --color
    tree        -> native color capability
    rg          -> native ripgrep coloring
    grep        -> native GNU coloring
    git         -> native Git coloring
    ip          -> native iproute2 coloring if supported
    systemctl   -> preserve native systemd output/color
    journalctl  -> preserve native behavior
    other tools -> grc selectively where it materially improves readability

Do NOT wrap every command in grc.

Do NOT pass already richly colored output through another colorizer merely to
make it "more colorful".

Avoid:

    native colors
        -> grc
        -> nested ANSI transformations

unless explicitly verified to behave correctly.

-------------------------------------------------------------------------------
18.1.7 GRC INTEGRATION
-------------------------------------------------------------------------------

grc is already part of the selected Rebuntu shell enhancement stack.

Use it selectively for commands whose plain-text output benefits from semantic
colorization and which do not already provide sufficiently good native output.

Discover existing grc Fish integration before creating aliases.

Prefer upstream-supported integration/configuration where available.

Do not shadow commands in a way that changes scripting behavior.

Any grc enhancement should be HUMAN-INTERACTIVE Fish behavior only.

Bash/POSIX automation must remain conventional.

-------------------------------------------------------------------------------
18.1.8 REDIRECTION / PIPES / MACHINE OUTPUT
-------------------------------------------------------------------------------

Color policy MUST distinguish:

    interactive terminal output

from:

    redirected output
    pipelines
    scripts
    machine-readable output

Prefer automatic terminal detection where mature tools support it.

For example:

    --color=auto

is normally preferable to:

    --color=always

for canonical interactive aliases.

Do not contaminate:

    command > file
    command | parser

with ANSI escape sequences merely for aesthetics.

Explicit forced-color commands may exist for deliberate interactive use, but
must not become the universal default.

-------------------------------------------------------------------------------
18.1.9 LL MUST REMAIN A UNIX LISTING
-------------------------------------------------------------------------------

`ll` should remain a recognizable conventional long UNIX listing.

It should expose standard information such as:

    permissions
    link count
    owner
    group
    size
    timestamp
    filename

Do not transform ll into a custom dashboard.

Do not replace permission notation with icons.

Do not reorder UNIX permission semantics.

The purpose of color is faster visual parsing, not replacing textual truth.

Example conceptual result:

    drwxr-x---   src/
    -rwxr-xr-x   build.sh
    -rw-r-----   config.toml
    lrwxrwxrwx   current -> releases/current

with appropriate semantic/file-type colors.

-------------------------------------------------------------------------------
18.1.10 FISH COMPLETION COLOR HARMONY
-------------------------------------------------------------------------------

Inspect Fish's existing completion and pager colors.

Where practical, harmonize:

    Fish syntax highlighting
    Fish completion pager
    autosuggestions
    GNU ls / LS_COLORS
    tree
    Git
    Zephyr

without destroying Fish's useful native semantic distinctions.

Do NOT reduce Fish syntax highlighting to one uniform palette merely for visual
consistency.

Harmony means:

    related semantic roles feel related

NOT:

    every component uses exactly the same literal color everywhere.

-------------------------------------------------------------------------------
18.1.11 CONFIGURATION OWNERSHIP
-------------------------------------------------------------------------------

After implementation there must be one obvious ownership path for CLI output
color configuration.

A desirable architecture is conceptually:

    Fish interactive configuration
              │
              ├── LS_COLORS / dircolors
              │       ├── GNU ls
              │       └── tree-compatible coloring
              │
              ├── native program colors
              │       ├── grep
              │       ├── ripgrep
              │       ├── Git
              │       └── other capable tools
              │
              └── grc
                      └── selected otherwise-plain commands

Do not scatter duplicate color configuration across arbitrary Fish functions.

If configuration is separated into conf.d files, give each file a clear
responsibility.

Example conceptual ownership:

    conf.d/
        rebuntu-colors.fish
        rebuntu-cli-tools.fish

Exact filenames should follow the discovered repository/configuration
architecture rather than being created blindly.

-------------------------------------------------------------------------------
18.1.12 PERFORMANCE
-------------------------------------------------------------------------------

Color integration must have effectively negligible interactive overhead.

Do not execute expensive external processes every time:

    ls
    prompt render
    directory change

merely to calculate colors.

LS_COLORS should be initialized efficiently.

Avoid repeatedly running dircolors when a stable environment initialization is
sufficient.

Measure if implementation introduces hooks or subprocesses into latency-critical
Fish paths.

-------------------------------------------------------------------------------
18.1.13 VALIDATION
-------------------------------------------------------------------------------

After implementation test at minimum:

    ls
    ll
    la
    tree

in:

    ~
    ~/Downloads
    ordinary non-Git directory
    clean Git repository
    dirty Git repository

Create/use safe temporary test fixtures where useful containing:

    regular file
    executable
    directory
    symlink
    broken symlink
    hidden file
    archive

Verify:

    file types remain visually distinguishable
    Git directories retain listing colors
    ll retains conventional UNIX information
    tree colors work interactively
    redirected output remains suitable for text processing
    Fish autosuggestions still work
    Fish syntax highlighting still works
    Zephyr remains intact
    Bash behavior remains conventional
    no eza dependency exists
    no Powerline separators have returned

Also verify representative redirection:

    ls > /tmp/rebuntu-ls-test.txt

and inspect the resulting file for unwanted ANSI escape sequences.

Do the equivalent for any aliases/functions whose behavior was changed.

-------------------------------------------------------------------------------
18.1.14 FINAL RESULT
-------------------------------------------------------------------------------

The desired visual relationship is:

    Fish / Zephyr
         │
         ├── semantic prompt colors
         │
         ├── Git state colors
         │
         └── command workspace
                  │
                  ▼
            COMMAND OUTPUT
                  │
         ┌────────┼─────────┐
         ▼        ▼         ▼
        ls       tree      tools
         │        │         │
         └────────┴─────────┘
                  │
                  ▼
        coherent Rebuntu CLI
          visual language

The terminal should no longer feel like:

    polished prompt
         +
    unrelated monochrome command output

It should feel like ONE restrained operator workstation environment.

Most importantly:

    KEEP GNU LS.
    KEEP STANDARD UNIX SEMANTICS.
    USE NATIVE COLOR SUPPORT FIRST.
    USE LS_COLORS / DIRCOLORS AS THE FILE-COLOR FOUNDATION.
    USE GRC SELECTIVELY.
    DO NOT RESTORE EZA.
    DO NOT RESTORE POWERLINE SEPARATORS.
    DO NOT BREAK MACHINE-READABLE OUTPUT FOR AESTHETICS.

===============================================================================
19. `console`
===============================================================================

Implement/preserve the Fish command:

    console

Prefer:

    ~/.config/fish/functions/console.fish

Required semantics:

    Fish
      ↓
    console
      ↓
    Bash
      ↓
    exit / Ctrl-D
      ↓
    original Fish session

Equivalent implementation:

    function console --description 'Enter standard Bash console'
        command bash
    end

DO NOT use:

    exec bash

Bash must be a child process.

Verify that normal interactive Bash configuration loads.

===============================================================================
20. BASH MUST REMAIN BORING
===============================================================================

This distinction is intentional:

    Fish = friendly Rebuntu cockpit
    Bash = boring predictable UNIX console

Do not apply the Fish visual theme to Bash.

Do not substantially redesign `.bashrc`.

Preserve existing useful Bash configuration.

`console` exists partly so the user always has a conventional maintenance
environment available.

===============================================================================
21. GNOME TERMINAL INTEGRATION
===============================================================================

Make the intended graphical terminal open into Fish WITHOUT changing the
account login shell.

Prefer a GNOME Terminal profile-level custom command such as:

    /usr/bin/fish

if appropriate after inspection.

Before modifying the profile:

- identify the correct profile;
- inspect its current configuration;
- preserve existing settings;
- create a rollback path;
- avoid affecting unrelated profiles.

If modifying the existing profile would create compatibility risk, create or
configure an appropriate dedicated human-facing profile instead.

Do not alter coding-agent execution semantics merely to make GNOME Terminal
prettier.

===============================================================================
22. STARTUP PERFORMANCE
===============================================================================

Beauty must not make the shell sluggish.

Measure Fish startup before/after where practical.

Avoid synchronous expensive operations during every prompt render.

Particularly inspect:

- Git status cost
- Python/environment detection
- external process spawning
- prompt engine startup
- plugin initialization
- directory-dependent hooks

Prefer mature cached/native implementations.

The prompt should feel effectively immediate.

===============================================================================
23. CONFIGURATION ARCHITECTURE
===============================================================================

Keep configuration understandable.

Prefer standard locations such as:

    ~/.config/fish/config.fish
    ~/.config/fish/functions/
    ~/.config/fish/conf.d/

plus Oh My Fish and Zephyr's canonical configuration locations.

Do not dump all logic into one enormous `config.fish`.

Do not duplicate functionality across:

    config.fish
    conf.d
    fish_prompt
    prompt engine
    aliases

There should be a clear owner for each responsibility.

===============================================================================
24. REBUNTU VISUAL LANGUAGE
===============================================================================

Treat this shell as the first implementation of a reusable Rebuntu terminal
visual language.

Future `panel` should be able to reuse the same broad grammar:

    compact layout
    approved icons
    spacing
    semantic colors
    warning/error conventions
    typography assumptions

Conceptually:

    SHELL

     DIABLO   ~/Gordon  ❯ command
                               main ↑3 !2  2.4s


    PANEL

    SYSTEM | HARDWARE | STORAGE | NETWORK
                              HEALTH:OK | 11:58

Do NOT implement Phase 25 Panel functionality here.

Only establish visual conventions suitable for reuse.

===============================================================================
24.1 CANONICAL INSTALLATION BASELINE
===============================================================================

The known desired package/bootstrap baseline is:

    sudo apt update
    sudo apt install -y fish
    fish --version
    curl https://raw.githubusercontent.com/oh-my-fish/oh-my-fish/master/bin/install | fish

Then inside Fish:

    omf install https://github.com/komarnitskyi/theme-zephyr
    omf theme zephyr

And the selected CLI tools:

    sudo apt install -y \
        grc \
        fzf \
        bat \
        fd-find \
        ripgrep \
        zoxide \
        btop \
        direnv \
        tldr

Do not install eza.
Do not install Starship or Tide.
Do not reintroduce Powerline separators.

===============================================================================
25. SAFETY
===============================================================================

Allowed:

- inspect existing configuration;
- create backups;
- install/reinstall appropriate shell UX packages;
- preserve/configure terminal font support as needed for the VERIFIED glyph whitelist;
- configure Fish;
- configure selected prompt engine;
- modify the intended GNOME Terminal profile;
- retire obsolete previous SHELL/SHELL.2 prompt configuration after backup.

Not allowed:

- deleting unrelated user data;
- deleting unrelated fonts;
- removing Bash;
- replacing `/bin/sh`;
- changing global interpreter semantics;
- `chsh`;
- destructive filesystem cleanup;
- modifying coding-agent behavior merely for aesthetics;
- blindly deleting previous configuration without inspection and backup.

Reinstallation means:

    normalize the selected tooling cleanly

NOT:

    wipe arbitrary configuration and hope for the best

===============================================================================
26. VALIDATION MATRIX
===============================================================================

Test at minimum:

### Shell architecture

    GNOME Terminal -> Fish

    Fish -> console -> Bash

    Bash -> exit -> original Fish

Verify actual process/shell identity.

### Bash compatibility

Verify ordinary interactive Bash configuration.

Verify representative:

    #!/bin/bash

and:

    #!/bin/sh

scripts still execute under their declared interpreters.

### Coding environment

Inspect/test locally available:

- VS Code
- Cline
- Codex
- relevant task execution paths

Confirm that Bash/POSIX-required execution has not accidentally been redirected
through Fish.

If something cannot be verified:

    report UNKNOWN

Do not fabricate PASS.

### Prompt

Test:

- home directory
- ordinary directory
- deep directory
- narrow terminal
- wide terminal
- clean Git repository
- dirty Git repository
- staged changes
- untracked changes
- ahead/behind where practical
- failed command
- successful command
- long-running command
- active Python venv if available
- background job if supported
- long command input
- Fish autosuggestion
- completion menu

### Glyphs

Verify:

      
            ➜ ❯
        
           
      
    ↑ ↓ + ! ? ✘

in the ACTUAL configured terminal profile.

No tofu squares.

### Listing

Verify:

- regular file
- executable
- directory
- symlink
- hidden file
- long listing
- permissions
- Git-aware listing where supported
- special permission bits if practical

### Performance

Check Fish startup latency.

Check prompt responsiveness in:

- ordinary directory
- Git repository
- reasonably large repository if available

===============================================================================
27. FINAL CLEANUP / NORMALIZATION AUDIT
===============================================================================

After everything works, perform a final configuration audit.

Look specifically for remnants of previous implementations:

- obsolete `fish_prompt`
- obsolete `fish_right_prompt`
- competing Starship/Tide/Oh My Posh initialization
- old Powerline helpers and separators
- duplicate Git helpers
- duplicate aliases
- conflicting Fish conf.d files
- obsolete prompt environment variables
- abandoned theme configuration

Do not leave dead competing implementations active.

Backups may remain.

The ACTIVE configuration should have one obvious architecture.

Example:

    GNOME Terminal
          ↓
         Fish
          ↓
     Oh My Fish
          ↓
       Zephyr
          +
    canonical CLI enhancement stack
          +
    small Fish functions
          │
          └── console -> Bash

There must be no competing prompt framework layered underneath or on top.

===============================================================================
28. DELIVERABLE
===============================================================================

After implementation report:

1. initial system state;
2. previous SHELL/SHELL.2 artifacts discovered;
3. tools already installed;
4. tools installed/reinstalled;
5. Oh My Fish/Zephyr state and any customization performed;
6. configuration backed up;
7. obsolete implementation retired;
8. files created;
9. files modified;
10. final Fish architecture;
11. exact `console` implementation;
12. GNOME Terminal integration;
13. verified glyph/font configuration;
14. prompt/context token meanings;
15. Git compact-status token meanings;
16. semantic color grammar;
17. GNU ls / LS_COLORS listing configuration;
18. Bash/POSIX compatibility results;
19. Cline/Codex/VS Code compatibility results;
20. startup/performance results;
21. validation results;
22. rollback procedure;
23. remaining UNKNOWNs or limitations.

Include exact textual examples of the resulting prompt states.

Screenshots may additionally be produced where practical.

===============================================================================
29. SUCCESS CRITERION
===============================================================================

The phase succeeds only when the workstation behaves conceptually as:

    ┌──────────────────────────────────────────────────────────────┐
    │ HUMAN                                                        │
    │                                                              │
    │ GNOME Terminal                                               │
    │      ↓                                                       │
    │     Fish                                                     │
    │      ↓                                                       │
    │ Oh My Fish + Zephyr + verified glyph set                       │
    │      │                                                       │
    │      ├── console -> Bash -> exit -> Fish                     │
    │      │                                                       │
    │      └── panel   -> Rebuntu control surface                  │
    └──────────────────────────────────────────────────────────────┘

    ┌──────────────────────────────────────────────────────────────┐
    │ AUTOMATION / DEVELOPMENT                                     │
    │                                                              │
    │ Cline / Codex / scripts -> Bash / POSIX                      │
    │ Docker / systemd         -> unchanged                        │
    └──────────────────────────────────────────────────────────────┘


And the normal interactive experience resembles:

     DIABLO   ~/Gordon  ❯ _

while context dynamically enriches it:

     DIABLO   ~/Gordon   main  ↑3 !2 ?1  ❯ make test    2.4s

and failure becomes immediately visible:

     DIABLO   ~/Gordon   main   ERR:127  ❯ command

while enhanced human-facing listings provide a coherent UNIX visual language:

    -rwxr-xr-x   script.sh
    -rw-r-----   config.toml
    drwxr-x---   src/

with useful semantic colors and icons supplied by mature tooling wherever
possible.

The final result must feel like:

    a workstation cockpit,
    not a shell configuration demo.

It should be beautiful enough to enjoy using all day, but predictable enough
that typing:

    console

immediately returns the operator to boring, conventional, dependable Bash.

Most importantly:

    USE EXISTING MATURE TOOLS.
    CONFIGURE THEM WELL.
    DO NOT REIMPLEMENT THEIR FUNCTIONALITY FOR SPORT.
    DO NOT LAYER THE NEW IMPLEMENTATION ON TOP OF OLD SHELL EXPERIMENTS.
    NORMALIZE THE SYSTEM INTO ONE CLEAN, MAINTAINABLE SHELL STACK.
