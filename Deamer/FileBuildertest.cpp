#include "Deamer/FileBuilder/File.h"
#include "Deamer/FileBuilder/Directory.h"
#include "Deamer/FileBuilder/HFileBuilder/HFileBuilder.h"
#include <iostream>
#include <vector>
#include <string>
#include "./testFileMacro.h"

using namespace deamer;

FileFunctionSection* createNewFunction(std::string funcName, std::vector<FileVariable*> args, FileVariableType* returnType, FileVariableType* scope)
{
	return new FileFunctionSection(new FileFunctionPrototypeSection(funcName, args, returnType, scope));
}

FileVariable* createNewVariable(FileVariableType* scope, std::string varName)
{
	return new FileVariable(scope, varName, false);
}

FileVariable* createNewVariable(FileVariableType* scope, std::string varName, bool isMember)
{
	return new FileVariable(scope, varName, isMember);
}

FileClassSection* _int = new FileClassSection("int", nullptr);
FileClassSection* _unsigned = new FileClassSection("unsigned", nullptr);
FileClassSection* _char = new FileClassSection("char", nullptr);	

int oldTestWithoutMacro()
{
	HFileBuilder* builder = new HFileBuilder({"hello", "Wereld!"}, "123bestand", "exe");
	
	auto namespace_base = new FileNamespaceSection("base_A");
	auto namespace_base2 = new FileNamespaceSection(namespace_base, "base_B");
	auto namespace_sub = new FileNamespaceSection(namespace_base2, "sub_C");
	
	auto class_a = new FileClassSection("class_a", namespace_sub);
	
	builder->GetHeaderSection()->AddClass(class_a);
	
	auto _testVar1 = createNewVariable(_char, "test1");
	auto _testVar2 = createNewVariable(_unsigned, "test2", true);
	auto _testVar3 = createNewVariable(class_a, "test3", true);
	
	class_a->AddPrivateMember("testfunction1", {_testVar1, _testVar2}, _int);
	class_a->AddProtectedMember("testfunction2", {_testVar1, _testVar3}, _int);
	class_a->AddPublicMember("testfunction3", {_testVar1, _testVar2, _testVar3}, _int);
	
	std::cout << builder->GetOutput();
	return 0;
}

int main()
{
	HFileBuilder* builder = new HFileBuilder({"hello", "Wereld!"}, "123bestand", "exe");
	
	new_namespace(base_A);
	new_namespace(base_A, base_B);
	new_namespace(base_B, sub_C);
	
	new_class(class_a, sub_C);
	
	builder->GetHeaderSection()->AddClass(class_a);
	
	new_var(_char, test1);
	new_var(_unsigned, test2, true);
	new_var(class_a, test3, true);
	
	class_a->AddPrivateMember("testfunction1", {test1, test2}, _int);
	class_a->AddProtectedMember("testfunction2", {test1, test3}, _int);
	class_a->AddPublicMember("testfunction3", {test1, test2, test3}, _int);
	
	get_output(builder);
	return 0;
}