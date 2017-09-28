//
//  StartScene.cpp
//  Escape
//
//  Created by student on 16/7/13.
//
//

#include "StartScene.hpp"
#include "GameScene.hpp"
#include "SimpleAudioEngine.h"
USING_NS_CC;

Scene* StartScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = StartScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool StartScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
//    SpriteFrameCache::getInstance() -> addSpriteFramesWithFile("player.plist");
//    auto playerText = Director::getInstance() -> getTextureCache() -> addImage("player.pvr.ccz");
//    auto playerNode = SpriteBatchNode::createWithTexture(playerText);
//    this -> addChild(playerNode);
    
    // 设置背景"
    auto bg = Sprite::create("bg.tiff");
    // position the sprite on the center of the screen
    bg->setPosition(Vec2(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
    bg->setScale(0.8f);
    // add the sprite as a child to this layer
    this->addChild(bg, 0);
    
    // 设置背景音乐
    CocosDenshion::SimpleAudioEngine::getInstance() -> preloadBackgroundMusic("bgm.mp3");
    CocosDenshion::SimpleAudioEngine::getInstance() -> playBackgroundMusic("bgm.mp3",true);
    
    //    auto title = Sprite::createWithSpriteFrameName("name.png");
    //    title -> setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height - title -> getContentSize().height - 50));
    //    title -> setScale(0.5f);
    //    this -> addChild(title);
    
    //设置标题
    auto mainTitle = Sprite::create("res/mainTitle.png");
    mainTitle->setPosition(Vec2(visibleSize.width/2+origin.x, 250));
    mainTitle->setScale(0.5);
    mainTitle->setColor(Color3B::RED);
    mainTitle->runAction(RepeatForever::create( Sequence::create(FadeTo::create(2, 0.8),FadeIn::create(2),Blink::create(2, 3),TintTo::create(2, Color3B::RED), NULL))) ;
    this->addChild(mainTitle);
    //设置菜单项，开始载入和退出
    auto startNor = Sprite::create("res/restart.png");
    startNor->setScale(0.5);
    auto startSel = Sprite::create("res/restart.png");
    startSel->setScale(0.35);
    auto quitNor = Sprite::create("res/quit.png");
    quitNor->setScale(0.5);
    auto quitSel = Sprite::create("res/quit.png");
    quitSel->setScale(0.35);
    auto loadGame = Sprite::create("res/loading.png");
    loadGame->setScale(0.5);
    auto loadFin = Sprite::create("res/loading.png");
    loadFin->setScale(0.35);
    auto startItem = MenuItemSprite::create(startNor, startSel, CC_CALLBACK_1(StartScene::menuStartCallback, this));
    auto quitItem = MenuItemSprite::create(quitNor, quitSel, CC_CALLBACK_1(StartScene::menuCloseCallback, this));
    auto loadItem = MenuItemSprite::create(loadGame, loadFin);
    //    startItem -> setPosition(Vec2(visibleSize.width / 4 + origin.x, startItem -> getContentSize().height + quitItem -> getContentSize().height));
    //    quitItem -> setPosition(Vec2(visibleSize.width / 4 + origin.x, quitItem -> getContentSize().height));
    auto menu = Menu::create(startItem, loadItem,quitItem, NULL);
    menu->setScale(0.7);
    menu -> setPosition(Vec2(visibleSize.width / 2-10+ origin.x, origin.y+80));
    menu -> alignItemsVertically();
    this -> addChild(menu,2);
    
    //设置角色移动动画
    //动画
    Vector<SpriteFrame*> animalFrames;
    animalFrames.reserve(12);
    animalFrames.pushBack(SpriteFrame::create("res/zq1.png", Rect(0,0,32,32)));
    animalFrames.pushBack(SpriteFrame::create("res/zq2.png", Rect(0,0,32,32)));
    animalFrames.pushBack(SpriteFrame::create("res/zq3.png", Rect(0,0,32,32)));
    
    animalFrames.pushBack(SpriteFrame::create("res/zh1.png", Rect(0,0,32,32)));
    animalFrames.pushBack(SpriteFrame::create("res/zh2.png", Rect(0,0,32,32)));
    animalFrames.pushBack(SpriteFrame::create("res/zh3.png", Rect(0,0,32,32)));
    
    animalFrames.pushBack(SpriteFrame::create("res/zy1.png", Rect(0,0,32,32)));
    animalFrames.pushBack(SpriteFrame::create("res/zy2.png", Rect(0,0,32,32)));
    animalFrames.pushBack(SpriteFrame::create("res/zy3.png", Rect(0,0,32,32)));
    
    animalFrames.pushBack(SpriteFrame::create("res/zz1.png", Rect(0,0,32,32)));
    animalFrames.pushBack(SpriteFrame::create("res/zz2.png", Rect(0,0,32,32)));
    animalFrames.pushBack(SpriteFrame::create("res/zz3.png", Rect(0,0,32,32)));
    
    //Animation
    Animation * ani = Animation::createWithSpriteFrames(animalFrames);
    ani->setDelayPerUnit(0.2f);
    
    
    auto sp = Sprite::create("res/zq1.png");
    sp->setPosition(Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
    this->addChild(sp,1);
    
    auto left = MoveTo::create(1, Vec2(origin.x+visibleSize.width/3,origin.y+visibleSize.height/2));
    auto down = MoveTo::create(2, Vec2(origin.x+visibleSize.width/3,origin.y+visibleSize.height/3));
    auto rightUp = MoveTo::create(2, Vec2(origin.x+visibleSize.width*2/3,origin.y+visibleSize.height*2/3));
    auto right = MoveTo::create(2, Vec2(origin.x+visibleSize.width,origin.y+visibleSize.height*2/3));
    auto reRight = MoveTo::create(2, Vec2(origin.x+visibleSize.width*2/3,origin.y+visibleSize.height*2/3));
    auto downAlittle = MoveTo::create(1,Vec2(origin.x+visibleSize.width*2/3,origin.y+visibleSize.height/2) );
    auto rightToE = MoveTo::create(2, Vec2(origin.x+visibleSize.width-20,origin.y+visibleSize.height/2));
    auto backDown = MoveTo::create(2, Vec2(origin.x+visibleSize.width-20,origin.y+20));
    auto goLeft = MoveTo::create(3, Vec2(origin.x+visibleSize.width/2,origin.y+20));
    auto upToOri = MoveTo::create(2, Vec2(origin.x+visibleSize.width/2,origin.y+visibleSize.height/2));
    sp->runAction(RepeatForever::create(Sequence::create(left,down,rightUp,right,reRight,downAlittle,rightToE,backDown,goLeft,upToOri,NULL)));
    
    
    auto animate = Animate::create(ani);
    sp->runAction(RepeatForever::create(animate));
    
    return true;
}

void StartScene::menuStartCallback(cocos2d::Ref* pSender)
{
//    auto gameScene = GameScene::createScene("leadRoom", "keting");
    auto gameScene = GameScene::createScene("first", "leadRoom");
    Director::getInstance()->pushScene(gameScene);
}

void StartScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
