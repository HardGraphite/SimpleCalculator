#pragma once

#include <token.h>

#include <list>

namespace hgl
{
    namespace calc
    {
        // convert to Reverse Polish Notation
        TokenStream toRPN(TokenStream && ts);


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
        public:
            AST parse(TokenStream && in);
        };


        std::ostream & operator<<(std::ostream & os, const AST & ast);

    } // namespace calc
} // namespace hgl
