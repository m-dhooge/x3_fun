/*=============================================================================
    Copyright (c) 2001-2015 Joel de Guzman

    Distributed under the Boost Software License, Version 1.0. (See accompanying
    file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
=============================================================================*/
#include <iostream>
#include <iterator>
#include <algorithm>
#include <sstream>

#include "../fun/ast.hpp"
#include "../fun/expression.hpp"
#include "../fun/error_handler.hpp"
#include "../fun/config.hpp"
#include "../fun/printer.hpp"

namespace x3 = boost::spirit::x3;


auto parse = [](std::string const& source)-> std::string
{
    std::stringstream out;

    using fun::parser::iterator_type;
    iterator_type iter(source.begin());
    iterator_type end(source.end());

    // Our AST
    fun::ast::expression ast;

    // Our error handler
    using boost::spirit::x3::with;
    using fun::parser::error_handler_type;
    error_handler_type error_handler(iter, end, out); // Our error handler

    // Our parser
    auto const parser =
        // we pass our error handler to the parser so we can access
        // it later on in our on_error and on_sucess handlers
        with<fun::parser::error_handler_tag>(std::ref(error_handler))
        [
            fun::expression()
        ];

    // Go forth and parse!
    using boost::spirit::x3::phrase_parse;
    using boost::spirit::x3::ascii::space;
    bool success = phrase_parse(iter, end, parser, space, ast);

    if (success)
    {
        if (iter != end)
            error_handler( iter, "Error! Expecting end of input here: " );
        else
            fun::ast::print(out, ast, error_handler);
    }

    return out.str();
};

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
       std::cout << "usage: " << argv[0] << " \"Expression\"" << std::endl;
       return -1;
    }

    std::cout << parse( argv[1] );
}
