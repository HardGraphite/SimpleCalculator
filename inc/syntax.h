#pragma once

#include <token.h>

#include <list>
#include <stack>

namespace hgl
{
    namespace calc
    {
        class AST
        {
            friend std::ostream & operator<<(std::ostream &, const AST &);

        public:
            struct Node
            {
                using NodeList = std::list<Node>;

                Token      value;
                NodeList   child;

                Node(Token && t): value(std::move(t)) {}
                Node(const Token & t): value(t) {}
                Token & operator*() {return this->value;}
                Token & operator[](std::size_t idx);
                void newChild(Node && x);
                void newChildR(Node && x);
                bool hasChild() const noexcept
                    {return !this->child.empty();}
            };

        private:
            Node root;

        public:
            AST();
            AST(Node && root);
            AST(const Node & root);

            // get root node
            Node & getRoot() noexcept
                {return this->root;}
            // get root node (const)
            const Node & getRootC() const noexcept
                {return this->root;}
        };


        class Parser
        {
        private:
            // node stack
            std::stack<AST::Node> nstack;
            // token stack
            std::stack<Token> tstack;

            // convert to Reverse Polish Notation
            TokenStream toRPN(TokenStream && ts);

        public:
            // parse token stream and generate AST
            AST parse(TokenStream && in);
        };


        std::ostream & operator<<(std::ostream & os, const AST & ast);

    } // namespace calc
} // namespace hgl
