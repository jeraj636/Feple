#include <boost/asio.hpp>
#include <memory>
#include <boost/bind/bind.hpp>
#include <iostream>
class TcpPovezava : public std::enable_shared_from_this<TcpPovezava>
{
public:
    typedef std::shared_ptr<TcpPovezava> Kazalec_t;
    static Kazalec_t Ustvari(boost::asio::io_context &ioKontekst)
    {
        return Kazalec_t(new TcpPovezava(ioKontekst));
    }
    boost::asio::ip::tcp::socket &Socket()
    {
        return m_Socket;
    }
    void Start()
    {
        for (;;)
        {
            std::string sporocilo;
            std::cout << "> ";
            std::cin >> sporocilo;
            PosljiSporocilo(sporocilo);
            std::cout << SprejmiSporocilo() << "\n";
        }
    }

private:
    TcpPovezava(boost::asio::io_context &ioKontekst)
        : m_Socket(ioKontekst)
    {
    }
    void PoprimiZaWrite(const boost::system::error_code &, size_t)
    {
    }
    std::string SprejmiSporocilo()
    {
        char buf[100];
        boost::system::error_code error;
        size_t len = m_Socket.read_some(boost::asio::buffer(buf), error);
        if (error == boost::asio::error::eof)
            return "";
        else if (error)
            throw boost::system::system_error(error);
        buf[len + 1] = 0;
        std::string sporocilo(buf);
        return sporocilo;
    }
    void PosljiSporocilo(std::string sporocilo)
    {
        boost::asio::async_write(m_Socket, boost::asio::buffer(sporocilo),
                                 boost::bind(&TcpPovezava::PoprimiZaWrite, shared_from_this(),
                                             boost::asio::placeholders::error,
                                             boost::asio::placeholders::bytes_transferred));
    }

private:
    boost::asio::ip::tcp::socket m_Socket;
};
class Streznik
{
public:
    Streznik(boost::asio::io_context &ioKontekst, int port)
        : m_ioKontekst(ioKontekst),
          m_acceptor(ioKontekst, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port))
    {
        ZacniSprejemati();
    }

private:
    void ZacniSprejemati()
    {
        TcpPovezava::Kazalec_t novaPovezava = TcpPovezava::Ustvari(m_ioKontekst);
        m_acceptor.async_accept(novaPovezava->Socket(),
                                boost::bind(&Streznik::PoprimiZaSprejem,
                                            this, novaPovezava,
                                            boost::asio::placeholders::error));
    }
    void PoprimiZaSprejem(TcpPovezava::Kazalec_t novaPovezava, const boost::system::error_code &error)
    {
        if (!error)
        {
            novaPovezava->Start();
        }
        ZacniSprejemati();
    }

private:
    boost::asio::io_context &m_ioKontekst;
    boost::asio::ip::tcp::acceptor m_acceptor;
};