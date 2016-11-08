#ifndef BASIC_SCENE_H__
#define BASIC_SCENE_H__

#include "cocos2d.h"
USING_NS_CC;
#include "Util.h"

class BasicScene : public Scene
{
public:
	virtual void onRemoveIntroLayerCallBack() = 0;
	virtual void onRemoveStartLayerCallBack() = 0;
	virtual void onHelpCloseCallBack(LayerEnum lenum) = 0;
	virtual void onSettingCallBack(LayerEnum lenum) = 0;
	virtual void onSelectThemeCallBack(int themen) = 0;
	virtual void onSelectLevelCallBack(int theme, int level) = 0;
	virtual void onSkipCallBack() = 0;
	virtual void onIntroCallBack() = 0;
	virtual void onFinishDrawCallBack() = 0;
};

#endif
