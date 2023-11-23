//
// client.cpp
// ~~~~~~~~~~
//
// Copyright (c) 2003-2021 Christopher M. Kohlhoff (chris at kohlhoff dot com)
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//

#include <iostream>
#include <boost/array.hpp>
#include <boost/asio.hpp>
#include "Odjemalec.h"
using boost::asio::ip::tcp;

int main()
{
    try
    {
        std::string ip, port;
        // std::cout << "IP: ";
        // std::cin >> ip;
        // std::cout << "PORT: ";
        // std::cin >> port;
        ip = "127.0.0.1";
        port = "6589";
        boost::asio::io_context ioKonetkst;
        Odjemalec test(ioKonetkst, ip, port);
        for (;;)
        {
            std::cout << test.SprejmiSporocilo() << "\n";
            std::string sporocilo;
            std::cout << "> ";
            std::cin >> sporocilo;
            test.PosljiSporocilo(sporocilo);
        }
    }
    catch (std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
