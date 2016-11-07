#include "TouchDrawLayer.h"
#include "Util.h"

TouchDrawLayer * TouchDrawLayer::createWithNothing(BasicScene* fa) {
	auto layer = TouchDrawLayer::create();
	if (layer->initWithNothing(fa)) return layer;
	return nullptr;
}

bool TouchDrawLayer::initWithNothing(BasicScene* fa) {
	container = fa;
	points.clear();

	auto visibleSize = Director::getInstance()->getVisibleSize();

	cursor = Sprite::create("Cursor.png");
	cursor->setPosition(visibleSize / 2);
	cursor->setAnchorPoint(Vec2(0, 0));
	cursor->setScale(180.0 / 1944 * visibleSize.width / cursor->getContentSize().width);
	this->addChild(cursor, 3);

	pointsTmp.clear();
	pointsVec.clear();
	this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);
	auto oneTouch = EventListenerTouchOneByOne::create();
	oneTouch->onTouchBegan = CC_CALLBACK_2(TouchDrawLayer::onTouchBegan, this);
	oneTouch->onTouchMoved = CC_CALLBACK_2(TouchDrawLayer::onTouchMoved, this);
	oneTouch->onTouchEnded = CC_CALLBACK_2(TouchDrawLayer::onTouchEnded, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(oneTouch, this);

	auto cg = Sprite::create("BackgroundLevel1.png");
	auto sc = std::max(visibleSize.width / cg->getContentSize().width, visibleSize.height / cg->getContentSize().height);
	cg->setScale(sc);
	cg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(cg, 0);

	auto cgbg = LayerColor::create(Color4B::WHITE);
	cgbg->setContentSize(Size(1724.0 / 1944 * visibleSize.width, 1110.0 / 1330 * visibleSize.height));
	cgbg->setPosition((visibleSize - cgbg->getContentSize()) / 2);
	this->addChild(cgbg, 0);

	l = 110.0 / 1944 * visibleSize.width;
	r = 1830.0 / 1944 * visibleSize.width;
	d = 110.0 / 1330 * visibleSize.height;
	u = 1220.0 / 1330 * visibleSize.height;

	drawNode = DrawNode::create();
	this->addChild(drawNode);
	tmpDrawNode = DrawNode::create();
	this->addChild(tmpDrawNode, 1);

	box = Sprite::create("ChestBoxBeforeFinish.png");
	box->setScale(410.0 / 1944 * visibleSize.width / box->getContentSize().width);
	box->setAnchorPoint(Vec2::ZERO);
	box->setPosition(30.0 / 1944 * visibleSize.width, 30.0 / 1330 * visibleSize.height);
	this->addChild(box, 1);

	finishItem = MenuItemImage::create("Finish.png", "FinishHover.png", CC_CALLBACK_1(TouchDrawLayer::menuFinishCallback, this));
	float finishItemSC = 337.0 / 1944 * visibleSize.width / finishItem->getContentSize().width;
	finishItem->setScale(finishItemSC);
	finishItem->setAnchorPoint(Vec2(1, 0));
	finishItem->setPosition((1 - 40.0 / 1944)*visibleSize.width, 30.0 / 1330 * visibleSize.height);

	closeItem = MenuItemImage::create("Exit.png", "ExitHover.png", CC_CALLBACK_1(TouchDrawLayer::menuExitCallback, this));
	float closeItemSC = 122.0 / 1944 * visibleSize.width / closeItem->getContentSize().width;
	closeItem->setScale(closeItemSC);
	closeItem->setAnchorPoint(Vec2(1, 1));
	closeItem->setPosition((1 - 40.0 / 1944)*visibleSize.width, (1 - 40.0 / 1330)  * visibleSize.height);

	auto menu = Menu::create(finishItem, closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	return true;
}

std::vector<Vec2> TouchDrawLayer::getPoints() {
	for (int i = 0; i < pointsVec.size(); ++i) {
		int sz = pointsVec[i].size();
		for (int j = 0; j < sz; ++j) {
			points.push_back(pointsVec[i][j]);
		}
	}
	return points;
}

void TouchDrawLayer::menuExitCallback(Ref* pSender) {
	Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void TouchDrawLayer::menuFinishCallback(Ref * sender) {
	//gameScene->menuFinishCallback();
}

bool TouchDrawLayer::onTouchBegan(Touch * touch, Event * event) {
	pointsTmp.clear();
	tmpDrawNode->clear();
	auto pos = Director::getInstance()->convertToUI(touch->getLocationInView());
	if (pos.x <= l || pos.x >= r || pos.y <= d || pos.y >= u || finishItem->getBoundingBox().containsPoint(pos) || closeItem->getBoundingBox().containsPoint(pos) || box->getBoundingBox().containsPoint(pos)) {
		return false;
	}
	cursor->setPosition(pos);
	CCLOG("touch began: %.2lf %.2lf\n", pos.x, pos.y);
	pointsTmp.push_back(pos);
	tmpDrawNode->drawPoint(pos, 2, Color4F::BLACK);
	return true;
}

void TouchDrawLayer::onTouchMoved(Touch * touch, Event * event) {
	auto pos = Director::getInstance()->convertToUI(touch->getLocationInView());
	if (pos.x <= l || pos.x >= r || pos.y <= d || pos.y >= u || finishItem->getBoundingBox().containsPoint(pos) || closeItem->getBoundingBox().containsPoint(pos) || box->getBoundingBox().containsPoint(pos)) {
		return;
	}
	cursor->setPosition(pos);
	tmpDrawNode->drawLine(pointsTmp.back(), pos, Color4F::BLACK);
	pointsTmp.push_back(pos);
}

void TouchDrawLayer::onTouchEnded(Touch * touch, Event * event) {
	pointsVec.push_back(Util::getInstance()->smoothify(pointsTmp));
	pointsTmp.clear();
	tmpDrawNode->clear();
	Vec2 *pts = &pointsVec.back()[0];
	drawNode->drawPoints(pts, pointsVec.back().size(), 2, Color4F::BLACK);
	CCLOG("#last added points: %d", pointsVec.back().size());
}
