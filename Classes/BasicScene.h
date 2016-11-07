#ifndef BASIC_SCENE_H__
#define BASIC_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;

class BasicScene : public Scene
{
public:
	virtual void onRemoveIntroLayerCallBack() = 0;
	virtual void onRemoveStartLayerCallBack() = 0;
	virtual void onHelpCloseCallBack() = 0;
	virtual void onSettingCallBack() = 0;
	virtual void onSelectThemeCallBack(int themen) = 0;
};

#endif
