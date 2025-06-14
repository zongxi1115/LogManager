#ifndef ARG_PARSER_H
#define ARG_PARSER_H

#include <string>
#include <vector>
#include <unordered_map>
#include <stdexcept>
#include <iostream>
#include <iomanip>

namespace cli
{

    struct Option
    {
        std::string shortName;
        std::string longName;
        std::string description;
        bool required;
        std::string defaultValue;
        bool provided;
        std::string value;
    };

    struct PositionalArgument
    {
        std::string name;
        std::string description;
        bool required;
        std::string value;
    };

    class ArgParser
    {
    private:
        std::string programName;
        std::string description;
        std::vector<Option> options;
        std::vector<PositionalArgument> positionalArgs;
        std::unordered_map<std::string, size_t> shortOptionMap;
        std::unordered_map<std::string, size_t> longOptionMap;

    public:
        ArgParser(const std::string &programName, const std::string &description = "");

        void addOption(const std::string &shortName, const std::string &longName,
                       const std::string &description, bool required,
                       const std::string &defaultValue = "");

        void addPositionalArgument(const std::string &name, const std::string &description,
                                   bool required);

        void parse(int argc, char *argv[]);

        std::string getOptionValue(const std::string &name) const;

        bool hasOption(const std::string &name) const;

        std::string getPositionalArgument(size_t index) const;

        size_t getPositionalArgumentsCount() const;

        void printUsage() const;
    };

}

#endif
