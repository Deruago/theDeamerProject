#include "Deamer/FileBuilder/File.h"
#include "Deamer/FileBuilder/Directory.h"
#include "Deamer/FileBuilder/HFileBuilder/HFileBuilder.h"
#include <iostream>
#include <vector>
#include <string>

int main()
{
	std::vector<std::string> dirName = {"hello", "Wereld!"};
	deamer::Directory* dir = new deamer::Directory(dirName);
	deamer::File* fil = new deamer::File("123bestand", "exe");
	deamer::HFileBuilder* builder = new deamer::HFileBuilder(dir, fil);
	std::cout << builder->GetOutput();
	return 0;
}