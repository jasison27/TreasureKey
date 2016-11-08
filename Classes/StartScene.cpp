#include "StartScene.h"
#include "StartLayer.h"
#include "IntroLayer.h"
#include "ThemeLayer.h"
#include "HelpLayer.h"
#include "LevelLayer.h"
#include "ExampleLayer.h"
#include "TouchDrawLayer.h"

const int numFig = 5;
const double levelPosX[] = { 100, 190, 340, 550, 770 };
const double levelPosY[] = { 200, 400, 630, 750, 850 };

StartScene* StartScene::createScene() {
	auto scene = StartScene::create();
	if (scene->initScene()) return scene;
	return nullptr;
}

bool StartScene::initScene() {

	StartLayer* startLayer = StartLayer::createWithTime(this, 3.0f);
	this->addChild(startLayer);

	max_theme = UserDefault::getInstance()->getIntegerForKey("MaxTheme");
	if (max_theme <= 0) {
		max_theme = 1;
	}
	max_level = UserDefault::getInstance()->getIntegerForKey("MaxLevel");
	if (max_level <= 0) {
		max_level = 1;
	}

	return true;
}

void StartScene::onHelpCloseCallBack(LayerEnum lenum) {
	if (lenum == INTRO_LAYER) {
		auto layer = IntroLayer::createWithTime(this, 5.0f);
		this->addChild(layer);
	}
	else if (lenum == THEME_LAYER) {
		auto layer = ThemeLayer::createWithTheme(this, max_theme);
		this->addChild(layer);
	}
	else if (lenum == LEVEL_LAYER) {
		auto layer = LevelLayer::createWithTheme(this, current_theme);
		this->addChild(layer);
	}
	else if (lenum == EXAMPLE_LAYER) {
		example->scheduleUpdate();
	}
}

void StartScene::onRemoveStartLayerCallBack() {
	UserDefault::getInstance()->setBoolForKey("Played", false);
	if (!UserDefault::getInstance()->getBoolForKey("Played")) {
		UserDefault::getInstance()->setBoolForKey("Played", true);
		IntroLayer* intro = IntroLayer::createWithTime(this, 4.0f);
		this->addChild(intro);
	}
	else {
		ThemeLayer* theme = ThemeLayer::createWithTheme(this, max_theme);
		this->addChild(theme);
	}
}

void StartScene::onRemoveIntroLayerCallBack() {
	if (example) example->removeFromParentAndCleanup(true);
	if (touchDraw) touchDraw->removeFromParentAndCleanup(true);
	ThemeLayer* theme = ThemeLayer::createWithTheme(this, max_theme);
	this->addChild(theme);
}

void StartScene::onSettingCallBack(LayerEnum lenum) {
	HelpLayer* help = HelpLayer::createWithOption(this, lenum);
	this->addChild(help, 1);
}

void StartScene::onSelectThemeCallBack(int themen) {
	if (example) example->removeFromParentAndCleanup(true);
	if (touchDraw) touchDraw->removeFromParentAndCleanup(true);
	if (themen != 0) {
		this->current_theme = themen;
	}
	LevelLayer* level = LevelLayer::createWithTheme(this, themen);
	this->addChild(level);
}

void StartScene::onSelectLevelCallBack(int theme, int level) {
	this->current_theme = theme;
	this->current_level = level;
	example = ExampleLayer::createWithThemeLevel(this, theme, level);
	this->addChild(example);
}

void StartScene::onSkipCallBack() {
	std::vector <Vec2> points = example->getPoints();
	touchDraw = TouchDrawLayer::createWithNothing(this, points);
	this->addChild(touchDraw);
}

void StartScene::onIntroCallBack() {
	if (example) example->removeFromParentAndCleanup(true);
	if (touchDraw) touchDraw->removeFromParentAndCleanup(true);
	IntroLayer* intro = IntroLayer::createWithTime(this, 5.0f);
	this->addChild(intro);
}

void StartScene::onFinishDrawCallBack() {
}
