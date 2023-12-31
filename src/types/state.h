# pragma once

#include <memory>

#include "account.h"

class State {
public:
  State();
  State(const std::string& snapshot);

  void snapshot(const std::string&);
  void restore(const std::string&);

  void insert(const address&, const Account&);
  void insert(const std::string&, const Account&);
  void remove(const address&);
  void remove(const std::string&);

  std::shared_ptr<Account> get(const address&);
  std::shared_ptr<Account> get(const std::string&);
private:
  std::map<address, Account> accounts; // TODO: Use merkle structure
};
