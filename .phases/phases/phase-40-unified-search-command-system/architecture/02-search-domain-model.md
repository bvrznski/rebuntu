# Search Domain Model

Canonical concepts include `SearchQuery`, `QueryAst`, `SearchPlan`, `SearchScope`, `SearchProviderId`, `SearchResult`, `ResultRef`, `EntityRef`, `MatchEvidence`, `SearchFacet`, `SearchCursor`, `SearchSessionId`, freshness and provenance.

A result distinguishes the entity/reference from the observation that caused it to match. Multiple evidence sources may support one entity without being flattened into one source.
