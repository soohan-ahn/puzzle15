#ifndef __PUZZLE15_SCENE_H__
#define __PUZZLE15_SCENE_H__

#include "cocos2d.h"

class Puzzle15 : public cocos2d::CCLayer
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(Puzzle15
                );
};

#endif // __Puzzle15_SCENE_H__
