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
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>

using namespace cocos2d;

class Puzzle15 : public cocos2d::CCLayer
{
    GameSprite * _player;
    CCArray * _puzzleArray;
    
    CCLabelTTF * _timeLabel;
    CCLabelTTF * _statusLabel;
    
    CCSize _screenSize;
    
    int _statusArray[5][5];
    int shuffledPuzzle[20] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,-1,15};
    int _currentBlank;
    int _currentTouched;
    
    int _playerTime;
    void playerTimer();
    
    bool _running = true;
    
public:
    ~Puzzle15();
    
    virtual bool init();
    
    static CCScene* scene();
    
    CREATE_FUNC(Puzzle15);
    
    void menuCloseCallback(CCObject* pSender);
    
    virtual void ccTouchesBegan(CCSet* pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesMoved(CCSet* pTouches, cocos2d::CCEvent *pEvent);
    virtual void ccTouchesEnded(CCSet* pTouches, cocos2d::CCEvent *pEvent);
    
    void timeDisplay();
    bool checkClear();
};

#endif /* defined(__puzzle15__GameLayer__) */
