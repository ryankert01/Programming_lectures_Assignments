#include<iostream>
#include<string>
#include<unordered_map>

//map will automatically ordered the key or map->first, so to speak.

int main(){
    using uMap = std::unordered_map<std::string, int>;
    using uMapIter = uMap::const_iterator;
    uMap map;
    map["ryan"] = 18;
    map["yu"] = 3;

    
    for(uMapIter it = map.begin(); it != map.end(); it++){
        auto& key = it->first;
        auto& value = it->second;
        std::cout << key << " " << value << std::endl;
    }
}