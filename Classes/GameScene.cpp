#include "GameScene.hpp"
#include "Items.hpp"
#include "Talk.hpp"
#include "load.hpp"
#include "TalkDialog.hpp"

Scene* GameScene::createScene(std::string from, std::string to)
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    layer->initRoom(from, to);
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    

    
    //监听人物移动按键是否被按
    this->schedule(CC_SCHEDULE_SELECTOR(GameScene::update), 0.04);
    
    //添加角色，设定位置以及视角
    SpriteFrameCache::getInstance() -> addSpriteFramesWithFile("player.plist");
    auto texture = Director::getInstance() -> getTextureCache() -> addImage("player.pvr.ccz");
    batchnode = SpriteBatchNode::createWithTexture(texture);
    
    //设置人物走动动画
    auto cache = SpriteFrameCache::getInstance();
    v_h.pushBack(cache->getSpriteFrameByName("zh1.png"));
    v_h.pushBack(cache->getSpriteFrameByName("zh2.png"));
    v_h.pushBack(cache->getSpriteFrameByName("zh3.png"));
    v_h.pushBack(cache->getSpriteFrameByName("zh2.png"));
    v_y.pushBack(cache->getSpriteFrameByName("zy1.png"));
    v_y.pushBack(cache->getSpriteFrameByName("zy2.png"));
    v_y.pushBack(cache->getSpriteFrameByName("zy3.png"));
    v_y.pushBack(cache->getSpriteFrameByName("zy2.png"));
    v_q.pushBack(cache->getSpriteFrameByName("zq1.png"));
    v_q.pushBack(cache->getSpriteFrameByName("zq2.png"));
    v_q.pushBack(cache->getSpriteFrameByName("zq3.png"));
    v_q.pushBack(cache->getSpriteFrameByName("zq2.png"));
    v_z.pushBack(cache->getSpriteFrameByName("zz1.png"));
    v_z.pushBack(cache->getSpriteFrameByName("zz2.png"));
    v_z.pushBack(cache->getSpriteFrameByName("zz3.png"));
    v_z.pushBack(cache->getSpriteFrameByName("zz2.png"));
    
    
    // 构造键盘监听
    auto listener = EventListenerKeyboard::create();
    listener->onKeyPressed = [=](EventKeyboard::KeyCode keyCode, Event* event){
        keys[keyCode] = true;
        //声明走路动画
        auto animation_q = Animation::createWithSpriteFrames(v_q, 0.15, 1);
        auto animation_h = Animation::createWithSpriteFrames(v_h, 0.15, 1);
        auto animation_z = Animation::createWithSpriteFrames(v_z, 0.15, 1);
        auto animation_y = Animation::createWithSpriteFrames(v_y, 0.15, 1);
        auto left =Animate::create(animation_z);
        auto right =Animate::create(animation_y);
        auto up =Animate::create(animation_h);
        auto down =Animate::create(animation_q);
        //声明按键
        auto leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW, rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW,upArrow = EventKeyboard::KeyCode::KEY_UP_ARROW,downArrow = EventKeyboard::KeyCode::KEY_DOWN_ARROW,enterArrow = EventKeyboard::KeyCode::KEY_ENTER;
        
        // 显示对话框时：
        if (talkDialog->isVisible()) {
            if (isKeyPressed(enterArrow)) {
                talkDialog->showNext();
            }
        }
        // 未显示对话框时:
        else {
            if(isKeyPressed(leftArrow)) {
                player->runAction(RepeatForever::create(left));
            } else if(isKeyPressed(rightArrow)) {
                player->runAction(RepeatForever::create(right));
            } else if(isKeyPressed(upArrow)) {
                player->runAction(RepeatForever::create(up));
            } else if(isKeyPressed(downArrow)) {
                player->runAction(RepeatForever::create(down));
            } else if(isKeyPressed(enterArrow)) {
                this->search();
            }
        }
    };
    
    listener->onKeyReleased = [=](EventKeyboard::KeyCode keyCode, Event* event){
        keys[keyCode] = false;
        player->stopAllActions();
    };
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    packageInit();
    
    talkDialog =TalkDialog::getInstance();
    this->addChild(talkDialog->getDialog(), 20);
    
    return true;
}

void GameScene::initRoom(std::string from, std::string to)
{
    // 创建地图资源
    tileMap = TMXTiledMap::create(to+".tmx");
    this->addChild(tileMap);
    
    item_objs = tileMap->getObjectGroup("Objects");
    pos_objs = tileMap->getObjectGroup("Pos");
    
    // 默认起始点
    auto spawnPoint = pos_objs->getObject(from);
    
    auto x = spawnPoint["x"].asInt();
    auto y = spawnPoint["y"].asInt();
    player = Sprite::createWithSpriteFrameName("zq2.png");
    player->setPosition(x, y);
    this->addChild(player);
    
    this->setViewPointCenter(player->getPosition());
    
    // 设置NPC
    if (to == "jiangwang_room") {
        auto jwPos = item_objs->getObject("npc");
        auto x= jwPos["x"].asInt();
        auto y= jwPos["y"].asInt();
        auto w= jwPos["width"].asInt();
        auto jw = Sprite::createWithSpriteFrameName("jq2.png");
        jw->setPosition(x + w/2 , y + w/2);
        this->addChild(jw);
    }
    if (to == "qine_room") {
        auto qePos = item_objs->getObject("npc");
        auto x= qePos["x"].asInt();
        auto y= qePos["y"].asInt();
        auto w= qePos["width"].asInt();
        auto qe = Sprite::createWithSpriteFrameName("qq2.png");
        qe->setPosition(x+ w/2, y+ w/2);
        this->addChild(qe);
    }
    
    
    //获取不能走动区域的图层
    meta = tileMap->getLayer("Meta");
    if (meta != NULL) {
        meta->setVisible(false);
    }
    
    // 恢复游戏数据;
//    itemMap = FileUtils::getInstance()->getValueMapFromFile(path);
}

void GameScene::search()
{

    auto px = player->getPositionX();
    auto py = player->getPositionY();
    auto winSize = Director::getInstance()->getWinSize();
    bool isOk = false;
    std::string id;
    ValueMap obj;
    
    for(auto v : item_objs->getObjects())
    {
        obj = v.asValueMap();
        auto x = obj["x"].asInt();
        auto y = obj["y"].asInt();
        auto w = obj["width"].asInt();
        auto h = obj["height"].asInt();
        
        id = obj["id"].asString();
        auto need = obj["need"].asString();
        if (need != "" && !load::getInstance()->isInPackage(need)) {
            continue;
        }
        if (id!= "" && px >= x && px <= x+w && py>= y && py <= y+h) {
            isOk = true;
            break;
        }
    }
    // 碰到对象
    if(isOk) {
        
        // 遇到NPC
        if (id == "npc") {
            auto npcName = item_objs->getObject(id)["npcName"].asString();
            if (npcName == "jiangwang") {
                TalkDialog::getInstance()->showTalk("先开了蒋的门");
            } else if (npcName == "qine") {
                TalkDialog::getInstance()->showTalk("先开了秦婀的门");
            }
        }
        // 遇到物品
        else
        {
            auto item =Items::getItem(id.c_str());
            
            if (!load::getInstance()->isInPackage(item->name)) {
                // 添加进背包
                load::getInstance()->addPackage(item->name);
                // 显示物品描述信息
                talkDialog->showDes(*item);
                return;
            }
        }
        
    }
    talkDialog->showTalk(TalkItem("苏杭","这里好像什么也没有"));
}

//判断一个按键是否处于被按的状态
bool GameScene::isKeyPressed(EventKeyboard::KeyCode keyCode){
    if(keys[keyCode]) {
        return true;
    } else {
        return false;
    }
}
void GameScene::update(float delta){
    if (!talkDialog->isVisible()) {
        Node::update(delta);
        auto leftArrow = EventKeyboard::KeyCode::KEY_LEFT_ARROW, rightArrow = EventKeyboard::KeyCode::KEY_RIGHT_ARROW,upArrow = EventKeyboard::KeyCode::KEY_UP_ARROW,downArrow = EventKeyboard::KeyCode::KEY_DOWN_ARROW;
        if(isKeyPressed(leftArrow)) {
            keyPressedDuration(leftArrow);
        } else if(isKeyPressed(rightArrow)) {
            keyPressedDuration(rightArrow);
        } else if(isKeyPressed(upArrow)) {
            keyPressedDuration(upArrow);
        } else if(isKeyPressed(downArrow)) {
            keyPressedDuration(downArrow);
        }
    }
}
//按键移动动画事件
void GameScene::keyPressedDuration(EventKeyboard::KeyCode code) {
    auto playerPos = player->getPosition();
    
    switch (code) {
        case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
            playerPos.x -= tileMap->getTileSize().width;
            break;
        case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
            playerPos.x += tileMap->getTileSize().width;
            break;
        case EventKeyboard::KeyCode::KEY_UP_ARROW:
            playerPos.y += tileMap->getTileSize().height;
            break;
        case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
            playerPos.y -= tileMap->getTileSize().height;
            break;
        default:
            playerPos = playerPos;
            break;
    }
    //判断是否超出地图范围
    if (playerPos.x <= (tileMap->getMapSize().width* tileMap->getTileSize().width) &&
        playerPos.y <= (tileMap->getMapSize().height * tileMap->getTileSize().height)&&
        playerPos.y >= 0 &&
        playerPos.x >= 0) {
        //进行对应坐标移动
        checkTransRoom();
        this->setPlayerPointCenter(playerPos);
    }
    //将视角中心调到玩家所在位置
    this->setViewPointCenter(player->getPosition());
}

void GameScene::checkTransRoom()
{
    std::string from, to;
    int px = player->getPositionX();
    int py = player->getPositionY();
    bool isOk = false;
    auto pos_objs_vec = pos_objs->getObjects();
    
    /// 这是一段神奇的代码，非懂勿动
    int theSecondDoorX = 160713;
    if (pos_objs_vec.size() > 2) {
        theSecondDoorX = pos_objs_vec[1].asValueMap()["x"].asInt();
    }
    
    for (auto v : pos_objs_vec) {
        auto p = v.asValueMap();
        int x = p["x"].asInt();
        int y = p["y"].asInt();
        
        
        from = p["from"].asString();
        to = p["to"].asString();
        
        if (from == "jiangwang_room") {
            
        }
        
        if ((from == "leadRoom" && py < y) ||
            (from == "qine_room" && py < y) ||
            (from == "jiangwang_room" && px > x) ||
            (to == "leadRoom" && py > y && px < theSecondDoorX) ||
            (to == "qine_room" && py > y) ||
            (to == "jiangwang_room" && px < x))
        {
            isOk = true;
            break;
        }
    }
    if (isOk) {
        auto nextScene = GameScene::createScene(from, to);
        Director::getInstance()->pushScene(nextScene);
    }
}

void GameScene::setPlayerPointCenter(Point pos) {
    auto tileCoord = this->tileCoorForPosition(pos);
    auto p = meta->getContentSize();
    auto tileGid = meta -> getTileGIDAt(tileCoord);
    auto playerPos = player->getPosition();
    if (tileGid) {
        Value* v = new Value();
        auto properties = tileMap->getPropertiesForGID(tileGid, &v);
        if (v) {
            auto p = v->asValueMap();
            auto collsion = p["Collidable"];
            if (collsion.asBool()) {
                auto moveTo = MoveTo::create(0, Vec2(playerPos.x,playerPos.y));
                player->runAction(moveTo);
                return;
            }
            auto collectable = p["Collectable"];
            if (collectable.asBool()) {
                meta->removeTileAt(tileCoord);
                foreground->removeTileAt(tileCoord);
            }
        }
    }
    auto moveTo = MoveTo::create(0, Vec2(pos.x,pos.y));
    player->runAction(moveTo);
}

void GameScene::setViewPointCenter(Point pos)
{

    Size visibleSize = Director::getInstance()->getVisibleSize();
    int x = MAX(pos.x, visibleSize.width/2.0f);
    int y = MAX(pos.y, visibleSize.height/2.0f);
    x = MIN(x, (tileMap->getMapSize().width * tileMap->getTileSize().width - visibleSize.width/2.0f));
    y = MIN(y, (tileMap->getMapSize().height * tileMap->getTileSize().height - visibleSize.height/2.0f));
    
    Point actualPosition(x, y);
    auto centerOfView = Point(visibleSize.width/2.0, visibleSize.height/2.0f);
    auto viewPoint = ccpSub(centerOfView, actualPosition);
    
    // 地图位置
    this->setPosition(viewPoint);
    
    // 背包按钮位置
    packageItem->setPosition(Vec2(x + visibleSize.width / 2, y - visibleSize.height / 2));
    // 背包列表位置
    itemList->setPosition(Vec2(x, y));
    // 对话框位置
    talkDialog->getDialog()->setPosition(x, y - visibleSize.height/2);
}

// 把屏幕转成方块坐标
Point GameScene::tileCoorForPosition(Point pos) {
    int x = pos.x /tileMap->getTileSize().width;
    int y = (tileMap->getMapSize().height* tileMap->getTileSize().height- pos.y)/tileMap->getTileSize().height;
    
    return Point(x,y);
    
}

//背包
void GameScene::packageInit()
{
    // 创建背包图标
    packageItem = MenuItemImage::create("item.png", "item.png", CC_CALLBACK_1(GameScene::select_package, this));
    
    packageItem -> setAnchorPoint(Vec2(1, 0));
    packageItem -> setScale(0.05f);
    packageItem -> setOpacity(100);
    auto menu = Menu::create(packageItem,NULL);
    menu -> setPosition(Vec2::ZERO);
    this -> addChild(menu, 10);
    
    // 创建背包列表
    auto itembutton = cocos2d::ui::Button::create("itembtn.png");
    itembutton -> setTitleText("pencil");
    itembutton -> setTitleFontSize(20);
    itembutton -> setTitleColor(Color3B::WHITE);
    
    itemList = cocos2d::ui::ListView::create();
    
    auto size = Size(144, 238);
    itemList -> setContentSize(size);
    itemList -> setAnchorPoint(Vec2(0.5,0.5));
    itemList -> setItemModel(itembutton);
    itemList -> setItemsMargin(5.0f);
    itemList -> setPosition(Vec2(Director::getInstance()->getWinSize().width/2, Director::getInstance()->getWinSize().height/2));
    itemList -> setVisible(false);
    
    // 添加listView
    this->addChild(itemList, 10);
}

void GameScene::packageListInit()
{
    auto itemTextVec = load::getInstance()->getItemVec();
    for (int i = 0; i<itemTextVec.size(); i++) {
        auto itembutton = cocos2d::ui::Button::create("itembtn.png");
        itembutton -> setTitleText(itemTextVec[i].asString());
        itembutton -> setTitleFontSize(20);
        itembutton -> setTitleColor(Color3B::WHITE);
        itembutton -> addClickEventListener([itembutton, this](Ref* p){
            auto itemName = itembutton -> getTitleText().c_str();
            this->talkDialog->showDes(itemName);
        });
        itemList -> pushBackCustomItem(itembutton);
    }
}
//背包界面
void GameScene::select_package(Ref* pSender)
{
    if (package_flag == false)
    {
        packageListInit();
        itemList -> setVisible(true);
        package_flag = true;
    }else{
        if (itemList) {
            itemList -> removeAllChildren();
            itemList -> setVisible(false);
            package_flag = false;
        }else{
            CCLOG("啦啦啦啦");
        }
    }
}

void GameScene::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
