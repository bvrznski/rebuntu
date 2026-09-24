#include <portability/install/forms.hpp>
#include <cassert>
#include <iostream>

using namespace rebuntu::install::forms;

int main() {
  auto form = FormBuilder::create("setup", "Setup")
      .add_enum_field("scope", "Scope", "Install scope", {"user", "system"})
      .add_boolean_field("verify", "Verify", "Verify changes")
      .build();
  
  // Test valid input
  ConfigFileChannel good({{"scope","user"},{"verify","yes"}});
  auto a = FormParser(form).parse(good);
  assert(a.is_valid());
  std::cout << "Valid input test passed\n";
  
  // Test invalid enum value
  ConfigFileChannel bad_enum({{"scope","planet"},{"verify","true"}});
  auto b = FormParser(form).parse(bad_enum);
  assert(!b.is_valid());
  std::cout << "Invalid enum test passed\n";
  
  // Test unknown field detection
  ConfigFileChannel unknown({{"scope","user"},{"verify","true"},{"mystery","x"}});
  auto c = FormParser(form).parse(unknown);
  assert(!c.is_valid());
  std::cout << "Unknown field detection test passed\n";
  
  // Test invalid boolean value
  ConfigFileChannel bad_bool({{"scope","user"},{"verify","maybe"}});
  auto d = FormParser(form).parse(bad_bool);
  assert(!d.is_valid());
  std::cout << "Invalid boolean test passed\n";
  
  std::cout << "All structured setup tests passed\n";
  return 0;
}