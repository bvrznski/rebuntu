from pathlib import Path
import hashlib, json, re
root=Path('/mnt/data/rebuntu_xxv/rebuntu_xxiv')
src=root/'src'
exclude={'contracts','model','verification','evidence','assertions','inputs','outputs','errors','invariants','entities','value_objects','identifiers','snapshots','transitions','commands','queries','events','results'}
facets=['identity','state','context','request','result','error','evidence','invariants','lifecycle','validation','integration','telemetry']
cppfacets={'lifecycle','validation','integration'}
created=[]; paired=[]
# candidate dirs: architectural dirs depth 2..5 with direct hpp/cpp or AGENTS/STRUCTURE/README
cands=[]
for d in src.rglob('*'):
    if not d.is_dir(): continue
    rel=d.relative_to(src); depth=len(rel.parts)
    if depth<2 or depth>5 or d.name in exclude: continue
    if any(p.startswith('.') or p in {'build','vendor','third_party','generated'} for p in rel.parts): continue
    direct=list(d.glob('*.hpp'))+list(d.glob('*.cpp'))
    marker=any((d/x).exists() for x in ['AGENTS.md','STRUCTURE.md','README.md','component.hpp','types.hpp'])
    if direct or marker: cands.append(d)
for d in cands:
    rel=d.relative_to(src)
    tag='Skeleton_'+hashlib.sha1(str(rel).encode()).hexdigest()[:10]
    for f in facets:
        hp=d/(f+'.hpp')
        if hp.exists(): continue
        type_name=f'{tag}_{f.title().replace("_","")}'
        hp.write_text(f'''#pragma once\n\n// Structural saturation XXV.\n// Architectural slot only: this file is NOT behavioral implementation evidence.\n// Preserve and implement in place according to the owning phase/subtask ledger.\n\n#include <cstdint>\n\nnamespace rebuntu::structural_slots {{\nstruct {type_name} final {{\n    static constexpr std::uint32_t structural_revision = 25;\n}};\n}} // namespace rebuntu::structural_slots\n''')
        created.append(str(hp.relative_to(root)))
        if f in cppfacets:
            cp=d/(f+'.cpp')
            if not cp.exists():
                inc=hp.relative_to(src).as_posix()
                cp.write_text(f'''#include "{inc}"\n\n// Structural translation-unit slot only. No maturity credit.\nnamespace rebuntu::structural_slots {{\nstatic_assert({type_name}::structural_revision == 25);\n}}\n''')
                paired.append(str(cp.relative_to(root)))
report={'pass':'XXV','candidate_directories':len(cands),'headers_created':len(created),'cpp_created':len(paired),'headers':created,'cpp':paired}
(root/'docs/reports').mkdir(parents=True,exist_ok=True)
(root/'docs/reports/structural_saturation_xxv.json').write_text(json.dumps(report,indent=2))
(root/'docs/reports/structural_saturation_xxv.md').write_text(f'''# Structural Saturation XXV\n\nThis pass intentionally materializes architectural implementation slots. It does **not** count as behavioral implementation.\n\n- Candidate architectural directories: {len(cands)}\n- New `.hpp` slots: {len(created)}\n- New `.cpp` slots: {len(paired)}\n- Preservation rule: generated slots are intentional architecture and must not be deleted merely because they are skeletal or currently unused.\n\nFacets materialized where absent: `{', '.join(facets)}`.\n''')
print(json.dumps({k:v for k,v in report.items() if k not in ('headers','cpp')},indent=2))
