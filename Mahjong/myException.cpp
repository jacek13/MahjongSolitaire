#include<iostream>

#include"myException.h"

const char* myException::what() const noexcept
{
	return message.empty() ? "Unknown ERROR!" : message.c_str();
}

const char* myException_Engine::what() const noexcept
{
	return message.empty() ? "Unknown engine ERROR!" : message.c_str();
}

const char* myException_fileSystem::what() const noexcept
{
	return message.empty() ? "Unknown fileSystem ERROR!" : message.c_str();
}

const char* myException_Board::what() const noexcept
{
	return message.empty() ? "Unknown board ERROR!" : message.c_str();
}