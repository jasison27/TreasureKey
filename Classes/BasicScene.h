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
	virtual void onNextLevelCallBack() = 0;
	virtual void onRetryLevelCallBack() = 0;
	virtual void onBackToLevelCallBack() = 0;
	virtual void onEnterThemeCallBack() = 0;
	virtual void onEnterIntroCallBack() = 0;
	virtual void onDisplayNextLevelCallBack() = 0;
};

#endif
