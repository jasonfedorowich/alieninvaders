#include "constants.h"
#include <fstream>


c_player::c_player()
{
}

c_player::~c_player()
{
}

c_blast::c_blast()
{
}

c_blast::~c_blast()
{
}

c_enemy::c_enemy()
{
}

c_enemy::~c_enemy()
{
}

game_constants::game_constants()
{
}

game_constants::~game_constants()
{
}


game_constants game_constants::load(std::string path)
{
	try {
		std::ifstream ifs(path);
		boost::archive::xml_iarchive ia(ifs);

		game_constants _constants;
		ia >> BOOST_SERIALIZATION_NVP(_constants);
		return _constants;
	}
	catch (std::exception e) {
		throw std::exception("Failed to load xml file");
	}
	
}

void save(game_constants _constants, std::string path)
{
	try {
		std::ofstream ofs(path);
		boost::archive::xml_oarchive oa(ofs);

		oa << BOOST_SERIALIZATION_NVP(_constants);
	}
	catch (std::exception e) {
		throw std::exception("Failed to save xml file");
	}

}
