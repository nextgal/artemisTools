/**
 * @file CMemoryFStream.hh
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
#include "IFStream.hh"

class CMemoryFStream final : public IFStream {
 public:
  // Inherited via IFStream
  virtual bool isOpened() override;
  virtual usize Read(void* buffer, usize size) override;
  virtual usize Write(const void* buffer, usize size) override;
  virtual usize Tell() override;
  virtual usize Seek(usize pos, u8 whence) override;

 public:
  CMemoryFStream(std::unique_ptr<std::vector<char>> buf);

  // TODO: make it private
 public:
  std::unique_ptr<std::vector<char>> fs;
  usize ptr = 0;
};
