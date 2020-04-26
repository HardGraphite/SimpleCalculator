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

static const Token sym_start_of_arglist("\x1d");
static const Token opr_call_function('F');

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
                        throw std::runtime_error("no enough tokens in stack");

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
            if (!in.empty() && in.front() == opr_call_function)
            {
                in.get();
                AST::Node node(std::move(token));

                while (!stack.empty())
                {
                    auto & oprd = stack.top();
                    if (oprd.value == sym_start_of_arglist)
                    {
                        stack.pop();
                        break;
                    }
                    else
                    {
                        node.newChildR(AST::Node(oprd));
                        stack.pop();
                    }
                }

                stack.push(std::move(node));
            }
            else
                stack.push(AST::Node(std::move(token)));
            break;
        }
    }

    if (stack.size() != 1)
        throw std::runtime_error("too many tokens left in stack");

    return AST(stack.top());
}
