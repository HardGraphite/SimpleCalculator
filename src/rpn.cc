#include <syntax.h>

#include <stack>

using namespace hgl::calc;


static std::int8_t priority(char opr)
{
    switch (opr)
    {
    case '+': case '-':
        return 0;

    case '*': case '/':
        return 2;

    case '^':
        return 4;

    case '~':
        return INT8_MAX - 1;

    default:
        return INT8_MIN;
    }
}

static const Token sym_start_of_arglist("\x1d");
static const Token opr_call_function('F');


TokenStream hgl::calc::toRPN(TokenStream && in)
{
    TokenStream out;
    std::stack<Token> stack;

    while (!in.empty())
    {
        auto token = in.get();

        switch (token.getType())
        {
        case Token::Type::Number :
            out << std::move(token);
            break;

        case Token::Type::Operator :
            if (stack.empty() || token.asOperator() == '(' ||
                (token.asOperator() != ')' && (
                priority(token.asOperator()) >= priority(stack.top().asOperator()) ||
                stack.top().asOperator() == '(')))
            {
                stack.push(std::move(token));
            }
            else if (token.asOperator() == ')')
            {
                while (!stack.empty())
                {
                    auto & top = stack.top();
                    stack.pop();

                    if (top.asOperator() == '(')
                        break;

                    out << top;
                }
            }
            else // priority(token.asOperator()) < priority(stack.top().asOperator())
            {
                auto token_priority = priority(token.asOperator());

                while (!stack.empty())
                {
                    auto & top = stack.top();
                    stack.pop();
                    out << top;

                    if (token_priority >= priority(top.asOperator())
                        || stack.empty())
                    {
                        stack.push(std::move(token));
                        break;
                    }
                }
            }
            break;

        case Token::Type::Symbol :
            if (!in.empty() && in.front() == Token('('))
            {
                stack.push(in.get()); // '('
                stack.push(opr_call_function);
                stack.push(std::move(token));
                out << sym_start_of_arglist;
            }
            else
                out << std::move(token);
            break;
        }
    }

    while (!stack.empty())
    {
        out << stack.top();
        stack.pop();
    }

    return out;
}
