#include "ThemeLayer.h"

ThemeLayer * ThemeLayer::createWithTheme(BasicScene* fa, int themen) {
	ThemeLayer * ret = ThemeLayer::create();
	if (ret->initWithTheme(fa, themen)) return ret;
	return nullptr;
}

bool ThemeLayer::initWithTheme(BasicScene* fa, int themen) {
	theme = themen;
	container = fa;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto cg = Sprite::create("Backgroundforscene3.png");
	auto sc = std::max(visibleSize.width / cg->getContentSize().width, visibleSize.height / cg->getContentSize().height);
	cg->setScale(sc);
	cg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(cg);

	auto mandy = Sprite::create("mandy.png");
	mandy->setScale(196.0f / 2017.0f * visibleSize.width / mandy->getContentSize().width);
	mandy->setAnchorPoint(Vec2(0, 0));
	mandy->setPosition(50.0f / 2017.0f * visibleSize.width, 905.0f / 1135.0f * visibleSize.height);
	this->addChild(mandy);

	auto menu = CCMenu::create();

	auto poly = MenuItemImage::create("theme1.png", "theme1.png", CC_CALLBACK_1(ThemeLayer::onSelectThemeCallBack, this));
	poly->setTag(1);
	poly->setScale(251.0f / 2017.0f * visibleSize.width / poly->getContentSize().width);
	poly->setAnchorPoint(Vec2(0, 0));
	poly->setPosition(629.0f / 2017.0f * visibleSize.width, 929.0f / 1135.0f * visibleSize.height);
	menu->addChild(poly);

	auto settingItem = MenuItemImage::create("Settings.png", "SettingsHover.png", CC_CALLBACK_1(ThemeLayer::onSettingCallBack, this));
	settingItem->setScale(103.0f / 2017.0f * visibleSize.width / settingItem->getContentSize().width);
	settingItem->setAnchorPoint(Vec2(0, 0));
	settingItem->setPosition(1898.0f / 2017.0f * visibleSize.width, 15.0f / 1135.0f  * visibleSize.height);
	menu->addChild(settingItem);

	menu->setPosition(0, 0);
	this->addChild(menu);

	return true;
}

void ThemeLayer::onSettingCallBack(Ref * pSender) {
	container->onSettingCallBack(THEME_LAYER);
	this->removeFromParentAndCleanup(true);
}

void ThemeLayer::onSelectThemeCallBack(Ref * pSender) {
	auto item = (MenuItemImage*)pSender;
	int tag = item->getTag();

	container->onSelectThemeCallBack(tag);
	this->removeFromParentAndCleanup(true);
}
