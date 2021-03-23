#include <stan/services/util/create_param_mask.hpp>
#include <gtest/gtest.h>

#include <set>

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

  std::set<std::string> clamped;
  //clamped.insert("mat55");
  clamped.insert("arr5mat");
  std::cout << stan::services::util::create_param_mask(ss, clamped) << std::endl;
}
