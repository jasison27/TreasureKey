#include "GameScene.h"
#include "ExampleLayer.h"
#include "TouchDrawLayer.h"
#include "Util.h"

USING_NS_CC;
const int numFig = 5;

Scene* Game::createWithLevel(int level) {
	auto scene = Game::create();
	Layer* layer = LayerColor::create(Color4B::WHITE);
	scene->addChild(layer, 0);
	scene->initWithLevel(level);
	return scene;
}

bool Game::initWithLevel(int lev) {
	if (!Scene::init()) {
		return false;
	}
	level = lev;
	if (level < 0 || level >= numFig) {
		level = 0;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();

	//exampleLayer = ExampleLayer::createWithShape(level);
	this->addChild(exampleLayer, 1);
	
	this->scheduleOnce(schedule_selector(Game::beginDraw), 5.0f);

	return true;
}

void Game::beginDraw(float dt) {
	CCLOG("Begin Draw");
	example.clear();
	example = exampleLayer->getPoints();
	exampleLayer->removeFromParentAndCleanup(true);
	//touchDrawLayer = TouchDraw::createWithScene(this);
	//this->addChild(touchDrawLayer);
}

void Game::menuFinishCallback() {
	//drawn = touchDrawLayer->getPoints();
	//touchDrawLayer->removeFromParentAndCleanup(true);
	auto visibleSize = Director::getInstance()->getVisibleSize();
	double similarity = 0;
	if (drawn.size() > 5) {
		similarity = Util::getInstance()->calcSimilarity(example, drawn, visibleSize);
	}
	CCLOG("game finished, similarity: %.3lf", similarity);
	
	finishLayer = Layer::create();
	this->addChild(finishLayer, 2);

	auto cg = Sprite::create("BackgroundLevel1.png");
	auto sc = std::max(visibleSize.width / cg->getContentSize().width, visibleSize.height / cg->getContentSize().height);
	cg->setScale(sc);
	cg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	finishLayer->addChild(cg, 0);

	auto cgbg = LayerColor::create(Color4B::WHITE);
	cgbg->setContentSize(Size(1724.0 / 1944 * visibleSize.width, 1110.0 / 1330 * visibleSize.height));
	cgbg->setPosition((visibleSize - cgbg->getContentSize()) / 2);
	finishLayer->addChild(cgbg, 0);

	auto closeItem = MenuItemImage::create("Exit.png", "ExitHover.png", CC_CALLBACK_1(Game::menuExitCallBack, this));
	float closeItemSC = 122.0 / 1944 * visibleSize.width / closeItem->getContentSize().width;
	closeItem->setScale(closeItemSC);
	closeItem->setAnchorPoint(Vec2(1, 1));
	closeItem->setPosition((1 - 40.0 / 1944)*visibleSize.width, (1 - 40.0 / 1330)  * visibleSize.height);

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(0, 0);
	finishLayer->addChild(menu);

	DrawNode *drawNode = DrawNode::create();
	finishLayer->addChild(drawNode, 1);
	//drawNode->drawPoints(&example[0], example.size(), 2, Color4F::RED);
	for (int i = 1; i < example.size(); ++i) {
		drawNode->drawLine(example[i - 1], example[i], Color4F::RED);
	}
	drawNode->drawLine(example.back(), example.front(), Color4F::RED);
	for (int i = 1; i < drawn.size(); ++i) {
		drawNode->drawLine(drawn[i - 1], drawn[i], Color4F::BLUE);
	}
	drawNode->drawLine(drawn.back(), drawn.front(), Color4F::BLUE);
	
	if (similarity < 0.9) {
		auto box = Sprite::create("ChestBoxBeforeFinish.png");
		box->setScale(410.0 / 1944 * visibleSize.width / box->getContentSize().width);
		box->setAnchorPoint(Vec2::ZERO);
		box->setPosition(30.0 / 1944 * visibleSize.width, 30.0 / 1330 * visibleSize.height);
		finishLayer->addChild(box, 1);

		char text[50];
		sprintf(text, "Your Score: %.1lf\nPlase Try Again!", similarity * 100);
		auto label = Label::createWithTTF(text, "Cartoonist.ttf", 24);
		auto retry = MenuItemLabel::create(label, CC_CALLBACK_1(Game::menuRetryCallBack, this));
		retry->setPosition(visibleSize / 2);
		retry->setColor(Color3B::BLACK);
		retry->setTag(0);
		menu->addChild(retry);
	}
	else {
		auto box = Sprite::create("ChestBoxAfterFinish.png");
		box->setScale(410.0 / 1944 * visibleSize.width / box->getContentSize().width);
		box->setAnchorPoint(Vec2::ZERO);
		box->setPosition(30.0 / 1944 * visibleSize.width, 30.0 / 1330 * visibleSize.height);
		finishLayer->addChild(box, 1);
		
		char text[50];
		sprintf(text, "Your Score: %.1lf\nCongratulation!", similarity * 100);
		auto label = Label::createWithTTF(text, "Cartoonist.ttf", 24);
		auto next = MenuItemLabel::create(label, CC_CALLBACK_1(Game::menuRetryCallBack, this));
		next->setPosition(visibleSize/2);
		next->setColor(Color3B::BLACK);
		next->setTag(1);
		menu->addChild(next);
	}
}

void Game::menuExitCallBack(cocos2d::Ref *sender) {
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void Game::menuRetryCallBack(cocos2d::Ref * sender) {
	int tag = ((MenuItemFont*)sender)->getTag();
	if (tag == 1) {
		level++;
		UserDefault::getInstance()->setIntegerForKey("level", level);
	}
	finishLayer->removeFromParentAndCleanup(true);
	this->initWithLevel(level);
}
