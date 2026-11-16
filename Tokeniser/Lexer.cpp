/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Lexer.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aoesterl <aoesterl@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/12 14:01:57 by aoesterl          #+#    #+#             */
/*   Updated: 2026/11/16 13:19:21 by aoesterl         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Lexer.hpp"

//constructor
Lexer::Lexer()
{ 
    _Rules.separator = " \t";
    _Rules.symbols = "{};" ; 
    _Rules.string_delims = "\"";    
    _Rules.comment_chars = "#"; 
    _Rules.escape_char = '\\';
}


Lexer::Lexer(const LexerRules& obj) : _Rules(obj) {
    return;
}


//start private member function

bool Lexer::is_find(const std::string& str, char c)
{  
    if(str.find(c) == std::string::npos)
        return false;
    return true;
}

bool Lexer::Handle_Escapement(std::istream& is , Token& curr_token, char& c, size_t& line, size_t& col)
{
    if(!is.get(c))
        return false;
    if(c == '\n')
    {
        line++;
        col = 1;    
    }
    else
    {
        curr_token.str += _Rules.escape_char;
        curr_token.str += c;   
    }
    return true;
}

void Lexer::Handle_newline(size_t& line, size_t& col)
{
    line++;
    col = 0;
    _State.b_comment = false;
}

void Lexer::Handle_delimiter(Token& curr_token, char& c)
{
    if(_State.b_delims == false)
    { 
        _State.b_delims = true;
        _State.active_delim = c;
    }
    else if(c == _State.active_delim)
        _State.b_delims = false;
    curr_token.str += c;
}

void Lexer::Handle_normal_char(Token& curr_token, char c, size_t& line, size_t& col)
{
    if(curr_token.str.empty())
    { 
        curr_token.line = line;
        curr_token.col = col;
    }
    curr_token.str += c;
}


void Lexer::Reset_Lexer_State(size_t& line, size_t& col)
{
    line = 1;
    col  = 0;
    _State.b_comment = false; 
    _State.b_delims = false;
    _State.active_delim = '\0'; 
    _tokens.clear(); 
}

void Lexer::push_token(Token& curr_token)
{ 
    if(!curr_token.str.empty())
    {
        _tokens.push_back(curr_token);
        curr_token.str.clear();   
    }
}
//end private member function

//setters
bool Lexer::Tokenizer(std::istream& is)
{ 
    Token curr_token;
    char c;
    size_t line;
    size_t col;
    
    Reset_Lexer_State(line, col);
    while(is.get(c))
    {
        col++;
        if(_State.b_comment && c != '\n') //Comment mode ? yes = continue
            continue;
        //Now it's sure comment mode is off or it's a \n and it will be next turn
        else if(c == _Rules.escape_char) //Echappement // virable je pense
        { 
            if(Handle_Escapement(is, curr_token, c, line, col) == false)
                break;
        }   
        else if(c == '\n') //new line
            Handle_newline(line, col);
        else if(is_find(_Rules.string_delims, c)) // delimiter
            Handle_delimiter(curr_token, c);
        else if(is_find(_Rules.comment_chars, c)) // Comment
            _State.b_comment = true;
        else if(is_find(_Rules.separator, c) && !_State.b_delims) // space 
            push_token(curr_token);
        else if (is_find(_Rules.symbols, c) && !_State.b_delims) // special char
        { 
            push_token(curr_token);
            Token tmp = {T_SYM, std::string(1, c), line, col};
            _tokens.push_back(tmp);
        }
        else                                                    //normal char
            Handle_normal_char(curr_token, c, line, col);
    }
    if(!curr_token.str.empty())
        return false;
    return true;
}

void Lexer::SetRules(const LexerRules& obj){ 
    _Rules = obj;
}


//output
std::vector<Token>  Lexer::output_tokens()
{ 
    return _tokens;
}


//debug
void Lexer::print_tokens()
{ 
    size_t line = 1;
    for(int i = 0; i < _tokens.size(); i++)
    { 
        if(_tokens[i].line > line)
            std::cout << std::endl;
        std::cout << "[" << _tokens[i].str << "]"; //<< tokens[i].line << "]";
        line = _tokens[i].line;
    }
}

//destructor
Lexer::~Lexer() {return;}


int main()
{
    std::ifstream ifs;
    ifs.open("nginx.config");
    std::vector<Token> tokens;
    Lexer Lexer;
    if(Lexer.Tokenizer(ifs) == false)
        return(std::cout << "Error parser : quotes \\r not close" << std::endl, 0);
    Lexer.print_tokens();
}
