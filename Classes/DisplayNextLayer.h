#ifndef DISPLAY_NEXT_LAYER_H__
#define DISPLAY_NEXT_LAYER_H__

#include "cocos2d.h"
#include "BasicScene.h"
USING_NS_CC;

class DisplayNextLayer : public Layer
{
public:
	CREATE_FUNC(DisplayNextLayer);
	static DisplayNextLayer* createWithThemeLevel(BasicScene* fa, int the, int lev);
	bool initWithThemeLevel(BasicScene* fa, int the, int lev);
	void displayShape();
	void displayMandy();
	void displayRobert();
	void onSettingCallBack(Ref * ref);
	void onNextCallBack(Ref * ref);
private:
	BasicScene* container;
	int themen, leveln;
	Sprite* mandyandbubble;
	Sprite *robertoandbubble;
	Label* text;
	MenuItemImage* nextItem;
	Menu* menu;
};

#endif
