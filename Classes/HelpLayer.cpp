#include "HelpLayer.h"

HelpLayer * HelpLayer::createWithOption(bool hintf) {
	HelpLayer* ret = HelpLayer::create();
	ret->initWithOption(hintf);
	return ret;
}

bool HelpLayer::initWithOption(bool hintf) {
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto theme = MenuItemImage::create("map.png", "mapHover.png", CC_CALLBACK_1(HelpLayer::menuThemeCallBack, this));
	theme->setScale(798.0f / 2017.0f * visibleSize.width / theme->getContentSize().width);
	theme->setAnchorPoint(Vec2(0, 0));
	theme->setPosition(76.0f / 2017.0f * visibleSize.width, 893.0f / 1135.0f * visibleSize.height);

	auto level = MenuItemImage::create("levels.png", "levelsHover.png", CC_CALLBACK_1(HelpLayer::menuLevelCallBack, this));
	level->setScale(687.0f / 2017.0f * visibleSize.width / level->getContentSize().width);
	level->setAnchorPoint(Vec2(0, 0));
	level->setPosition(76.0f / 2017.0f * visibleSize.width, 685.0f / 1135.0f * visibleSize.height);

	auto intro = MenuItemImage::create("video.png", "videoHover.png", CC_CALLBACK_1(HelpLayer::menuIntroCallBack, this));
	intro->setScale(498.0f / 2017.0f * visibleSize.width / intro->getContentSize().width);
	intro->setAnchorPoint(Vec2(0, 0));
	intro->setPosition(76.0f / 2017.0f * visibleSize.width, 479.0f / 1135.0f * visibleSize.height);

	auto hint = MenuItemImage::create("hint.png", "hingHover.png", CC_CALLBACK_1(HelpLayer::menuHintCallBack, this));
	hint->setEnabled(hintf);
	hint->setScale(257.0f / 2017.0f * visibleSize.width / hint->getContentSize().width);
	hint->setAnchorPoint(Vec2(0, 0));
	hint->setPosition(76.0f / 2017.0f * visibleSize.width, 273.0f / 1135.0f * visibleSize.height);

	auto menu = Menu::create(theme, level, intro, hint, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto logo = Sprite::create("logomenu.png");
	logo->setScale(879.0f / 2017.0f * visibleSize.width / logo->getContentSize().width);
	logo->setAnchorPoint(Vec2(0, 0));
	logo->setPosition(948.0f / 2017.0f * visibleSize.width, 506.f / 1135.0f * visibleSize.height);
	this->addChild(logo);

	auto twitter = Sprite::create("twitter.png");
	twitter->setScale(782.0f / 2017.0f * visibleSize.width / twitter->getContentSize().width);
	twitter->setAnchorPoint(Vec2(0, 0));
	twitter->setPosition(1185.0f / 2017.0f * visibleSize.width, 338.f / 1135.0f * visibleSize.height);
	this->addChild(twitter);

	auto ins = Sprite::create("instagram-facebook.png");
	ins->setScale(992.0f / 2017.0f * visibleSize.width / ins->getContentSize().width);
	ins->setAnchorPoint(Vec2(0, 0));
	ins->setPosition(978.0f / 2017.0f * visibleSize.width, 238.f / 1135.0f * visibleSize.height);
	this->addChild(ins);

	auto youtube = Sprite::create("youtube.png");
	youtube->setScale(1130.0f / 2017.0f * visibleSize.width / youtube->getContentSize().width);
	youtube->setAnchorPoint(Vec2(0, 0));
	youtube->setPosition(832.0f / 2017.0f * visibleSize.width, 150.f / 1135.0f * visibleSize.height);
	this->addChild(youtube);

	auto gmail = Sprite::create("gmail.png");
	gmail->setScale(1295.0f / 2017.0f * visibleSize.width / gmail->getContentSize().width);
	gmail->setAnchorPoint(Vec2(0, 0));
	gmail->setPosition(673.0f / 2017.0f * visibleSize.width, 26.f / 1135.0f * visibleSize.height);
	this->addChild(gmail);

	return true;
}

void HelpLayer::menuThemeCallBack(Ref * pSender) {
}

void HelpLayer::menuLevelCallBack(Ref * pSender) {
}

void HelpLayer::menuIntroCallBack(Ref * pSender) {
}

void HelpLayer::menuHintCallBack(Ref * pSender) {
}
