#include "GameStatistics.hpp"
#include <iomanip>
#include <iostream>


GameStatistics::GameStatistics() : _file("Save/saveStatistics.txt")
{

}

void GameStatistics::incrementGameStarts() {
	++gameStarts;
}

void GameStatistics::incrementClicks() {
	++clicks;
}

void GameStatistics::updateGameTime(float deltaTime) {
	totalTime += deltaTime;
}

std::string GameStatistics::getTotalGameTime() const {
	int minutes = static_cast<int>(totalTime / 60);
	int seconds = static_cast<int>(totalTime) % 60;
	return std::to_string(minutes) + "." + (seconds < 10 ? "0" : "") + std::to_string(seconds);
}

void GameStatistics::saveStatistics() {
	std::ofstream file(_file);
	if (file) {
		file << "timePlaying=" << getTotalGameTime() << std::endl;
		file << "gameOpenned=" << gameStarts << std::endl;
		file << "clicks=" << clicks << std::endl;
	}
	else {
		std::cerr << "Unable to open file for writing: " << _file << std::endl;
	}
}

void GameStatistics::loadStatistics()
{
	gameStarts = static_cast<unsigned int>(std::stoi(getParamFromString("gameOpenned", _file)));
	clicks = static_cast<unsigned int>(std::stoi(getParamFromString("clicks", _file)));

	std::string timeStr = getParamFromString("timePlaying", _file);
	size_t dotPos = timeStr.find('.');
	int minutes = std::stoi(timeStr.substr(0, dotPos));
	int seconds = std::stoi(timeStr.substr(dotPos + 1));
	totalTime = static_cast<float>(minutes * 60 + seconds); // convert into seconds
}

unsigned int GameStatistics::getGameStarts() const {
	return gameStarts;
}

unsigned int GameStatistics::getClicks() const {
	return clicks;
}

std::string GameStatistics::getParamFromString(std::string param, const std::string& file) {
	std::fstream fileStream(file);
	std::string line;
	std::string emptyStr("");

	if (!fileStream) {
		std::cerr << "Can't open input file" << std::endl;
		return emptyStr;
	}
	while (std::getline(fileStream, line)) {
		if (line.find(param) != line.npos) {

			size_t pos = line.find(param + "=");
			if (pos != std::string::npos) {
				return line.substr(pos + param.length() + 1);
			}

		}
	}
	return emptyStr;
}

void GameStatistics::saveSettingsValue(const std::string& param, const std::string& file, const std::string& newValue) {
	std::ifstream fileStream(file);
	std::string line;
	std::vector<std::string> lines;
	bool found = false;

	if (!fileStream) {
		std::cerr << "Cannot open file for reading: " << file << std::endl;
		return;
	}
	while (std::getline(fileStream, line)) {
		size_t pos = line.find(param + "=");
		if (pos != std::string::npos) {
			line = param + "=" + newValue; // Replace the entire line
			found = true;
		}
		lines.push_back(line);
	}
	fileStream.close();
	if (!found)
		std::cerr << "Parameter not found in file: " << param << std::endl;

	// Rewrite the file
	std::ofstream outFile(file);
	for (const auto& outLine : lines) {
		outFile << outLine << std::endl;
	}
	return;
}
