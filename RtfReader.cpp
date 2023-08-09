#include <sstream>

#include "RtfReader.h"
#include "cpp/text.h"

bool RtfReader::RtfStream2TextString(std::string &outstring, std::istream &instream)
{
	try
	{
		// "{\r" at the beginning, the RTF file is considered
		char head[3] = { 0 };
		instream.read(head, sizeof(head));
		if (head[0] != '{' || head[1] != '\\' || head[2] != 'r')
		{
			return false;
		}

		instream.seekg(0, ios::beg);
        format::utils::stream_logger log(cerr, true, true, true);
        format::utils::stream_source src(instream);
		std::stringstream stream;
		RtfReader::text proc(stream);

		format::parsers::rtf parser(src, proc, log);
		outstring = stream.str();
	}
	catch (...)
	{
		return false;
	}
	return true;
}


bool RtfReader::RtfString2TextString(std::string &outstring, const std::string &instring)
{
	std::stringstream instream(instring);
	return RtfStream2TextString(outstring, instream);
}


bool RtfReader::RtfFile2TextString(std::string &outstring, const char * filename)
{
    std::ifstream file(filename);
	if (file.is_open())
	{
		bool ret = RtfStream2TextString(outstring, file);
		file.close();
		return ret;	
	}
	return false;
}
