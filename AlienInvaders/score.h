#include <vector>
#include <string>
#pragma once

struct score;
class scoreboard {
private:
	std::vector<score> scores;
	std::string file_name;
public:
	scoreboard(std::string);
	void sort();
	void save();
	void trim();
	void add(std::string, int);
	std::vector<score> get_scores();
};
struct score {

	std::string name;
	int value;
	score(std::string, int);
	std::string to_string();
};