//
//  StartScene.hpp
//  Escape
//
//  Created by student on 16/7/13.
//
//

#ifndef StartScene_hpp
#define StartScene_hpp

#include <stdio.h>
#include "cocos2d.h"

class StartScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    void menuStartCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(StartScene);
};

#endif /* StartScene_hpp */
