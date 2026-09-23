#!/usr/bin/env python3
from pathlib import Path
import sys
ROOT=Path(__file__).resolve().parents[2]
PH=ROOT/'.phases'
errors=[]
contract=PH/'EXECUTION_CONTRACT.md'; agents=PH/'AGENTS.md'
tasks=sorted((PH/'phases').glob('phase-*/TASK.md'))
if not contract.is_file(): errors.append('missing .phases/EXECUTION_CONTRACT.md')
if not agents.is_file(): errors.append('missing .phases/AGENTS.md')
else:
    a=agents.read_text(errors='replace')
    for token in ('EXECUTION_CONTRACT.md','executable complete-phase entrypoint'):
        if token not in a: errors.append(f'AGENTS.md missing contract token: {token}')
if len(tasks)!=107: errors.append(f'expected 107 TASK.md files, found {len(tasks)}')
for p in tasks:
    s=p.read_text(errors='replace')
    for label,tok in {
      'contract hook':'PHASE_EXECUTION_CONTRACT:',
      'contract target':'.phases/EXECUTION_CONTRACT.md',
      'complete mode':'EXECUTION_MODE:** `complete-phase`',
      'all scope':'every source prompt/subtask belonging to this phase',
      'evidence completion':'evidence-based, per-subtask',
    }.items():
        if tok not in s: errors.append(f'{p.relative_to(ROOT)}: missing {label}')
    if s.count('PHASE_EXECUTION_CONTRACT:') != 1: errors.append(f'{p.relative_to(ROOT)}: hook count != 1')
prompt_files=[]
for phase in sorted((PH/'phases').glob('phase-*')):
    pr=phase/'prompts'
    if pr.is_dir(): prompt_files.extend(pr.rglob('*.md'))
print(f'PHASE_TASKS: {len(tasks)}/107')
print(f'PROMPT_MARKDOWN_DISCOVERED: {len(prompt_files)}')
print(f'CONTRACT_HOOKED_TASKS: {sum("PHASE_EXECUTION_CONTRACT:" in p.read_text(errors="replace") for p in tasks)}/{len(tasks)}')
if errors:
    print('PHASE_EXECUTION_CONTRACT_VALIDATION_FAIL')
    for e in errors: print('ERROR:',e)
    sys.exit(1)
print('PHASE_EXECUTION_CONTRACT_VALIDATION_PASS')
