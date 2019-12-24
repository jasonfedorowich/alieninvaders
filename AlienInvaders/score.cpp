#include "score.h"
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <algorithm>    // std::sort


std::vector<std::string> split(std::string str, char delim = ' ') {
	std::vector<std::string> cont;
	std::size_t current, previous = 0;
	current = str.find(delim);
	while (current != std::string::npos) {
		cont.push_back(str.substr(previous, current - previous));
		previous = current + 1;
		current = str.find(delim, previous);
	}
	cont.push_back(str.substr(previous, current - previous));

}

bool score_comparator(score _scoreA, score _scoreB) {
	return (_scoreA.value > _scoreB.value);
}

scoreboard::scoreboard(std::string file_name)
{
	std::vector<std::string> line_split_by_space;
	std::ifstream file(file_name);
	std::vector<score> scores;
	if (file.is_open()) {
		std::string line;
		while (getline(file, line)) {
			line_split_by_space = split(line);
			int value = std::stoi(line_split_by_space[1]);
			score _score(line_split_by_space[0], value);
			scores.push_back(_score);
		}
		file.close();
	}
	else
		throw std::exception("Failed to open scoreboard file");

	this->scores = scores;
	this->file_name = file_name;
}

void scoreboard::sort()
{
	std::sort(this->scores.begin(), this->scores.end(), score_comparator);
}

void scoreboard::save()
{
	std::ofstream file(file_name, std::ios::trunc);
	if (file.is_open()) {
		for (score _score : scores) {
			file << _score.name << " " << _score.value;
		}
		file.close();
	}
}

void scoreboard::trim()
{
	while (this->scores.size() > 100) {
		this->scores.pop_back();
	}
}

void scoreboard::add(std::string name, int value)
{
	score _score(name, value);
	this->scores.push_back(_score);
}

score::score(std::string name, int value)
{
	this->name = name;
	this->value = value;
}
