#ifndef __START_SCENE_H__
#define __START_SCENE_H__

#include "cocos2d.h"
#include "BasicScene.h"
#include "ExampleLayer.h"
#include "TouchDrawLayer.h"
USING_NS_CC;

class StartScene : public BasicScene
{
public:
	CREATE_FUNC(StartScene);
	static StartScene* createScene();
	bool initScene();
	virtual void onHelpCloseCallBack();
	virtual void onRemoveStartLayerCallBack();
	virtual void onRemoveIntroLayerCallBack();
	virtual void onSettingCallBack();
	virtual void onSelectThemeCallBack(int themen);
	virtual void onSelectLevelCallBack(int theme, int level);
	virtual void onSkipCallBack();
	virtual void onIntroCallBack();
private:
	int current_theme;
	int current_level;
	int max_theme;
	int max_level;
	ExampleLayer* example;
	TouchDrawLayer* touchDraw;
};

#endif
