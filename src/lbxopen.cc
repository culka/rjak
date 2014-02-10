// Opens up the mysterious .lbx files which Master of Magic uses
// This file contains the implementation
// Teemu Mäkinen <culkah@gmail.com> 2014

#include "lbxopen.h"
#include <fstream>
#include <vector>

LBXAnimation::LBXAnimation(uint16_t width_, uint16_t height_, uint16_t numFrames_, LBXPalette* palette_,
		                   std::vector<uint32_t> frame_, uint8_t* data_, std::string &name_) : width(width_), height(height_),
		                   numFrames(numFrames_), palette(palette_), frame(frame_), data(data_), name(name_)

{

}

LBXAnimation::~LBXAnimation() {
	if (data != nullptr) {
		delete[] data;
		data = nullptr;
	}
    /*
	if (palette != nullptr) {
		delete palette;
		palette = nullptr;
	}*/
}

LBXPalette::~LBXPalette() {
    if (data != nullptr) {
        delete[] data;
        data = nullptr;
    }
}

LBXopen::LBXopen() {

}

LBXopen::~LBXopen() {

}

LBXHeader LBXopen::readHeader(std::ifstream &stream) {
	LBXHeader header;
	stream.read(reinterpret_cast<char*>(&header), sizeof(LBXHeader));
	return header;
}

std::vector<uint32_t> LBXopen::readEntries(std::ifstream &stream) {
	std::vector<uint32_t> entry;
	entry.resize(126);
	for (unsigned int i = 0; i < 126; ++i)
	{
		stream.read(reinterpret_cast<char*>(&entry[i]), sizeof(uint32_t));
	}
	return entry;
}

std::vector<std::string> LBXopen::readAnnotations(std::ifstream &stream, const uint32_t &endpos) {
	std::vector<std::string> annotation;

	while (stream.tellg() != endpos)
	{
		char* buffer = new char[32];
		stream.read(buffer, 32);
		std::string tempstring;
		for (unsigned int j = 0; j < 8; ++j)
		{
			if (buffer[j] != 0)
			{
				tempstring.push_back(buffer[j]);
			}
		}
		annotation.push_back(tempstring);
		delete[] buffer;
	}

	return annotation;
}

LBXAnimation* LBXopen::readAnimation(std::ifstream &stream, const uint32_t &location, std::string &name) {

	LBXPalette* pal = nullptr;
	uint16_t width;					// 0  Image width
	uint16_t height;				// 2  Image height
	uint16_t numFrames;				// 6  Number of frames in each image
	uint16_t palette;				// 14 Palette location
	std::vector<uint32_t> frame;	// 18 Frame locations in file, last one is address for the end

	stream.seekg(location);
	stream.read(reinterpret_cast<char*>(&width), sizeof(uint16_t));
	stream.read(reinterpret_cast<char*>(&height), sizeof(uint16_t));
	stream.seekg(location + 6);
	stream.read(reinterpret_cast<char*>(&numFrames), sizeof(uint16_t));
	stream.seekg(location + 14);
	stream.read(reinterpret_cast<char*>(&palette), sizeof(uint16_t));

	stream.seekg(location + 18);
	for (uint16_t i = 0; i <= numFrames; ++i) {
		frame.push_back(uint32_t());
		stream.read(reinterpret_cast<char*>(&frame.back()), sizeof(uint32_t));
	}

	stream.seekg(location + frame[0]);
	uint8_t* data = new uint8_t[frame[numFrames] - frame[0]];
	stream.read(reinterpret_cast<char*>(data), frame[numFrames] - frame[0]);

	if (palette != 0) {
		pal = new LBXPalette;

		stream.seekg(location + palette);
		stream.read(reinterpret_cast<char*>(&(pal->offset)), sizeof(uint16_t));
		stream.read(reinterpret_cast<char*>(&(pal->firstColor)), sizeof(uint16_t));
		stream.read(reinterpret_cast<char*>(&(pal->colorCount)), sizeof(uint16_t));

		pal->data = new uint8_t[3*pal->colorCount];

		stream.seekg(location + pal->offset);
		stream.read(reinterpret_cast<char*>(pal->data), 3*pal->colorCount*sizeof(uint8_t));
	}

	return new LBXAnimation(width, height, numFrames, pal, frame, data, name);
}

std::vector<uint32_t> LBXopen::readAnimationEntry(std::ifstream &stream) {
	std::vector<uint32_t> entry;

	return entry;
}


bool LBXopen::openFile(std::string filename) {
	return 1;
}

std::vector<LBXAnimation*> LBXopen::openAnimationFile(std::string filename) {

	std::vector<LBXAnimation*> images;

	std::ifstream file;

	file.open(filename, std::istream::binary);

	if (!file.is_open()) return images;

	LBXHeader header = readHeader(file);

	std::vector<uint32_t> entry = readEntries(file);

	std::vector<std::string> annotations = readAnnotations(file, entry[0]);

	for(unsigned int i = 0; i < 126; ++i) {
		if (entry[i] != 0 && (i != 124 && entry[i + 1] != 0)) {
			LBXAnimation* ani = readAnimation(file, entry[i], annotations[i]);
			if (i > 0 && images.back()->palette.get() != nullptr) ani->palette = images.back()->palette;
            images.push_back(ani);
		}
		else break;
	}

	file.close();

	return images;
}

bool LBXopen::openSoundFile(std::string filename) {
	return false;
}
