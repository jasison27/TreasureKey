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

	mandy = Sprite::create("Mandy_00.png");
	mandy->setScale(106.0f / 2017.0f * visibleSize.width / mandy->getContentSize().width);
	mandy->setAnchorPoint(Vec2(0, 0));
	mandy->setPosition(50.0f / 2017.0f * visibleSize.width, 905.0f / 1135.0f * visibleSize.height);
	this->addChild(mandy, 2);

	auto menu = CCMenu::create();

	auto poly = MenuItemImage::create("theme1.png", "theme1.png", CC_CALLBACK_1(ThemeLayer::onSelectThemeCallBack, this));
	poly->setTag(1);
	poly->setScale(201.0f / 2017.0f * visibleSize.width / poly->getContentSize().width);
	poly->setAnchorPoint(Vec2(0, 0));
	poly->setPosition(609.0f / 2017.0f * visibleSize.width, 909.0f / 1135.0f * visibleSize.height);
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
	Util::getInstance()->playClick();
	container->onSettingCallBack(THEME_LAYER);
	this->removeFromParentAndCleanup(true);
}

void ThemeLayer::enterTheme(int tag) {
	container->onSelectThemeCallBack(tag);
	this->removeFromParentAndCleanup(true);
}

void ThemeLayer::onSelectThemeCallBack(Ref * pSender) {
	auto item = (MenuItemImage*)pSender;
	int tag = item->getTag();

	auto moveTo = MoveTo::create(1, item->getPosition());
	Vector<SpriteFrame*>animFrames;
	animFrames.reserve(5);
	auto animation = Animation::create();
	for (int i = 0; i <= 4; i++) {
		char str[50];
		sprintf(str, "Mandy_%02d.png", i);
		animation->addSpriteFrameWithFileName(str);
	}
	animation->setDelayPerUnit(2.0f / 14.0f);
	//animation->setRestoreOriginalFrame(true);
	//animation->setDelayPerUnit(2.0 / 14.0);
	//animation->setLoops(-1);
	auto animate = RepeatForever::create(Animate::create(animation));
	auto callBack = CallFunc::create(CC_CALLBACK_0(ThemeLayer::enterTheme, this, tag));
	mandy->runAction(animate);
	mandy->runAction(Sequence::create(moveTo, callBack, nullptr));
}
