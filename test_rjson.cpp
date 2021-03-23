#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "./lib/rapidjson_1.1.0/rapidjson/document.h"
#include "./lib/rapidjson_1.1.0/rapidjson/istreamwrapper.h"


int main(void){ 
    std::ifstream json_file("test.json");
    
    rapidjson::IStreamWrapper isw(json_file);

    rapidjson::Document d;
    d.ParseStream(isw);

    for (auto const& p : d.GetArray()){
        std::cout << p.GetObject()["name"].GetString() << std::endl;
    }
    return 0;
}

