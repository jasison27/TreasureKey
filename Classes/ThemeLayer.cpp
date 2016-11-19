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
	cg->setScaleX(visibleSize.width / cg->getContentSize().width);
	cg->setScaleY(visibleSize.height / cg->getContentSize().height);
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

	Util::getInstance()->startBackgroundMusic(THEME_PARK_MUSIC);

	return true;
}

void ThemeLayer::onSettingCallBack(Ref * pSender) {
	Util::getInstance()->playClick();
	Util::getInstance()->stopBackgroudMusic();
	Util::getInstance()->stopAudio(mandy_run_effect_id);
	container->onSettingCallBack(THEME_LAYER);
	this->removeFromParentAndCleanup(true);
}

void ThemeLayer::enterTheme(int tag) {
	Util::getInstance()->stopBackgroudMusic();
	Util::getInstance()->stopAudio(mandy_run_effect_id);
	container->onSelectThemeCallBack(tag);
	this->removeFromParentAndCleanup(true);
}

void ThemeLayer::onSelectThemeCallBack(Ref * pSender) {
	mandy_run_effect_id = Util::getInstance()->startAudio(MANDY_RUN_EFFECT);
	auto item = (MenuItemImage*)pSender;
	item->setEnabled(false);
	int tag = item->getTag();

	auto moveTo = MoveTo::create(1, item->getPosition());
	Vector<SpriteFrame*>animFrames;
	animFrames.reserve(5);
	auto animation = Animation::create();
	char str[20];
	for (int i = 0; i <= 4; i++) {
		sprintf(str, "Mandy_%02d.png", i);
		animation->addSpriteFrameWithFile(str);
	}
	animation->setDelayPerUnit(2.0f / 14.0f);
	auto animate = RepeatForever::create(Animate::create(animation));
	auto callBack = CallFunc::create(CC_CALLBACK_0(ThemeLayer::enterTheme, this, tag));
	mandy->runAction(animate);
	mandy->runAction(Sequence::create(moveTo, callBack, nullptr));
}
