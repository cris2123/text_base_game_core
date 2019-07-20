#pragma once

#include <vector>
#include <unordered_map>

class CommandParser
{

public:
    CommandParser(){};

    // Global command Tokens
    std::vector<std::tuple<std::string, std::string>> v;

    // Command from user to use my game
    std::string command;

    // Declaring valid options
    std::vector<std::string> verbs = {"abrir", "mirar", "mover", "caminar", "leer", "usar", "tomar", "ayuda"};
    std::vector<std::string> nouns = {"llave", "periodico", "linterna", "bateria", "gancho", "puerta", "escritorio", "basura", "simbolos"};
    std::vector<std::string> adverbs = {"above", "below", "left", "right", "east", "north", "west", "south"};

    // Valid semantics
    std::vector<std::string> grammars = {"VERB + NOUN", "VERB + ADVERB", "ADVERB", "VERB + NOUN + ADVERB"};
    std::unordered_map<std::string, std::unordered_map<std::string, std::vector<std::string>>> dict_semantics;

    void initSemantics();
    void removedNonUsedCharacters(std::string &command);
    bool checkValidGrammar(std::string &expression);
    void lexCommand(std::string command);    // This will tokenize my input //
    std::tuple<std::string, std::vector<std::string>, std::unordered_map<std::string, std::string>> parseCommand(std::string &command); // This will check the structure of my tokens and parse the command
    bool checkSentences(std::string const &grammar, std::vector<std::string> vec);
    bool checkSentences3Words(std::string const &grammar, std::vector<std::string> vec);
    bool checkSemantics(std::string grammar, std::string const &expression, std::vector<std::string> vec); // If command is valid will return true , el false. When i say valid im speaking semantically valid
    std::string getCommand();
    std::string setWordTag(std::string word); // maybe check some permitted string or something
};