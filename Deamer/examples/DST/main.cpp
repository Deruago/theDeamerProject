#include "Deamer/File/Generate/Compiler.h"
#include "Definition/CompilerGenerator.h"

using namespace DST;

int main()
{
	CompilerGenerator compiler;
	deamer::file::generate::Compiler WriteToDisk(compiler.Generate());
	WriteToDisk.Generate();
}
