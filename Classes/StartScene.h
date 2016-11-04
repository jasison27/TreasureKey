#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
#include "BasicScene.h"
USING_NS_CC;

class StartScene : public BasicScene
{
public:
	static Scene* createScene();
	virtual bool init();
	void menuStartCallback(Ref *pSender);
	void menuSelectCallback(Ref* pSender);
	void menuCloseCallback(Ref* pSender);
	virtual void onHelpCloseCallBack();
	CREATE_FUNC(StartScene);
private:
	Layer *startLayer;
	LayerColor *selectLayer;
};

#endif
