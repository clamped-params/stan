#ifndef STAN_SERVICES_UTIL_CREATE_PARAM_MASKS
#define STAN_SERVICES_UTIL_CREATE_PARAM_MASKS

#include <set>
#include <rapidjson/document.h>
#include <string>
#include <vector>
#include <stan/math.hpp>

namespace stan{
namespace services{
namespace util{

template<typename T>
void recurse_obj(std::vector<double>& v, const T& rtype_obj, bool clamped){
  std::string name = rtype_obj["name"].GetString();
  if (name == "array") {
    for(int i = 0; i < rtype_obj["length"].GetInt(); i++){
      recurse_obj(v, rtype_obj["element_type"].GetObject(), clamped);
    }
  }
  else if(name == "matrix") {
    v.insert(v.end(), rtype_obj["rows"].GetInt() * rtype_obj["cols"].GetInt(),
	     clamped ? 1 : 0);
  }
  else if(name == "vector") {
    v.insert(v.end(), rtype_obj["length"].GetInt(), clamped ? 1 : 0);
  }
  else{
    v.push_back(clamped ? 1 : 0);
  }
}

Eigen::VectorXd create_param_mask(std::string& unconstrained_param_str, std::set<std::string>& clamped){
  rapidjson::Document d;
  d.Parse(unconstrained_param_str.c_str());

  std::vector<double> mask;

  for (auto const& p : d.GetArray()){
    if(clamped.find(p.GetObject()["name"].GetString()) != clamped.end()){
      recurse_obj(mask, p.GetObject()["type"].GetObject(), false);
    }
    else{
      recurse_obj(mask, p.GetObject()["type"].GetObject(), true);
    }
  }
  return Eigen::Map<Eigen::VectorXd>(mask.data(), mask.size());
}

}
}
}

#endif
