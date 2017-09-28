//
//  TalkDialog.cpp
//  Escape
//
//  Created by student on 16/7/14.
//
//

#define OneContentLength (50*3)

#include "TalkDialog.hpp"
#include "Talk.hpp"
#include "Items.hpp"
#include <string>

TalkDialog* TalkDialog::instance = nullptr;

TalkDialog::TalkDialog()
{
    SpriteFrameCache::getInstance() -> addSpriteFramesWithFile("dialog.plist");
    auto texture = Director::getInstance() -> getTextureCache() -> addImage("dialog.pvr.ccz");
    dialog = Sprite::createWithSpriteFrameName("talk.png");
    dialog->setAnchorPoint(Vec2(0.5, 0));
    dialog->setVisible(false);
    
    label = Label::createWithTTF("", "fonts/迷你简古隶.TTF", 16);
    label->setColor(Color3B::BLACK);
    label->setDimensions(dialog->getContentSize().width - 40, dialog->getContentSize().height - 15);
    label->setAnchorPoint(Vec2(0.0f, 0.5f));
    label->setPosition(20, dialog->getContentSize().height/2);
    
    dialog->addChild(label);
}

TalkDialog* TalkDialog::getInstance()
{
    if (instance == nullptr) {
        instance = new TalkDialog();
    }
    return instance;
}

Sprite* TalkDialog::getDialog()
{
    if (dialog->getParent() != nullptr) {
        dialog->setParent(nullptr);
    }
    return dialog;
}

void TalkDialog::showNext()
{
    if (!contentList.empty()) {
        label->setString(contentList.front());
        contentList.pop();
    }else{
        dialog->setVisible(false);
    }
}

void TalkDialog::setTalk(TalkItem talk)
{
    std::string source = talk.source;
    std::string content = talk.content;
    
    if (source != "") {
        source = source + ": ";
    }
    
    while (content.length() > OneContentLength) {
        contentList.push(source + content.substr(0, OneContentLength));
        content = content.substr(OneContentLength);
    }
    
    content = source + content;
    contentList.push(content);
    
    dialog->setVisible(true);
}

void TalkDialog::setTalk(std::vector<TalkItem> talkVec)
{
    for (auto iter = talkVec.begin(); iter!=talkVec.end(); iter++) {
        setTalk(*iter);
    }
}

void TalkDialog::setDiscover(std::vector<TalkItem> desVec)
{
    setTalk(desVec);
}

void TalkDialog::showDes(Item& item)
{
    dialog->setSpriteFrame("descrip.png");
    // 显示物品名
    setTalk(TalkItem("发现物品", item.description));
    
    // 显示物品中的内容
    auto conVec = Talk::getInstance()->getDescription(item.name);
    
    if (conVec.size() > 0) {
        setTalk(conVec);
    }
    // 显示玩家描述
    setTalk(Talk::getInstance()->getOneDiscover(item.name));
    showNext();
}

void TalkDialog::showDes(std::string itemName)
{
    dialog->setSpriteFrame("descrip.png");
    // 显示物品中的内容
    auto conVec = Talk::getInstance()->getDescription(itemName);
    
    if (conVec.size() > 0) {
        setTalk(conVec);
    }
    // 显示玩家描述
    setTalk(Talk::getInstance()->getOneDiscover(itemName));
    showNext();
}

void TalkDialog::showTalk(std::vector<TalkItem> talkVec)
{
    dialog->setSpriteFrame("descrip.png");
    setTalk(talkVec);
    showNext();
}

void TalkDialog::showTalk(std::string eventName)
{
    dialog->setSpriteFrame("talk.png");
    auto tv = Talk::getInstance()->getOneTalk(eventName);
    setTalk(tv);
    showNext();
}

void TalkDialog::showTalk(TalkItem talk)
{
    dialog->setSpriteFrame("talk.png");
    setTalk(talk);
    showNext();
}