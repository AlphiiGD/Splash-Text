#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include "ScalingLabel.hpp"
#include "SplashRead.hpp"

using namespace geode::prelude;

class $modify(ST_MenuLayer, MenuLayer)
{
	struct Fields
	{
		std::string m_SplashStr;
		static SplashRead* m_SplashRead;
		ScalingLabel* m_SplashText = nullptr;
	};

	bool init()
	{
		if (!MenuLayer::init())
		{
			return false;
		}
		
		if (!m_fields->m_SplashRead) m_fields->m_SplashRead = new SplashRead("splash.splash");
		m_fields->m_SplashStr = m_fields->m_SplashRead->getRandomLine();
		auto mainTitle = getChildByIDRecursive("main-title");
		
		m_fields->m_SplashText = ScalingLabel::create(m_fields->m_SplashStr.c_str(), "goldFont.fnt");
		m_fields->m_SplashText->setScale(0.5f / (1.0f + 0.05f * strlen(m_fields->m_SplashText->getLabel()->getString())));
		m_fields->m_SplashText->setPosition(mainTitle->getContentSize().width - 10.f, mainTitle->getContentSize().height * 0.5f);
		m_fields->m_SplashText->setRotation(20.0f);
		mainTitle->addChild(m_fields->m_SplashText);
		
		return true;
	}

	void onEnter()
	{
		MenuLayer::onEnter();
		m_fields->m_SplashText->getLabel()->setString(m_fields->m_SplashStr.c_str());
		m_fields->m_SplashText->setScale(0.5f / (1.0f + 0.05f * strlen(m_fields->m_SplashText->getLabel()->getString())));
	}

	void onExit()
	{
		MenuLayer::onExit();
		m_fields->m_SplashStr = m_fields->m_SplashRead->getRandomLine();
	}
};

SplashRead* ST_MenuLayer::Fields::m_SplashRead = nullptr;
