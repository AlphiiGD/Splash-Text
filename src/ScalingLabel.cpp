#include "ScalingLabel.hpp"

using namespace geode::prelude;

ScalingLabel::ScalingLabel(std::string text, std::string fntFile, float scalingFactor)
	: m_Text(text), m_FntFile(fntFile), m_ScalingFactor(scalingFactor), m_Time(0.0f)
{
}

bool ScalingLabel::init()
{
	if (!CCNode::init())
	{
		return false;
	}

	m_Label = CCLabelBMFont::create(m_Text.c_str(), m_FntFile.c_str());
	addChild(m_Label);
	scheduleUpdate();
	return true;
}

void ScalingLabel::update(float dt)
{
    m_Time += dt * m_ScalingFactor;
    float newScale = 1.0f + std::sin(m_Time * 3.0f) * 0.3f; // https://www.desmos.com/calculator/gcf3iidbr6
    m_Label->setScale(newScale);
}

ScalingLabel* ScalingLabel::create(std::string text, std::string fntFile, float scalingFactor)
{
	auto ret = new ScalingLabel(text, fntFile, scalingFactor);
	if (ret->init())
	{
		ret->autorelease();
		return ret;
	}

	delete ret;
	return nullptr;
}