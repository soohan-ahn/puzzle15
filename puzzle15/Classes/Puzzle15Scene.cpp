//
//  Puzzle15.cpp
//  puzzle15
//
//  Created by Soo Han Ahn on 2014. 5. 30..
//
//

#include "Puzzle15Scene.h"
/*
 Puzzle15::Puzzle15()
 {
 
 }
 */
Puzzle15::~Puzzle15()
{
    
}

CCScene* Puzzle15::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Puzzle15 *layer = Puzzle15::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool Puzzle15::init()
{
    _screenSize = CCDirector::sharedDirector()->getWinSize();
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    char fileIndex[20][3] = {"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15"};
    _puzzleArray = CCArray::createWithCapacity(16);
    _puzzleArray->retain();
    CCSprite* _tempPuzzle = GameSprite::gameSpriteWithFile("Icon.png");
    _puzzleArray->insertObject(_tempPuzzle, 0);
    for(int i = 1; i <= 15; i++)
    {
        char picFileName[10];
        strcpy(picFileName, fileIndex[i]);
        strcat(picFileName, ".png");
        CCSprite* _eachPuzzle = GameSprite::gameSpriteWithFile(picFileName);
 //     CCSprite* _eachPuzzle = GameSprite::gameSpriteWithFile("Icon.png");
        _eachPuzzle->setPosition(ccp(_screenSize.width * 0.2 + ((i - 1) % 4) * 60, _screenSize.height * 0.8 - ((i - 1) / 4) * 60));
        
        _puzzleArray->insertObject(_eachPuzzle, i);
        this->addChild(_eachPuzzle);
     }
    
    _playerTime = 0;
    _timeLabel = CCLabelTTF::create("initial", "Arial", 60);
    _timeLabel->setPosition(ccp(_screenSize.width * 0.9, _screenSize.height * 0.1));
    this->schedule(schedule_selector(Puzzle15::timeDisplay),1.0);
    this->addChild(_timeLabel);
    
    return true;
}

void Puzzle15::timeDisplay()
{
    _playerTime++;
    char timeLabel[10];
    sprintf(timeLabel,"%d",_playerTime);
    _timeLabel->setString(timeLabel);
}

void Puzzle15::ccTouchesBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}

void Puzzle15::ccTouchesEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}

void Puzzle15::ccTouchesMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}

void Puzzle15::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
