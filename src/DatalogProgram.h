#include <sstream>
#include <string>
#include <vector>
#include <set>
#include "Predicate.h"
#include "Rule.h"

class DatalogProgram {
public:
    DatalogProgram() {}

    void addToSchemes(Predicate scheme) {
        schemes.push_back(scheme);
    }

    void addToFacts(Predicate fact) {
        facts.push_back(fact);
    }

    void addToRules(Rule rule) {
        rules.push_back(rule);
    }

    void addToQueries(Predicate query) {
        queries.push_back(query);
    }

    std::string toString() const {
        std::stringstream ss;
        ss << "Schemes(" << schemes.size() << "):\n";
        for (const Predicate& scheme : schemes) {
            ss << "  " << scheme.toString() << '\n';
        }
        ss << "\nFacts(" << facts.size() << "):\n";
        for (const Predicate& fact : facts) {
            ss << "  " << fact.toString() << ".\n";
        }
        ss << "\nRules(" << rules.size() << "):\n";
        for (const Rule& rule : rules) {
            ss << "  " << rule.toString() << ".\n";
        }
        ss << "\nQueries(" << queries.size() << "):\n";
        for (const Predicate& query : queries) {
            ss << "  " << query.toString() << "?\n";
        }
        ss << "\nDomain(" << domains.size() << "):\n";
        for (const Parameter& domain : domains) {
            ss << "  " << domain.toString() << '\n';
        }
        return ss.str();
    }


private:
    std::vector<Predicate> schemes;
    std::vector<Predicate> facts;
    std::vector<Rule> rules;
    std::vector<Predicate> queries;
    std::set<Parameter> domains;
};
