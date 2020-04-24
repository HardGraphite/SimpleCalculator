#include <syntax.h>

using namespace hgl::calc;

Token & AST::Node::operator[](std::size_t idx)
{
    auto iter = this->child.begin();
    while (idx--)
        ++iter;
    return iter->value;
}

void AST::Node::newChild(Node && x)
{
    this->child.push_back(std::move(x));
}

void AST::Node::newChildR(Node && x)
{
    this->child.push_front(std::move(x));
}


AST::AST(): root(Token(""))
{
}

AST::AST(Node && root): root(std::move(root))
{
}

AST::AST(const Node & root): root(root)
{
}


std::ostream & hgl::calc::operator<<(std::ostream & os, const AST & ast)
{
    auto dump = [&] (const AST::Node & node)
    {
        switch (node.value.getType())
        {
        case Token::Type::Number :
        case Token::Type::Symbol :
            os << node.value;
            break;

        case Token::Type::Operator :
            os << node.value << '(';
            if (node.child.size())
            {
                for (auto & child : node.child)
                    os << child << ", ";
                // os.seekp(-2, std::ios::cur);
                os << "\b\b";
            }
            os << ") ";
            break;
        }
    };

    dump(ast.getRootC());
    return os;
}
