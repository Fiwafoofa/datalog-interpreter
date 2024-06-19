#pragma once
#include <vector>
#include <sstream>
#include <string>
#include "Predicate.h"


class Rule {
public:

    Rule() {}

    Rule(Predicate headPredicate) : headPredicate(headPredicate) {}

    void setHeadPredicate(Predicate predicate) {
        headPredicate = predicate;
    }

    void addToPredicateList(Predicate predicate) {
        predicates.push_back(predicate);
    }

    std::string toString() const {
        std::stringstream ss;
        ss << headPredicate.toString() << " :- ";
        for (int i = 0; i < predicates.size(); i++) {
            ss << predicates.at(i).toString();
            if (i != predicates.size() - 1) {
                ss << ',';
            }
        }
        return ss.str();
    }

private:
    Predicate headPredicate;
    std::vector<Predicate> predicates = std::vector<Predicate>();

};