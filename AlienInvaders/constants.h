#include <string>
#include <vector>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/string.hpp>
#pragma once
//TODO load in all constants function which will take xml and parse it TODO need XML parser librar
const float PLAYER_DAMAGE = 10.0f;
const float PLAYER_HEALTH = 100.0f;
const float ENEMY_SPEED = 5.0f;
const float ENEMY_DAMAGE = 5.0f;
const float ENEMY_HEALTH = 50.0f;
const float DEFAULT_SIZE = 128.0f;
const float DEFAULT_BLAST_SIZE = 64.0;
const float BLAST_SPEED = -10.0f;
const float ENEMY_BLAST_SPEED = 7.0f;


struct c_blast {

	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& BOOST_SERIALIZATION_NVP(_file);
		ar& BOOST_SERIALIZATION_NVP(_explosion);
	}
	c_blast();
	~c_blast();
	std::string _file;
	std::string _explosion;
};
struct c_player {
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& BOOST_SERIALIZATION_NVP(_animations);
		ar& BOOST_SERIALIZATION_NVP(_blast);
		ar& BOOST_SERIALIZATION_NVP(_explosion);
	}
	c_player();
	~c_player();
	std::vector<std::string> _animations;
	c_blast _blast;
	std::string _explosion;
};
struct c_enemy {
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& BOOST_SERIALIZATION_NVP(_animations);
		ar& BOOST_SERIALIZATION_NVP(_blast);
		ar& BOOST_SERIALIZATION_NVP(_explosion);
	}
	c_enemy();
	~c_enemy();
	std::vector<std::string> _animations;
	c_blast _blast;
	std::string _explosion;
};
struct game_constants {
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& BOOST_SERIALIZATION_NVP(_player);
		ar& BOOST_SERIALIZATION_NVP(_enemy);
	}
	game_constants();
	~game_constants();
	static game_constants load(std::string);
	c_player _player;
	c_enemy _enemy;

};

//TODO maybe use enum

void save(game_constants, std::string);