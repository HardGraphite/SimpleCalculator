#include <lexic.h>

#include <cctype>

using namespace hgl::calc;


TokenStream Scanner::scan(std::istream & in)
{
    buffer.clear();
    status = Status::Idle;
    TokenStream out;

    auto newNumber = [&]
    {
        out << Token(std::atof(buffer.str().c_str()));
        buffer.str("");
        buffer.clear();
    };

    auto newSymbol = [&]
    {
        out << Token(buffer.str().c_str());
        buffer.str("");
        buffer.clear();
    };

    while (in.peek() != EOF)
    {
        char ch = in.get();

        switch (status)
        {
        case Status::Idle :
            if (std::isdigit(ch) || ch == '.')
            {
                status = Status::RdNumber;
                buffer << ch;
            }
            else if (std::isalpha(ch))
            {
                status = Status::RdLetter;
                buffer << ch;
            }
            else if (std::isspace(ch))
            {
                ;
            }
            else
            {
                // status = Status::Idle;
                if (ch == '-' && (out.empty() || out.back() != Token(')')))
                    ch = '~'; // e.g. "-1+3" --> "~1+3"
                out << Token(ch);
            }
            break;

        case Status::RdNumber :
            if (std::isdigit(ch) || ch == '.')
            {
                // status = Status::RdNumber;
                buffer << ch;
            }
            else if (std::isalpha(ch))
            {
                status = Status::RdLetter;
                newNumber();
                buffer << ch;
            }
            else if (std::isspace(ch))
            {
                status = Status::Idle;
                newNumber();
            }
            else
            {
                status = Status::Idle;
                newNumber();
                out << Token(ch);
            }
            break;

        case Status::RdLetter :
            if (std::isalnum(ch))
            {
                // status = Status::RdLetter;
                buffer << ch;
            }
            else if (std::isspace(ch))
            {
                status = Status::Idle;
                newNumber();
            }
            else
            {
                status = Status::Idle;
                newSymbol();
                out << Token(ch);
            }
            break;
        }
    }

    if (buffer.str().length())
    {
        switch (status)
        {
        case Status::Idle :
            // impossile
            break;

        case Status::RdNumber :
            newNumber();
            break;

        case Status::RdLetter :
            newSymbol();
            break;
        }
    }

    return out;
}
