# pragma once

#include <string>
#include <map>

#include "core.h"
#include "../utils/utils.h"

#include <intx/intx.hpp>
#include <ethash/keccak.h>

// TODO: Visit which functions should be virtual and which not
class Account {
public:
  Account() = default;
  Account(const std::string& serialized) { fromSerialized(serialized); }

  virtual ~Account() = default;

  virtual std::string toString() const { return "Account{nonce=" + std::to_string(nonce) + ", balance=" + to_string(balance) + ", storage=" + std::to_string(storage.size()) + ", code=" + std::to_string(code.size()) + "}"; }

  virtual std::string toSerialized() const {
    // For now : Use pretty-json like formatting
    std::string serialized = "{\n";
    serialized += "      \"nonce\": " + std::to_string(nonce) + ",\n";
    serialized += "      \"balance\": " + to_string(balance) + ",\n";
    serialized += "      \"storage\": [\n";
    for (auto it = storage.begin(); it != storage.end(); ++it) {
      serialized += "        \"" + to_string(it->first) + "\": " + to_string(it->second) + "";
      if (std::next(it) != storage.end()) {
        serialized += ",";
      }
      serialized += "\n";
    }
    serialized += "      ],\n";
    serialized += "      \"code\": \"";
    for (const auto &byte : code) {
      serialized += byteToHex(byte);
    }
    serialized += "\"\n";
    serialized += "    }";
    return serialized;
  }

  virtual void fromSerialized(const std::string& serialized) {
    // Parse the flattened json like
    // {"nonce"123,"balance"3001,"storage"[],"code""6020600052"}
    size_t i = 0;
    for (; i < serialized.size(); ++i) {
      if (serialized[i] == '{') {
        continue;
      } else if (serialized[i] == '"') {
        // Parse key
        std::string key; 
        for (++i; serialized[i] != '"'; ++i) {
          key += serialized[i];
        }
        ++i; // Skip the closing "
        ++i; // Skip the :
        if (key == "nonce") {
          // Parse nonce
          std::string nonceStr;
          for (; serialized[i] != ','; ++i) {
            nonceStr += serialized[i]; 
          }
          nonce = std::stoull(nonceStr);
        } else if (key == "balance") {
          // Parse balance
          std::string balanceStr;
          for (; serialized[i] != ','; ++i) {
            balanceStr += serialized[i];
          }
          balance = intx::from_string<intx::uint256>(balanceStr);
        } else if (key == "storage") {
          // Parse storage
          for (; serialized[i] != '['; ++i) {}
          for (++i; serialized[i] != ']'; ++i) {
            // Parse key
            std::string keyStr;
            for (++i; serialized[i] != '"'; ++i) {
              keyStr += serialized[i];    
            }
            ++i; // Skip the closing "
            ++i; // Skip the :
            // Parse value
            std::string valueStr;
            for (; serialized[i] != ',' && serialized[i] != ']'; ++i) {
              valueStr += serialized[i];
            }
            storage[intx::from_string<intx::uint256>(keyStr)] = intx::from_string<intx::uint256>(valueStr);
            if (serialized[i] == ']') {  
              break;
            }
          }
        } else if (key == "code") {
          // Parse code
          ++i; // Skip the opening "
          for (; serialized[i] != '"'; ++i) {
            uint8_t byte = (uint8_t) strtol(serialized.substr(i, 2).c_str(), nullptr, 16);
            code.push_back(byte);
            ++i;
          }
        }
      } 
    }
  }

  uint64_t getNonce() const { return nonce; }
  virtual void setNonce(uint64_t value) { nonce = value; }
  intx::uint256 getBalance() const { return balance; }
  virtual void setBalance(const intx::uint256& value) { balance = value; }

  intx::uint256 getStorage(const intx::uint256& key) const {
    auto it = storage.find(key);
    if (it == storage.end()) {
      return 0;
    }
    return it->second;
  }
  virtual void setStorage(const intx::uint256& key, const intx::uint256& value) { storage[key] = value; }

  bytes getCode() const { return code; }
  virtual void setCode(const bytes& bytecode) { code = bytecode; }
  virtual void setCode(const std::string& bytecode) { code = parseBytecode(bytecode); }
  uint64_t getCodeSize() const { return code.size(); }
  uint8_t* getCodePtrAt(uint64_t offset) const { return (uint8_t*) &code[offset]; }
  intx::uint256 getCodeHash() const { return intx::be::load<intx::uint256>(ethash_keccak256(getCodePtrAt(0), getCodeSize())); }

private:
  uint64_t nonce;
  intx::uint256 balance;
  std::map<intx::uint256, intx::uint256> storage; // TODO: use a merkle tree type structure?
  bytes code;
};
