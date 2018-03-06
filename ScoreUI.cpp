#include "ScoreUI.h"
#include <algorithm>

ScoreUI::ScoreUI(int digits, int x, int y, std::string texture_digit, std::string texture_title) : NumberUI(digits, x, y, texture_digit, texture_title)
{
	this->timer = 0.0f;
	this->score = 0;
	this->value = 0;
}

void ScoreUI::Update(void)
{
	if (this->score == this->value)
		return;

	this->timer += Time::DeltaTime();

	if (this->timer >= UpdateTime)
	{
		SetNumber(clamp(this->value + this->diff*(int)(this->timer / UpdateTime), 0, this->score));
		this->timer = 0.0f;
	}
}

void ScoreUI::SetScore(unsigned int score)
{
	this->diff = score - this->value;
	if (this->diff == 0) return;
	this->diff /= abs(this->diff);
	this->score = score;
}
