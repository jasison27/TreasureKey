#include "LevelLayer.h"
#include "Util.h"

const float px[] = { 3.0f, 101.0f, 198.0f, 294.0f, 391.0f };
const float py[] = { 123.0f, 174.0f, 227.0f, 267.0f, 306.0f };

LevelLayer * LevelLayer::createWithTheme(BasicScene * fa, int themen) {
	LevelLayer* ret = LevelLayer::create();
	if (ret->initWithTheme(fa, themen)) return ret;
	return nullptr;
}

bool LevelLayer::initWithTheme(BasicScene * fa, int themen) {
	container = fa;
	theme = themen;
	int max_theme = UserDefault::getInstance()->getIntegerForKey("MaxTheme");
	int max_level = UserDefault::getInstance()->getIntegerForKey("MaxLevel");
	if (max_theme <= 0) max_theme = 1;
	if (max_level <= 0) max_level = 1;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto cg = Sprite::create("Backgroundforscene4_5_6.png");
	cg->setScaleX(visibleSize.width / cg->getContentSize().width);
	cg->setScaleY(visibleSize.height / cg->getContentSize().height);
	cg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(cg);

	auto robert = Sprite::create("key.png");
	robert->setScale(visibleSize.width / robert->getContentSize().width);
	robert->setAnchorPoint(Vec2(0, 0));
	robert->setPosition(0, 0);
	this->addChild(robert);

	auto menu = Menu::create();
	char itemname[] = "shape0.png";
	for (int i = 0; i < max_level; ++i) {
		itemname[5] = i + '1';
		auto item = MenuItemImage::create(itemname, itemname, CC_CALLBACK_1(LevelLayer::onSelectLevelCallBack, this));
		item->setTag(i+1);
		item->setScale(97.0f / 968.3f * visibleSize.width / item->getContentSize().width);
		item->setAnchorPoint(Vec2(0, 0));
		item->setPosition( px[i] / 968.3f * visibleSize.width, py[i] / 544.65f * visibleSize.height);
		menu->addChild(item);
	}
	for (int i = max_level; i < 5; ++i) {
		auto locked = Sprite::create("Locked.png");
		locked->setScale(97.0f / 968.3f * visibleSize.width / locked->getContentSize().width);
		locked->setAnchorPoint(Vec2(0, 0));
		locked->setPosition(px[i] / 968.3f * visibleSize.width, py[i] / 544.65f * visibleSize.height);
		this->addChild(locked);
	}

	auto settingItem = MenuItemImage::create("Settings.png", "SettingsHover.png", CC_CALLBACK_1(LevelLayer::onSettingCallBack, this));
	settingItem->setScale(103.0f / 2017.0f * visibleSize.width / settingItem->getContentSize().width);
	settingItem->setAnchorPoint(Vec2(0, 0));
	settingItem->setPosition(1898.0f / 2017.0f * visibleSize.width, 15.0f / 1135.0f  * visibleSize.height);
	menu->addChild(settingItem);

	auto closeItem = MenuItemImage::create("Exit.png", "ExitHover.png", CC_CALLBACK_1(LevelLayer::onCloseCallBack, this));
	closeItem->setScale(103.0f / 2017.0f * visibleSize.width / closeItem->getContentSize().width);
	closeItem->setAnchorPoint(Vec2(0, 0));
	closeItem->setPosition(1898.0f / 2017.0f * visibleSize.width, 1015.0f / 1135.0f  * visibleSize.height);
	menu->addChild(closeItem);

	menu->setPosition(0, 0);
	this->addChild(menu);

	Util::getInstance()->startBackgroundMusic(LEVELS_SCREEN_MUSIC);

	return true;
}

void LevelLayer::onSelectLevelCallBack(Ref * ref) {
	Util::getInstance()->playClick();
	auto item = (MenuItemImage*)ref;
	int tag = item->getTag();

	Util::getInstance()->stopBackgroudMusic();
	container->onSelectLevelCallBack(theme, tag);
	this->removeFromParentAndCleanup(true);
}

void LevelLayer::onSettingCallBack(Ref * ref) {
	Util::getInstance()->playClick();
	Util::getInstance()->stopBackgroudMusic();
	container->onSettingCallBack(LEVEL_LAYER);
	this->removeFromParentAndCleanup(true);
}

void LevelLayer::onCloseCallBack(Ref * ref) {
	Util::getInstance()->playClick();
	Util::getInstance()->stopBackgroudMusic();
	container->onRemoveIntroLayerCallBack(); // last theme
	this->removeFromParentAndCleanup(true);
}
