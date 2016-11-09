#include "HelpLayer.h"
#include "Util.h"

HelpLayer * HelpLayer::createWithOption(BasicScene* fa, LayerEnum lenum) {
	HelpLayer* ret = HelpLayer::create();
	if (ret->initWithOption(fa, lenum)) return ret;
	return nullptr;
}

bool HelpLayer::initWithOption(BasicScene* fa, LayerEnum lenum) {
	container = fa;
	mylenum = lenum;

	auto visibleSize = Director::getInstance()->getVisibleSize();

	auto cg = Sprite::create("greenbackground.png");
	auto sc = std::max(visibleSize.width / cg->getContentSize().width, visibleSize.height / cg->getContentSize().height);
	cg->setScale(sc);
	cg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(cg);

	auto menu = Menu::create();

	auto theme = MenuItemImage::create("map.png", "mapHover.png", CC_CALLBACK_1(HelpLayer::menuThemeCallBack, this));
	theme->setScale(798.0f / 2017.0f * visibleSize.width / theme->getContentSize().width);
	theme->setAnchorPoint(Vec2(0, 0));
	theme->setPosition(76.0f / 2017.0f * visibleSize.width, 893.0f / 1135.0f * visibleSize.height);
	menu->addChild(theme);

	auto level = MenuItemImage::create("levels.png", "levelsHover.png", CC_CALLBACK_1(HelpLayer::menuLevelCallBack, this));
	level->setScale(687.0f / 2017.0f * visibleSize.width / level->getContentSize().width);
	level->setAnchorPoint(Vec2(0, 0));
	level->setPosition(76.0f / 2017.0f * visibleSize.width, 685.0f / 1135.0f * visibleSize.height);
	menu->addChild(level);

	auto intro = MenuItemImage::create("video.png", "videoHover.png", CC_CALLBACK_1(HelpLayer::menuIntroCallBack, this));
	intro->setScale(498.0f / 2017.0f * visibleSize.width / intro->getContentSize().width);
	intro->setAnchorPoint(Vec2(0, 0));
	intro->setPosition(76.0f / 2017.0f * visibleSize.width, 479.0f / 1135.0f * visibleSize.height);
	menu->addChild(intro);

	if (Util::getInstance()->getMusic()) {
		itemMusic = MenuItemImage::create("SoundOn.png", "SoundOn.png", CC_CALLBACK_1(HelpLayer::onMusicCallBack, this));
	}
	else {
		itemMusic = MenuItemImage::create("SoundOff.png", "SoundOff.png", CC_CALLBACK_1(HelpLayer::onMusicCallBack, this));
	}
	itemMusic->setScale(543.0f / 2017.0f * visibleSize.width / itemMusic->getContentSize().width);
	itemMusic->setAnchorPoint(Vec2(0, 0));
	itemMusic->setPosition(76.0f / 2017.0f * visibleSize.width, 304.0f / 1135.0f * visibleSize.height);
	menu->addChild(itemMusic);

	auto closeItem = MenuItemImage::create("Exit.png", "ExitHover.png", CC_CALLBACK_1(HelpLayer::menuCloseCallBack, this));
	closeItem->setScale(129.0f / 949.0f * visibleSize.width / closeItem->getContentSize().width);
	closeItem->setAnchorPoint(Vec2(0, 0));
	closeItem->setPosition(1720.0f / 2017.0f * visibleSize.width, 980.0f / 1135.0f  * visibleSize.height);
	menu->addChild(closeItem);

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

	auto oneTouch = EventListenerTouchOneByOne::create();
	oneTouch->onTouchBegan = CC_CALLBACK_2(HelpLayer::onTouchBegan, this);
	oneTouch->setSwallowTouches(true);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(oneTouch, this);

	return true;
}

void HelpLayer::menuThemeCallBack(Ref * pSender) {
	Util::getInstance()->playClick();
	container->onRemoveIntroLayerCallBack();
	this->removeFromParentAndCleanup(true);
}

void HelpLayer::menuLevelCallBack(Ref * pSender) {
	Util::getInstance()->playClick();
	container->onSelectThemeCallBack(0); // last theme
	this->removeFromParentAndCleanup(true);
}

void HelpLayer::menuIntroCallBack(Ref * pSender) {
	Util::getInstance()->playClick();
	container->onIntroCallBack();
	this->removeFromParentAndCleanup(true);
}

void HelpLayer::menuCloseCallBack(Ref * pSender) {
	Util::getInstance()->playClick();
	container->onHelpCloseCallBack(mylenum);
	this->removeFromParentAndCleanup(true);
}

bool HelpLayer::onTouchBegan(Touch * touch, Event * event) {
	return true;
}

void HelpLayer::onMusicCallBack(Ref* ref) {
	if (Util::getInstance()->getMusic()) {
		Util::getInstance()->setMusic(false);
		auto pic = Sprite::create("SoundOff.png");
		itemMusic->setNormalImage(pic);
		itemMusic->setSelectedImage(pic);
	}
	else {
		Util::getInstance()->setMusic(true);
		Util::getInstance()->playClick();
		auto pic = Sprite::create("SoundOn.png");
		itemMusic->setNormalImage(pic);
		itemMusic->setSelectedImage(pic);
	}
}