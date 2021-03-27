#include <stan/services/util/create_param_mask.hpp>
#include <stan/io/var_context.hpp>
#include <gtest/gtest.h>
#include <string>
#include <stan/io/validate_dims.hpp>
#include <vector>


class TestVarContext : public stan::io::var_context {
 public:
  TestVarContext(std::string s) : test_clamp_var(s) {}

  bool contains_i(const std::string& name) const {
    return(test_clamp_var == name ? true : false);
  }
  bool contains_r(const std::string& name) const {
    return(test_clamp_var == name ? true : false);
  }

  std::vector<double> vals_r(const std::string& name) const {
    return std::vector<double>();
  }
  std::vector<size_t> dims_r(const std::string& name) const {
    return std::vector<size_t>();
  }
  std::vector<int> vals_i(const std::string& name) const {
    return std::vector<int>();
  }
  std::vector<size_t> dims_i(const std::string& name) const {
    return std::vector<size_t>();
  }
  void validate_dims(const std::string& stage, const std::string& name,
                     const std::string& base_type,
                     const std::vector<size_t>& dims_declared) const {
    stan::io::validate_dims(*this, stage, name, base_type, dims_declared);
  }
  void names_r(std::vector<std::string>& names) const { names.clear(); }
  void names_i(std::vector<std::string>& names) const { names.clear(); }
 private:
  std::string test_clamp_var;
};


TEST(rng, create_param_mask_works) {
  std::string ss = "["
    "{"
    "    \"name\": \"mat55\","
    "    \"type\": {"
    "        \"name\": \"matrix\","
    "        \"rows\": 1,"
    "        \"cols\": 2"
    "    },"
    "    \"block\": \"parameters\""
    "},"
    "{"
    "    \"name\": \"arr5\","
    "    \"type\": {"
    "        \"name\": \"array\","
    "        \"length\": 2,"
    "        \"element_type\": {"
    "            \"name\": \"real\""
    "        }"
    "    },"
    "    \"block\": \"parameters\""
    "},"
    "{"
    "    \"name\": \"arr5mat\","
    "    \"type\": {"
    "        \"name\": \"array\","
    "        \"length\": 1,"
    "        \"element_type\": {"
    "            \"name\": \"matrix\","
    "            \"rows\": 1,"
    "            \"cols\": 1"
    "        }"
    "    },"
    "    \"block\": \"parameters\""
    "},"
    "{"
    "    \"name\": \"g\","
    "    \"type\": {"
    "        \"name\": \"real\""
    "    },"
    "    \"block\": \"generated_quantities\""
    "}"
    "]";

  TestVarContext test_var_context("arr5");
  //clamped.insert("mat55");
  std::cout << stan::services::util::create_param_mask(ss, test_var_context) << std::endl;
}
