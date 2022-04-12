#include <iostream>
#include <string>

#include"Enum.h"

std::string TILE_TYPEtoString(TILE_TYPE _tileType)
{
	switch (_tileType)
	{
	case SIGN_RED_ONE:
		return "SIGN_RED_ONE";
		break;
	case SIGN_RED_TWO:
		return "SIGN_RED_TWO";
		break;
	case SIGN_RED_THREE:
		return "SIGN_RED_THREE";
		break;
	case SIGN_RED_FOUR:
		return "SIGN_RED_FOUR";
		break;
	case SIGN_RED_FIVE:
		return "SIGN_RED_FIVE";
		break;
	case SIGN_GREEN:
		return "SIGN_GREEN";
		break;
	case SIGN_GOLD_ONE:
		return "SIGN_GOLD_ONE";
		break;
	case SIGN_GOLD_TWO:
		return "SIGN_GOLD_TWO";
		break;
	case SIGN_GOLD_THREE:
		return "SIGN_GOLD_THREE";
		break;
	case SIGN_GOLD_FOUR:
		return "SIGN_GOLD_FOUR";
		break;
	case SIGN_BLACK_ONE:
		return "SIGN_BLACK_ONE";
		break;
	case SIGN_BLACK_TWO:
		return "SIGN_BLACK_TWO";
		break;
	case SIGN_BLACK_THREE:
		return "SIGN_BLACK_THREE";
		break;
	case SIGN_BLACK_FOUR:
		return "SIGN_BLACK_FOUR";
		break;
	case SIGN_RECTANGLE:
		return "SIGN_RECTANGLE";
		break;
	case SIGNS_ONE:
		return "SIGNS_ONE";
		break;
	case SIGNS_TWO:
		return "SIGNS_TWO";
		break;
	case SIGNS_THREE:
		return "SIGNS_THREE";
		break;
	case SIGNS_FOUR:
		return "SIGNS_FOUR";
		break;
	case SIGNS_FIVE:
		return "SIGNS_FIVE";
		break;
	case SIGNS_SIX:
		return "SIGNS_SIX";
		break;
	case SIGNS_SEVEN:
		return "SIGNS_SEVEN";
		break;
	case SIGNS_EIGHT:
		return "SIGNS_EIGHT";
		break;
	case SIGNS_NINE:
		return "SIGNS_NINE";
		break;
	case DOTS_ONE:
		return "DOTS_ONE";
		break;
	case DOTS_TWO:
		return "DOTS_TWO";
		break;
	case DOTS_THREE:
		return "DOTS_THREE";
		break;
	case DOTS_FOUR:
		return "DOTS_FOUR";
		break;
	case DOTS_FIVE:
		return "DOTS_FIVE";
		break;
	case DOTS_SIX:
		return "DOTS_SIX";
		break;
	case DOTS_SEVEN:
		return "DOTS_SEVEN";
		break;
	case DOTS_EIGHT:
		return "DOTS_EIGHT";
		break;
	case DOTS_NINE:
		return "DOTS_NINE";
		break;
	case BAMBOO_ONE:
		return "BAMBOO_ONE";
		break;
	case BAMBOO_TWO:
		return "BAMBOO_TWO";
		break;
	case BAMBOO_THREE:
		return "BAMBOO_THREE";
		break;
	case BAMBOO_FOUR:
		return "BAMBOO_FOUR";
		break;
	case BAMBOO_FIVE:
		return "BAMBOO_FIVE";
		break;
	case BAMBOO_SIX:
		return "BAMBOO_SIX";
		break;
	case BAMBOO_SEVEN:
		return "BAMBOO_SEVEN";
		break;
	case BAMBOO_EIGHT:
		return "BAMBOO_EIGHT";
		break;
	case BAMBOO_NINE:
		return "BAMBOO_NINE";
		break;
	case DEFAULT:
		return "DEFAULT";
		break;
	case SELECTED:
		return "SELECTED";
		break;
	case HELP:
		return "HELP";
		break;
	default:
		return "UNKNOWN";
		break;
	}
}

std::string SOUNDtoString(SOUND _sound)
{
	switch (_sound)
	{
	case SOUND_BUTTON_PRESS:
		return "SOUND_BUTTON_PRESS";
		break;
	default:
		return "UNKNOWN";
		break;
	}
}

std::string ACHIEVEMENTStoString(ACHIEVEMENT _achievement)
{
	switch (_achievement)
	{
	case ACHIEVEMENT_TIME_LESS_THAN_10_MIN:
		return "ACHIEVEMENT_TIME_LESS_THAN_10_MIN";
		break;
	case ACHIEVEMENT_TIME_LESS_THAN_5_MIN:
		return "ACHIEVEMENT_TIME_LESS_THAN_5_MIN";
		break;
	case ACHIEVEMENT_TIME_LESS_THAN_4_MIN:
		return "ACHIEVEMENT_TIME_LESS_THAN_4_MIN";
		break;
	case ACHIEVEMENT_TIME_LESS_THAN_3_MIN:
		return "ACHIEVEMENT_TIME_LESS_THAN_3_MIN";
		break;
	case ACHIEVEMENT_TIME_LESS_THAN_2_MIN:
		return "ACHIEVEMENT_TIME_LESS_THAN_2_MIN";
		break;
	case ACHIEVEMENT_TIME_GAME_MORE_THAN_2_HOURS:
		return "ACHIEVEMENT_TIME_GAME_MORE_THAN_2_HOURS";
		break;
	case ACHIEVEMENT_TIME_GAME_MORE_THAN_4_HOURS:
		return "ACHIEVEMENT_TIME_GAME_MORE_THAN_4_HOURS";
		break;
	case ACHIEVEMENT_TIME_GAME_MORE_THAN_8_HOURS:
		return "ACHIEVEMENT_TIME_GAME_MORE_THAN_8_HOURS";
		break;
	case ACHIEVEMENT_TIME_GAME_MORE_THAN_16_HOURS:
		return "ACHIEVEMENT_TIME_GAME_MORE_THAN_16_HOURS";
		break;
	case ACHIEVEMENT_TIME_GAME_MORE_THAN_32_HOURS:
		return "ACHIEVEMENT_TIME_GAME_MORE_THAN_32_HOURS";
		break;
	case ACHIEVEMENT_TIME_GAME_MORE_THAN_64_HOURS:
		return "ACHIEVEMENT_TIME_GAME_MORE_THAN_64_HOURS";
		break;
	case ACHIEVEMENT_TIME_GAME_MORE_THAN_128_HOURS:
		return "ACHIEVEMENT_TIME_GAME_MORE_THAN_128_HOURS";
		break;
	case ACHIEVEMENT_TIME_GAME_MORE_THAN_256_HOURS:
		return "ACHIEVEMENT_TIME_GAME_MORE_THAN_256_HOURS";
		break;
	case ACHIEVEMENT_TIME_GAME_MORE_THAN_512_HOURS:
		return "ACHIEVEMENT_TIME_GAME_MORE_THAN_512_HOURS";
		break;
	case ACHIEVEMENT_TIME_GAME_MORE_THAN_1024_HOURS:
		return "ACHIEVEMENT_TIME_GAME_MORE_THAN_1024_HOURS";
		break;
	case ACHIEVEMENT_TOTAL_COUNT:
		return "ACHIEVEMENT_TOTAL_COUNT";
		break;
	default:
		return "UNKNOWN";
		break;
	}
}

GAME_EVENT convertBestTime(int _time)
{
	if (_time < 120)
		return TIME_LESS_THAN_2_MIN;
	else if (_time < 180)
		return TIME_LESS_THAN_3_MIN;
	else if (_time < 240)
		return TIME_LESS_THAN_4_MIN;
	else if (_time < 300)
		return TIME_LESS_THAN_5_MIN;
	else if (_time < 600)
		return TIME_LESS_THAN_10_MIN;
	return NONE;
}

GAME_EVENT convertOverallTime(int _time)
{
	if (_time > 3'686'400)
		return TIME_GAME_MORE_THAN_1024_HOURS;
	else if (_time > 1'843'200)
		return TIME_GAME_MORE_THAN_512_HOURS;
	else if (_time > 921'600)
		return TIME_GAME_MORE_THAN_256_HOURS;
	else if (_time > 460'800)
		return TIME_GAME_MORE_THAN_128_HOURS;
	else if (_time > 230'400)
		return TIME_GAME_MORE_THAN_64_HOURS;
	else if (_time > 115'200)
		return TIME_GAME_MORE_THAN_32_HOURS;
	else if (_time > 57'600)
		return TIME_GAME_MORE_THAN_16_HOURS;
	else if (_time > 28'800)
		return TIME_GAME_MORE_THAN_8_HOURS;
	else if (_time > 14'400)
		return TIME_GAME_MORE_THAN_4_HOURS;
	else if (_time > 7'200)
		return TIME_GAME_MORE_THAN_2_HOURS;
	return NONE;
}

ACHIEVEMENT GAME_EVENTtoACHIEVEMENT(GAME_EVENT _event)
{
	switch (_event)
	{
	case TIME_LESS_THAN_10_MIN:
		return ACHIEVEMENT_TIME_LESS_THAN_10_MIN;
		break;
	case TIME_LESS_THAN_5_MIN:
		return ACHIEVEMENT_TIME_LESS_THAN_5_MIN;
		break;
	case TIME_LESS_THAN_4_MIN:
		return ACHIEVEMENT_TIME_LESS_THAN_4_MIN;
		break;
	case TIME_LESS_THAN_3_MIN:
		return ACHIEVEMENT_TIME_LESS_THAN_3_MIN;
		break;
	case TIME_LESS_THAN_2_MIN:
		return ACHIEVEMENT_TIME_LESS_THAN_2_MIN;
		break;
	case TIME_GAME_MORE_THAN_2_HOURS:
		return ACHIEVEMENT_TIME_GAME_MORE_THAN_2_HOURS;
		break;
	case TIME_GAME_MORE_THAN_4_HOURS:
		return ACHIEVEMENT_TIME_GAME_MORE_THAN_4_HOURS;
		break;
	case TIME_GAME_MORE_THAN_8_HOURS:
		return ACHIEVEMENT_TIME_GAME_MORE_THAN_8_HOURS;
		break;
	case TIME_GAME_MORE_THAN_16_HOURS:
		return ACHIEVEMENT_TIME_GAME_MORE_THAN_16_HOURS;
		break;
	case TIME_GAME_MORE_THAN_32_HOURS:
		return ACHIEVEMENT_TIME_GAME_MORE_THAN_32_HOURS;
		break;
	case TIME_GAME_MORE_THAN_64_HOURS:
		return ACHIEVEMENT_TIME_GAME_MORE_THAN_64_HOURS;
		break;
	case TIME_GAME_MORE_THAN_128_HOURS:
		return ACHIEVEMENT_TIME_GAME_MORE_THAN_128_HOURS;
		break;
	case TIME_GAME_MORE_THAN_256_HOURS:
		return ACHIEVEMENT_TIME_GAME_MORE_THAN_256_HOURS;
		break;
	case TIME_GAME_MORE_THAN_512_HOURS:
		return ACHIEVEMENT_TIME_GAME_MORE_THAN_512_HOURS;
		break;
	case TIME_GAME_MORE_THAN_1024_HOURS:
		return ACHIEVEMENT_TIME_GAME_MORE_THAN_1024_HOURS;
		break;
	default:
		return ACHIEVEMENT_TOTAL_COUNT; // traktujemy jako default
		break;
	}
}