#include <string>
#include <gtest/gtest.h>
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Foundation/Http/Double/FakeRouter.h"
#include "Foundation/Http/Double/EscapedErrorMessageParser.h"

class HttpResourceTest : public ::testing::Test
{
public:
    HttpResourceTest() = default;
    ~HttpResourceTest() override = default;

protected:
    const std::string TEST_ADDRESS              = "127.0.0.1";
    const std::string TEST_ENDPOINT             = "/test_endpoint";
    const std::string TEST_EXCEPTION_ENDPOINT   = "/test_endpoint_exception";
    const std::string CONTENT_TYPE              = "application/xml";

};


TEST_F(HttpResourceTest, XMLInHttpMediaHeader) {

    using namespace Poco::Net;

    ServerSocket serverSocket(0);
    auto httpParameters = new HTTPServerParams();
    httpParameters->setKeepAlive(false);

    HTTPServer httpServer(new Foundation::Http::FakeRouter(), serverSocket, httpParameters);
    httpServer.start();

    HTTPClientSession session(TEST_ADDRESS, serverSocket.address().port());
    HTTPRequest request(HTTPRequest::HTTP_PATCH, TEST_ENDPOINT);

    request.setContentLength(0);
    request.setContentType(CONTENT_TYPE);
    session.sendRequest(request);

    HTTPResponse response;
    session.receiveResponse(response);

    ASSERT_EQ(CONTENT_TYPE, response.getContentType());

}

TEST_F(HttpResourceTest, UnsupportedHttpMediaType) {

    using namespace Poco::Net;

    ServerSocket serverSocket(0);
    auto httpParameters = new HTTPServerParams();
    httpParameters->setKeepAlive(false);

    HTTPServer httpServer(new Foundation::Http::FakeRouter(), serverSocket, httpParameters);
    httpServer.start();

    HTTPClientSession session(TEST_ADDRESS, serverSocket.address().port());
    HTTPRequest request(HTTPRequest::HTTP_POST, TEST_ENDPOINT);

    request.setContentLength(0);
    request.setContentType("application/json");
    session.sendRequest(request);

    HTTPResponse response;
    session.receiveResponse(response);

    ASSERT_EQ(HTTPResponse::HTTP_UNSUPPORTED_MEDIA_TYPE, response.getStatus());

}

TEST_F(HttpResourceTest, MethodNotAllowed) {

    using namespace Poco::Net;

    ServerSocket serverSocket(0);
    auto httpParameters = new HTTPServerParams();
    httpParameters->setKeepAlive(false);

    HTTPServer httpServer(new Foundation::Http::FakeRouter(), serverSocket, httpParameters);
    httpServer.start();

    HTTPClientSession session(TEST_ADDRESS, serverSocket.address().port());
    HTTPRequest request(HTTPRequest::HTTP_TRACE, TEST_ENDPOINT);

    request.setContentLength(0);
    request.setContentType(CONTENT_TYPE);
    session.sendRequest(request);

    HTTPResponse response;
    session.receiveResponse(response);

    ASSERT_EQ(HTTPResponse::HTTP_METHOD_NOT_ALLOWED, response.getStatus());

}

TEST_F(HttpResourceTest, MethodNotImplemented) {

    using namespace Poco::Net;

    ServerSocket serverSocket(0);
    auto httpParameters = new HTTPServerParams();
    httpParameters->setKeepAlive(false);

    HTTPServer httpServer(new Foundation::Http::FakeRouter(), serverSocket, httpParameters);
    httpServer.start();

    HTTPClientSession session(TEST_ADDRESS, serverSocket.address().port());
    HTTPRequest request(HTTPRequest::HTTP_PATCH, TEST_ENDPOINT);

    request.setContentLength(0);
    request.setContentType(CONTENT_TYPE);
    session.sendRequest(request);

    HTTPResponse response;
    session.receiveResponse(response);

    ASSERT_EQ(HTTPResponse::HTTP_NOT_IMPLEMENTED, response.getStatus());

}

TEST_F(HttpResourceTest, HttpGETResponse) {

    using namespace Poco::Net;

    ServerSocket serverSocket(0);
    auto httpParameters = new HTTPServerParams();
    httpParameters->setKeepAlive(false);

    HTTPServer httpServer(new Foundation::Http::FakeRouter(), serverSocket, httpParameters);
    httpServer.start();

    HTTPClientSession session(TEST_ADDRESS, serverSocket.address().port());
    HTTPRequest request(HTTPRequest::HTTP_GET, TEST_ENDPOINT);

    request.setContentLength(0);
    request.setContentType(CONTENT_TYPE);
    session.sendRequest(request);

    std::string responseContent;
    HTTPResponse response;
    session.receiveResponse(response) >> responseContent;

    ASSERT_EQ("{}", responseContent);
    ASSERT_EQ(CONTENT_TYPE, response.getContentType());
    ASSERT_EQ(HTTPResponse::HTTP_OK, response.getStatus());

}

TEST_F(HttpResourceTest, HttpPOSTResponse) {

    using namespace Poco::Net;

    ServerSocket serverSocket(0);
    auto httpParameters = new HTTPServerParams();
    httpParameters->setKeepAlive(false);

    HTTPServer httpServer(new Foundation::Http::FakeRouter(), serverSocket, httpParameters);
    httpServer.start();

    HTTPClientSession session(TEST_ADDRESS, serverSocket.address().port());
    HTTPRequest request(HTTPRequest::HTTP_POST, TEST_ENDPOINT);

    request.setContentLength(0);
    request.setContentType(CONTENT_TYPE);
    session.sendRequest(request);

    HTTPResponse response;
    session.receiveResponse(response);

    ASSERT_EQ(CONTENT_TYPE, response.getContentType());
    ASSERT_EQ(HTTPResponse::HTTP_CREATED, response.getStatus());
    ASSERT_EQ("http://localhost?key=value", response.get("Content-Location"));

}

TEST_F(HttpResourceTest, HttpOPTIONSResponse) {

    using namespace Poco::Net;

    ServerSocket serverSocket(0);
    auto httpParameters = new HTTPServerParams();
    httpParameters->setKeepAlive(false);

    HTTPServer httpServer(new Foundation::Http::FakeRouter(), serverSocket, httpParameters);
    httpServer.start();

    HTTPClientSession session(TEST_ADDRESS, serverSocket.address().port());
    HTTPRequest request(HTTPRequest::HTTP_OPTIONS, TEST_ENDPOINT);

    request.setContentLength(0);
    request.setContentType(CONTENT_TYPE);
    session.sendRequest(request);

    HTTPResponse response;
    session.receiveResponse(response);

    ASSERT_EQ(CONTENT_TYPE, response.getContentType());
    ASSERT_EQ(HTTPResponse::HTTP_OK, response.getStatus());
    ASSERT_EQ("GET, POST, PUT, OPTIONS, PATCH", response.get("Allow"));

}

TEST_F(HttpResourceTest, HttpErrorMessage) {

    using namespace Poco::Net;

    ServerSocket serverSocket(0);
    auto httpParameters = new HTTPServerParams();
    httpParameters->setKeepAlive(false);

    HTTPServer httpServer(new Foundation::Http::FakeRouter(), serverSocket, httpParameters);
    httpServer.start();

    HTTPClientSession session(TEST_ADDRESS, serverSocket.address().port());
    HTTPRequest request(HTTPRequest::HTTP_GET, "/not_existing_endpoint");

    request.setContentLength(0);
    request.setContentType(CONTENT_TYPE);
    session.sendRequest(request);

    std::string xmlResponse;
    HTTPResponse response;
    session.receiveResponse(response) >> xmlResponse;

    auto errorParser = Foundation::Http::EscapedErrorMessageParser();
    auto errorMessage = errorParser.toXml(
        HTTPResponse::HTTP_REASON_NOT_FOUND,
        std::to_string(HTTPResponse::HTTP_NOT_FOUND),
        "This endpoint does not exist."
    );

    ASSERT_EQ(errorMessage, xmlResponse);
    ASSERT_EQ(CONTENT_TYPE, response.getContentType());
    ASSERT_EQ(errorMessage.length(), response.getContentLength());
    ASSERT_EQ(HTTPResponse::HTTP_NOT_FOUND, response.getStatus());

}

TEST_F(HttpResourceTest, ExceptionThrownWithinHttpMethodHandler) {

    using namespace Poco::Net;

    ServerSocket serverSocket(0);
    auto httpParameters = new HTTPServerParams();
    httpParameters->setKeepAlive(false);

    HTTPServer httpServer(new Foundation::Http::FakeRouter(), serverSocket, httpParameters);
    httpServer.start();

    HTTPClientSession session(TEST_ADDRESS, serverSocket.address().port());
    HTTPRequest request(HTTPRequest::HTTP_PUT, TEST_ENDPOINT);

    request.setContentLength(0);
    request.setContentType(CONTENT_TYPE);
    session.sendRequest(request);

    std::string responseContent;
    HTTPResponse response;
    session.receiveResponse(response) >> responseContent;

    auto errorParser = Foundation::Http::EscapedErrorMessageParser();
    auto errorMessage = errorParser.toXml(
        HTTPResponse::HTTP_REASON_BAD_REQUEST,
        std::to_string(HTTPResponse::HTTP_BAD_REQUEST),
        "You sent a request that this server could not understand."
    );

    // ASSERT_EQ(errorMessage, responseContent);
    ASSERT_EQ(CONTENT_TYPE, response.getContentType());
    // ASSERT_EQ(errorMessage.length(), response.getContentLength());
    ASSERT_EQ(HTTPResponse::HTTP_BAD_REQUEST, response.getStatus());

}

TEST_F(HttpResourceTest, ExceptionThrownWithinResourceFactory) {

    using namespace Poco::Net;
    
    ServerSocket serverSocket(0);
    auto httpParameters = new HTTPServerParams();
    httpParameters->setKeepAlive(false);

    HTTPServer httpServer(new Foundation::Http::FakeRouter(), serverSocket, httpParameters);
    httpServer.start();

    HTTPClientSession session(TEST_ADDRESS, serverSocket.address().port());
    HTTPRequest request(HTTPRequest::HTTP_PUT, TEST_EXCEPTION_ENDPOINT);

    request.setContentLength(0);
    request.setContentType(CONTENT_TYPE);
    session.sendRequest(request);

    std::string responseContent;
    HTTPResponse response;
    session.receiveResponse(response) >> responseContent;

    auto errorParser = Foundation::Http::EscapedErrorMessageParser();
    auto errorMessage = errorParser.toXml(
        HTTPResponse::HTTP_REASON_INTERNAL_SERVER_ERROR,
        std::to_string(HTTPResponse::HTTP_INTERNAL_SERVER_ERROR),
        "NullPointerException"
    );

    // ASSERT_EQ(errorMessage, responseContent);
    ASSERT_EQ(CONTENT_TYPE, response.getContentType());
    // ASSERT_EQ(errorMessage.length(), response.getContentLength());
    ASSERT_EQ(HTTPResponse::HTTP_INTERNAL_SERVER_ERROR, response.getStatus());

}
