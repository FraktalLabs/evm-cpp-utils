#pragma once

#include "../types/core.h"

bytes parseBytecode(const std::string& bytecode);
bytes parseBytecodeFile(const std::string& filename);
bytes parseBytes(const std::string& bytes);
address parseAddress(const std::string& addr);
std::string byteToHex(uint8_t byte);
std::string bytecodeToHex(const bytes& bytecode);
std::string addressToHex(const address& addr);

bytes compileContract(const std::string& source);