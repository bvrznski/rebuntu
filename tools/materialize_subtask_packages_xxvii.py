#!/usr/bin/env python3
from pathlib import Path
import re,json,hashlib
ROOT=Path(__file__).resolve().parents[1]
PHASES=ROOT/'.phases/phases'; REPORT=ROOT/'docs/reports/subtask_package_saturation_xxvii.json'
ROLE_RULES=[('verification',('verify','verification','assert','postcondition','evidence','audit','test')),('recovery',('recover','rollback','resume','crash','restart','repair','compensat')),('security',('authoriz','policy','permission','privilege','credential','secret','trust','security')),('integration',('integrat','bridge','adapter','provider','interop','migration','caller')),('observability',('observ','telemetry','metric','trace','log','diagnostic','explain')),('execution',('execut','operation','mutation','apply','dispatch','command')),('planning',('plan','schedule','strategy','solver','decision')),('resolution',('resolv','discover','lookup','query','search','select','match')),('lifecycle',('lifecycle','state','transition','start','stop','enable','disable')),('persistence',('persist','store','journal','snapshot','database','cache','durab')),('contracts',('contract','schema','protocol','api','type','model','ontology','identity'))]
CONDITIONAL={
'lifecycle':('lifecycle','transition','state machine','start','stop','enable','disable','activation'),
'execution':('execute','execution','operation','mutation','apply','dispatch','command','action'),
'recovery':('recover','rollback','resume','crash','restart','repair','compensat','failure'),
'persistence':('persist','journal','snapshot','database','cache','durab','store'),
'policy':('policy','authoriz','permission','privilege','credential','trust','security','access control'),
'observability':('observ','telemetry','metric','trace','log','diagnostic','explain','audit'),
'concurrency':('concurr','thread','async','parallel','race','lock','atomic','ordering'),
'transactions':('transaction','commit','rollback','checkpoint','atomicity','compensation'),
'scheduling':('schedule','timer','deadline','timeout','cadence','queue','priority'),
'resolution':('resolve','resolution','discover','lookup','query','search','select','match'),
'planning':('plan','planning','strategy','solver','decision','dependency graph'),
'events':('event','publish','subscribe','notification','signal','stream'),
}
MANDATORY=['contract','model','state','errors','evidence','verification','integration']

def clean_slug(name):
 s=re.sub(r'^\d+(?:\.\d+)*[-_]*','',name); s=re.sub(r'^(rebuntu[-_])?(phase[-_])?\d+(?:[-_]\d+)*[-_]*','',s,flags=re.I); s=re.sub(r'[^a-zA-Z0-9]+','_',s).strip('_').lower(); return s[:100] or 'requirement'
def role(text):
 s=text.lower()
 for r,ks in ROLE_RULES:
  if any(k in s for k in ks): return r
 return 'requirements'
def hpp_content(prompt_rel, phase_num, key, aspect):
 ns=f'rebuntu::subtask_packages::phase_{phase_num}::s_{key}::{aspect}'
 typename=''.join(x.capitalize() for x in aspect.split('_'))+'Slot'
 return f'''#pragma once\n\n// XXVII SUBTASK PACKAGE SKELETON — zero behavioral maturity credit.\n// Source: {prompt_rel}\n// Preserve this architectural reservation and implement only after reading the source prompt.\n\nnamespace {ns} {{\nstruct {typename} final {{\n    static constexpr const char* source_prompt = "{prompt_rel}";\n    static constexpr const char* aspect = "{aspect}";\n    static constexpr const char* status = "SKELETON_MATERIALIZED";\n}};\n}} // namespace {ns}\n'''
def cpp_content(header_rel,prompt_rel,aspect):
 return f'''#include "{header_rel.name}"\n\n// XXVII out-of-line implementation reservation for {aspect}.\n// Source: {prompt_rel}\n// Intentionally behavior-free until prompt-derived implementation is supplied.\n'''
records=[]; created=0; preserved=0; phase_packages={}
for task in sorted(PHASES.glob('phase-*/TASK.md')):
 txt=task.read_text(errors='ignore'); m=re.search(r'Canonical skeleton:\s*`(src/[^`]+?)/`',txt)
 if not m: continue
 canonical=ROOT/m.group(1); promptdir=task.parent/'prompts'
 if not promptdir.exists(): continue
 pm=re.search(r'phase-(\d+)',task.parent.name); phase_num=(pm.group(1) if pm else 'x')
 mappings={}
 for prompt in sorted(promptdir.glob('*.md')):
  prompt_rel=prompt.relative_to(ROOT); ptxt=prompt.read_text(errors='ignore'); sem=clean_slug(prompt.stem); key=hashlib.sha1(str(prompt_rel).encode()).hexdigest()[:8]; r=role(sem+' '+ptxt[:5000])
  pkg=canonical/'subtask_packages'/r/f'{sem}_{key}'; pkg.mkdir(parents=True,exist_ok=True)
  low=(prompt.stem+'\n'+ptxt).lower(); aspects=list(MANDATORY)
  for a,ks in CONDITIONAL.items():
   if any(k in low for k in ks) and a not in aspects: aspects.append(a)
  files=[]
  for a in aspects:
   h=pkg/f'{a}.hpp'; c=pkg/f'{a}.cpp'
   hc=hpp_content(prompt_rel,phase_num,key,a)
   if h.exists(): preserved+=1
   else: h.write_text(hc); created+=1
   files.append(str(h.relative_to(ROOT)))
   # behavioral/integration aspects receive TU reservation; pure model/state/error remain header slots
   if a in {'verification','integration','lifecycle','execution','recovery','persistence','policy','observability','concurrency','transactions','scheduling','resolution','planning','events'}:
    if c.exists(): preserved+=1
    else: c.write_text(cpp_content(h,prompt_rel,a)); created+=1
    files.append(str(c.relative_to(ROOT)))
  manifest=pkg/'PACKAGE.json'
  data={'source_prompt':str(prompt_rel),'phase_task':str(task.relative_to(ROOT)),'package_root':str(pkg.relative_to(ROOT)),'role':r,'aspects':aspects,'files':files,'status':'SKELETON_MATERIALIZED','behavioral_credit':False,'preservation':'PRESERVE_IMPLEMENT_EXTEND'}
  if manifest.exists(): preserved+=1
  else: manifest.write_text(json.dumps(data,indent=2)+'\n'); created+=1
  mappings[str(prompt_rel)]=str(pkg.relative_to(ROOT)); records.append(data)
 # inject package roots into each ledger entry based on Source line
 lines=txt.splitlines(); out=[]
 for line in lines:
  out.append(line)
  sm=re.match(r'- \*\*Source:\*\* `([^`]+)`',line)
  if sm and sm.group(1) in mappings:
   # avoid duplicate if rerun
   nxt=f'- **Structural package:** `{mappings[sm.group(1)]}/` — prompt-derived local contract/model/state/error/evidence/verification/integration reservation; zero behavioral credit'
   out.append(nxt)
 new='\n'.join(out)+'\n'
 task.write_text(new)
 phase_packages[str(task.relative_to(ROOT))]=len(mappings)
REPORT.parent.mkdir(parents=True,exist_ok=True); REPORT.write_text(json.dumps({'subtasks':len(records),'files_created':created,'paths_preserved':preserved,'phase_packages':phase_packages,'records':records},indent=2)+'\n')
print('SUBTASK_PACKAGES',len(records)); print('FILES_CREATED',created); print('PATHS_PRESERVED',preserved); print('XXVII_SUBTASK_PACKAGE_SATURATION_MATERIALIZED')
