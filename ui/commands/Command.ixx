//
// Created by max on 4/16/26.
//

module;

#include <map>
#include <string>

export module Command;

export class Command {
protected:
    Command() = default;
public:
    virtual ~Command() = default;

    [[nodiscard]] virtual std::string getName() const = 0;
    virtual void exec(int clientId, std::map<std::string, std::string> args) const = 0;
};
