#include <string>
#include <sstream>
#include <vector>
#include "Parameter.h"

class Predicate {
public:

    Predicate(std::string name) : name(name) {}

    void addParameter(Parameter parameter) {
        parameters.push_back(parameter);
    }

    std::string getName() const {
        return name;
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