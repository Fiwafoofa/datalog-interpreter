#pragma once
#include <string>
#include <sstream>
#include <set>
#include "Scheme.h"
#include "Tuple.h"

class Relation {
public:

    Relation(const std::string& name, const Scheme& scheme) : name(name), scheme(scheme) { }

    void addTuple(const Tuple& tuple) {
        tuples.insert(tuple);
    }

    Relation select(int index, const std::string& value) const {
        Relation result(name, scheme);
        for (Tuple tuple : tuples) {
            if (tuple.at(index) == value) {
                result.addTuple(tuple);
            }
        }
        return result;
    }

    Relation project(std::vector<int> positions) const {
        std::vector<std::string> projectedSchemes;
        for (const int& position : positions) {
            projectedSchemes.push_back(scheme.at(position));
        }
        Relation newRelation = Relation(name, projectedSchemes);
        for (Tuple tuple : tuples) {
            std::vector<std::string> projectedTuple;
            for (const int& position : positions) {
                projectedTuple.push_back(tuple.at(position));
            }
            newRelation.addTuple(Tuple(projectedTuple));
        }
        return newRelation;
    }

    Relation rename(const Scheme& newScheme) const {
        Relation newRelation = Relation(name, newScheme);
        for (Tuple tuple : tuples) {
            newRelation.addTuple(tuple);
        }
        return newRelation;
    }

    std::string toString() const {
        std::stringstream ss;      
        for (const Tuple& tuple : tuples) {
            ss << tuple.toString(scheme) << '\n';
        }
        return ss.str();
    }

private:

    std::string name;
    Scheme scheme;
    std::set<Tuple> tuples;

};