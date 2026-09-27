// rebuntu::shell::output - Unit Tests (Phase 6.11)
#include <gtest/gtest.h>
#include "../src/system/shell/output/contract.hpp"

using namespace rebuntu::shell;

// Test RenderMode enum values
TEST(RenderModeTest, EnumValues) {
    EXPECT_EQ(to_string(RenderMode::AUTO), "auto");
    EXPECT_EQ(to_string(RenderMode::HUMAN), "human");
    EXPECT_EQ(to_string(RenderMode::STRUCTURED), "structured");
    EXPECT_EQ(to_string(RenderMode::SILENT), "silent");
}

// Test OutputContext default values
TEST(OutputContextTest, DefaultValues) {
    OutputContext ctx;
    EXPECT_EQ(ctx.mode, RenderMode::AUTO);
    EXPECT_TRUE(ctx.color_enabled);
    EXPECT_EQ(ctx.max_width, 80);
    EXPECT_FALSE(ctx.include_timestamps);
    EXPECT_FALSE(ctx.compact);
}

// Test StructuredResult default values
TEST(StructuredResultTest, DefaultValues) {
    StructuredResult result;
    EXPECT_EQ(result.status, SemanticStatus::kUnknown);
    EXPECT_FALSE(result.is_true.has_value());
    EXPECT_TRUE(result.command_id.empty());
    EXPECT_TRUE(result.verb.empty());
    EXPECT_FALSE(result.changed);
    EXPECT_FALSE(result.verified);
    EXPECT_EQ(result.elapsed_ms, 0);
    EXPECT_TRUE(result.evidence.empty());
    EXPECT_FALSE(result.error.has_value());
    EXPECT_TRUE(result.warnings.empty());
    EXPECT_FALSE(result.output_value.has_value());
    EXPECT_FALSE(result.exit_code.has_value());
}

// Test StructuredResult to_json() with all fields
TEST(StructuredResultTest, ToJsonComplete) {
    StructuredResult result;
    result.command_id = "test-123";
    result.verb = "install";
    result.subject_type = "package";
    result.target = "foo";
    result.changed = true;
    result.verified = true;
    result.elapsed_ms = 1500;
    
    std::string json = result.to_json();
    EXPECT_NE(json.find("\"command_id\""), std::string::npos);
    EXPECT_NE(json.find("\"verb\""), std::string::npos);
    EXPECT_NE(json.find("\"schema_version\""), std::string::npos);
}

// Test StructuredResult to_json() with empty fields
TEST(StructuredResultTest, ToJsonMinimal) {
    StructuredResult result;
    std::string json = result.to_json();
    EXPECT_NE(json.find("\"status\": \"unknown\""), std::string::npos);
    EXPECT_NE(json.find("\"is_true\": null"), std::string::npos);
}

// Test RenderedOutput factory methods
TEST(RenderedOutputTest, FactoryMethods) {
    auto success = RenderedOutput::success("output", true);
    EXPECT_EQ(success.text, "output");
    EXPECT_TRUE(success.is_structured);
    EXPECT_EQ(success.exit_code, 0);
    
    auto failure = RenderedOutput::failure("error", 1);
    EXPECT_EQ(failure.text, "error");
    EXPECT_FALSE(failure.is_structured);
    EXPECT_EQ(failure.exit_code, 1);
}

// Test HumanRenderer status formatting
TEST(HumanRendererTest, StatusFormatting) {
    HumanRenderer renderer;
    EXPECT_EQ(renderer.format_status(SemanticStatus::kSuccess), "success");
    EXPECT_EQ(renderer.format_status(SemanticStatus::kCompleted), "completed");
    EXPECT_EQ(renderer.format_status(SemanticStatus::kFailure), "failure");
    EXPECT_EQ(renderer.format_status(SemanticStatus::kUnknown), "unknown");
    EXPECT_EQ(renderer.format_status(SemanticStatus::kCancelled), "cancelled");
}

// Test JSONRenderer produces structured output
TEST(JSONRendererTest, ProducesStructuredOutput) {
    JSONRenderer renderer;
    StructuredResult result;
    result.command_id = "test";
    
    auto output = renderer.render(result, OutputContext{});
    EXPECT_TRUE(output.is_structured);
    EXPECT_EQ(output.exit_code, 0);
}

// Test CollectionRenderer adds results
TEST(CollectionRendererTest, AddResults) {
    CollectionRenderer renderer;
    StructuredResult r1, r2;
    r1.command_id = "r1";
    r2.command_id = "r2";
    
    renderer.add_result(std::move(r1));
    renderer.add_result(std::move(r2));
    
    auto output = renderer.render(OutputContext{});
    EXPECT_TRUE(output.is_structured);
}

// Test RenderedOutput JSON escaping
TEST(RenderedOutputTest, JsonEscaping) {
    // This test verifies escape_string works properly
    std::string escaped = escape_string("hello \"world\"");
    EXPECT_EQ(escaped, "hello \\\"world\\\"");
    
    std::string escaped2 = escape_string("line1\nline2");
    EXPECT_NE(escaped2.find("\\n"), std::string::npos);
}