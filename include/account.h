#include <string>
#include <unordered_map>
#include <vector>

#include "order.h"

class Account {
    int user_id;
    std::string username;
    std::unordered_map<std::string, long long> owned_entities;
public:
    Account(int _user_id, std::string _username):
        user_id(_user_id), username(_username), owned_entities() {}
};