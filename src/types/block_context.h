#pragma once

#include <intx/intx.hpp>

#include "core.h"
#include "../utils/utils.h"

class BlockContext {
public:
  BlockContext() = default;
  BlockContext(address coinbase, uint64_t gasLimit, uint64_t timestamp,
               intx::uint256 number, intx::uint256 difficulty):
    coinbase(coinbase), gasLimit(gasLimit), timestamp(timestamp),
    number(number), difficulty(difficulty) {}
  BlockContext(const std::string& blockContextFile) { load(blockContextFile); }

  virtual void load(const std::string& blockContextFile) {
    // TODO
  }

  address getCoinbase() const { return coinbase; }
  std::string getCoinbaseString() const { return addressToHex(coinbase); }

  //TODO: Implement simple functions like this inside this repo?
  uint64_t getGasLimit() const { return gasLimit; }
  uint64_t getTimestamp() const { return timestamp; }
  intx::uint256 getNumber() const { return number; }
  intx::uint256 getDifficulty() const { return difficulty; }
  uint64_t getChainId() const { return chainId; }

  intx::uint256 getBlockHash() const {
    // TODO: Implement this
    return 42;
  }

private:
  address coinbase;
  uint64_t gasLimit;
  uint64_t timestamp;
  intx::uint256 number;
  intx::uint256 difficulty;
  uint64_t chainId;
};
