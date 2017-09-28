//
//  load.hpp
//  userFile
//
//  Created by sun on 16/7/14.
//
//

#ifndef load_hpp
#define load_hpp

#include "cocos2d.h"
#include <stdio.h>
#include "ui/CocosGUI.h"

USING_NS_CC;


// 物品类
class load
{
public:
    static load* getInstance();
    ValueVector getItemVec();
    void addPackage(std::string name);
    bool isInPackage(std::string name);
private:
    load();
    static load* instance;

    ValueVector itemVec;
};


#endif /* load_hpp */
