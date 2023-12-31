#pragma once

#include <vector>

#include "core.h"
#include "../utils/utils.h"

#include <intx/intx.hpp>

class TxContext {
public:
  TxContext() = default;
  TxContext(address origin, intx::uint256 gasPrice): origin(origin), gasPrice(gasPrice) {}
  TxContext(const std::string& txContextFile) { load(txContextFile); }

  virtual void load(const std::string& txContextFile) {
    // TODO
  }

  address getOrigin() const { return origin; }
  std::string getOriginString() const { return addressToHex(origin); }
  intx::uint256 getGasPrice() const { return gasPrice; }

  bytes getBlobHash(uint64_t index) const { return blobHashes[index]; }
  std::string getBlobHashString(uint64_t index) const { return bytecodeToHex(blobHashes[index]); }

private:
  address origin;
  intx::uint256 gasPrice;
  // TODO: Not sure on this type
  std::vector<bytes> blobHashes;
};

