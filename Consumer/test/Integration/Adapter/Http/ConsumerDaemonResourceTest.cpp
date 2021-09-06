#include <string>
#include "gmock/gmock.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Adapter/Http/RouterEntrypoint.h"

class ConsumerDaemonResourceTest : public ::testing::Test
{
public:
    ConsumerDaemonResourceTest() = default;
    ~ConsumerDaemonResourceTest() override = default;

protected:
    const std::string TEST_ADDRESS  = "127.0.0.1";
    const std::string CONTENT_TYPE  = "application/xml";
    const std::string TEST_ENDPOINT = "/consumer/daemon_loop";

};

TEST_F(ConsumerDaemonResourceTest, GET_With_NOT_FOUND)
{
    using namespace Poco::Net;

    ServerSocket serverSocket(0);
    auto httpParameters = new Poco::Net::HTTPServerParams();
    httpParameters->setKeepAlive(false);

    HTTPServer httpServer(new Consumer::Http::RouterEntrypoint(), serverSocket, httpParameters);
    httpServer.start();

    HTTPClientSession clientSession(TEST_ADDRESS, serverSocket.address().port());
    HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, TEST_ENDPOINT);

    request.setContentType(CONTENT_TYPE);
    clientSession.sendRequest(request);

    HTTPResponse response;
    clientSession.receiveResponse(response);

    ASSERT_EQ(CONTENT_TYPE, response.getContentType());
    ASSERT_EQ(Poco::Net::HTTPResponse::HTTP_NOT_FOUND, response.getStatus());
    ASSERT_EQ(Poco::Net::HTTPMessage::UNKNOWN_CONTENT_LENGTH, response.getContentLength());

}

TEST_F(ConsumerDaemonResourceTest, OPTIONS_With_Success)
{

    Poco::Net::ServerSocket serverSocket(0);
    auto httpParameters = new Poco::Net::HTTPServerParams();
    httpParameters->setKeepAlive(false);

    Poco::Net::HTTPServer httpServer(new Consumer::Http::RouterEntrypoint(), serverSocket, httpParameters);
    httpServer.start();

    Poco::Net::HTTPClientSession session(TEST_ADDRESS, serverSocket.address().port());
    Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_OPTIONS, TEST_ENDPOINT);

    request.setContentLength(0);
    request.setContentType(CONTENT_TYPE);
    session.sendRequest(request);

    Poco::Net::HTTPResponse response;
    session.receiveResponse(response);

    ASSERT_EQ(CONTENT_TYPE, response.getContentType());
    ASSERT_EQ(Poco::Net::HTTPResponse::HTTP_OK, response.getStatus());
    ASSERT_EQ("GET, OPTIONS", response.get("Allow"));

}
