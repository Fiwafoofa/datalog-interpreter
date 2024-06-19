#pragma once
#include <string>
#include <sstream>
#include <vector>
#include "Parameter.h"

class Predicate {
public:

    Predicate() {}

    void setName(std::string newName) {
        name = newName;
    }

    std::string getName() const {
        return name;
    }

    void addParameter(Parameter parameter) {
        parameters.push_back(parameter);
    }

    std::vector<Parameter> getParameters() const {
        return parameters;
    }

    std::string toString() const {
        std::stringstream ss;
        ss << name << '(';
        for (int i = 0; i < parameters.size(); i++) {
            ss << parameters.at(i).toString();
            if (i != parameters.size() - 1) {
                ss << ',';
            }
        }
        ss << ')';
        return ss.str();
    }

private:
    std::string name;
    std::vector<Parameter> parameters = std::vector<Parameter>();

};