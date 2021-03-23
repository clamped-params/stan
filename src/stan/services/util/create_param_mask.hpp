#ifndef STAN_SERVICES_UTIL_CREATE_PARAM_MASKS
#define STAN_SERVICES_UTIL_CREATE_PARAM_MASKS

#include <set>
#include <rapidjson/document.h>
#include <rapidjson/stringbuffer.h>
#include <rapidjson/writer.h>
#include <string>

namespace stan{
namespace services{
namespace util{

void recurse_obj(std::vector<double>& v, const rapidjson::Value& r, bool clamped){
  if (r["type"].GetString() == "array"){
    for(int i = 0; i < r["length"].GetInt(); i++){
      recurse_obj(v, r["type"].GetObject()["element_type"]);
    }
  }
  else if(r["type"].GetString() == "matrix"){
    v.insert(v.end(), r["rows"].GetInt() * r["cols"].GetInt(), clamped ? 1 : 0);
  }
  else if(r["type"].GetString() == "vector"){
    v.insert(v.end(), r["length"].GetInt(), clamped ? 1 : 0);
  }
  else{
    v.push_back(clamped? 1 : 0);
  }
}

Eigen::VectorXd create_param_mask(string& unconstrained_param_str, std::set<std::string>& clamped){
  rapidjson::Document d;
  d.Parse(unconstrained_param_str);

  std::vector<double> mask;

  for (auto const& p : d.GetArray()){
    if(clamped.find(p.GetObject()["name"].GetString()) != clamped.end()){
      recurse_obj(mask, p.GetObject(), false);
    }
    else{
      recurse_obj(mask, p.GetObject(), true);
    }
  }
  return Eigen::Map<Eigen::VectorXd>(mask.data(), mask.size());
}

}
}
}

#endif