#!/usr/bin/env python3
from pathlib import Path
import re, json, hashlib
ROOT=Path(__file__).resolve().parents[1]
PHASES=ROOT/'.phases/phases'
SRC=ROOT/'src'
TESTS=ROOT/'tests/structural-closure'
REPORT=ROOT/'docs/reports/subtask_structural_closure_xxvi.json'
ROLE_RULES=[
 ('verification',('verify','verification','assert','postcondition','evidence','audit','test')),
 ('recovery',('recover','rollback','resume','crash','restart','repair','compensat')),
 ('security',('authoriz','policy','permission','privilege','credential','secret','trust','security')),
 ('integration',('integrat','bridge','adapter','provider','interop','migration','caller')),
 ('observability',('observ','telemetry','metric','trace','log','diagnostic','explain')),
 ('execution',('execut','operation','mutation','apply','dispatch','command')),
 ('planning',('plan','schedule','strategy','solver','decision')),
 ('resolution',('resolv','discover','lookup','query','search','select','match')),
 ('lifecycle',('lifecycle','state','transition','start','stop','enable','disable')),
 ('persistence',('persist','store','journal','snapshot','database','cache','durab')),
 ('contracts',('contract','schema','protocol','api','type','model','ontology','identity')),
]

def role(slug):
 s=slug.lower()
 for r,ks in ROLE_RULES:
  if any(k in s for k in ks): return r
 return 'requirements'

def clean_slug(name):
 s=re.sub(r'^\d+(?:\.\d+)*[-_]*','',name)
 s=re.sub(r'^(rebuntu[-_])?(phase[-_])?\d+(?:[-_]\d+)*[-_]*','',s,flags=re.I)
 s=re.sub(r'[^a-zA-Z0-9]+','_',s).strip('_').lower()
 return s[:110] or 'requirement'

def ns_for(rel):
 parts=['rebuntu']+[re.sub(r'[^a-zA-Z0-9_]','_',p) for p in rel.parts[:-1]]
 keywords={'operator','class','namespace','new','delete','template','concept','requires','private','protected','public','struct','union','enum','using','typedef','typename','this','default','static','inline','virtual','explicit','export','extern','friend','const','volatile','auto','void','int','long','short','signed','unsigned','float','double','char','bool'}
 return '::'.join((p+'_ns' if p in keywords else p) for p in parts if p)

records=[]; created=[]; existing=[]
for task in sorted(PHASES.glob('phase-*/TASK.md')):
 txt=task.read_text(errors='ignore')
 m=re.search(r'Canonical skeleton:\s*`(src/[^`]+?)/`',txt)
 if not m: continue
 canonical=ROOT/m.group(1)
 promptdir=task.parent/'prompts'
 if not promptdir.exists(): continue
 for prompt in sorted(promptdir.glob('*.md')):
  stem=prompt.stem; sem=clean_slug(stem); r=role(sem)
  # collision-proof but readable filename
  key=hashlib.sha1(str(prompt.relative_to(ROOT)).encode()).hexdigest()[:8]
  base=f'{sem}_{key}'
  idir=canonical/'subtask_targets'/r
  hpp=idir/(base+'.hpp'); cpp=idir/(base+'.cpp')
  tdir=TESTS/canonical.relative_to(SRC)/r
  test=tdir/('test_'+base+'.cpp')
  manifest=idir/(base+'.target.json')
  for d in (idir,tdir): d.mkdir(parents=True,exist_ok=True)
  relhpp=hpp.relative_to(ROOT); nspace=ns_for(relhpp)
  guard='REBUNTU_'+re.sub(r'[^A-Z0-9]','_',str(relhpp).upper())
  hcontent=f'''#pragma once\n\n// STRUCTURAL CLOSURE SLOT — no behavioral maturity credit.\n// Source subtask: {prompt.relative_to(ROOT)}\n// Preserve this target and implement it in place after reading the source prompt.\n\nnamespace {nspace} {{\n\nstruct SubtaskTarget_{key} final {{\n    static constexpr const char* source_prompt = "{prompt.relative_to(ROOT)}";\n    static constexpr const char* structural_status = "SKELETON_MATERIALIZED";\n}};\n\n}} // namespace {nspace}\n'''
  ccontent=f'''#include "{hpp.name}"\n\n// STRUCTURAL CLOSURE SLOT — intentionally behavior-free.\n// Implement prompt-derived out-of-line behavior here when applicable.\n'''
  tcontent=f'''// STRUCTURAL TEST TARGET — no test evidence until assertions are implemented and executed.\n// Source subtask: {prompt.relative_to(ROOT)}\n// Intended implementation target: {hpp.relative_to(ROOT)}\nint main() {{ return 0; }}\n'''
  data={"source_prompt":str(prompt.relative_to(ROOT)),"phase_task":str(task.relative_to(ROOT)),"canonical_root":str(canonical.relative_to(ROOT)),"role":r,"implementation_header":str(hpp.relative_to(ROOT)),"implementation_source":str(cpp.relative_to(ROOT)),"test_target":str(test.relative_to(ROOT)),"status":"SKELETON_MATERIALIZED","behavioral_credit":False,"preservation":"PRESERVE_IMPLEMENT_EXTEND"}
  for p,c in ((hpp,hcontent),(cpp,ccontent),(test,tcontent),(manifest,json.dumps(data,indent=2)+"\n")):
   if p.exists(): existing.append(str(p.relative_to(ROOT)))
   else: p.write_text(c); created.append(str(p.relative_to(ROOT)))
  records.append(data)
REPORT.parent.mkdir(parents=True,exist_ok=True); REPORT.write_text(json.dumps({"subtasks":len(records),"created_files":len(created),"existing_paths":len(existing),"records":records},indent=2)+"\n")
print('SUBTASKS_MAPPED',len(records)); print('FILES_CREATED',len(created)); print('EXISTING_PATHS',len(existing)); print('SUBTASK_STRUCTURAL_CLOSURE_MATERIALIZED')
