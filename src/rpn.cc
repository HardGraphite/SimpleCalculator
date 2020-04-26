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

static const Token sym_start_of_arglist("#A");
static const Token sym_call_function("#F");


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
            if (token.asOperator() == ',')
            {
                if (!stack.empty() && stack.top() != sym_call_function)
                {
                    auto & top = stack.top();
                    out << top;
                    stack.pop();
                }
            }
            else if (stack.empty() || token.asOperator() == '(' ||
                (token.asOperator() != ')' && (
                priority(token.asOperator()) > priority(stack.top().asOperator()) ||
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
            else // priority(token.asOperator()) <= priority(stack.top().asOperator())
            {
                auto token_priority = priority(token.asOperator());

                while (true)
                {
                    if (stack.empty())
                    {
                        stack.push(std::move(token));
                        break;
                    }

                    auto & top = stack.top();

                    if (token_priority > priority(top.asOperator()))
                    {
                        stack.push(std::move(token));
                        break;
                    }

                    out << top;
                    stack.pop();
                }
            }
            break;

        case Token::Type::Symbol :
            if (!in.empty() && in.front() == '(')
            {
                stack.push(in.get()); // '('
                stack.push(std::move(token));
                stack.push(sym_call_function);
                out << sym_start_of_arglist;
            }
            else
                out << std::move(token);
            break;
        }
    }

    while (!stack.empty())
    {
        auto & x = stack.top();
        if (x == '(')
            throw std::runtime_error("unmatched brackets");
        out << x;
        stack.pop();
    }

    return out;
}
