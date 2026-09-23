#!/usr/bin/env python3
from pathlib import Path
import json,re,sys
ROOT=Path(__file__).resolve().parents[2]; phases=ROOT/'.phases/phases'
expected=0; manifests=[]; errors=[]; hooks=0
for task in sorted(phases.glob('phase-*/TASK.md')):
 txt=task.read_text(errors='ignore'); prompts=list((task.parent/'prompts').glob('*.md')) if (task.parent/'prompts').exists() else []
 expected+=len(prompts); hooks+=txt.count('- **Structural package:**')
for m in ROOT.glob('src/**/subtask_packages/**/PACKAGE.json'):
 manifests.append(m)
 try: d=json.loads(m.read_text())
 except Exception as e: errors.append(f'{m}: json {e}'); continue
 for a in ('contract','model','state','errors','evidence','verification','integration'):
  if a not in d.get('aspects',[]): errors.append(f'{m}: missing mandatory aspect {a}')
 for f in d.get('files',[]):
  if not (ROOT/f).exists(): errors.append(f'{m}: missing {f}')
 if d.get('behavioral_credit') is not False: errors.append(f'{m}: behavioral_credit must be false')
print('SUBTASKS_EXPECTED',expected); print('PACKAGE_MANIFESTS',len(manifests)); print('TASK_PACKAGE_HOOKS',hooks); print('VALIDATION_ERRORS',len(errors))
if errors:
 print('\n'.join(errors[:30])); sys.exit(1)
if len(manifests)!=expected or hooks!=expected: sys.exit(2)
print('XXVII_SUBTASK_PACKAGE_CLOSURE_PASS')
