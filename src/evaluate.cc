#include <eval.h>
#include <calcfn.h>

using namespace hgl::calc;

double hgl::calc::evaluate(
    const AST::Node & n, const CalcFnPool * calcfnpool, Memory * memory)
{
    double result;

    switch (n.value.getType())
    {
    case Token::Type::Number :
        result = n.value.asNumber();
        break;

    case Token::Type::Operator :
        if (memory && n.value.asOperator() == '$') // read value
        {
            auto & name = n.child.front();
            if (n.child.size() != 1 || name.value.getType() != Token::Type::Symbol)
                throw std::runtime_error("syntax error while using '$'");
            result = (*memory)[name.value.asSymbol()];
        }
        else if (memory && n.value.asOperator() == '=') // assign
        {
            auto & name = n.child.front();
            auto & value = n.child.back();
            if (n.child.size() != 2 || name.value.getType() != Token::Type::Symbol)
                throw std::runtime_error("syntax error while using '='");
            result = evaluate(value, calcfnpool, memory);
            memory->emplace(name.value.asSymbol(), result);
        }
        else
        {
            const int oprdn = n.child.size();
            double oprds[oprdn];
            auto iter = n.child.begin();
            for (int i = 0; i < oprdn; i++, ++iter)
                oprds[i] = evaluate(*iter, calcfnpool, memory);
            result = (*calcfnpool)[n.value.asOperator()](oprds, oprdn);
        }
        break;

    case Token::Type::Symbol :
        if (n.hasChild()) // function
        {
            const int oprdn = n.child.size();
            double oprds[oprdn];
            auto iter = n.child.begin();
            for (int i = 0; i < oprdn; i++, ++iter)
                oprds[i] = evaluate(*iter, calcfnpool, memory);
            result = (*calcfnpool)[n.value.asSymbol()](oprds, oprdn);
        }
        else // value
            throw std::runtime_error("invalid symbol");
        break;
    }

    return result;
}


double hgl::calc::evaluate(const AST & t, const CalcFnPool *cf, Memory * m)
{
    return evaluate(t.getRootC(), cf, m);
}
