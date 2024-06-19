#pragma once
#include <vector>
#include <string>

class Scheme : public std::vector<std::string> {
public:
    Scheme(std::vector<std::string> names) : std::vector<std::string>(names) {}

    Scheme(const std::vector<Parameter>& schemeParameters) {
        std::vector<std::string> schemeColumns;
        for (const Parameter& parameter : schemeParameters) {
            schemeColumns.push_back(parameter.getTokenValue());
        }
        std::vector<std::string>(schemeColumns);
    }
};