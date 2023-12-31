# pragma once

#include <string>
#include <map>

#include "core.h"

#include <intx/intx.hpp>

class Account {
public:
  Account();
  Account(const std::string&);

  std::string toString() const;
  std::string toSerialized() const;

  uint64_t getNonce() const;
  intx::uint256 getBalance() const;
  intx::uint256 getStorage(const intx::uint256&) const;
  void setStorage(const intx::uint256& key, const intx::uint256& value);

  void setCode(const bytes& bytecode);
  void setCode(const std::string& bytecode);
  uint64_t getCodeSize() const;
  uint8_t* getCodePtrAt(uint64_t offset) const;
  intx::uint256 getCodeHash() const;

private:
  uint64_t nonce;
  intx::uint256 balance;
  std::map<intx::uint256, intx::uint256> storage; // TODO: use a merkle tree type structure?
};
