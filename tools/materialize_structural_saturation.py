#!/usr/bin/env python3
from pathlib import Path
import json, re
ROOT=Path(__file__).resolve().parents[1]
SRC=ROOT/'src'

TREES={
'adapters': {
 'dbus':['connection','object_path','interface','method_call','signal','property','error_mapping','timeouts','cancellation'],
 'netlink':['socket','message','attributes','route','link','address','neighbor','error_mapping','sequence'],
 'udev':['context','device','enumeration','monitor','properties','events','error_mapping'],
 'procfs':['process','memory','cpu','mounts','pressure','network','parsing','identity_tokens'],
 'sysfs':['devices','class','block','network','power','thermal','attributes','parsing'],
 'systemd':['manager','units','jobs','properties','signals','transient_units','error_mapping'],
 'network_manager':['connection','device','profile','state','signals','properties','error_mapping'],
 'package_managers':['apt','dpkg','snap','flatpak','capability_detection','transaction_mapping','error_mapping'],
 'polkit':['subject','action','details','decision','challenge','error_mapping'],
 'nftables':['ruleset','table','chain','rule','set','transaction','error_mapping'],
 'mount':['request','flags','namespace','result','error_mapping'],
 'cgroups':['hierarchy','controller','group','limits','statistics','events','error_mapping'],
 'namespaces':['mount','network','pid','user','ipc','uts','identity','error_mapping'],
 'devices':['identity','properties','capabilities','health','events','error_mapping'],
},
'core': {
 'identity':['stable_id','native_id','generation','scope','alias','resolver'],
 'evidence':['record','source','provenance','freshness','binding','chain','validation'],
 'state':['observed','desired','effective','snapshot','delta','generation','transition'],
 'transactions':['intent','operation','checkpoint','commit','rollback','compensation','journal'],
 'verification':['predicate','postcondition','probe','result','evidence_binding','failure'],
 'errors':['category','code','context','cause','retriability','redaction'],
 'time':['monotonic','wall_clock','deadline','lease','freshness','duration'],
 'contracts':['invariant','precondition','postcondition','constraint','violation'],
 'result':['status','value','error','diagnostic','evidence'],
},
'governance': {
 'architecture_audit':['inventory','ownership','reachability','duplication','boundary','report'],
 'invariant_audit':['catalog','probe','evaluation','violation','report'],
 'compatibility':['contract','matrix','assessment','exception','report'],
 'deprecation':['notice','window','migration_path','usage_scan','retirement'],
 'migration':['plan','step','caller_map','verification','rollback','closure'],
 'ownership':['claims','identity','manifest','validation','conflict','transfer'],
 'native_authority':['catalog','boundary','provider_map','violation','audit'],
 'phase_traceability':['requirement','source_prompt','implementation','evidence','gap','coverage'],
 'build_reachability':['target','source','dependency','entrypoint','orphan','report'],
 'test_governance':['suite','coverage','host_safety','evidence','flakiness','report'],
},
'interfaces': {
 'operator':['request','response','session','notification','confirmation','error'],
 'automation':['trigger','request','response','status','cancellation','error'],
 'planning':['goal','constraint','plan','step','assessment','error'],
 'control':['intent','operation','transaction','verification','recovery','error'],
 'observation':['query','snapshot','subscription','event','evidence','error'],
 'security':['principal','authorization','policy_decision','credential_reference','audit','error'],
 'distributed':['node','lease','coordination','placement','failure','error'],
 'provider':['capability','request','result','native_identity','generation','error'],
},
'portability': {
 'platform_detection':['kernel','distribution','init_system','architecture','container','virtualization','capabilities'],
 'capabilities':['discovery','requirements','constraints','matching','evidence','degradation'],
 'provider_selection':['candidate','score_inputs','compatibility','selection','fallback','evidence'],
 'feature_negotiation':['offer','requirement','agreement','degradation','failure'],
 'compatibility':['platform','provider','schema','version','matrix','assessment'],
 'degradation':['mode','reason','impact','fallback','operator_notice','recovery'],
 'install':['prerequisite','package','service','configuration','verification','rollback'],
 'setup':['profile','native','configuration','validation','verification','recovery'],
 'migration':['source','target','assessment','plan','translation','verification','rollback'],
},
'system': {
 'runtime':['bootstrap','shutdown','health','readiness','liveness','identity','diagnostics'],
 'environment':['identity','profile','facts','constraints','capabilities','drift','validation'],
 'state':['snapshot','history','persistence','transitions','recovery','consistency'],
 'units':['identity','dependency','lifecycle','health','desired_state','observation'],
 'shell':['boundary','invocation','environment','result','redaction','policy','audit'],
 'composition':['component','dependency','binding','lifecycle','health','graph'],
 'startup':['stage','dependency','probe','failure','rollback','report'],
 'shutdown':['stage','drain','checkpoint','failure','recovery','report'],
 'diagnostics':['probe','snapshot','bundle','redaction','report','export'],
},
}

HEADER='''#pragma once\n\n#include <string_view>\n\nnamespace rebuntu::skeleton::{ns} {{\nstruct {tag} final {{\n    static constexpr std::string_view path = "{path}";\n    static constexpr bool behavioral_implementation = false;\n}};\n}}  // namespace rebuntu::skeleton::{ns}\n'''
AGENTS='''# Structural Skeleton Boundary\n\nThis directory is structural scaffolding only. It is **not behavioral implementation evidence**.\n\nRules:\n- Preserve Rebuntu's Native Authority contract; do not reimplement Linux mechanisms here.\n- Add behavior only in the canonical owning subsystem and wire it into real callers.\n- Thin adapter/provider leaves translate typed Rebuntu contracts to native authorities.\n- A skeleton may define vocabulary and placement, but cannot raise implementation depth by itself.\n- Before adding behavior, reconcile the owning phase prompts and update the relevant aggregate TASK ledger.\n'''

CPP_KEYWORDS={'alignas','alignof','and','and_eq','asm','atomic_cancel','atomic_commit','atomic_noexcept','auto','bitand','bitor','bool','break','case','catch','char','char8_t','char16_t','char32_t','class','compl','concept','const','consteval','constexpr','constinit','const_cast','continue','co_await','co_return','co_yield','decltype','default','delete','do','double','dynamic_cast','else','enum','explicit','export','extern','false','float','for','friend','goto','if','inline','int','long','mutable','namespace','new','noexcept','not','not_eq','nullptr','operator','or','or_eq','private','protected','public','reflexpr','register','reinterpret_cast','requires','return','short','signed','sizeof','static','static_assert','static_cast','struct','switch','synchronized','template','this','thread_local','throw','true','try','typedef','typeid','typename','union','unsigned','using','virtual','void','volatile','wchar_t','while','xor','xor_eq'}
def ident(s):
    s=re.sub(r'[^a-zA-Z0-9]+','_',s).strip('_')
    if not s: s='node'
    if s[0].isdigit(): s='n_'+s
    if s in CPP_KEYWORDS: s=s+'_node'
    return s

def camel(s):
    return ''.join(x.capitalize() for x in ident(s).split('_'))+'Skeleton'

created_dirs=[]; created_headers=[]; created_agents=[]
for top, branches in TREES.items():
    topdir=SRC/top; topdir.mkdir(parents=True,exist_ok=True)
    for branch, leaves in branches.items():
        b=topdir/branch; b.mkdir(parents=True,exist_ok=True)
        for leaf in leaves:
            d=b/leaf; existed=d.exists(); d.mkdir(parents=True,exist_ok=True)
            if not existed: created_dirs.append(str(d.relative_to(ROOT)))
            a=d/'AGENTS.md'
            if not a.exists(): a.write_text(AGENTS); created_agents.append(str(a.relative_to(ROOT)))
            h=d/'types.hpp'
            if True:
                rel=str(d.relative_to(ROOT))
                ns='::'.join(ident(x) for x in d.relative_to(SRC).parts)
                h.write_text(HEADER.format(ns=ns,tag=camel(leaf),path=rel))
                created_headers.append(str(h.relative_to(ROOT)))

inventory={
 'pass':'XXII structural oversaturation',
 'policy':'structural-only; no maturity credit without behavior',
 'created_directories':created_dirs,
 'created_headers':created_headers,
 'created_agents':created_agents,
 'counts':{'directories':len(created_dirs),'headers':len(created_headers),'agents':len(created_agents)}
}
(ROOT/'docs/reports/structural_saturation_xxii.json').write_text(json.dumps(inventory,indent=2)+'\n')
print(json.dumps(inventory['counts']))

# Deep structural facets deliberately make ownership/contract/evidence placement explicit.
# They remain skeleton-only and therefore carry zero behavioral maturity credit.
FACETS=[
 ('contracts','inputs'),('contracts','outputs'),('contracts','errors'),('contracts','invariants'),
 ('model','entities'),('model','value_objects'),
 ('verification','evidence'),('verification','assertions'),
]
deep_dirs=[]; deep_headers=[]; deep_agents=[]
for top, branches in TREES.items():
    for branch, leaves in branches.items():
        for leaf in leaves:
            base=SRC/top/branch/leaf
            for group,name in FACETS:
                d=base/group/name
                existed=d.exists(); d.mkdir(parents=True,exist_ok=True)
                if not existed: deep_dirs.append(str(d.relative_to(ROOT)))
                a=d/'AGENTS.md'
                if not a.exists(): a.write_text(AGENTS); deep_agents.append(str(a.relative_to(ROOT)))
                h=d/'types.hpp'
                if True:
                    rel=str(d.relative_to(ROOT))
                    ns='::'.join(ident(x) for x in d.relative_to(SRC).parts)
                    h.write_text(HEADER.format(ns=ns,tag=camel(name),path=rel))
                    deep_headers.append(str(h.relative_to(ROOT)))
inventory['deep_facets']={'directories':deep_dirs,'headers':deep_headers,'agents':deep_agents}
inventory['counts']['deep_directories']=len(deep_dirs)
inventory['counts']['deep_headers']=len(deep_headers)
inventory['counts']['deep_agents']=len(deep_agents)
(ROOT/'docs/reports/structural_saturation_xxii.json').write_text(json.dumps(inventory,indent=2)+'\n')
print(json.dumps(inventory['counts']))
