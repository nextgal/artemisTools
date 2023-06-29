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
