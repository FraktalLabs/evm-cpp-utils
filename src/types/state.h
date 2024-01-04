# pragma once

#include <memory>

#include "account.h"

class State {
public:
  State() = default;
  State(const std::string& snapshot) { restore(snapshot); }
  
  virtual ~State() = default;

  virtual void snapshot(const std::string& filepath) {
    // For now : Use pretty-json like formatting
    std::string serialized = "[\n";
    for (auto it = state.begin(); it != state.end(); ++it) {
      serialized += "  {\n";
      serialized += "    \"";
      for (const auto &byte : it->first) {
        serialized += byteToHex(byte);
      }
      serialized += "\" : " + it->second->toSerialized();
      if (it == --state.end()) {
        serialized += "\n  }\n";
      } else {
        serialized += "\n  },\n";
      }
    }
    serialized += "]\n";

    // Open file for writing
    std::ofstream file(filepath);
    file << serialized;
    file.close();
  }

  virtual void restore(const std::string& filepath) {
    // Open file for reading
    std::ifstream file(filepath);
    std::string line;

    // Flatten json file
    std::string flattened;
    while (std::getline(file, line)) {
      // trim line
      line.erase(std::remove_if(line.begin(), line.end(), isspace), line.end());
      flattened += line;
    }
    file.close();

    // Parse flattened json
    // [ { "address": { value } }, { "address": { value } } ]
    
    // Loop through { "address": { value } } items
    std::string item;
    bool isItem = false;
    uint64_t bracketCount = 0;
    for (const auto &c : flattened) {
      if (c == '{') {
        isItem = true;
        bracketCount++;
        if (bracketCount != 1) {
          item += c;
        }
      } else if (c == '}') {
        bracketCount--;
        if (bracketCount == 0) {
          isItem = false;

          std::string key;
          std::string value;
          bool isKey = false;
          bool isValue = false;
          bool valueColon = false;
          for (const auto &c : item) {
            if (c == '"' && !isValue) {
              if (isKey) {
                isKey = false;
                isValue = true;
                valueColon = true;
              } else {
                isKey = true;
              }
            } else if (c == ':' && !isValue) {
              continue;
            } else if (c == ':' && valueColon) {
              valueColon = false;
              continue;
            } else if (isKey) {
              key += c;
            } else if (isValue) {
              value += c;
            }
          }
          uint8_t keyBytes[20];
          for (int i = 0; i < 20; i++) {
            std::string byteStr = key.substr(i * 2, 2);
            keyBytes[i] = static_cast<uint8_t>(std::stoi(byteStr, nullptr, 16));
          }
          std::array<uint8_t, 20> keyArray;
          std::copy(keyBytes, keyBytes + 20, keyArray.begin());
          insert(keyArray, std::make_shared<Account>(value));
          //state[keyBytes] = Account(value);

          item = "";
        } else {
          item += c;
        }
      } else if (isItem) {
        item += c;
      }
    }
  }

  virtual void insert(const address& addr, std::shared_ptr<Account> account) { state[addr] = account; }
  virtual void insert(const std::string& addr, std::shared_ptr<Account> account) { insert(parseAddress(addr), account); }

  virtual void remove(const address& addr) { state.erase(addr); }
  virtual void remove(const std::string& addr) { remove(parseAddress(addr)); }

  virtual std::shared_ptr<Account> get(const address& addr) const {
    auto it = state.find(addr);
    if (it == state.end()) {
      return nullptr;
    }
    return it->second;
  }
  virtual std::shared_ptr<Account> get(const std::string& addr) const { return get(parseAddress(addr)); }
protected:
  std::map<address, std::shared_ptr<Account>> state; // TODO: Use merkle structure
};
