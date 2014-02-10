// Resource files to be loaded
//
// Teemu Mäkinen <culkah@gmail.com> 2014


#ifndef RESOURCES_H_
#define RESOURCES_H_

#include <string>

const unsigned int resource_figures_size = 17;

const std::string resource_dir = "lbx/";

const std::string resource_figures[resource_figures_size] = {
	"FIGURES1.LBX",
	"FIGURES2.LBX",
	"FIGURES3.LBX",
	"FIGURES4.LBX",
	"FIGURES5.LBX",
	"FIGURES6.LBX",
	"FIGURES7.LBX",
	"FIGURES8.LBX",
	"FIGURES9.LBX",
	"FIGURE10.LBX",
	"FIGURE11.LBX",
	"FIGURE12.LBX",
	"FIGURE13.LBX",
	"FIGURE14.LBX",
	"FIGURE15.LBX",
	"FIGURE16.LBX",
    "MAINSCRN.LBX"
};

const std::string resource_xml_dir = "xml/";

const unsigned int resource_unit_stats_size = 1;

const std::string resource_unit_stats[resource_unit_stats_size] = {
    "darkelf.xml"
};

#endif
