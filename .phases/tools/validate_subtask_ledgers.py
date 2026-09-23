#!/usr/bin/env python3
from pathlib import Path
import sys
PH=Path(__file__).resolve().parents[1]
errors=[]; prompts=0; entries=0
for phase in sorted((PH/'phases').glob('phase-*')):
    task=phase/'TASK.md'; pr=phase/'prompts'
    if not task.exists(): errors.append(f'{phase.name}: missing TASK.md'); continue
    s=task.read_text(errors='replace')
    files=sorted(pr.rglob('*.md')) if pr.is_dir() else []
    prompts += len(files)
    if '## Subtask Coverage Ledger' not in s: errors.append(f'{phase.name}: missing ledger')
    for p in files:
        token=f'- **Source:** `{p.relative_to(PH.parent)}`'
        n=s.count(token); entries += n
        if n!=1: errors.append(f'{phase.name}: {p.name} ledger mapping count {n}')
print(f'SUBTASK_PROMPTS_DISCOVERED: {prompts}')
print(f'SUBTASK_LEDGER_SOURCE_MAPPINGS: {entries}')
if errors:
    print('SUBTASK_LEDGER_VALIDATION_FAIL')
    for e in errors[:100]: print('ERROR:',e)
    sys.exit(1)
print('SUBTASK_LEDGER_VALIDATION_PASS')
