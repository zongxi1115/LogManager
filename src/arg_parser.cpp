#include "arg_parser.h"
#include <sstream>
#include <algorithm>

namespace cli
{

    ArgParser::ArgParser(const std::string &programName, const std::string &description)
        : programName(programName), description(description)
    {

        addOption("h", "help", "Show help.", false);
    }

    void ArgParser::addOption(const std::string &shortName, const std::string &longName,
                              const std::string &description, bool required,
                              const std::string &defaultValue)
    {

        if (!shortName.empty() && shortOptionMap.find(shortName) != shortOptionMap.end())
        {
            throw std::invalid_argument("短选项 '" + shortName + "' 已存在");
        }

        if (!longName.empty() && longOptionMap.find(longName) != longOptionMap.end())
        {
            throw std::invalid_argument("长选项 '" + longName + "' 已存在");
        }

        Option option;
        option.shortName = shortName;
        option.longName = longName;
        option.description = description;
        option.required = required;
        option.defaultValue = defaultValue;
        option.provided = false;
        option.value = defaultValue;

        size_t index = options.size();
        options.push_back(option);

        if (!shortName.empty())
        {
            shortOptionMap[shortName] = index;
        }

        if (!longName.empty())
        {
            longOptionMap[longName] = index;
        }
    }

    void ArgParser::addPositionalArgument(const std::string &name, const std::string &description,
                                          bool required)
    {
        PositionalArgument arg;
        arg.name = name;
        arg.description = description;
        arg.required = required;

        positionalArgs.push_back(arg);
    }

    void ArgParser::parse(int argc, char *argv[])
    {

        for (auto &option : options)
        {
            option.provided = false;
        }

        int posArgIndex = 0;

        for (int i = 1; i < argc; ++i)
        {
            std::string arg = argv[i];

            if (arg.size() >= 2 && arg[0] == '-')
            {
                if (arg[1] == '-')
                {

                    std::string longName = arg.substr(2);
                    std::string value;

                    size_t equalsPos = longName.find('=');
                    if (equalsPos != std::string::npos)
                    {
                        value = longName.substr(equalsPos + 1);
                        longName = longName.substr(0, equalsPos);
                    }

                    auto it = longOptionMap.find(longName);
                    if (it == longOptionMap.end())
                    {
                        throw std::invalid_argument("unknown option: --" + longName);
                    }

                    size_t optionIndex = it->second;
                    options[optionIndex].provided = true;

                    if (value.empty() && i + 1 < argc && argv[i + 1][0] != '-')
                    {
                        value = argv[++i];
                    }

                    if (!value.empty())
                    {
                        options[optionIndex].value = value;
                    }

                    if (longName == "help")
                    {
                        printUsage();
                        exit(0);
                    }
                }
                else
                {

                    std::string shortName = arg.substr(1);

                    for (size_t j = 0; j < shortName.size(); ++j)
                    {
                        std::string singleShortName(1, shortName[j]);

                        auto it = shortOptionMap.find(singleShortName);
                        if (it == shortOptionMap.end())
                        {
                            throw std::invalid_argument("unknown option: -" + singleShortName);
                        }

                        size_t optionIndex = it->second;
                        options[optionIndex].provided = true;

                        if (j < shortName.size() - 1)
                        {
                            continue;
                        }

                        if (i + 1 < argc && argv[i + 1][0] != '-')
                        {
                            options[optionIndex].value = argv[++i];
                        }

                        if (singleShortName == "h")
                        {
                            printUsage();
                            exit(0);
                        }
                    }
                }
            }
            else
            {

                if (posArgIndex >= positionalArgs.size())
                {
                    throw std::invalid_argument("Too many positional arguments");
                }

                positionalArgs[posArgIndex].value = arg;
                posArgIndex++;
            }
        }

        for (const auto &option : options)
        {
            if (option.required && !option.provided)
            {
                throw std::invalid_argument("Missing required option: --" + option.longName);
            }
        }

        for (const auto &arg : positionalArgs)
        {
            if (arg.required && arg.value.empty())
            {
                throw std::invalid_argument("Missing required args: " + arg.name);
            }
        }
    }

    std::string ArgParser::getOptionValue(const std::string &name) const
    {
        // 先从缩写找，再找大写
        auto shortIt = shortOptionMap.find(name);
        if (shortIt != shortOptionMap.end())
        {
            return options[shortIt->second].value;
        }

        auto longIt = longOptionMap.find(name);
        if (longIt != longOptionMap.end())
        {
            return options[longIt->second].value;
        }

        throw std::invalid_argument("unknown option: " + name);
    }

    bool ArgParser::hasOption(const std::string &name) const
    {

        auto shortIt = shortOptionMap.find(name);
        if (shortIt != shortOptionMap.end())
        {
            return options[shortIt->second].provided;
        }

        auto longIt = longOptionMap.find(name);
        if (longIt != longOptionMap.end())
        {
            return options[longIt->second].provided;
        }

        return false;
    }

    std::string ArgParser::getPositionalArgument(size_t index) const
    {
        if (index >= positionalArgs.size())
        {
            throw std::out_of_range("Index out of range");
        }

        return positionalArgs[index].value;
    }

    size_t ArgParser::getPositionalArgumentsCount() const
    {
        return positionalArgs.size();
    }

    void ArgParser::printUsage() const
    {
        std::cout << "Usage: " << programName << " [option]";

        for (const auto &arg : positionalArgs)
        {
            std::cout << " [" << (arg.required ? "" : "[") << arg.name << (arg.required ? "" : "]]");
        }

        std::cout << std::endl
                  << std::endl;

        if (!description.empty())
        {
            std::cout << description << std::endl
                      << std::endl;
        }

        std::cout << "Options:" << std::endl;

        size_t maxOptionWidth = 0;
        for (const auto &option : options)
        {
            std::string optionStr;
            if (!option.shortName.empty())
            {
                optionStr += "-" + option.shortName;
                if (!option.longName.empty())
                {
                    optionStr += ", ";
                }
            }

            if (!option.longName.empty())
            {
                optionStr += "--" + option.longName;
            }

            maxOptionWidth = std::max(maxOptionWidth, optionStr.size());
        }

        for (const auto &option : options)
        {
            std::cout << "  ";

            if (!option.shortName.empty())
            {
                std::cout << "-" << option.shortName;
                if (!option.longName.empty())
                {
                    std::cout << ", ";
                }
            }
            else
            {
                std::cout << "   ";
            }

            if (!option.longName.empty())
            {
                std::cout << "--" << option.longName;
            }

            std::string optionStr;
            if (!option.shortName.empty())
            {
                optionStr += "-" + option.shortName;
                if (!option.longName.empty())
                {
                    optionStr += ", ";
                }
            }

            if (!option.longName.empty())
            {
                optionStr += "--" + option.longName;
            }

            std::cout << std::string(maxOptionWidth - optionStr.size() + 2, ' ');

            std::cout << option.description;

            if (!option.defaultValue.empty())
            {
                std::cout << " [Default: " << option.defaultValue << "]";
            }

            if (option.required)
            {
                std::cout << " [Required]";
            }

            std::cout << std::endl;
        }

        std::cout << std::endl;

        if (!positionalArgs.empty())
        {
            std::cout << "Positional arguments:" << std::endl;

            maxOptionWidth = 0;
            for (const auto &arg : positionalArgs)
            {
                maxOptionWidth = std::max(maxOptionWidth, arg.name.size());
            }

            for (const auto &arg : positionalArgs)
            {
                std::cout << "  " << std::left << std::setw(maxOptionWidth + 2) << arg.name
                          << arg.description;

                if (arg.required)
                {
                    std::cout << " [Required]";
                }

                std::cout << std::endl;
            }

            std::cout << std::endl;
        }
    }

}
