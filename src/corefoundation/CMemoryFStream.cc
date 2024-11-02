/**
 * @file CMemoryFStream.cc
 * @author ryank231231
 * @brief
 * @version 0.1
 * @date 2023-02-04
 *
 * @copyright Copyright (c) 2023
 *
 */

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

#include "core/CMemoryFStream.hh"

bool CMemoryFStream::isOpened() { return true; }

usize CMemoryFStream::Read(void* buffer, usize size) {
  // basic check
  if (size + ptr > this->fs->size()) {
    // overlap
    memcpy(buffer, this->fs->data() + ptr, this->fs->size() - ptr);
    ptr += (this->fs->size() - ptr);
    return this->fs->size() - ptr;
  }
  memcpy(buffer, this->fs->data() + ptr, size);
  ptr += size;
  return size;
}

usize CMemoryFStream::Write(const void* buffer, usize size) { return -1; }

usize CMemoryFStream::Tell() { return ptr; }

usize CMemoryFStream::Seek(usize pos, u8 whence) {
  switch (whence) {
    case SEEK_SET:
      ptr = pos;
      break;
    case SEEK_CUR:
      ptr += pos;
      break;
    case SEEK_END:
      // throw std::runtime_error("Not supported!");
      break;
    default:
      break;
  }
  return ptr;
}

CMemoryFStream::CMemoryFStream(std::unique_ptr<std::vector<char>> buf) {
  fs = std::move(buf);
}
