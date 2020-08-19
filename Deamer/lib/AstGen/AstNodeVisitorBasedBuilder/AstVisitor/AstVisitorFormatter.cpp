#include "Deamer/AstGen/AstNodeVisitorBasedBuilder/AstVisitor/AstVisitorFormatter.h"
#include <iostream>
#include <fstream>
#include <sstream>

void deamer::AstVisitorBuilder::AstVisitorFormatter::WriteOutputToFile(const std::string& file_path_location, const std::string& file_content) const
{
    std::ostringstream file_path;
    file_path << file_path_location;
    std::ofstream new_file;

    new_file.open(file_path.str(), std::ios_base::app);

    new_file << file_content << '\n';

    new_file.close();
}