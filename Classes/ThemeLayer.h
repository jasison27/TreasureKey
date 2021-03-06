#ifndef THEME_LAYER_H__
#define THEME_LAYER_H__

#include "cocos2d.h"
#include "BasicScene.h"
USING_NS_CC;

class ThemeLayer : public Layer
{
public:
	CREATE_FUNC(ThemeLayer);
	static ThemeLayer* createWithTheme(BasicScene* fa, int themen);
	bool initWithTheme(BasicScene* fa, int themen);
	void onSelectThemeCallBack(Ref *pSender);
	void onSettingCallBack(Ref* pSender);
private:
	Sprite* mandy;
	BasicScene* container;
	int theme;
	int mandy_run_effect_id;
	void enterTheme(int tag);
};

#endif
