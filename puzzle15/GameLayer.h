//
//  GameLayer.h
//  puzzle15
//
//  Created by Soo Han Ahn on 2014. 5. 30..
//
//

#ifndef __puzzle15__GameLayer__
#define __puzzle15__GameLayer__

#include "cocos2d.h"
#include "GameSprite.h"
#include <string.h>
#include <stdlib.h>

using namespace cocos2d;

class GameLayer : public cocos2d::CCLayer
{
    GameSprite * _player;
    CCArray * _puzzleArray;
    
    CCLabelTTF * _timeLabel;
    
    CCSize _screenSize;
    
    int _playerTime;
    void playerTimer();
    
public:
    ~GameLayer();
    
    virtual bool init();
    
    static CCScene* scene();
    
    CREATE_FUNC(GameLayer);
    
    virtual void ccTouchesBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    void timeDisplay();
    
};

#endif /* defined(__puzzle15__GameLayer__) */
