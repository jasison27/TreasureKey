#include "StartScene.h"
#include "GameScene.h"
#include "HelpLayer.h"
USING_NS_CC;

const int numFig = 5;
const double levelPosX[] = { 100, 190, 340, 550, 770 };
const double levelPosY[] = { 200, 400, 630, 750, 850 };

Scene* StartScene::createScene() {
	auto scene = StartScene::create();
	return scene;
}

bool StartScene::init() {
	auto visibleSize = Director::getInstance()->getVisibleSize();

	startLayer = Layer::create();
	this->addChild(startLayer);

	auto cg = Sprite::create("StartingScreenLandscape.png");
	auto sc = std::max(visibleSize.width/ cg->getContentSize().width, visibleSize.height/ cg->getContentSize().height);
	cg->setScale(sc);
	cg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	startLayer->addChild(cg);

	auto startItem = MenuItemImage::create("Start.png", "StartHover.png", CC_CALLBACK_1(StartScene::menuStartCallback, this));
	float startItemSC = 3.3/13.5 * visibleSize.width / startItem->getContentSize().width;
	startItem->setScale(startItemSC);
	startItem->setAnchorPoint(Vec2(0,0));
	startItem->setPosition(1.0/13.5*visibleSize.width, 0.5/8.5*visibleSize.height);
	auto menu = Menu::create(startItem, NULL);
	menu->setPosition(Vec2::ZERO);
	startLayer->addChild(menu, 1);

	HelpLayer* help = HelpLayer::createWithOption(false);
	this->addChild(help, 5);

	return true;
}

void StartScene::menuStartCallback(cocos2d::Ref * pSender) {
	auto visibleSize = Director::getInstance()->getVisibleSize();

	CCLOG("start!");
	startLayer->removeFromParentAndCleanup(true);

	selectLayer = LayerColor::create(Color4B::WHITE);
	this->addChild(selectLayer);
	
	auto bg = Sprite::create("BackgroundLevel1.png");
	auto bgsc = std::max(visibleSize.width / bg->getContentSize().width, visibleSize.height / bg->getContentSize().height);
	bg->setScale(bgsc);
	bg->setPosition(visibleSize / 2);
	selectLayer->addChild(bg);

	auto role = Sprite::create("Roberto.png");
	// right 160 down 200
	auto rolesc = 809.0 / 1944 * visibleSize.width / role->getContentSize().width;
	role->setScale(rolesc);
	role->setAnchorPoint(Vec2(1, 0));
	role->setPosition( (1 - 160.0/1944) *visibleSize.width, 200.0/1330*visibleSize.height);
	selectLayer->addChild(role);

	auto menu = Menu::create(NULL);
	menu->setPosition(0, 0);
	selectLayer->addChild(menu, 1);

	int level = 0;;
	if (!UserDefault::getInstance()->getIntegerForKey("level")) {
		UserDefault::getInstance()->setIntegerForKey("level", 0);
	}
	else {
		level = UserDefault::getInstance()->getIntegerForKey("level");
	}
	for (int i = 0; i < numFig; ++i) {
		auto item = MenuItemImage::create("lockopen.png", "lockopen.png", "lockclose.png", CC_CALLBACK_1(StartScene::menuSelectCallback, this));
		item->setTag(i);
		auto itemsc = 180.0 / 1944 * visibleSize.width / item->getContentSize().width;
		item->setScale(itemsc);
		item->setAnchorPoint(Vec2::ZERO);
		if (i > level) {
			item->setEnabled(false);
		}
		else {
			item->setEnabled(true);
		}
		item->setPosition(levelPosX[i] / 1944 * visibleSize.width, levelPosY[i] / 1330 * visibleSize.height);
		menu->addChild(item);
	}

	auto closeItem = MenuItemImage::create("Exit.png", "ExitHover.png", CC_CALLBACK_1(StartScene::menuCloseCallback, this));
	float closeItemSC = 1.0/13.5 * visibleSize.width / closeItem->getContentSize().width;
	closeItem->setScale(closeItemSC);
	closeItem->setAnchorPoint(Vec2(1, 1));
	closeItem->setPosition((1 - 0.4 / 13.5) * visibleSize.width, (1 - 0.4 / 8.5) * visibleSize.height);
	menu->addChild(closeItem);
}

void StartScene::menuCloseCallback(Ref* pSender) {
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void StartScene::onHelpCloseCallBack() {
}

void StartScene::menuSelectCallback(Ref* pSender) {
	auto item = (MenuItemImage*)pSender;
	int tag = item->getTag();

	auto gameScene = Game::createWithLevel(tag);
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, gameScene, Color3B::WHITE));
}
