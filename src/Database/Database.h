#pragma once
#include <map>
#include <string>
#include <stdexcept>
#include "Relation.h"
#include "DatalogProgram.h"

class Database {
public:
    Database() {}

    void addRelation(std::string name, const Scheme& scheme) {
        Relation relation = Relation(name, scheme);
        namesToRelations[name] = relation;
    }

    void addTupleToRelation(const std::string& name, const Tuple& tuple) {
        if (namesToRelations.find(name) == namesToRelations.end()) {
            throw std::invalid_argument("Name does not exist in database: " + name);
        }
        namesToRelations[name].addTuple(tuple);
    }

    Relation getRelation(const std::string& name) const {
        if (namesToRelations.find(name) == namesToRelations.end()) {
            throw std::invalid_argument("Name does not exist in database: " + name);
        }
        return namesToRelations.at(name);
    }

private:
    std::map<std::string, Relation> namesToRelations;

};