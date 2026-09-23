#pragma once
#include <cstdint>
#include <deque>
#include <optional>
#include <string>
#include <unordered_map>
#include <vector>

namespace rebuntu::operator_ui::gui {
enum class Risk { read_only, reversible, destructive };
enum class ActionState { proposed, awaiting_confirmation, authorized, dispatched, succeeded, failed, cancelled };
struct Evidence { std::string source; std::string summary; std::uint64_t generation{}; };
struct Action {
 std::string id, label, intent, target, provider; Risk risk{Risk::read_only}; ActionState state{ActionState::proposed};
 bool policy_allowed{false}; bool confirmed{false}; std::vector<Evidence> evidence;
};
struct ViewState { std::string route{"home"}; std::optional<std::string> selected; std::string query; bool busy{false}; };
struct Notification { std::string id, message; bool error{false}; };
class GuiRuntime final {
public:
 bool register_action(Action action);
 [[nodiscard]] const Action* action(const std::string& id) const noexcept;
 [[nodiscard]] bool request_execution(const std::string& id);
 [[nodiscard]] bool confirm(const std::string& id);
 [[nodiscard]] bool mark_dispatched(const std::string& id);
 [[nodiscard]] bool complete(const std::string& id, bool success, Evidence evidence);
 [[nodiscard]] bool cancel(const std::string& id);
 [[nodiscard]] bool navigate(std::string route);
 [[nodiscard]] bool select(std::string id);
 void set_query(std::string query);
 void notify(Notification n);
 [[nodiscard]] const ViewState& view() const noexcept { return view_; }
 [[nodiscard]] const std::deque<Notification>& notifications() const noexcept { return notifications_; }
 [[nodiscard]] std::vector<std::string> searchable_actions() const;
private:
 std::unordered_map<std::string,Action> actions_; ViewState view_; std::deque<Notification> notifications_;
};
} // namespace rebuntu::operator_ui::gui
