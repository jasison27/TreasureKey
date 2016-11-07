#include "ExampleLayer.h"
#include "StartScene.h"
#include <algorithm>
#include "Util.h"
USING_NS_CC;

const double PI = acos(-1);
int num_vertex[] = { 0,3,4,6,8 };
Example* Example::createWithShape(int shape) {
	auto layer = Example::create();
	layer->initWithShape(shape);
	return layer;
}

bool Example::initWithShape(int shape) {
	if (!Layer::init()) {
		return false;
	}
	auto visibleSize = Director::getInstance()->getVisibleSize();

	shape = num_vertex[shape];
	if (shape == 0) {
		for (int i = 0; i < 1000; ++ i) {
			points.push_back(Vec2(cos(2*PI/1000*i), sin(2*PI/1000*i)));
		}
	} else {
		std::vector <Vec2> v;
		for (int i = 0; i < shape; ++ i) {
			v.push_back(Vec2(cos(PI*(1+2*i)/ shape), sin(PI*(1+2*i)/ shape)) );
		}
		v.push_back(v[0]);
		for (int i = 0; i < shape; ++ i) {
			points.push_back(v[i]);
			int np = 1000 / shape;
			Vec2 dir = (v[i + 1] - v[i]) / np;
			for (int j = 1; j < np; ++ j) {
				points.push_back(v[i] + dir*j );
			}
		}

	}
	int npoints = points.size();
	
	float minx = points[0].x, maxx = points[0].x, miny = points[0].y, maxy = points[0].y;
	Util::minmaxify(points, minx, maxx, miny, maxy);
	float resol = std::min( 0.7 * visibleSize.width / (maxx - minx), 0.7 * visibleSize.height / (maxy - miny));
	for (int i = 0; i < npoints; ++i) {
		points[i].x = points[i].x * resol + visibleSize.width / 2;
		points[i].y = points[i].y * resol + visibleSize.height / 2;
	}

	auto cg = Sprite::create("BackgroundLevel1.png");
	auto sc = std::max(visibleSize.width / cg->getContentSize().width, visibleSize.height / cg->getContentSize().height);
	cg->setScale(sc);
	cg->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(cg, 0);

	/*
	auto cgbg = LayerColor::create(Color4B::WHITE);
	cgbg->setContentSize(Size(1724.0 / 1944 * visibleSize.width, 1110.0 / 1330 * visibleSize.height));
	cgbg->setPosition( (visibleSize- cgbg->getContentSize()) / 2 );
	this->addChild(cgbg, 0);
	*/

	drawNode = DrawNode::create();
	this->addChild(drawNode, 1);
	drawNode->drawPolygon(&points[0], npoints, Color4F::WHITE, 2, Color4F::BLACK);
	//drawNode->drawPoints(&points[0], npoints, 2, Color4F::BLACK);

	auto gobackItem = MenuItemImage::create("Back.png", "BackHover.png", CC_CALLBACK_1(Example::menuGoBackCallback, this));
	float gobackItemSC = 293.0 / 1944 * visibleSize.width / gobackItem->getContentSize().width;
	gobackItem->setScale(gobackItemSC);
	gobackItem->setAnchorPoint(Vec2(1,0));
	gobackItem->setPosition((1 - 40.0 / 1944)*visibleSize.width, 30.0 / 1330*visibleSize.height);
	menu = Menu::create(gobackItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto box = Sprite::create("ChestBoxBeforeFinish.png");
	box->setScale(410.0 / 1944 * visibleSize.width / box->getContentSize().width);
	box->setAnchorPoint(Vec2::ZERO);
	box->setPosition(30.0 / 1944*visibleSize.width, 30.0 / 1330*visibleSize.height);
	this->addChild(box, 1);

	auto logo = Sprite::create("Logo.png");
	logo->setAnchorPoint(Vec2(0, 1));
	logo->setScale(427.0 / 1944 * visibleSize.width / logo->getContentSize().width);
	logo->setPosition(30.0 / 1944 * visibleSize.width, (1 - 40.0 / 1330)*visibleSize.height);
	this->addChild(logo, 1);

	auto timerframe = Sprite::create("Time.png");
	float timerframesc = 244.0 / 1944 * visibleSize.width / timerframe->getContentSize().width;
	timerframe->setScale(timerframesc);
	timerframe->setPosition((1 - 40.0 / 1944)*visibleSize.width - timerframesc*timerframe->getContentSize().width / 2, (1 - 40.0 / 1330)*visibleSize.height - timerframesc*timerframe->getContentSize().height/2);
	this->addChild(timerframe, 1);
	
	tme = Label::createWithTTF("05:00", "Cartoonist.ttf", 24);
	tmeremain = 5.0;
	tme->setColor(Color3B::BLACK);
	tme->setPosition(timerframe->getPosition());
	this->addChild(tme, 1);

	this->scheduleUpdate();

	return true;
}

void Example::update(float dt) {
	tmeremain -= dt;
	if (tmeremain < 0) {
		tme->setString("00:00");
		tmeremain = 0;
		return;
	}
	char todisplay[] = "xx:yy";
	sprintf(todisplay, "0%d:%02d", int(tmeremain), int( (tmeremain - int(tmeremain) ) * 60) );
	tme->setString(todisplay);
}

void Example::removeFigure() {
	this->removeChild(drawNode);
	this->removeChild(menu);
}

void Example::menuGoBackCallback(Ref* sender) {
	auto gameScene = StartScene::create();
	//gameScene->menuStartCallback(gameScene);
	Director::getInstance()->replaceScene(TransitionFade::create(0.5, gameScene, Color3B::WHITE));
}

std::vector<Vec2> Example::getPoints() {
	return points;
}