#pragma once
#include <Geode/Geode.hpp>

using namespace geode::prelude;

// bullshit wrapper class yaaay
class ScalingLabel : public CCNode
{
private:
	float m_ScalingFactor;
    float m_Time;
	bool m_ShouldShrink;
	std::string m_Text;
	std::string m_FntFile;
	CCLabelBMFont* m_Label = nullptr;

	ScalingLabel(std::string text, std::string fntFile, float scalingFactor);
public:
	inline CCLabelBMFont* getLabel() { return m_Label; }
	inline void setScalingFactor(float scalingFactor) { m_ScalingFactor = scalingFactor; }
	bool init() override;
	void update(float dt) override;
    void resetLabelScale();
	static ScalingLabel* create(std::string text, std::string fntFile, float scalingFactor = 0.5f);
};