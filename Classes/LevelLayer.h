#ifndef LEVEL_LAYER_H__
#define LEVEL_LAYER_H__

#include "cocos2d.h"
#include "BasicScene.h"
USING_NS_CC;

class LevelLayer : public Layer
{
public:
	CREATE_FUNC(LevelLayer);
	static LevelLayer* createWithTheme(BasicScene* fa, int themen);
	bool initWithTheme(BasicScene* fa, int themen);
	void onSelectLevelCallBack(Ref *ref);
	void onSettingCallBack(Ref *ref);
	void onCloseCallBack(Ref *ref);
private:
	BasicScene * container;
	int theme;
};

#endif
