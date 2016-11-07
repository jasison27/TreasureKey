#include "ThemeLayer.h"

ThemeLayer * ThemeLayer::createWithTheme(int themen) {
	ThemeLayer * ret = ThemeLayer::create();
	if (ret->initWithTheme(themen)) return ret;
	return nullptr;
}

bool ThemeLayer::initWithTheme(int themen) {
	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto bg = Sprite::create("Backgroundforscene3.png");
	bg->setScale(visibleSize.width / bg->getContentSize().width, visibleSize.height / bg->getContentSize().height);
	bg->setAnchorPoint(Vec2(0, 0));
	bg->setPosition(0, 0);
	this->addChild(bg);

	auto mandy = Sprite::create("mandy.png");
	mandy->setScale(196.0f / 2017.0f * visibleSize.width / mandy->getContentSize().width);
	mandy->setAnchorPoint(Vec2(0, 0));
	mandy->setPosition(50.0f / 2017.0f * visibleSize.width, 905.0f / 1135.0f * visibleSize.height);
	this->addChild(mandy);

	auto poly = MenuItemImage::create("theme1.png", "theme1.png", CC_CALLBACK_1(ThemeLayer::menuSelectCallBack, this));
	poly->setScale(251.0f / 2017.0f * visibleSize.width / poly->getContentSize().width);
	poly->setAnchorPoint(Vec2(0, 0));
	poly->setPosition(629.0f / 2017.0f * visibleSize.width, 929.0f / 1135.0f * visibleSize.height);
	this->addChild(poly);

	return true;
}

void ThemeLayer::menuSelectCallBack(Ref * pSender) {
}
