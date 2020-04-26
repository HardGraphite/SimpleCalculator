#include <syntax.h>


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


TokenStream Parser::toRPN(TokenStream && in)
{
    TokenStream out;

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
                if (!this->tstack.empty() && this->tstack.top() != sym_call_function)
                {
                    auto & top = this->tstack.top();
                    out << top;
                    this->tstack.pop();
                }
            }
            else if (this->tstack.empty() || token.asOperator() == '(' ||
                (token.asOperator() != ')' && (
                priority(token.asOperator()) > priority(this->tstack.top().asOperator()) ||
                this->tstack.top().asOperator() == '(')))
            {
                this->tstack.push(std::move(token));
            }
            else if (token.asOperator() == ')')
            {
                while (!this->tstack.empty())
                {
                    auto & top = this->tstack.top();
                    this->tstack.pop();

                    if (top.asOperator() == '(')
                        break;

                    out << top;
                }
            }
            else // priority(token.asOperator()) <= priority(this->tstack.top().asOperator())
            {
                auto token_priority = priority(token.asOperator());

                while (true)
                {
                    if (this->tstack.empty())
                    {
                        this->tstack.push(std::move(token));
                        break;
                    }

                    auto & top = this->tstack.top();

                    if (token_priority > priority(top.asOperator()))
                    {
                        this->tstack.push(std::move(token));
                        break;
                    }

                    out << top;
                    this->tstack.pop();
                }
            }
            break;

        case Token::Type::Symbol :
            if (!in.empty() && in.front() == '(')
            {
                this->tstack.push(in.get()); // '('
                this->tstack.push(std::move(token));
                this->tstack.push(sym_call_function);
                out << sym_start_of_arglist;
            }
            else
                out << std::move(token);
            break;
        }
    }

    while (!this->tstack.empty())
    {
        auto & x = this->tstack.top();
        if (x == '(')
            throw std::runtime_error("unmatched brackets");
        out << x;
        this->tstack.pop();
    }

    return out;
}
