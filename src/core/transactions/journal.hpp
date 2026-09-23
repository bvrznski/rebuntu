#pragma once
#include <chrono>
#include <stdexcept>
#include <string>
#include <vector>
namespace rebuntu::core::transactions {
enum class Stage{prepared,executing,verifying,committed,rolling_back,rolled_back,replanning,failed};
struct Entry{Stage stage; std::string detail; std::chrono::system_clock::time_point at{std::chrono::system_clock::now()};};
class Journal {
 Stage stage_{Stage::prepared}; std::vector<Entry> entries_{{Stage::prepared,"prepared"}};
 static bool terminal(Stage s){return s==Stage::committed||s==Stage::rolled_back||s==Stage::failed;}
 static bool allowed(Stage a,Stage b){
  switch(a){
   case Stage::prepared:return b==Stage::executing||b==Stage::replanning||b==Stage::committed||b==Stage::failed;
   case Stage::executing:return b==Stage::verifying||b==Stage::rolling_back||b==Stage::replanning||b==Stage::failed;
   case Stage::verifying:return b==Stage::committed||b==Stage::rolling_back||b==Stage::replanning||b==Stage::failed;
   case Stage::replanning:return b==Stage::executing||b==Stage::rolling_back||b==Stage::failed;
   case Stage::rolling_back:return b==Stage::rolled_back||b==Stage::failed;
   default:return false;
  }
 }
public:
 Stage stage()const noexcept{return stage_;} const std::vector<Entry>& entries()const noexcept{return entries_;}
 void advance(Stage next,std::string detail){if(terminal(stage_))throw std::logic_error("terminal transaction");if(!allowed(stage_,next))throw std::logic_error("invalid transaction transition");stage_=next;entries_.push_back({next,std::move(detail)});}
 bool committed()const noexcept{return stage_==Stage::committed;} bool recovered()const noexcept{return stage_==Stage::rolled_back;}
};
}
