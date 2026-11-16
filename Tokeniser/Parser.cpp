/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arthurito <arthurito@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/13 15:31:09 by aoesterl          #+#    #+#             */
/*   Updated: 2026/11/14 23:11:40 by arthurito        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Parser.hpp"




struct OperatorRule
{ 
        std::string _symbol;
        int _priority;
        bool _left_assoc;  
};

class ParserRules
{ 
    private :
        std::vector<OperatorRule> _Operators; 
    public :
        //constructor
        ParserRules();
        ParserRules(const ParserRules& cpy);
        //setter
        void AddOperator(const std::string& str, int priority, bool left_assoc = true);
        const OperatorRule* GetOperator(const std::string& str) const;
        
        //destructor
        ~ParserRules();
};

//constructor
ParserRules::ParserRules() {
    return;
}

ParserRules::ParserRules(const ParserRules& cpy)
{ 
    _Operators = cpy._Operators;
}


void ParserRules::AddOperator(const std::string& str, int priority, bool left_assoc)
{ 
    OperatorRule obj;
    obj._symbol = str;
    obj._priority = priority;
    obj._left_assoc = left_assoc;
    _Operators.push_back(obj);
}

const OperatorRule* ParserRules::GetOperator(const std::string& str) const
{ 
    for(int i = 0; i < _Operators.size(); i++)
    { 
        if(_Operators[i]._symbol == str)
            return &_Operators[i];
    }
    return(NULL);
}

//destructor
ParserRules::~ParserRules() {
    return;
}



class AstNode
{ 
    private :
        int type;
        std::string _name;
        std::vector<std::string> _args;
        std::vector<AstNode>    _left;
        std::vector<AstNode>    _right;
    public :
        //define
        
        
        //constructor
        AstNode();
        AstNode(const std::string& name, const std::vector<std::string> args);
        AstNode(const AstNode& cpy);

        //operator
        AstNode& operator=(const AstNode& cpy);
        
        //destructor
        ~AstNode();
};

//constructor
AstNode::AstNode() : _name(""),
{
    return;   
}

AstNode::AstNode(const std::string& name, const std::vector<std::string> args) : _name(name), _args(args)
{
     return;
}

AstNode::AstNode(const AstNode& obj) : _name(obj._name), _args(obj._args),\
 _left(obj._left), _right(obj._right)
{
    return;
}

//operator
AstNode& AstNode::operator=(const AstNode& cpy)
{ 
    if(this != &cpy)
    {
        _name = cpy._name;
        _args = cpy._args;
        _left = cpy._left;
        _right = cpy._right;
    }
    return(*this);
}



//destructor
AstNode::~AstNode()
{ 
    return;
}


class AST
{ 
    private :
        AstNode* _Root; 
    public :
        AST();
        void SetRoot(AstNode *Root);Parsing()
        ~AST();
};


AST::AST() : _Root(NULL)
{ 
    return;
}


void AST::SetRoot(AstNode *Root)
{ 
    delete _Root;
    _Root = Root; 
}

AST::~AST()
{ 
    delete _Root;
}

class Parser
{ 
    private :
        AST _tree;
        ParserRules _Operators;
    public :
        Parser(ParserRules& Rules);
        
        bool Parsing(std::vector<Token>& tokens);

        ~Parser();
    
};


Parser::Parser(ParserRules& Operators) : _Operators(Operators)
{ 
    return;
}


bool Parsing(std::vector<Token>& tokens)
{   
    const OperatorRule* Operator;
    for(int i = 0; i < tokens.size())
    { 
        
    }


}


