#include <iostream>
#include <list>
#include "Parser/Parser.h"
#include "Scheme.h"
#include "Tuple.h"
#include "Relation.h"

int main(int argc, char* argv[]) {    

    std::vector<std::string> names = { "ID", "Name", "Major" };

    Scheme scheme(names);

    std::vector<std::string> values[] = {
        {"'42'", "'Ann'", "'CS'"},
        {"'32'", "'Bob'", "'CS'"},
        {"'64'", "'Ned'", "'EE'"},
        {"'16'", "'Jim'", "'EE'"},
    };

    Relation relation("student", scheme);
    for (auto& value : values) {
        Tuple tuple(value);
        std::cout << tuple.toString(scheme) << std::endl;
        relation.addTuple(tuple);
    }

    std::cout << "relation:" << std::endl;
    std::cout << relation.toString();

    Relation result = relation.select(2, "'CS'");

    std::cout << "select Major='CS' result:" << std::endl;
    std::cout << result.toString();

    // if (argc < 2) {
    //     std::cout << "./exe filename.txt" << std::endl;
    //     return -1;
    // }

    // std::string fileName = argv[1];
    // try {
    //     DatalogProgram datalogProgram = Parser::parse(fileName);
    //     std::cout << "Success!\n" << datalogProgram.toString() << std::endl;
    // } catch (Token token) {
    //     std::cout << "Failure!\n  " << token.toString() << std::endl;
    //     return 1;
    // }

    return 0;
}
