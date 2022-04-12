#include<iostream>
#include<vector>
#include<regex>

#include"Achievements.h"

void Achievements::onNotify(GAME_EVENT _event)
{
	switch (_event)
	{
	case TIME_LESS_THAN_10_MIN:
		unlock(ACHIEVEMENT_TIME_LESS_THAN_10_MIN);
		break;
	case TIME_LESS_THAN_5_MIN:
		unlock(ACHIEVEMENT_TIME_LESS_THAN_10_MIN);
		unlock(ACHIEVEMENT_TIME_LESS_THAN_5_MIN);
		break;
	case TIME_LESS_THAN_4_MIN:
		unlock(ACHIEVEMENT_TIME_LESS_THAN_10_MIN);
		unlock(ACHIEVEMENT_TIME_LESS_THAN_5_MIN);
		unlock(ACHIEVEMENT_TIME_LESS_THAN_4_MIN);
		break;
	case TIME_LESS_THAN_3_MIN:
		unlock(ACHIEVEMENT_TIME_LESS_THAN_10_MIN);
		unlock(ACHIEVEMENT_TIME_LESS_THAN_5_MIN);
		unlock(ACHIEVEMENT_TIME_LESS_THAN_4_MIN);
		unlock(ACHIEVEMENT_TIME_LESS_THAN_3_MIN);
		break;
	case TIME_LESS_THAN_2_MIN:
		unlock(ACHIEVEMENT_TIME_LESS_THAN_10_MIN);
		unlock(ACHIEVEMENT_TIME_LESS_THAN_5_MIN);
		unlock(ACHIEVEMENT_TIME_LESS_THAN_4_MIN);
		unlock(ACHIEVEMENT_TIME_LESS_THAN_3_MIN);
		unlock(ACHIEVEMENT_TIME_LESS_THAN_2_MIN);
		break;
	case TIME_GAME_MORE_THAN_2_HOURS:
		unlock(ACHIEVEMENT_TIME_GAME_MORE_THAN_2_HOURS);
		break;
	case TIME_GAME_MORE_THAN_4_HOURS:
		unlock(ACHIEVEMENT_TIME_GAME_MORE_THAN_4_HOURS);
		break;
	case TIME_GAME_MORE_THAN_8_HOURS:
		unlock(ACHIEVEMENT_TIME_GAME_MORE_THAN_8_HOURS);
		break;
	case TIME_GAME_MORE_THAN_16_HOURS:
		unlock(ACHIEVEMENT_TIME_GAME_MORE_THAN_16_HOURS);
		break;
	case TIME_GAME_MORE_THAN_32_HOURS:
		unlock(ACHIEVEMENT_TIME_GAME_MORE_THAN_32_HOURS);
		break;
	case TIME_GAME_MORE_THAN_64_HOURS:
		unlock(ACHIEVEMENT_TIME_GAME_MORE_THAN_64_HOURS);
		break;
	case TIME_GAME_MORE_THAN_128_HOURS:
		unlock(ACHIEVEMENT_TIME_GAME_MORE_THAN_128_HOURS);
		break;
	case TIME_GAME_MORE_THAN_256_HOURS:
		unlock(ACHIEVEMENT_TIME_GAME_MORE_THAN_256_HOURS);
		break;
	case TIME_GAME_MORE_THAN_512_HOURS:
		unlock(ACHIEVEMENT_TIME_GAME_MORE_THAN_512_HOURS);
		break;
	case TIME_GAME_MORE_THAN_1024_HOURS:
		unlock(ACHIEVEMENT_TIME_GAME_MORE_THAN_1024_HOURS);
		break;
	default:
		break;
	}
}

void Achievements::unlock(ACHIEVEMENT _achievement)
{
	if (!achievements.at(_achievement))
	{
		achievements.at(_achievement) = true;

		std::string toConvert(ACHIEVEMENTStoString(_achievement));
		std::string replace1("ACHIEVEMENT_UNLOCKED:_TIME");
		std::string replace2(" ");
		std::regex r1("ACHIEVEMENT_TIME");
		std::regex r2("(_GAME_)|_");

		auto tmp = std::regex_replace(toConvert,r1,replace1);
		toDisplay.push({ std::regex_replace(tmp, r2, replace2),std::chrono::seconds(0)});

		//DEBUG
		std::cout << toDisplay.front().first << std::endl;
	}
}

void Achievements::removeAchievmentFromQueue()
{
	toDisplay.pop();
}

bool Achievements::isAchievementToDisplay()
{
	return !toDisplay.empty();
}

std::string Achievements::getAchievementFromQueue()
{
	return toDisplay.front().first;
}

void Achievements::addDuration(double _duration) noexcept
{
	std::chrono::duration<double>tmp(_duration);
	toDisplay.front().second += tmp;
}

double Achievements::getDurationTime()
{
	return isAchievementToDisplay() ? toDisplay.front().second.count() : throw std::exception("Container is empty!");
}