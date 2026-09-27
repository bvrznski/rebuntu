// rebuntu::system::observation::output unit tests (Phase 5.61)
//
// Tests for machine-readable observation output with schema/versioning.

#include <gtest/gtest.h>
#include <system/observation/output/types.hpp>

TEST(ObservationOutputTest, OutputSchemaDefault) {
    auto schema = rebuntu::system::observation::output::OutputSchema::make_v1();
    
    EXPECT_EQ(schema.name, "observation");
    EXPECT_EQ(schema.version, "1.0.0");
    EXPECT_TRUE(schema.schema_uri.has_value());
    EXPECT_FALSE(schema.schema_uri.value().empty());
}

TEST(ObservationOutputTest, ObservationValueCreation) {
    auto now = std::chrono::system_clock::now();
    
    auto obs = rebuntu::system::observation::output::ObservationValue::make(
        "procfs",
        "/proc/1234/stat",
        now,
        "1234 (bash) R 1000 ..."
    );
    
    EXPECT_EQ(obs.source, "procfs");
    ASSERT_TRUE(obs.path.has_value());
    EXPECT_EQ(obs.path.value(), "/proc/1234/stat");
    EXPECT_EQ(obs.observed_at, now);
    EXPECT_EQ(obs.validation_status, 
              rebuntu::system::observation::output::ObservationValue::ValidationStatus::kValid);
}

TEST(ObservationOutputTest, ObservationRecordCreation) {
    auto record = rebuntu::system::observation::output::ObservationRecord{};
    
    record.id = "service:nginx";
    record.name = "nginx.service";
    record.category = "service";
    record.state = rebuntu::system::observation::output::ObservationRecord::State::kActive;
    record.observed_at = std::chrono::system_clock::now();
    
    // Add an attribute
    record.attributes["description"] = "High performance web server";
    
    EXPECT_EQ(record.id, "service:nginx");
    ASSERT_TRUE(record.name.has_value());
    EXPECT_EQ(record.name.value(), "nginx.service");
    EXPECT_EQ(record.state, rebuntu::system::observation::output::ObservationRecord::State::kActive);
}

TEST(ObservationOutputTest, OutputOptionsDefault) {
    auto options = rebuntu::system::observation::output::OutputOptions{};
    
    EXPECT_EQ(options.format, rebuntu::system::observation::output::OutputFormat::kJSON);
    EXPECT_EQ(options.max_records, 1000u);
    EXPECT_EQ(options.include_statistics, true);
    EXPECT_TRUE(options.schema.name == "observation");
}

TEST(ObservationOutputTest, OutputGeneratorInterface) {
    auto generator = rebuntu::system::observation::output::make_output_generator();
    
    ASSERT_NE(generator, nullptr);
    
    auto options = rebuntu::system::observation::output::OutputOptions{};
    EXPECT_TRUE(generator->configure(options).is_success());
}

TEST(ObservationOutputTest, OutputGeneratorAddRecord) {
    auto generator = rebuntu::system::observation::output::make_output_generator();
    
    auto record = rebuntu::system::observation::output::ObservationRecord{};
    record.id = "test-record";
    record.state = rebuntu::system::observation::output::ObservationRecord::State::kActive;
    
    EXPECT_TRUE(generator->add_record(record).is_success());
}

TEST(ObservationOutputTest, OutputGeneratorGenerateJSON) {
    auto generator = rebuntu::system::observation::output::make_output_generator();
    
    auto options = rebuntu::system::observation::output::OutputOptions{};
    EXPECT_TRUE(generator->configure(options).is_success());
    
    auto record = rebuntu::system::observation::output::ObservationRecord{};
    record.id = "test-record";
    record.name = "Test Service";
    record.state = rebuntu::system::observation::output::ObservationRecord::State::kActive;
    
    EXPECT_TRUE(generator->add_record(record).is_success());
    
    auto output = generator->generate();
    
    // Verify output contains expected JSON structure
    EXPECT_NE(output.find("\"version\""), std::string::npos);
    EXPECT_NE(output.find("\"records\""), std::string::npos);
    EXPECT_NE(output.find("\"test-record\""), std::string::npos);
}