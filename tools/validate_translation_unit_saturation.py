#!/usr/bin/env python3
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]; SRC=ROOT/'src'; marker='behavioral_implementation = false'
headers=[]; missing=[]; empty=[]
for h in sorted(SRC.rglob('types.hpp')):
    try: t=h.read_text()
    except UnicodeDecodeError: continue
    if marker not in t or 'namespace rebuntu::skeleton::' not in t: continue
    headers.append(h)
    c=h.with_suffix('.cpp')
    if not c.exists(): missing.append(c)
    elif not c.read_text().strip(): empty.append(c)
print(f'STRUCTURAL_SKELETON_HEADERS: {len(headers)}')
print(f'PAIRED_CPP: {len(headers)-len(missing)-len(empty)}')
print(f'MISSING_CPP: {len(missing)}')
print(f'EMPTY_CPP: {len(empty)}')
if missing or empty: raise SystemExit(1)
print('TRANSLATION_UNIT_PAIRING_PASS')
