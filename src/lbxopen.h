// Opens up the mysterious .lbx files which Master of Magic uses
//
// Teemu Mäkinen <culkah@gmail.com> 2014

#ifndef LBXOPEN_H_
#define LBXOPEN_H_

#include <string>
#include <vector>
#include <memory>
#include <stdint.h>

// pack(push, 1) makes sure these can be loaded straight from stream
#pragma pack(push, 1)
struct LBXHeader {
	uint16_t numEntries;  // Number of entries
	uint16_t ADFE;        // ADFE?
	uint16_t mystery;     // ???
	uint16_t fileType;    // Type of file: sound, array, animation etc.
};

struct LBXSoundHeader {
	uint16_t magic;       // ??
	uint16_t type;        // Sound file type
	uint16_t reserved;    // ??
};

struct LBXArrayHeader {
	uint16_t numElements; // Number of elements
	uint16_t elementSize; // Size of each element
};
#pragma pack(pop)

struct LBXPalette {
    ~LBXPalette();
	uint16_t offset;
	uint16_t firstColor;
	uint16_t colorCount;
	uint8_t* data;
};

struct LBXAnimation {
	LBXAnimation(uint16_t width_, uint16_t height_, uint16_t numFrames_, LBXPalette* palette_, std::vector<uint32_t> frame_, uint8_t* data_, std::string &name_);
	~LBXAnimation();
	uint16_t width;       // Image width
	uint16_t height;      // Image height
	uint16_t numFrames;   // Number of frames in each image
	std::shared_ptr<LBXPalette> palette;  // Palette information
	std::vector<uint32_t> frame;
	uint8_t* data;
	std::string name;
};


class LBXopen {
public:
	LBXopen();
	~LBXopen();

	LBXHeader readHeader(std::ifstream &stream);
	std::vector<uint32_t> readEntries(std::ifstream &stream);
	std::vector<std::string> readAnnotations(std::ifstream &stream, const uint32_t &endpos);
	LBXAnimation* readAnimation(std::ifstream &stream, const uint32_t &location, std::string &name);
	std::vector<uint32_t> readAnimationEntry(std::ifstream &stream);

	bool openFile(std::string filename);
	std::vector<LBXAnimation*> openAnimationFile(std::string filename);
	bool openSoundFile(std::string filename);

private:

};

#endif
