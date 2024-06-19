#pragma once
#include <vector>
#include "Database.h"
#include "DatalogProgram.h"

class Interpreter {
public:
    Interpreter(DatalogProgram datalogProgram) : datalogProgram(datalogProgram) {
        populateDatabase();
    }

private:
    DatalogProgram datalogProgram;
    Database database; 

    void populateDatabase() {
        createRelations(); // Evaluate Schemes
        addTuples(); // Evaluate Facts
        evaluateQueries; // Hmm, I wonder what this does...
    }

    void createRelations() {
        for (const Predicate& scheme : datalogProgram.getSchemes()) {
            Scheme schemeColumns = Scheme(scheme.getParameters());
            database.addRelation(scheme.getName(), schemeColumns);
        }
    }

    void addTuples() {
        for (const Predicate& fact : datalogProgram.getFacts()) {
            Tuple tuple = Tuple(fact.getParameters());
            database.addTupleToRelation(fact.getName(), tuple);
        }
    }

    void evaluateQueries() {
        for (const Predicate& query : datalogProgram.getQueries()) {
            evaluateQuery(query);
        }
    }

    void evaluateQuery(const Predicate& query) {
        Relation relation = database.getRelation(query.getName());
        std::vector<Parameter> queryParameters = query.getParameters();
        for (int i = 0; i < queryParameters.size(); i++) {
            Parameter parameter = queryParameters.at(i);
            if (isConstant(parameter)) {
                relation = relation.select(i, parameter.getTokenValue());
            } else {
                
            }
        }
    }

    static bool isConstant(const Parameter& parameter) {
        return parameter.getType() == STRING;
    }

};