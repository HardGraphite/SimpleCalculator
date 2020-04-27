#include <syntax.h>


using namespace hgl::calc;

static std::uint8_t oprdcnt(char opr)
{
    switch (opr)
    {
    case '~':
    case '$':
        return 1;

    default:
        return 2;
    }
}

static const Token sym_start_of_arglist("#A");
static const Token sym_call_function("#F");

AST Parser::parse(TokenStream && ts)
{
    auto in = Parser::toRPN(std::move(ts));

    while (!in.empty())
    {
        auto token = in.get();

        switch (token.getType())
        {
        case Token::Type::Number :
            this->nstack.push(AST::Node(std::move(token)));
            break;

        case Token::Type::Operator :
            {
                AST::Node node(std::move(token));

                auto n = oprdcnt(node.value.asOperator());
                if (n > this->nstack.size())
                        throw std::runtime_error("no enough tokens in this->nstack");

                while (n--)
                {
                    auto & oprd = this->nstack.top();
                    node.newChildR(AST::Node(oprd));
                    this->nstack.pop();
                }

                this->nstack.push(std::move(node));
            }
            break;

        case Token::Type::Symbol :
            if (token == sym_call_function)
            {
                if (in.empty())
                    throw std::runtime_error("in-stream error");

                AST::Node node(in.get());

                while (!this->nstack.empty())
                {
                    auto & oprd = this->nstack.top();
                    if (oprd.value == sym_start_of_arglist)
                    {
                        this->nstack.pop();
                        break;
                    }
                    else
                    {
                        node.newChildR(AST::Node(oprd));
                        this->nstack.pop();
                    }
                }

                this->nstack.push(std::move(node));
            }
            else
                this->nstack.push(AST::Node(std::move(token)));
            break;
        }
    }

    if (this->nstack.size() != 1)
        throw std::runtime_error("too many tokens left in stack");

    AST res(this->nstack.top());
    this->nstack.pop(); // clear stack

    return res;
}
