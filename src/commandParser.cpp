#include <iostream>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <string>
#include <tuple>
#include "commandParser.h"

#define DEBUG

void CommandParser::initSemantics()
{

    /* Here we declare all valids words in game*/

    // VERB + NOUN
    std::unordered_map<std::string, std::vector<std::string>> verb_noun_dicts = {

        {"abrir", {"puerta"}},
        {"caminar", {"none"}},
        {"mirar", {"all"}},
        {"mover", {"escritorio", "basura", "gancho"}},
        {"leer", {"periodico", "simbolos"}},
        {"usar", {"llave", "periodico", "linterna", "bateria", "gancho"}},
        {"tomar", {"llave", "periodico", "linterna", "bateria", "gancho"}}

    };

    // VERB + ADVERBS
    std::unordered_map<std::string, std::vector<std::string>> verb_adverb_dicts = {

        {"abrir", {"none"}},
        {"caminar", {"west", "east", "north", "south"}},
        {"mirar", {"all"}},
        {"mover", {"east", "west", "right", "left"}},
        {"leer", {"none"}},
        {"usar", {"none"}},
        {"tomar", {"none"}}

    };

    // VERB + NOUN + ADVERBS
    std::unordered_map<std::string, std::vector<std::string>> verb_noun_adverb_dicts = {

        {"abrir", {"all"}},
        {"caminar", {"none"}},
        {"mirar", {"none"}},
        {"mover", {"east", "west", "right", "left"}},
        {"leer", {"none"}},
        {"usar", {"none"}},
        {"tomar", {"west", "east", "left", "right", "abajo"}}

    };

    dict_semantics["VERB + NOUN"] = verb_noun_dicts;
    dict_semantics["VERB + ADVERB"] = verb_adverb_dicts;
    dict_semantics["VERB + NOUN + ADVERB"] = verb_adverb_dicts;

#ifdef DEBUG

    // Printing dictionary
    for (auto entry : dict_semantics)
    {
        std::cout << entry.first << " :: ";
        for (auto n_map : entry.second)
        {
            std::cout << "{ " << n_map.first << " : ";
            for (std::string i : n_map.second)
                std::cout << i << ", ";
            std::cout << "} ";
        }
        std::cout << std::endl;
    }
#endif

    //ADVERB
    // when only adverb i will pass everything to state machine because this is a exception
    // VERB + NOUN + ADVERB
    // check if verb and nouns are correct and then check dictionary to make any sense from the input

    // need a method to insert this list in a dict inside a dict wich havegrammars like keys
    // Also need to make a method to find the valid sintax if semantics does not have any meaning give
    // eror to user parafrasea tu frase con los comandos disponibles, de no conocerlos usa el comando de ayuda
    // if semantics is valid the engine can pass the command if not see above

};

std::string CommandParser::getCommand()
{

    // Funcion utilizada para obtener la data de entrada del usuario

    std::cout << "> ";
    std::string user_data;

    getline(std::cin, user_data);

    return user_data;
};

std::string CommandParser::setWordTag(std::string word)
{

    /* Function used to tokenize phrase
    Function to search is a given word is valid for this game

    verbs : is a dict define on header with all valid verbs
    Same apply for nouns and adverbs 
    If word is not any of before vector, word does not being used on game
    */
    std::vector<std::string>::iterator it;

    it = std::find(verbs.begin(), verbs.end(), word);

    if (it != verbs.end())
    {

        return "VERB";
    }

    it = std::find(nouns.begin(), nouns.end(), word);

    if (it != nouns.end())
    {
        return "NOUN";
    }

    it = std::find(adverbs.begin(), adverbs.end(), word);

    if (it != adverbs.end())
    {
        return "ADVERB";
    }

    else
    {
        return "NOTAG";
    }
};

void CommandParser::removedNonUsedCharacters(std::string &command)
{

    /* Function to delete  unused character from input string*/

    std::string nonCharacters = "+-$%^&*!@#?><(){}[]:;";

    for (int i = 0; i < nonCharacters.length(); i++)
    {

        std::string::iterator end_pos = std::remove(command.begin(), command.end(), nonCharacters[i]);
        command.erase(end_pos, command.end());
    }
};

void CommandParser::lexCommand(std::string command)
{

    /* Lexer : Basically here we apply a lexer to input string
    
        Here we read word by word input string and tokenize with setWordTag()
        then we put it on a vector with a tuple of the form (wordTag, word)
    
    */
    std::vector<std::string> command_elements;
    removedNonUsedCharacters(command); // remove some symbols

    std::stringstream ss(command);
    std::string temp;

    std::string tag;

    while (ss >> temp)
    {

        tag = setWordTag(temp);

        {
            v.push_back(std::make_tuple(tag, temp));
        }
    }
#ifdef DEBUG

    // printing tuple 
    for (auto tuple : v)
    {
        std::cout << std::get<0>(tuple) << ": " << std::get<1>(tuple) << std::endl;
    }
#endif
};

bool CommandParser::checkValidGrammar(std::string &expression)
{
    // TODO : Better to pass object with NOTAGS too , and then remove no tags
    // until we get a grammar which works, with that we could check semantics
    // and suggest some input to user

    /* Here we will check y after lexing user input its structure  could be find 
    in our dict of valir grammars called grammar */

    std::vector<std::string>::iterator it;
    it = std::find(grammars.begin(), grammars.end(), expression);

    if (it != grammars.end())
    {
        return true;
    }

    return false;
};

bool CommandParser::checkSentences(std::string const &grammar, std::vector<std::string> vec)
{

    /* Here we check  if  the user input without articles, prepositions and not valid word inside 
    game, have some meaning inside game, also check if a valid sentence have a semantic meaning
    in the used context */


    std::unordered_map<std::string, std::vector<std::string>> sentence_grammar_list;
    std::vector<std::string>::iterator it;

    if (dict_semantics.find(grammar) != dict_semantics.end())
    {
        sentence_grammar_list = dict_semantics[grammar];
    }
    else
    {
        std::cout << "That sentence is invalid try another one" << std::endl;
        return false;
    }

    // always position 0 is a VERB, on my model
    std::vector<std::string> verb_and_semantics = sentence_grammar_list[vec[0]];

    // Now need validate if my first item is None or all

    if (vec.size() < 3)
    {

        if (verb_and_semantics[0] == "none")
        {
            std::cout << "The keyword : " << vec[1] << " cannot be use with this action on this context. Try another one" << std::endl;
            return false;
        }
        else if (verb_and_semantics[0] == "all")
        {
            std::cout << "Valid syntax. Good one" << std::endl;
            return true;
        }
        else
        {
            it = std::find(verb_and_semantics.begin(), verb_and_semantics.end(), vec[1]);

            if (it != verb_and_semantics.end())
            {
                std::cout << "Valid syntax. Good one";
                return true;
            }
            else
            {
                std::cout << "With " << vec[0] << " does not make sense to use keyword: " << vec[1] << std::endl;
                return false;
            }
        }
    }

    else if (vec.size() >= 3)
    {

        if (verb_and_semantics[0] == "none")
        {
            std::cout << "The keyword : " << vec[1] << " cannot be use with this action on this context. Try another one" << std::endl;
            return false;
        }
        else if (verb_and_semantics[0] == "all")
        {
            std::cout << "Valid syntax. Good one" << std::endl;
            return true;
        }
        else
        {
            it = std::find(verb_and_semantics.begin(), verb_and_semantics.end(), vec[2]);

            if (it != verb_and_semantics.end())
            {
                std::cout << "Valid syntax. Good one";
                return true;
            }
            else
            {
                std::cout << "With " << vec[0] << " does not make sense to use keywords: " << vec[1] << " " << vec[2] << std::endl;
                return false;
            }
        }
    }
};

bool CommandParser::checkSemantics(std::string grammar, std::string const &expression, std::vector<std::string> vec)
{

    /* Esta duncion es un wrapper alrededor de varias funciones utilizadas para verificar si la expresion de 
    entrada es valida para el juego*/

    bool semantics;
    bool sementics3words;

    if (grammar == "VERB + NOUN" || grammar == "VERB + ADVERB")
    {
        semantics = checkSentences(grammar, vec);

        if (semantics)
        {

            std::cout << "Good everything ok" << std::endl;
        }
        else
        {
            std::cout << "Problems with some of your strings" << std::endl;
        }
    }
    else if (grammar == "VERB + NOUN + ADVERB")
    {
        semantics = checkSentences("VERB + NOUN", vec);

        if (semantics)
        {
            checkSentences(grammar, vec);
        }
        else
        {
            std::cout << "Your sentence does not make sense in this context. Please try another one" << std::endl;
        }
    }

    return semantics;

    // // always position 0 is a VERB, on my model
    // std::vector<std::string> verb_and_semantics = sentence_grammar_list[vec[0]];
};

std::tuple<std::string, std::vector<std::string>, std::unordered_map<std::string, std::string>> CommandParser::parseCommand(std::string &command)
{

    // Here we parse everything and return all information necessary for gameStateMachine
    // gameInput is the return values and is a tuple with this form :
    // ('VERB+NOUN+ADVERB',['verb','noun','adverb'],{'verb':tomar,'noun':llave,'adverb': abajo})


    // TODO : return gameInput object
    
    std::tuple<std::string, std::vector<std::string>, std::unordered_map<std::string, std::string>> gameInput;

    std::vector<std::string> input_key_tags;
    std::unordered_map<std::string, std::string> expression_dict;

    std::string tokenExpression;
    std::string expression;
    std::string tokenExpressionNoTag;
    std::vector<std::string> expressionVector;
    bool semantics;

    for (auto tuple : v)
    {
        std::cout << "Impriemiendo la tupla" << std::endl;
        std::cout << std::get<0>(tuple) << "," << std::get<1>(tuple) << std::endl;


        // Refactorizar este codigo, verificar not_tag primero y luego la condicion del token expression es
        // mas logico y mas sencillo de entender

        if(std::get<0>(tuple) != "NOTAG")
        {

            if(tokenExpression.length() !=0)
            {
                tokenExpression += " + " + std::get<0>(tuple);
            }
            else
            {
                tokenExpression += std::get<0>(tuple);
            }
            std::cout << "Codigo refactorizado" << std::endl;
            expressionVector.push_back(std::get<1>(tuple));

            //vector with all type of words keys on sentence
            input_key_tags.push_back(std::get<0>(tuple));    
            expression_dict[std::get<0>(tuple)] = std::get<1>(tuple);
        }

        expression += " " + std::get<1>(tuple);
        // tokenExpressionNoTag += " + " + std::get<0>(tuple); // make suggestion over command typed
        // implement later

        // for( auto vector: input_key_tags)
        // {
        //     // iterate here to create dict
        //     //expression_dict.insert(std::make_pair<std::string, std::string>(vector,))
        // }
    }

    std::cout << tokenExpression << std::endl;
    std::cout << "PRINTING EXPRESSIONS TO PASS TO STATE MACHINES" << std::endl;
    std::cout << expression << std::endl;

    if (checkValidGrammar(tokenExpression))
    {

        std::cout << "Check valid grammar works" << std::endl;
        semantics = checkSemantics(tokenExpression, expression, expressionVector);

        std::cout << "Checking semantics" << std::endl ;
        std::cout << semantics << std::endl;

        // if valid grammar and sentence we will return to process on games state machines
        return std::make_tuple(tokenExpression,input_key_tags,expression_dict);

        
    }
    else
    {
        std::cout << "Check valid grammar not working" << std::endl;
    }
};