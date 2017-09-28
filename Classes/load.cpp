//
//  load.cpp
//  userFile
//
//  Created by sun on 16/7/14.
//
//

#include "load.hpp"

load* load::instance = nullptr;

load::load()
{
}

load* load::getInstance()
{
    if (instance == nullptr) {
        instance = new load();
    }
    return instance;
}

ValueVector load::getItemVec()
{
    return itemVec;
}

void load::addPackage(std::string name)
{
//    auto itembutton = cocos2d::ui::Button::create("itembtn.png");
//    itembutton -> setTitleText(name);
//    itemVec.push_back(Value(name));
//    itembutton -> setTitleFontSize(20);
//    itembutton -> setTitleColor(Color3B::WHITE);
//    return itembutton;
    itemVec.push_back(Value(name));
}

bool load::isInPackage(std::string name)
{
    for (int i=0; i<itemVec.size(); i++) {
        if (itemVec[i].asString() == name) {
            return true;
        }
    }
    return false;
}