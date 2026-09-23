#!/bin/bash
# src/system/shell/sources/sources.sh — Shell Source Library Entry Point
#
# This file loads all shell source categories into the current shell environment.
# It should be sourced once at shell startup, not repeatedly.

# Exit early if already loaded (prevents redefinition issues)
if [[ -n "${_REBUNTU_SOURCES_LOADED:-}" ]]; then
    return 0
fi

# Mark as loaded
_REBUNTU_SOURCES_LOADED=1

# Get the directory where this file is located
_REBUNTU_SOURCES_DIR="${BASH_SOURCE[0]%/*}"

# Verify sources directory exists
if [[ ! -d "$_REBUNTU_SOURCES_DIR" ]]; then
    echo "Error: Shell sources directory not found: $_REBUNTU_SOURCES_DIR" >&2
    return 1
fi

# Load individual category modules
# Order matters for dependencies; categories without dependencies first.

## Core utilities (no dependencies)
source "$_REBUNTU_SOURCES_DIR/paths/_init.sh" 2>/dev/null || true
source "$_REBUNTU_SOURCES_DIR/text/_init.sh" 2>/dev/null || true
source "$_REBUNTU_SOURCES_DIR/time/_init.sh" 2>/dev/null || true
source "$_REBUNTU_SOURCES_DIR/structures/_init.sh" 2>/dev/null || true

## Flow and composition
source "$_REBUNTU_SOURCES_DIR/flow/_init.sh" 2>/dev/null || true

## I/O handling
source "$_REBUNTU_SOURCES_DIR/input/_init.sh" 2>/dev/null || true
source "$_REBUNTU_SOURCES_DIR/output/_init.sh" 2>/dev/null || true

## Parsing and data handling
source "$_REBUNTU_SOURCES_DIR/parsing/_init.sh" 2>/dev/null || true

## System operations
source "$_REBUNTU_SOURCES_DIR/filesystem/_init.sh" 2>/dev/null || true
source "$_REBUNTU_SOURCES_DIR/processes/_init.sh" 2>/dev/null || true
source "$_REBUNTU_SOURCES_DIR/execution/_init.sh" 2>/dev/null || true

## Information and observation
source "$_REBUNTU_SOURCES_DIR/information/_init.sh" 2>/dev/null || true

## State management
source "$_REBUNTU_SOURCES_DIR/state/_init.sh" 2>/dev/null || true
source "$_REBUNTU_SOURCES_DIR/configuration/_init.sh" 2>/dev/null || true

## Safety and verification
source "$_REBUNTU_SOURCES_DIR/security/_init.sh" 2>/dev/null || true
source "$_REBUNTU_SOURCES_DIR/verification/_init.sh" 2>/dev/null || true

## Coordination and construction
source "$_REBUNTU_SOURCES_DIR/coordination/_init.sh" 2>/dev/null || true
source "$_REBUNTU_SOURCES_DIR/construction/_init.sh" 2>/dev/null || true

## Admin and requests (loaded last, may depend on others)
source "$_REBUNTU_SOURCES_DIR/administration/_init.sh" 2>/dev/null || true
source "$_REBUNTU_SOURCES_DIR/requests/_init.sh" 2>/dev/null || true

# Export the sources directory for reference
export REBUNTU_SOURCES_DIR="$_REBUNTU_SOURCES_DIR"

return 0