#include "Util.h"
#pragma warning(disable : 4996)

namespace fs = std::filesystem;

std::string Util::getCurrentTime()
{
    std::time_t current_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::string result= std::string(std::ctime(&current_time));
	std::replace(result.begin(), result.end(), ':', '_');
	result.erase(std::remove(result.begin(), result.end(), '\n'), result.end());
	return result;

}
std::string Util::getCurrentPath()
{
    return fs::current_path().generic_string();
}
bool Util::doesDirectoryExist(std::string dirName)
{
	fs::path pathToDir(dirName);
	return fs::is_directory(pathToDir);
}

void Util::createDirectory(std::string dirName)
{
	fs::path pathToDir(dirName);
	fs::create_directory(pathToDir);
}
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
void Util::messageBox(std::string message)
{
    //to do
}
#else
void Util::messageBox(std::string message)
{
        std::string s1="/usr/bin/notify-send Message ";
        std::string s2="\""+message+"\"";
        std::string s3=s1+s2;
        const char* msg=s3.data();
        system(msg);
}
	#endif
