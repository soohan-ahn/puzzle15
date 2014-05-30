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

using namespace cocos2d;

class GameLayer : public cocos2d::CCLayer
{
    GameSprite * _player;
    CCSpriteBatchNode * _puzzleBatchNode;
    
    CCLabelTTF * _timeLabel;
    
    CCSize _screenSize;
    
    int _playerTime;
    void playerTimer();
    
public:
    ~GameLayer();
    
    virtual bool init();
    
    static CCScene* scene();
    
    CREATE_FUNC(GameLayer);
    
    virtual void ccTouchesBegan();
    virtual void ccTouchesMoved();
    virtual void ccTouchesEnded();
    
};

#endif /* defined(__puzzle15__GameLayer__) */
