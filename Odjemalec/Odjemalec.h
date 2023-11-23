#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <string>
#include <iostream>

class Odjemalec
{
public:
    Odjemalec(boost::asio::io_context &ioKontekst, std::string ip, std::string port)
        : resolver(ioKontekst), socket(ioKontekst)
    {
        endpoints = resolver.resolve(ip, port);
        boost::asio::connect(socket, endpoints);
    }
    std::string SprejmiSporocilo()
    {
        char buf[100];
        boost::system::error_code error;

        size_t len = socket.read_some(boost::asio::buffer(buf), error);

        if (error == boost::asio::error::eof)
            return ""; // Connection closed cleanly by peer.
        else if (error)
            throw boost::system::system_error(error); // Some other error.
        buf[len + 1] = 0;
        std::string sporocilo(buf);
        return sporocilo;
    }
    void PosljiSporocilo(const std::string &sporocilo)
    {
        boost::system::error_code ignored_error;
        boost::asio::write(socket, boost::asio::buffer(sporocilo), ignored_error);
    }

private:
    boost::asio::ip::tcp::resolver resolver;
    boost::asio::ip::tcp::resolver::results_type endpoints;
    boost::asio::ip::tcp::socket socket;
};