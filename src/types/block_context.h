#pragma once

#include <intx/intx.hpp>

#include "core.h"

class BlockContext {
public:
  BlockContext();
  BlockContext(address coinbase, uint64_t gasLimit, uint64_t timestamp,
               intx::uint256 number, intx::uint256 difficulty);

  address getCoinbase() const;
  std::string getCoinbaseString() const;

  //TODO: Implement simple functions like this inside this repo?
  uint64_t getGasLimit() const;
  uint64_t getTimestamp() const;
  intx::uint256 getNumber() const;
  intx::uint256 getDifficulty() const;
  uint64_t getChainId() const;

  intx::uint256 getBlockHash();
private:
  address coinbase;
  uint64_t gasLimit;
  uint64_t timestamp;
  intx::uint256 number;
  intx::uint256 difficulty;
  uint64_t chainId;
};
