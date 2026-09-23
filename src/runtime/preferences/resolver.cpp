#include "resolver.hpp"
#include <algorithm>
namespace rebuntu::runtime::preferences {
PreferenceResolution resolve(const std::vector<PreferenceLayer>& layers,const std::vector<std::string>& available,const std::optional<std::string>& fallback,const std::vector<std::string>& forbidden){
 PreferenceResolution r; const PreferenceLayer* best=nullptr; for(const auto& l:layers) if(l.value && (!best||l.precedence>best->precedence)) best=&l;
 if(!best){r.explanation="no preference configured"; return r;} r.requested=best->value; r.source=best->source;
 auto allowed=[&](const std::string& v){return std::find(forbidden.begin(),forbidden.end(),v)==forbidden.end();};
 auto present=[&](const std::string& v){return std::find(available.begin(),available.end(),v)!=available.end();};
 if(allowed(*best->value)&&present(*best->value)){r.effective=best->value;r.satisfied=true;r.explanation="preferred value available";return r;}
 if(fallback&&allowed(*fallback)&&present(*fallback)){r.effective=fallback;r.explanation=allowed(*best->value)?"preferred value unavailable; explicit fallback selected":"preferred value forbidden by policy; explicit fallback selected";return r;}
 r.explanation=allowed(*best->value)?"preferred value unavailable and no usable fallback":"preferred value forbidden by policy and no usable fallback"; return r;
}
}
