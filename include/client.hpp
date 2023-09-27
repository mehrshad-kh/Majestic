#ifndef CLIENT_HPP
#define CLIENT_HPP

#include <cstdint>
#include <memory>
#include <string>
#include <vector>

#include <grpcpp/channel.h>

#include "majestic.grpc.pb.h"

using grpc::Channel;

class Client
{
public:
    explicit Client(const std::shared_ptr<Channel>& channel) :
        stub_(Majestic::NewStub(channel)) {}
    std::vector<uint8_t> retrieveMySalt(const std::string& username);

private:
    std::unique_ptr<Majestic::Stub> stub_;
};

#endif // CLIENT_HPP
