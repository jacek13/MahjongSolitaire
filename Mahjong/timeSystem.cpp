#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<chrono>	// Biblioteka chrono wspiera informacje o kalendarzu i czasie lokalnym dopiero w stanradzie C++20
#include<time.h>	// Zatem w celu zdobycia inforamcji o lokalnym czasie oraz dacie skorzystam z biblioteki jezyka C
#include<utility>

#include"timeSystem.h"
#include"Enum.h"

void timeSystem::init()
{
	load();

	startLoopTime = endLoopTime = std::chrono::steady_clock::now();
	elapsedSeconds = std::chrono::duration_cast<std::chrono::duration<double>>(endLoopTime - startLoopTime);
	sumOfElapsedSeconds = elapsedSeconds;
}

void timeSystem::start() noexcept
{
	startLoopTime = endLoopTime;
}

void timeSystem::update() noexcept
{
	endLoopTime = std::chrono::steady_clock::now();
	elapsedSeconds = std::chrono::duration_cast<std::chrono::duration<double>>(endLoopTime - startLoopTime);
	sumOfElapsedSeconds += elapsedSeconds;
	setTotalGameTime(getTotalGameTime() + elapsedSeconds.count());
}

void timeSystem::reset() noexcept
{
	sumOfElapsedSeconds = elapsedSeconds.zero();
}

void timeSystem::addTimePenalty(std::chrono::seconds _penalty) noexcept
{
	sumOfElapsedSeconds += _penalty;
}

std::pair<int,int> timeSystem::secToMinSecFormat(int _sec) noexcept// Czas wejsciowy jest podawany w sekundach
{
	std::pair<int, int>minSecFormat;
	minSecFormat.first = _sec / 60;		// integers  
	minSecFormat.second = _sec % 60;	// rest

	return minSecFormat;
}

double timeSystem::getTime()
{
	return sumOfElapsedSeconds.count();
}

double timeSystem::getLoopTime()
{
	return elapsedSeconds.count();
}

std::string timeSystem::getTimeAsString(bool _min_sec_format)
{
	std::stringstream buffer;
	std::string s;
	int tmp;

	buffer.clear();
	buffer.str("");
	tmp = static_cast<int>(sumOfElapsedSeconds.count());

	if (_min_sec_format)
	{
		auto pair = secToMinSecFormat(tmp);
		if(pair.second < 10)
			buffer << pair.first << ":0" << pair.second;
		else
			buffer << pair.first << ':' << pair.second;
	}
	else
		buffer << tmp;

	s = buffer.str();

	return s;
}

std::string timeSystem::getDate(char _separator)
{
	time_t now = time(nullptr);

	tm* t = std::localtime(&now);

	std::stringstream date("");
	date << t->tm_mday << _separator;
	if (1 + t->tm_mon < 10)
		date << '0' << 1 + t->tm_mon;
	else
		date << 1 + t->tm_mon;
	date << _separator << (1900 + t->tm_year);

	return date.str();
}

std::string timeSystem::getDaytime(char _separator)
{
	time_t now = time(nullptr);

	tm* dt = std::localtime(&now);

	std::stringstream daytime("");

	daytime << dt->tm_hour << _separator;
	if (dt->tm_min < 10)
		daytime << '0' << dt->tm_min << _separator;
	else
		daytime << dt->tm_min << _separator;
	if (dt->tm_sec < 10)
		daytime << '0' << dt->tm_sec;
	else
		daytime << dt->tm_sec;

	return daytime.str();
}

std::string timeSystem::getMonthYear(char _separator)
{
	time_t now = time(nullptr);

	tm* my = std::localtime(&now);

	std::stringstream monthYear("");

	if (1 + my->tm_mon < 10)
		monthYear << '0' << 1 + my->tm_mon;
	else
		monthYear << 1 + my->tm_mon;
	monthYear << _separator << my->tm_year + 1900;

	return monthYear.str();
}

double timeSystem::getPersonalBest()
{
	return fileSystem_Time::getBestTime();
}

double timeSystem::getOverallTime()
{
	return fileSystem_Time::getTotalGameTime();
}

bool timeSystem::isNewPersonalBest()
{
	return getBestTime() > sumOfElapsedSeconds.count() ? true : false;
}

bool timeSystem::saveGameInfo()
{
	auto tmp = convertBestTime(static_cast<int>(sumOfElapsedSeconds.count()));
	if (tmp != NONE)
		Subject::notify(tmp);

	tmp = convertOverallTime(static_cast<int>(getOverallTime()));
	if(tmp != NONE)
		Subject::notify(tmp);

	return fileSystem_Time::saveCSV(getDate().c_str(),getDaytime().c_str(),getMonthYear().c_str(),static_cast<int>(sumOfElapsedSeconds.count()));
}

void timeSystem::checkForUpdate()
{
	if (isNewPersonalBest())
		setBestTime(sumOfElapsedSeconds.count());
}

timeSystem::~timeSystem()
{
	save(true);
}