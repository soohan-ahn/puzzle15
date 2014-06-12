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
    CC_SAFE_RELEASE(_puzzleArray);
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
    
    CCSprite* _tempPuzzle = GameSprite::gameSpriteWithFile("Icon.png"); //for blank part.
    _puzzleArray->insertObject(_tempPuzzle, shuffledPuzzle[0]);
    
    for(int i = 1, j = 1; i <= 16; i++, j++)
    {
        GameSprite* _eachPuzzle;
        if(shuffledPuzzle[i] == -1){
            _eachPuzzle = GameSprite::gameSpriteWithFile("16.png");
            _currentBlank = i;
 //           _statusArray[(i - 1) / 4][(i - 1) % 4] = shuffledPuzzle[i];
            j--;
 //           continue;
        }
        else{
            char picFileName[10];
            strcpy(picFileName, fileIndex[shuffledPuzzle[i]]);
            strcat(picFileName, ".png");
            _eachPuzzle = GameSprite::gameSpriteWithFile(picFileName);
        }
        
        _eachPuzzle->setPosition(ccp(_screenSize.width * 0.2 + ((i - 1) % 4) * 60, _screenSize.height * 0.8 - ((i - 1) / 4) * 60));
        _statusArray[(i - 1) / 4][(i - 1) % 4] = shuffledPuzzle[i];//
        
        _puzzleArray->insertObject(_eachPuzzle, i);
        this->addChild(_eachPuzzle);
     }
    
    _playerTime = 0;
    _timeLabel = CCLabelTTF::create("initial", "Arial", 60);
    _timeLabel->setPosition(ccp(_screenSize.width * 0.9, _screenSize.height * 0.1));
    this->schedule(schedule_selector(Puzzle15::timeDisplay),1.0);
    this->addChild(_timeLabel);
    
    _statusLabel = CCLabelTTF::create("initial","Arial", 40);
    _statusLabel->setPosition(ccp(_screenSize.width * 0.5, _screenSize.height * 0.9));
    this->addChild(_statusLabel);
    
    this->setTouchEnabled(true);
    
    printf("Blank : %d\n",_currentBlank);
    
    return true;
}

void Puzzle15::timeDisplay()
{
    if(_running){
        _playerTime++;
        char timeLabel[10];
        sprintf(timeLabel,"%d",_playerTime);
        _timeLabel->setString(timeLabel);
    }
}

/*
 
 초기 위치 2차원 배열에 저장. ->Done
 현재 상태를 항상 이 2차원 배열에 저장. -> Done
 
 TouchesBegin 에서 touch 인식 (41, 70페이지 참고.) ->Done
 위치 얻어온 다음, 몇 번 블록에 해당되는지 확인. -> 해당되는 블록에 setTouch ->Done
 
 TouchesMoved 에서 setTouch되어 있는 블록에 대해 이동조건 검색.
 - +모양으로 빈 슬롯이 있다면, 그 방향으로 이동.
 - 없다면 그냥 내버려 두고 return.
 
 TouchedEnd 에서 setTouch들 해제. 그리고 종료조건 검사.
*/

void Puzzle15::ccTouchesBegan(CCSet* pTouches, cocos2d::CCEvent *pEvent)
{
    char currentStatusLabel[30];
    CCSetIterator p;
    CCTouch * touch;
    CCPoint tap;
    GameSprite * _currentPuzzle;
    printf("Current Blank: %d!\n",_currentBlank);
    
    for( p = pTouches->begin(); p != pTouches->end(); p++)
    {
        touch = (CCTouch*)(*p);
        if(touch){
            tap = touch->getLocation();
            for(int i = 1; i<= 16; i++)
            {
                _currentPuzzle = (GameSprite*)_puzzleArray->objectAtIndex(i);
                if(_currentPuzzle->boundingBox().containsPoint(tap)){
//                  _currentPuzzle->setTouch(touch);
//                  printf("%s\n",currentStatusLabel);
                    _currentTouched = i;
                    
                    if( ((_currentTouched - 1) % 4) == ((_currentBlank - 1) % 4)
                       && ((_currentTouched - 1) / 4) == ((_currentBlank - 1) / 4)){
                        sprintf(currentStatusLabel, "%d can't move!", i);
                        printf("%s\n",currentStatusLabel);
                    }
                    else if( ((_currentTouched - 1) % 4) == ((_currentBlank - 1) % 4)
                       || ((_currentTouched - 1) / 4) == ((_currentBlank - 1) / 4)){
                        sprintf(currentStatusLabel, "%d Touched", i);
                        printf("%s\n",currentStatusLabel);
                    }
                    else{
                        sprintf(currentStatusLabel, "%d can't move!", i);
                        printf("%s\n",currentStatusLabel);
                    }
                    
                    _statusLabel->setString(currentStatusLabel);
                }
            }
        }
    }
}

void Puzzle15::ccTouchesEnded(CCSet* pTouches, cocos2d::CCEvent *pEvent)
{
    int i,j;
    
    if( ((_currentTouched - 1) % 4) == ((_currentBlank - 1) % 4)
       || ((_currentTouched - 1) / 4) == ((_currentBlank - 1) / 4)){
        
        if( ((_currentTouched - 1) % 4) == ((_currentBlank - 1) % 4)){ // Move Up&down
            
            if(((_currentTouched - 1) / 4) > ((_currentBlank - 1) / 4)){ // Move up
                
                j = (_currentTouched - 1) % 4;
                
                GameSprite* _eachPuzzle = (GameSprite*)_puzzleArray->objectAtIndex( ((_currentBlank - 1) / 4 * 4 + (j + 1)) );
                _puzzleArray->removeObjectAtIndex(((_currentBlank - 1) / 4 * 4 + (j + 1)));
                
                printf("Finally Moving %d j = %d i = %d\n",((_currentBlank - 1) / 4 * 4 + (j + 1)), (j + 1) % 4,_currentTouched % 4);
                
                _eachPuzzle->setPosition(ccp(_screenSize.width * 0.2 + (j % 4) * 60, _screenSize.height * 0.8 - _currentTouched / 4 * 60));
                _puzzleArray->insertObject(_eachPuzzle, (_currentTouched - 1) / 4 * 4 + j + 1);
                
                printf("Insert to the %d\n",(_currentTouched - 1) / 4 * 4 + j + 1);
                
                for(i = ((_currentBlank - 1) / 4) + 1; i <= ((_currentTouched - 1) / 4); i++)
                {
                    GameSprite* _eachPuzzle = (GameSprite*)_puzzleArray->objectAtIndex( (i * 4 + (j + 1)) - 1 );
                    _puzzleArray->removeObjectAtIndex((i * 4) + (j + 1) - 1);
                    
                    printf("Moving %d j = %d i = %d\n",(i * 4 + (j + 1)), ((j + 1) % 4), (i - 1) % 4);
                    _eachPuzzle->setPosition(ccp(_screenSize.width * 0.2 + j * 60, _screenSize.height * 0.8 - ((i - 1) % 4 * 60)) );
                    
                    _puzzleArray->insertObject(_eachPuzzle, ((i - 1) * 4) + (j + 1));
                    
                    printf("Insert to the %d\n",((i - 1) * 4) + (j + 1) );
                }
                // !! From here! debug it !!
                
                for(i = ((_currentBlank - 1) / 4); i < ((_currentTouched - 1) / 4); i++)
                {
                    _statusArray[i][j] = _statusArray[i + 1][j];
                }
                _statusArray[i][j] = -1;
                _currentBlank = (i * 4 + (j + 1));
                
            }
            else if(((_currentTouched - 1) / 4) < ((_currentBlank - 1) / 4)){ // Move Down
                
                j = (_currentTouched - 1) % 4;
                
                GameSprite* _eachPuzzle = (GameSprite*)_puzzleArray->objectAtIndex( ((_currentBlank - 1) / 4 * 4 + (j + 1)) );
                _puzzleArray->removeObjectAtIndex(((_currentBlank - 1) / 4 * 4 + (j + 1)));
                
                printf("Finally Moving %d j = %d i = %d\n",((_currentBlank - 1) / 4 * 4 + (j + 1)), (j + 1) % 4,_currentTouched / 4);
                
                _eachPuzzle->setPosition(ccp(_screenSize.width * 0.2 + (j % 4) * 60, _screenSize.height * 0.8 - _currentTouched / 4 * 60));
                _puzzleArray->insertObject(_eachPuzzle, (_currentTouched - 1) / 4 * 4 + j + 1);
                
                printf("Insert to the %d\n",(_currentTouched - 1) / 4 * 4 + j + 1);
                
                for(i = ((_currentBlank - 1) / 4) - 1; i >= ((_currentTouched - 1) / 4); i--)
                {
                    GameSprite* _eachPuzzle = (GameSprite*)_puzzleArray->objectAtIndex( (i * 4 + (j + 1)) + 1 );
                    _puzzleArray->removeObjectAtIndex((i * 4) + (j + 1) + 1);
                    
                    printf("Moving %d j = %d i = %d\n",(i * 4 + (j + 1)), ((j + 1) % 4), (i + 1) % 4);
                    _eachPuzzle->setPosition(ccp(_screenSize.width * 0.2 + j * 60, _screenSize.height * 0.8 - ((i + 1) % 4 * 60)) );
                    
                    _puzzleArray->insertObject(_eachPuzzle, ((i + 1) * 4) + (j + 1));
                    
                    printf("Insert to the %d\n",((i + 1) * 4) + (j + 1) );
                }
                // !! From here! debug it !!
                
                for(i = ((_currentBlank - 1) / 4); i > ((_currentTouched - 1) / 4); i--)
                {
                    _statusArray[i][j] = _statusArray[i - 1][j];
                }
                _statusArray[i][j] = -1;
                _currentBlank = (i * 4 + (j + 1));
            
            }
        }
        else if(((_currentTouched - 1) / 4) == ((_currentBlank - 1) / 4)){ // Move Side.
            
            if( ((_currentTouched - 1) % 4) > ((_currentBlank - 1) % 4)){ // Move left
                // Blank ~ Touch - 1
                // [current] = [current + 1]
                // [touch] = make it blank.
                
                i = (_currentTouched - 1) / 4;
                
                for(j = ((_currentBlank - 1) % 4) + 1; j <= ((_currentTouched - 1) % 4); j++)
                {
                    GameSprite* _eachPuzzle = (GameSprite*)_puzzleArray->objectAtIndex( (i * 4 + (j + 1)) );
                    printf("Moving %d j = %d i = %d\n",(i * 4 + (j + 1)), ((j - 1) % 4), i);
                    _eachPuzzle->setPosition(ccp(_screenSize.width * 0.2 + ((j - 1) % 4) * 60, _screenSize.height * 0.8 - i * 60));
                }
                
                GameSprite* _eachPuzzle = (GameSprite*)_puzzleArray->objectAtIndex( (i * 4 + ((_currentBlank % 4))) );
                _puzzleArray->removeObjectAtIndex((i * 4 + (((_currentBlank - 1) % 4 + 1))));
                printf("Finally Moving %d j = %d i = %d\n",(i * 4 + ((_currentBlank % 4))), ((_currentTouched - 1) % 4), i);
                _eachPuzzle->setPosition(ccp(_screenSize.width * 0.2 + ((_currentTouched - 1) % 4) * 60, _screenSize.height * 0.8 - i * 60));
                _puzzleArray->insertObject(_eachPuzzle, i * 4 + (_currentTouched - 1) % 4 + 1);
                printf("Insert to the %d\n",i * 4 + (_currentTouched - 1) % 4 + 1);
                
                for(j = ((_currentBlank - 1) % 4); j < ((_currentTouched - 1) % 4); j++)
                {
                    _statusArray[i][j] = _statusArray[i][j + 1];
                }
                _statusArray[i][j] = -1;
                _currentBlank = (i * 4 + (j + 1));
                
            }
            else if( ((_currentTouched - 1) % 4) < ((_currentBlank - 1) % 4)){ // Move right
                i = (_currentTouched - 1) / 4;
                
                for(j = ((_currentBlank - 1) % 4) - 1; j >= ((_currentTouched - 1) % 4); j--)
                {
                    GameSprite* _eachPuzzle = (GameSprite*)_puzzleArray->objectAtIndex( (i * 4 + (j + 1)) );
                    printf("Moving %d j = %d i = %d\n",(i * 4 + (j + 1)), ((j + 1) % 4), i);
                    _eachPuzzle->setPosition(ccp(_screenSize.width * 0.2 + ((j + 1) % 4) * 60, _screenSize.height * 0.8 - i * 60));
                }
                
                GameSprite* _eachPuzzle = (GameSprite*)_puzzleArray->objectAtIndex( (i * 4 + ((_currentBlank - 1) % 4 + 1)) );
                _puzzleArray->removeObjectAtIndex((i * 4 + (((_currentBlank - 1) % 4 + 1))));
                printf("Finally Moving %d j = %d i = %d\n",(i * 4 + (((_currentBlank - 1) % 4))), ((_currentTouched - 1) % 4), i);
                _eachPuzzle->setPosition(ccp(_screenSize.width * 0.2 + ((_currentTouched - 1) % 4) * 60, _screenSize.height * 0.8 - i * 60));
                _puzzleArray->insertObject(_eachPuzzle, i * 4 + (_currentTouched - 1) % 4 + 1);
                printf("Insert to the %d\n",i * 4 + (_currentTouched - 1) % 4 + 1);
                
                for(j = ((_currentBlank - 1) % 4); j > ((_currentTouched - 1) % 4); j--)
                {
                    _statusArray[i][j] = _statusArray[i][j - 1];
                }
                _statusArray[i][j] = -1;
                _currentBlank = (i * 4 + (j + 1)); 
            }
        }
    }
    
    int k = 1;
    for(i = 0; i < 4; i++)
    {
        for(j = 0; j < 4; j++)
            shuffledPuzzle[k++] = _statusArray[i][j];
    }
    for(i = 0; i <= 16; i++)
        printf("%d ",shuffledPuzzle[i]);
    printf("\n");
    
    if(checkClear()){
        _statusLabel->setString("Clear!!");
        this->setTouchEnabled(false);
        _running = false;
    }
    
    printf("Touch Ended!!\n");
}

bool Puzzle15::checkClear()
{
    int i;
    for(i = 1; i <= 15; i++)
    {
        if(shuffledPuzzle[i] != i) return false;
    }
    if(shuffledPuzzle[i] == -1) return true;
    else return false;
}

void Puzzle15::ccTouchesMoved(CCSet* pTouches, cocos2d::CCEvent *pEvent)
{
    printf("Touch Moving!\n");
}

void Puzzle15::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
