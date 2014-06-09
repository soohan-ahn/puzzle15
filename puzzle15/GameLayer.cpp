//
//  GameLayer.cpp
//  puzzle15
//
//  Created by Soo Han Ahn on 2014. 5. 30..
//
//

#include "GameLayer.h"
/*
GameLayer::GameLayer()
{
    
}
*/
GameLayer::~GameLayer()
{
    
}

CCScene* GameLayer::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    GameLayer *layer = GameLayer::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool GameLayer::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    /*
    char fileIndex[20][3] = {"0","1","2","3","4","5","6","7","8","9","10","11","12","13","14","15"};
    _puzzleArray = CCArray::createWithCapacity(16);
    for(int i = 1; i <= 15; i++)
    {
        char picFileName[10];
        strcpy(picFileName, fileIndex[i]);
        strcat(picFileName, ".png");
        CCSprite* _eachPuzzle = GameSprite::gameSpriteWithFile(picFileName);
        _puzzleArray->objectAtIndex(i)->operator=(*_eachPuzzle);
        this->addChild(_eachPuzzle);
    }
    _puzzleArray->retain();
     */
     _playerTime = 0;
    _timeLabel = CCLabelTTF::create("0", "Arial", 60);
    _timeLabel->setPosition(ccp(_screenSize.width - 60, _screenSize.height * 0.5 - 80));
    this->schedule(schedule_selector(GameLayer::timeDisplay),1.0);
    this->addChild(_timeLabel);
    
    return true;
}

void GameLayer::timeDisplay()
{
    _playerTime++;
    char timeLabel[10];
    sprintf(timeLabel,"%d",_playerTime);
    _timeLabel->setString(timeLabel);
}

void GameLayer::ccTouchesBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}

void GameLayer::ccTouchesEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}

void GameLayer::ccTouchesMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    
}


