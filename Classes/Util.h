#ifndef __UTIL_H__
#define __UTIL_H__

#include <vector>
#include "cocos2d.h"
USING_NS_CC;

enum LayerEnum {
	START_LAYER,
	INTRO_LAYER,
	THEME_LAYER,
	HELP_LAYER,
	LEVEL_LAYER,
	EXAMPLE_LAYER,
	TOUCHDRAW_LAYER,
	FINISH_LAYER
};

enum AudioEnum {
	MANDY_RUN_EFFECT,
	START_SCREEN_MUSIC,
	THEME_PARK_MUSIC,
	LEVELS_SCREEN_MUSIC
};

class Util {
public:
	static Util* getInstance();
	static void simplify(std::vector<Vec2> &v, Vec2 cen);
	static float cross(Vec2 A, Vec2 B, Vec2 C);
	static void minmaxify(std::vector<Vec2> &v, float &minx, float &maxx, float &miny, float &maxy);
	static float randomAB(float a, float b);
	static bool inPolygon(Vec2 p, std::vector<Vec2> &v);
	static double calcSimilarity(std::vector<Vec2> &a, std::vector<Vec2> &b, Size visibleSize);
	static std::vector<Vec2> smoothify(std::vector<Vec2> &pts);
	void setMusic(bool flag);
	bool getMusic();
	void playClick();
	int startAudio(AudioEnum a);
	void stopAudio(int id);
	void startBackgroundMusic(AudioEnum a);
	void stopBackgroudMusic();
private:
	bool music;
};

#endif
