/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 16:02:16 by aoesterl          #+#    #+#             */
/*   Updated: 2026/11/16 13:19:04 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "main.hpp"

struct Token
{ 
    int type;
    std::string str;
    //info
    size_t line;
    size_t col;
};

struct LexerRules
{ 
    std::string separator;      // Comportement : "J'arrête le mot et je l'oublie"
    std::string symbols;        // Comportement : "J'arrête le mot j'en fais un token, et je fais de moi un token isolé"
    std::string string_delims;  // Comportement : "Je rentre dans une bulle hermétique jusqu'au prochain guillemet"
    std::string comment_chars;  // Comportement : "Je jette tout ce qui suit jusqu'à la fin de la ligne"
    char escape_char;           // Comportement : "J'ajoute le \ dans le token et 
};

struct LexerState
{ 
    bool b_comment;
    bool b_delims;
    char active_delim;
};

class Lexer
{ 
    private :
        std::vector<Token> _tokens;
        LexerRules _Rules;
        LexerState _State;
        
        bool is_find(const std::string& str, char c);
        void Reset_Lexer_State(size_t& line, size_t& col);
        bool Handle_Escapement(std::istream& is , Token& curr_token, char& c, size_t& line, size_t& col);
        void Handle_newline(size_t& line, size_t& col);
        void Handle_delimiter(Token& curr_token, char& c);
        void Handle_normal_char(Token& curr_token, char c, size_t& line, size_t& col);
        void push_token(Token& curr_token);
    public :
        enum Tokentype{T_WORD, T_STRING, T_SYM};
    
        //constructor
        Lexer();
        Lexer(const LexerRules& obj);

        // setter
        bool Tokenizer(std::istream& ifs);
        void SetRules(const LexerRules& obj);
        
        //output
        std::vector<Token> output_tokens();

        //debug
        void print_tokens();

        //destructor
        ~Lexer();
};
