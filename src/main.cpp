#include <cxxopts.hpp>
#include <iostream>

int main(int argc, char *argv[]) {
    cxxopts::Options options("YourProgram", "Description of your program");

    options.add_options()
        ("v,verbose", "Enable verbose mode")
        ("i,input", "Input file", cxxopts::value<std::string>())
        ("o,output", "Output file", cxxopts::value<std::string>())
        ("h,help", "Print usage")
    ;

    auto result = options.parse(argc, argv);

    if (result.count("verbose")) {
        std::cout << "Verbose mode enabled\n";
    }

    if (result.count("input")) {
        std::cout << "Input file: " << result["input"].as<std::string>() << "\n";
    }

    if (result.count("output")) {
        std::cout << "Output file: " << result["output"].as<std::string>() << "\n";
    }

    if (result.count("help")) {
        std::cout << options.help() << std::endl;
        exit(0);
    }

    // Rest of your program logic goes here

    return 0;
}