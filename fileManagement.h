#ifndef FILEMANAGEMENT_H
#define FILEMANAGEMENT_H

#include "rune.h"
#include "runepage.h"
#include <string>
#include <vector>

std::vector<Rune> loadIndexFromFile(std::string const& path);
void saveRunePageToFile(const std::vector<Rune> &index, RunePage const& page, QString const& path);

#endif // FILEMANAGEMENT_H
