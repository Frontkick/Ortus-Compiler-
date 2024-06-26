#include <fstream>
#include <iostream>
#include <optional>
#include <sstream>
#include <vector>
#include "./arena.hpp"

#include "./generation.hpp"

int main(int argc, char* argv[])
{
    if (argc != 2) {
        std::cerr << "Incorrect usage. Correct usage is..." << std::endl;
        std::cerr << "ortus <input.ort>" << std::endl;
        return EXIT_FAILURE;
    }

    std::string contents;
    {
        std::stringstream contents_stream;
        std::fstream input(argv[1], std::ios::in);
        contents_stream << input.rdbuf();
        contents = contents_stream.str();
    }

    Tokenizer tokenizer(std::move(contents));
    std::vector<Token> tokens = tokenizer.tokenize();

    Parser parser(std::move(tokens));
    std::optional<NodeProg> program = parser.parse_prog();

    if (!program.has_value()) {
        std::cerr << "Invalid Program" << std::endl;
        exit(EXIT_FAILURE);
    }
    {
        Generator generator(program.value());
        std::fstream file("out.asm", std::ios::out);
        file << generator.gen_prog();

    }


    system("nasm -felf64 out.asm");
    system("ld -o out out.o");

    return EXIT_SUCCESS;
}