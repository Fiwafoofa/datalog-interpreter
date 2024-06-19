#pragma once
#include <vector>
#include <string>
#include <sstream>
#include <stdexcept>
#include "Scheme.h"

class Tuple : public std::vector<std::string> {
public:

    Tuple(std::vector<std::string> values) : std::vector<std::string>(values) { }

    Tuple(const std::vector<Parameter>& factParameters) {
        std::vector<std::string> tupleValues;
        for (const Parameter& parameter : factParameters) {
            tupleValues.push_back(parameter.getTokenValue());
        }
        std::vector<std::string>(tupleValues);
    }

    std::string toString(const Scheme& scheme) const {
        if (scheme.size() != this->size()) {
            throw std::invalid_argument("Scheme must be same size as tuple");
        }
        std::stringstream ss;
        for (int i = 0; i < this->size(); i++) {
            ss << scheme.at(i) << '=' << this->at(i);
            if (i != this->size() - 1) {
                ss << ", ";
            }
        }
        return ss.str();
    }
};