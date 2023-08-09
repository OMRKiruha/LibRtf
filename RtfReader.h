#ifndef __RTFREADER_H__
#define __RTFREADER_H__

#include <string>

namespace RtfReader
{
	bool RtfStream2TextString(std::string &outstring, std::istream &instream);
	bool RtfString2TextString(std::string &outstring, const std::string &instring);
	bool RtfFile2TextString(std::string &outstring, const char *filename);
}

#endif
