#include "client.hpp"

#include <algorithm>
#include <exception>
#include <iostream>
#include <string>

#include <fmt/core.h>

using grpc::ClientContext;
using grpc::Status;

std::vector<uint8_t> Client::retrieveMySalt(const std::string& username)
{
    ClientContext context;
    ByteArray salt;
    MKString username_as_mk_string;
    username_as_mk_string.set_value(username);

    Status status = stub_->RetrieveSalt(&context, username_as_mk_string, &salt);
    if (!status.ok()) {
        throw std::runtime_error(fmt::format("{:d} {:s} {:s}", (int)status.error_code(), status.error_message(), status.error_details()));
    }

    return std::vector<uint8_t>(salt.value().begin(), salt.value().end());
}
