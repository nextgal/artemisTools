// Copyright (C) 2023 ryank231231 / The nextgal Team
// This file is part of artemisTools <https://github.com/nextgal/artemisTools>.
// 
// artemisTools is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
// 
// artemisTools is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with artemisTools. If not, see <http://www.gnu.org/licenses/>.
//
#include <asbutil/CScriptBlock.hh>
#include <corefoundation/core/CMemoryFStream.hh>
#include <format>
#include <memory>
#include <spdlog/fmt/bin_to_hex.h>
#include <spdlog/spdlog.h>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

using namespace std;

void asbparse(CMemoryFStream &asb) {
  char header[5]; // magic: ASB<version>\x00
  i32 blockCount;
  asb.Read(&header, sizeof(header));
  if (header[0] != 'A' | header[1] != 'S' | header[2] != 'B' |
      header[4] != 0x00) {
    spdlog::error("magic not match!");
    return;
  }

  auto version = header[3];
  asb.Read(&blockCount, sizeof(blockCount));
  // spdlog::info("blockCount: {:#x}", blockCount);

  for (auto i = 0; i < blockCount; ++i) {
    i32 type = 0;
    u32 size = 0;
    asb.Read(&type, sizeof(type));
    asb.Read(&size, sizeof(size));

    std::vector<char> tagname;
    tagname.resize(size + 1);
    asb.Read(tagname.data(), size + 1);

    std::string blockInfo;
    if (false) {
    } else if (type == 0) {
      i32 paramCount = 0;
      auto sb = std::make_shared<artemis::CScriptBlock>();
      sb->name = std::string(tagname.data()); // payload + 0
      asb.Read(&sb->line, sizeof(sb->line));
      asb.Read(&paramCount, sizeof(paramCount));

      blockInfo.append(std::format("[{}",
                                   tagname.data()));
      for (auto j = 0; j < paramCount; ++j) {
        u32 size = 0;
        asb.Read(&size, sizeof(size));
        std::vector<char> key;
        key.resize(size + 1);
        asb.Read(key.data(), size + 1);

        u32 size2 = 0;
        asb.Read(&size2, sizeof(size2));
        std::vector<char> value;
        value.resize(size2 + 1);
        asb.Read(value.data(), size2 + 1);

        blockInfo.append(
            std::format(" {}=\"{}\"", key.data(), value.data()));
      }
      blockInfo.append("]");
      spdlog::info(blockInfo);
    } else if (type == 1) {
      spdlog::info("*{}",tagname.data());
    }
  }
};

int main(int argc, char **argv) {
  if (argc != 2)
    return 1;
  spdlog::set_pattern("%v");
  FILE *handle = fopen(argv[1], "rb");
  if (!handle) {
    spdlog::error("cannot open file!");
    return -1;
  }
  fseek(handle, 0, CMemoryFStream::SEEK_END);
  auto size = ftell(handle);
  auto asbfile = std::make_unique<std::vector<char>>();
  asbfile->resize(size);
  rewind(handle);
  fread(asbfile->data(), sizeof(char), size, handle);
  CMemoryFStream asb(std::move(asbfile));

  asbparse(asb);
  return 0;
}
