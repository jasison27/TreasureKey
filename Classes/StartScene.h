#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"

class StartScene : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	void menuStartCallback(cocos2d::Ref *pSender);
	void menuSelectCallback(cocos2d::Ref* pSender);
	void menuCloseCallback(cocos2d::Ref* pSender);
	CREATE_FUNC(StartScene);
private:
	cocos2d::Layer *startLayer;
	cocos2d::LayerColor *selectLayer;
};

#endif
