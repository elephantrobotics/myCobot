#ifndef mycobotsaver_h
#define mycobotsaver_h

#include <Arduino.h>
#include "FS.h"
#include "SPIFFS.h"
#define FORMAT_SPIFFS_IF_FAILED true

#define FILENAME "/Angles.txt"


class MycobotSaver
{
public:

	MycobotSaver();

	typedef struct{
	  int joint_angle[6];
	} saver_angles_enc;

	void listDir(fs::FS &fs, const char * dirname, uint8_t levels);
	void writeFile(fs::FS &fs, const char * path, const char * message);
	void appendFile(fs::FS &fs, const char * path, const char * message);
	void deleteFile(fs::FS &fs, const char * path);
	void readFile(fs::FS &fs, const char * path);
	saver_angles_enc processStringIntoInts(String string_input);


private:


};


#endif