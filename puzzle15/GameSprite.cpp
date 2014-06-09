//
//  GameSprite.cpp
//  puzzle15
//
//  Created by Soo Han Ahn on 2014. 5. 30..
//
//

#include "GameSprite.h"

GameSprite::GameSprite(void)
{
    _vector = ccp(0,0);
}


GameSprite::~GameSprite(void)
{
}

GameSprite* GameSprite::gameSpriteWithFile(const char *pszFileName)
{
    GameSprite *sprite = new GameSprite();
    if(sprite && sprite->initWithFile(pszFileName)){
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return NULL;
}

void GameSprite::setPosition(const cocos2d::CCPoint &pos)
{
    CCSprite::setPosition(pos);
    if(!_nextPosition.equals(pos)){
        _nextPosition = pos;
    }
}