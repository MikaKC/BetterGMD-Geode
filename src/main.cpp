#include <Geode/Geode.hpp>
#include <Geode/modify/PauseLayer.hpp>
#include <Geode/modify/OptionsLayer.hpp>

USE_GEODE_NAMESPACE();

class $modify(NewOptionsLayer, OptionsLayer)
{
	void customSetup()
	{
		OptionsLayer::customSetup();
	}
};

class $modify(UpgradedPauseLayer, PauseLayer) {
	void customSetup()
	{
		PauseLayer::customSetup();

		auto winSize = CCDirector::sharedDirector()->getWinSize();
		int nodeCount = this->getChildrenCount();

		auto pauseBtn = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_optionsBtn_001.png"), this, menu_selector(UpgradedPauseLayer::onOptions));
		pauseBtn->setScale(0.85f);
		pauseBtn->m_baseScale = 0.85f;
		
		auto m = CCMenu::create();
		m->setPosition(40, winSize.height - 40);
		m->addChild(pauseBtn);
		this->addChild(m);
		
		auto hideUIMenu = CCMenu::create();
		this->addChild(hideUIMenu, 11);

		hideUIMenu->setPosition({winSize.width - 40, winSize.height - 40});

		auto hideUIButton = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_closeBtn_001.png"), this, menu_selector(UpgradedPauseLayer::onHideUI));
		hideUIButton->setUserObject(this);
		hideUIMenu->addChild(hideUIButton);

		auto buttonsMenu = findFirstChildRecursive<CCMenu>(this, [](CCMenu *mn){
			auto btn = findFirstChildRecursive<CCMenuItemSpriteExtra>(mn, [](CCMenuItemSpriteExtra *ch) {
				return ch->getChildrenCount() == 1;
			});

			return btn->getChildrenCount() == 1;
		});

		if(PlayLayer::get()->m_level->m_levelType != GJLevelType::Editor)
		{
			auto infoButton = CCMenuItemSpriteExtra::create(CCSprite::createWithSpriteFrameName("GJ_infoBtn_001.png"), this, (SEL_MenuHandler)(&UpgradedPauseLayer::onInfoLayer));
			infoButton->setScale(1.3f);
			infoButton->m_baseScale = 1.3f;
			infoButton->setPositionX(-209.f);
			
			//insert child manually at index 0 (left) 
			buttonsMenu->getChildren()->insertObject(infoButton, 0);
			infoButton->setParent(buttonsMenu);
			infoButton->onEnter();
			infoButton->onEnterTransitionDidFinish();
			buttonsMenu->alignItemsHorizontallyWithPadding(15.0f);
		}
	}

	void onOptions(CCObject*)
	{
		auto layer = OptionsLayer::create();
		cocos2d::CCDirector::sharedDirector()->getRunningScene()->addChild(layer, 100);
		layer->showLayer(false);
	}

	void onHideUI(CCObject* pSender)
	{
		PauseLayer* self = static_cast<PauseLayer*>(((CCNode*)pSender)->getUserObject());
		self->setVisible(false);
	}
	
	void onInfoLayer(CCObject*)
	{
		InfoLayer::create(PlayLayer::get()->m_level, nullptr)->show();
	}
};
