#pragma once
#include <map>
#include <string>

// #include "ISerializable.hh"

namespace artemis {
struct ISerializable {};

struct CScriptBlock : public ISerializable {
  std::string name;
  std::map<std::string, std::string> params;
  std::string file;
  int line;
};
}  // namespace artemis
