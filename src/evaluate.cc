#include <eval.h>
#include <calcfn.h>

using namespace hgl::calc;

double hgl::calc::evaluate(const AST::Node & n, const CalcFnPool * calcfnpool)
{
    double result;

    switch (n.value.getType())
    {
    case Token::Type::Number :
        result = n.value.asNumber();
        break;

    case Token::Type::Operator : {
        const int oprdn = n.child.size();
        double oprds[oprdn];
        auto iter = n.child.begin();
        for (int i = 0; i < oprdn; i++, ++iter)
            oprds[i] = evaluate(*iter);
        result = (*calcfnpool)[n.value.asOperator()](oprds, oprdn);
    } break;

    case Token::Type::Symbol :
        if (n.hasChild()) // function
        {
            const int oprdn = n.child.size();
            double oprds[oprdn];
            auto iter = n.child.begin();
            for (int i = 0; i < oprdn; i++, ++iter)
                oprds[i] = evaluate(*iter);
            result = (*calcfnpool)[n.value.asSymbol()](oprds, oprdn);
        }
        else // value
            throw std::runtime_error("invalid symbol");
        break;
    }

    return result;
}


double hgl::calc::evaluate(const AST & t, const CalcFnPool *cf)
{
    return evaluate(t.getRootC(), cf);
}
