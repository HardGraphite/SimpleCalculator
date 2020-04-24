#include <eval.h>
#include "calcx.h"

using namespace hgl::calc;

static auto builtin_calcfnpool = getBuiltinCalcFnPool();

double hgl::calc::evaluate(const AST::Node & n)
{
    double result;

    switch (n.value.getType())
    {
    case Token::Type::Number :
        result = n.value.asNumber();
        break;

    case Token::Type::Operator : {
        char opr[2] = {n.value.asOperator(), '\0'};
        const int oprdn = n.child.size();
        double oprds[oprdn];
        auto iter = n.child.begin();
        for (int i = 0; i < oprdn; i++, ++iter)
            oprds[i] = evaluate(*iter);
        result = builtin_calcfnpool[opr](oprds, oprdn);
    } break;

    case Token::Type::Symbol :
        throw std::runtime_error("invalid symbol");
        break;
    }

    return result;
}


double hgl::calc::evaluate(const AST & t)
{
    return evaluate(t.getRootC());
}
