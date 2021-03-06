# What Is It?

RESTinio is a header-only C++14 library that gives you an embedded
HTTP/Websocket server. It is based on standalone version of ASIO and targeted
primarily for asynchronous processing of HTTP-requests.

# A Very Basic Example Of RESTinio

Consider the task of writing a C++ application that must support some REST API,
RESTinio represents our solution for that task. Currently it is in stable beta state.
Lets see how it feels like in the simplest case:

~~~~~{.cpp}
#include <iostream>
#include <restinio/all.hpp>
int main()
{
    restinio::run(
        restinio::on_this_thread()
        .port(8080)
        .address("localhost")
        .request_handler([](auto req) {
            return req->create_response().set_body("Hello, World!").done();
        }));
    return 0;
}
~~~~~

Server runs on the main thread, and respond to all requests with hello-world
message. Of course you've got an access to the structure of a given HTTP request,
so you can apply a complex logic for handling requests.

# Features

* Async request handling. Cannot get the response data immediately? That's ok,
  store request handle somewhere and/or pass it to another execution context
  and get back to it when the data is ready.
* HTTP pipelining. Works well with async request handling.
  It might increase your server throughput dramatically.
* Timeout control. RESTinio can take care of bad connection that are like: send
  "GET /" and then just stuck.
* Response builders. Need chunked-encoded body - then RESTinio has a special
  response builder for you (obviously it is not the only builder).
* ExpressJS-like request routing.
* Supports TLS (HTTPS).
* Basic websocket support. Simply restinio::websocket::basic::upgrade() the
  request handle and start websocket session on a corresponding connection.
* Can run on external asio::io_context. RESTinio is separated from execution
  context.
* Some tune options. One can set acceptor and socket options. When running
  RESTinio on a pool of threads connections can be accepted in parallel.

# License

RESTinio is distributed under BSD-3-CLAUSE license.

# How To Use It?

The full documentation for RESTinio can be found [here](https://stiffstream.com/en/docs/restinio/0.4).

# More

* Issues and bugs:
[Issue Tracker on BitBucket](https://bitbucket.org/sobjectizerteam/restinio-0.4/issues).
