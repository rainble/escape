//
//  Talk.cpp
//  Tile
//
//  Created by student on 16/7/13.
//
//

#include "Talk.hpp"

Talk* Talk::instance = nullptr;

Talk::Talk()
{
    readJson();
}

Talk* Talk::getInstance()
{
    if (instance == nullptr) {
        instance = new Talk();
    }
    return instance;
}

void Talk::readJson()
{
    // 将JSON文件解析为字符串
    std::string jsonStr = FileUtils::getInstance()->getStringFromFile("talk.json");
    
    // 将JSON字符串解析成JSON对象
    doc.Parse<0>(jsonStr.c_str());
    
    // 检查解析是否出错
    if (doc.HasParseError()) {
        rapidjson::ParseErrorCode code = doc.GetParseError();
        CCLOG("JSON解析错误：%d", code);
        return;
    }
}

std::vector<TalkItem> Talk::getXu()
{
    std::vector<TalkItem> xuVec;
    rapidjson::Value& value = doc["序章"];
    for (size_t i=0; i<value.Size(); i++) {
        rapidjson::Value& tv = value[i];
        xuVec.push_back(TalkItem(tv["source"].GetString(), tv["content"].GetString()));
    }
    return xuVec;
}

std::vector<TalkItem> Talk::getOneTalk(std::string eventName)
{
    // 获得talk对象
    rapidjson::Value& talkData = doc["talk"];
    // 获得talk对象中名为eventName的数组
    rapidjson::Value& value = talkData[eventName.c_str()];
    // 遍历value数组，并将数组中的对话放入talkVew容器
    std::vector<TalkItem> talkVec;
    for (size_t i=0; i<value.Size(); i++) {
        rapidjson::Value& tv = value[i];
        talkVec.push_back(TalkItem(tv["source"].GetString(), tv["content"].GetString()));
    }
    return talkVec;
}

std::vector<TalkItem> Talk::getDescription(std::string name)
{
    std::vector<TalkItem> desVec;

    rapidjson::Value& desData = doc["others"];
    if(desData.HasMember(name.c_str()))
    {
        rapidjson::Value& value = desData[name.c_str()];
        for (size_t i=0; i<value.Size(); i++) {
            rapidjson::Value& tv = value[i];
            desVec.push_back(TalkItem(tv["source"].GetString(), tv["content"].GetString()));
        }
    }
    return desVec;
}

TalkItem Talk::getOneDiscover(std::string eventName)
{
    rapidjson::Value& talkData = doc["discover"];
    rapidjson::Value& value = talkData[eventName.c_str()];
    auto ti = TalkItem(value["source"].GetString(), value["content"].GetString());
    return ti;
}