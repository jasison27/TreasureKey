#ifndef THEME_LAYER_H__
#define THEME_LAYER_H__

#include "cocos2d.h"
USING_NS_CC;

class ThemeLayer : public Layer
{
public:
	CREATE_FUNC(ThemeLayer);
	static ThemeLayer* createWithTheme(int themen);
	bool initWithTheme(int themen);
	void menuSelectCallBack(Ref *pSender);
private:
};

#endif
