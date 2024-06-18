#include <vector>
#include <sstream>
#include <string>
#include "Predicate.h"


class Rule {
public:
    Rule(Predicate headPredicate) : headPredicate(headPredicate) {}

    std::string toString() const {
        std::stringstream ss;
        ss << headPredicate.toString() << " :- ";
        for (int i = 0; i < predicates.size(); i++) {
            ss << predicates.at(i).toString();
            if (i != predicates.size() - 1) {
                ss << ',';
            }
        }
        ss << '.';
        return ss.str();
    }


private:

    Predicate headPredicate;
    std::vector<Predicate> predicates = std::vector<Predicate>();

};