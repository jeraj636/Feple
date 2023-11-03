#include "HenigmaEngine/Include/Risalnik.h"
#include "HenigmaEngine/Include/Log.h"
#include "HenigmaEngine/Include/Font.h"
#include "HenigmaEngine/Include/Matematika/Matematika.h"
#include "HenigmaEngine/Include/Scena.h"
#include "HenigmaEngine/Include/Objekt.h"

#include <string>
#include <iostream>
#include <chrono>

#include <boost/asio.hpp>
using boost::asio::ip::tcp;

int main()
{
    /*
    Risalnik::Init("Jakob", 400, 600, 0);
    Risalnik::odzadje = 0xcc7722ff;
    Risalnik::sredstvaPath = "../Sredstva";

    while (!Risalnik::AliSeMoramZapreti())
    {
        Risalnik::ZacetekFrame();

        Risalnik::KonecFrame();
    }
    Risalnik::Konec();
    */
    std::string ip;
    std::cout << "ip: ";
    std::cin >> ip;
    std::cout << '\n';

    boost::asio::io_context io_context;

    tcp::resolver resolver(io_context);

    tcp::resolver::results_type endPoints = resolver.resolve(ip, "daytime");

    tcp::socket socket(io_context);

    boost::asio::connect(socket, endPoints);
    for (;;)
    {
        char buf[128];
        boost::system::error_code error;

        size_t len = socket.read_some(boost::asio::buffer(buf), error);

        std::cout.write(buf, len);
    }
}
