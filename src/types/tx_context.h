#pragma once

#include <vector>

#include "core.h"

#include <intx/intx.hpp>

class TxContext {
public:
  TxContext();
  TxContext(address origin, intx::uint256 gasPrice);
  TxContext(const std::string& txContextFile);

  address getOrigin() const;
  std::string getOriginString();
  intx::uint256 getGasPrice() const;

  bytes getBlobHash(uint64_t index) const;
  std::string getBlobHashString(uint64_t index) const;

private:
  address origin;
  intx::uint256 gasPrice;
  // TODO: Not sure on this type
  std::vector<bytes> blobHashes;
};

