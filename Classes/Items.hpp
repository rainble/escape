//
//  Items.hpp
//  Tile
//
//  Created by student on 16/7/12.
//
//

#ifndef Items_hpp
#define Items_hpp

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

// 物品类
class Item
{
public:
    Item(std::string id, std::string name, std::string description) {
        this->id = id;
        this->name = name;
        this->description = description;
    }
    std::string id;
    std::string name;
    std::string description;
};

// 物品集类
class Items
{
private:
    Items(){};
    static Items* instance;
    static std::map<std::string, Item*> items;
public:
    static Items* getInstance();
    static Item* getItem(std::string id);
    
    static void readJson();
};



#endif /* Items_hpp */
