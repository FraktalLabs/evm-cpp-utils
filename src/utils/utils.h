#pragma once

#include <fstream>
#include <iomanip>

#include "../types/core.h"

// TODO: Reconsider using inline functions

inline bytes parseBytecode(const std::string& bytecode) {
  bytes result;
  for(int i = 0; i < bytecode.size(); i += 2) {
    std::string byteString = bytecode.substr(i, 2);
    uint8_t byte = std::stoi(byteString, nullptr, 16);
    result.push_back(byte);
  }

  return result;
};

inline bytes parseBytecodeFile(const std::string& filename) {
  std::ifstream file(filename);
  std::string bytecode;
  std::getline(file, bytecode);
  // TODO: handle errors & multiple lines
  return parseBytecode(bytecode);
};

inline bytes parseBytes(const std::string& byteStr) {
  bytes result;
  for(int i = 0; i < byteStr.size(); i += 2) {
    std::string byteString = byteStr.substr(i, 2);
    uint8_t byte = std::stoi(byteString, nullptr, 16);
    result.push_back(byte);
  }

  return result;
};

inline address parseAddress(const std::string& addr) {
  address result;
  for(int i = 0; i < addr.size(); i += 2) {
    std::string byteString = addr.substr(i, 2);
    uint8_t byte = std::stoi(byteString, nullptr, 16);
    result[i / 2] = byte;
  }

  return result;
}

inline std::string byteToHex(uint8_t byte) {
  std::stringstream ss;
  ss << std::setfill('0') << std::setw(2) << std::hex << static_cast<int>(byte);
  return ss.str();
}

inline std::string bytecodeToHex(const bytes& bytecode) {
  std::stringstream ss;
  for(uint8_t byte : bytecode) {
    ss << byteToHex(byte);
  }
  return ss.str();
}

inline std::string addressToHex(const address& address) {
  std::stringstream ss;
  for (int i = 0; i < 20; i++) {
    ss << byteToHex(address[i]);
  }
  return ss.str();
}

inline bytes compileContract(const std::string& source) {
  // TODO: implement
  return bytes();
}
