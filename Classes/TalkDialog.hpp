//
//  TalkDialog.hpp
//  Escape
//
//  Created by student on 16/7/14.
//
//

#ifndef TalkDialog_hpp
#define TalkDialog_hpp

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include "Talk.hpp"
class Item;

USING_NS_CC;

class TalkDialog
{
private:
    TalkDialog();
    static TalkDialog* instance;
    Label* label;
    Sprite* dialog;
    
    std::queue<std::string> contentList;
public:
    static TalkDialog* getInstance();
    bool isVisible(){return dialog->isVisible();}
    void setTalk(TalkItem talk);
    void setTalk(std::vector<TalkItem> talkVec);
    void setDiscover(std::vector<TalkItem> desVec);
    // 显示下一句
    void showNext();
    void showDes(Item& item);
    void showDes(std::string itemName);
    void showTalk(std::string eventName);
    void showTalk(std::vector<TalkItem> talkVec);
    void showTalk(TalkItem talk);
    
    Sprite* getDialog();
};

#endif /* TalkDialog_hpp */
