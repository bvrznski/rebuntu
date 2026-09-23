// rebuntu::install::forms - Tests (Phase 1.3)

#include <system/install/forms.hpp>

#include <cassert>
#include <iostream>

namespace rebuntu::install::forms {
namespace {

void test_interactive_input_channel() {
    InteractiveInputChannel channel;
    channel.set_value("version", "1.0.0");
    assert(channel.has_field("version"));
}

void test_config_file_channel() {
    std::map<std::string, std::string> config = {
        {"registration", "true"}
    };
    ConfigFileChannel channel(std::move(config));
    assert(channel.has_field("registration"));
}

void test_form_builder() {
    auto form = FormBuilder::create("installation", "Installation Form")
        .add_string_field("version", "Version", "Target version")
        .build();
    assert(form.name == "installation");
    assert(form.fields.size() == 1);
    assert(form.fields[0].type == FieldType::kString);
}

void test_installation_form_factory() {
    auto intent_form = InstallationFormFactory::create_installation_intent_form();
    assert(intent_form.name == "installation_intent");
    assert(intent_form.fields.size() == 3);
}

}  // namespace
}  // namespace rebuntu::install::forms

int main() {
    using namespace rebuntu::install::forms;
    test_interactive_input_channel();
    test_config_file_channel();
    test_form_builder();
    test_installation_form_factory();
    std::cout << "All tests passed" << std::endl;
    return 0;
}
