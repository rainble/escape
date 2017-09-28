//
//  Items.cpp
//  Tile
//
//  Created by student on 16/7/12.
//
//

#include "Items.hpp"
// json
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

Items* Items::instance = nullptr;//m_singleton指向空指针
std::map<std::string, Item*> Items::items = std::map<std::string, Item*>();

Items* Items::getInstance()
{
    if (instance == nullptr) {
        readJson();
        instance = new Items();
    }
    return instance;
}

Item* Items::getItem(std::string id)
{
    if (instance == nullptr) {
        getInstance();
    }
    return items[id];
}

void Items::readJson()
{
    std::string jsonStr = FileUtils::getInstance()->getStringFromFile("items.json");
    rapidjson::Document doc;
    doc.Parse<0>(jsonStr.c_str());
    
    if (doc.HasParseError()) {
        rapidjson::ParseErrorCode code = doc.GetParseError();
        CCLOG("JSON解析错误：%d", code);
        return;
    }
    
    rapidjson::Value& value = doc["Items"];
    for (size_t i=0; i < value.Size(); ++i) {
        rapidjson::Value& tv = value[i];
        std::string id = tv["id"].GetString();
        std::string name = tv["name"].GetString();
        std::string desc = tv["description"].GetString();
        
        items[id] = new Item(id, name, desc);
    }
}