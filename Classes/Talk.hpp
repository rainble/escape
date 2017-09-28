//
//  Talk.hpp
//  Tile
//
//  Created by student on 16/7/13.
//
//

#ifndef Talk_hpp
#define Talk_hpp

#include <stdio.h>
#include "cocos2d.h"
// json
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

USING_NS_CC;

class TalkItem
{
public:
    TalkItem(std::string source, std::string content) {
        this->source = source;
        this->content = content;
    }
    std::string source;
    std::string content;
};

class Talk
{
private:
    Talk();
    static Talk* instance;
    
    rapidjson::Document doc;
    rapidjson::Value discorverData;

public:
    static Talk* getInstance();
    
    void readJson();
    std::vector<TalkItem> getXu();
    std::vector<TalkItem> getOneTalk(std::string eventName);
    std::vector<TalkItem> getDescription(std::string name);
    TalkItem getOneDiscover(std::string eventName);
};

#endif /* Talk_hpp */
