#!/usr/bin/env python3
from pathlib import Path
import json, sys
ROOT=Path(__file__).resolve().parents[2]
report=ROOT/'docs/reports/subtask_structural_closure_xxvi.json'
data=json.loads(report.read_text())
missing=[]
for r in data['records']:
 for k in ('implementation_header','implementation_source','test_target'):
  if not (ROOT/r[k]).is_file(): missing.append((r['source_prompt'],k,r[k]))
 # target manifest beside hpp
 h=ROOT/r['implementation_header']; mf=h.with_suffix('.target.json')
 if not mf.is_file(): missing.append((r['source_prompt'],'target_manifest',str(mf.relative_to(ROOT))))
print('SUBTASKS_EXPECTED',len(data['records']))
print('MISSING_TARGET_ARTIFACTS',len(missing))
if missing:
 for x in missing[:20]: print('MISSING',*x)
 sys.exit(1)
print('SUBTASK_STRUCTURAL_CLOSURE_PASS')
