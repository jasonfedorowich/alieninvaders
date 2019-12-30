#include <string>
#include <map>
#include <boost/archive/xml_oarchive.hpp>
#include <boost/archive/xml_iarchive.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/string.hpp>
#include "staticdisplayobject.h"
#pragma once

struct healthbar_serializer {
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version) {
		ar& BOOST_SERIALIZATION_NVP(_animations);
	}
	healthbar_serializer();
	~healthbar_serializer();
	std::map<int, std::string> _animations;
	static healthbar_serializer load(std::string);
};

void save(healthbar_serializer, std::string);

class healthbar: public staticdisplayobject {
public:
	healthbar();
	~healthbar();
	healthbar(staticdisplaybuilder*);
	void draw(int);
};