#include "healthbar.h"
#include <fstream>

healthbar_serializer::healthbar_serializer()
{
}
healthbar_serializer::~healthbar_serializer()
{
}
healthbar_serializer healthbar_serializer::load(std::string path)
{
	try {
		
		std::ifstream ifs(path);
		boost::archive::xml_iarchive ia(ifs);
		healthbar_serializer _healthbar;
		ia >> BOOST_SERIALIZATION_NVP(_healthbar);
		ia.delete_created_pointers();
		return _healthbar;
	}
	catch (std::exception e) {
		throw std::exception("Failed to load from xml file");
	}
	
}

void save(healthbar_serializer _healthbar, std::string path)
{
	try {
		std::ofstream ofs(path);
		boost::archive::xml_oarchive oa(ofs);

		oa << BOOST_SERIALIZATION_NVP(_healthbar);
	}
	catch (std::exception e) {
		throw std::exception("Failed to save xml file");
	}

}

healthbar::healthbar()
{
}

healthbar::~healthbar()
{
}

healthbar::healthbar(staticdisplaybuilder* builder) : staticdisplayobject(builder)
{

}

void healthbar::draw(int health)
{
	this->set_bitmap(this->get_animations()[health]);
	staticdisplayobject::draw();
}
