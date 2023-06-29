/**
 * @file IFStream.hh
 * @author ryank231231
 * @brief
 * @version 0.1
 * @date 2023-02-04
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once
#include <corefoundation/common.h>
#undef SEEK_SET
#undef SEEK_CUR
#undef SEEK_END

/**
 * @brief file interface
*/
class IFStream {
 public:
  virtual ~IFStream(){};
  virtual bool isOpened() = 0;
  virtual usize Read(void* m_buffer, usize size) = 0;
  virtual usize Write(const void* m_buffer, usize size) = 0;
  virtual usize Tell() = 0;
  virtual usize Seek(usize pos, u8 whence) = 0;

 public:
  static const u8 FILE_READ = 1 << 0;
  static const u8 FILE_WRITE = 1 << 1;
  static const u8 FILE_APPEND = 1 << 2;

  static const u8 SEEK_SET = 0;
  static const u8 SEEK_CUR = 1;
  static const u8 SEEK_END = 2;
};
