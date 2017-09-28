#ifndef __GameScene_SCENE_H__
#define __GameScene_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "TalkDialog.hpp"

USING_NS_CC;

class GameScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(std::string from, std::string to);
    
    int count;
    Vector<SpriteFrame*> animalFrames;
    virtual bool init();
    
    // 搜索
    void search();
    
    // 判断房间的转换
    void checkTransRoom();
    // 转换场景地图
    void initRoom(std::string from, std::string to);
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);
    // 设置视图视角
    void setViewPointCenter(cocos2d::Point viewPoint);
    // 设置Player视角
    void setPlayerPointCenter(Point pos);
    
    void packageInit();
    void packageListInit();
    void select_package(Ref* pSender);
//    void pushPackage(std::string name);
//    ValueVector itemVec;
//    void packageRe();
    
    cocos2d::Point tileCoorForPosition(cocos2d::Point pos);
    
    cocos2d::Sprite* player;
    cocos2d::TMXTiledMap* tileMap;
    cocos2d::TMXLayer* meta;
    cocos2d::TMXLayer* background;
    cocos2d::TMXLayer* foreground;
    
    //添加map类，用于保存按键记录
    std::map<cocos2d::EventKeyboard::KeyCode, bool> keys;
    bool isKeyPressed(EventKeyboard::KeyCode keyCode);
    void keyPressedDuration(EventKeyboard::KeyCode code);
    void update(float delta);
    void run_animate(float delta);
    //人物资源
    SpriteBatchNode* batchnode;
    //走路动画队列
    Vector<SpriteFrame*> v_q;
    Vector<SpriteFrame*> v_h;
    Vector<SpriteFrame*> v_z;
    Vector<SpriteFrame*> v_y;
    
    
    // 谈话
    
    
private:
    TMXObjectGroup* item_objs;
    TMXObjectGroup* pos_objs;
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    cocos2d::ui::ListView* itemList;
    bool package_flag = false;
    MenuItemImage* packageItem;
    
    std::string path = "./game.dat";
    
    TalkDialog* talkDialog;
};

#endif // __GameScene_SCENE_H__
