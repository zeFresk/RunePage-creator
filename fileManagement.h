#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include "rune.h"
#include "runepage.h"
#include <string>
#include <vector>

std::vector<Rune> loadIndexFromFile(std::string const& path);
void saveRunePageToFile(RunePage const& page, std::string path);

#endif // FILEMANAGEMENT_H
