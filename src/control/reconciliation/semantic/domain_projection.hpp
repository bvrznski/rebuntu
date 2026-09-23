#pragma once
#include "../pipeline/pipeline.hpp"
#include "../../../domains/common/model.hpp"
#include <functional>
namespace rebuntu::control::reconciliation::semantic {
using Projector = std::function<domains::common::DomainModel(const core::Entity&)>;
class SemanticObserver final : public pipeline::Observer {
  pipeline::Observer& inner_; Projector projector_; std::optional<domains::common::DomainModel> last_;
public:
  SemanticObserver(pipeline::Observer& inner, Projector projector):inner_(inner),projector_(std::move(projector)){}
  std::optional<pipeline::Observation> observe(const std::string& id) override { auto o=inner_.observe(id); if(!o){last_.reset(); return std::nullopt;} last_=projector_(o->entity); return o; }
  const std::optional<domains::common::DomainModel>& last_model() const noexcept { return last_; }
};
}
