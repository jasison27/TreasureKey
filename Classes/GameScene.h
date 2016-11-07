#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"
#include "ExampleLayer.h"
#include "TouchDrawLayer.h"

class Game : public cocos2d::Scene
{
public:
	static cocos2d::Scene* createWithLevel(int level);
	virtual bool initWithLevel(int level);
	CREATE_FUNC(Game);
	void menuFinishCallback();
	void menuRetryCallBack(cocos2d::Ref *sender);
	void menuExitCallBack(cocos2d::Ref *sender);
private:
	std::vector <Vec2> example;
	std::vector <Vec2> drawn;
	int level;
	void beginDraw(float dt);
	ExampleLayer *exampleLayer;
	TouchDrawLayer *touchDrawLayer;
	cocos2d::Layer *finishLayer;
};

#endif
