#include <syntax.h>

#include <stack>

using namespace hgl::calc;


static std::uint8_t oprdcnt(char opr)
{
    switch (opr)
    {
    case '~':
        return 1;

    default:
        return 2;
    }
}


AST Parser::parse(TokenStream && in)
{
    std::stack<AST::Node> stack;

    while (!in.empty())
    {
        auto token = in.get();

        switch (token.getType())
        {
        case Token::Type::Number :
            stack.push(AST::Node(std::move(token)));
            break;

        case Token::Type::Operator :
            {
                AST::Node node(std::move(token));

                auto n = oprdcnt(node.value.asOperator());
                if (n > stack.size())
                {
                    if (node.value.asOperator() == '-' && stack.size() == 1)
                    // opr_neg, e.g. -1, -NUM
                    {
                        node.value = Token('~');
                        n = 1;
                    }
                    else
                        throw std::runtime_error("no enough tokens in stack");
                }

                while (n--)
                {
                    auto & oprd = stack.top();
                    node.newChildR(AST::Node(oprd));
                    stack.pop();
                }

                stack.push(std::move(node));
            }
            break;

        case Token::Type::Symbol :
            stack.push(AST::Node(std::move(token)));
            break;
        }
    }

    if (stack.size() != 1)
        throw std::runtime_error("too many tokens left in stack");

    return AST(stack.top());
}
