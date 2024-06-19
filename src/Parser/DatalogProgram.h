#pragma once
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

    void addToDomains(std::string domain) {
        domains.insert(domain);
    }

    std::vector<Predicate> getSchemes() const {
        return schemes;
    }

    std::vector<Predicate> getFacts() const {
        return facts;
    }

    std::vector<Rule> getRules() const {
        return rules;
    }

    std::vector<Predicate> getQueries() const {
        return queries;
    }

    std::set<std::string> getDomains() const {
        return domains;
    }

    std::string toString() const {
        std::stringstream ss;
        ss << "Schemes(" << schemes.size() << "):\n";
        for (const Predicate& scheme : schemes) {
            ss << "  " << scheme.toString() << '\n';
        }
        ss << "Facts(" << facts.size() << "):\n";
        for (const Predicate& fact : facts) {
            ss << "  " << fact.toString() << ".\n";
        }
        ss << "Rules(" << rules.size() << "):\n";
        for (const Rule& rule : rules) {
            ss << "  " << rule.toString() << ".\n";
        }
        ss << "Queries(" << queries.size() << "):\n";
        for (const Predicate& query : queries) {
            ss << "  " << query.toString() << "?\n";
        }
        ss << "Domain(" << domains.size() << "):\n";
        for (const std::string& domain : domains) {
            ss << "  " << domain << '\n';
        }
        return ss.str();
    }

private:
    std::vector<Predicate> schemes;
    std::vector<Predicate> facts;
    std::vector<Rule> rules;
    std::vector<Predicate> queries;
    std::set<std::string> domains;
};
