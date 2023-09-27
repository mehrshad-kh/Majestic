cmake_minimum_required(VERSION 3.20)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(gRPC CONFIG REQUIRED)
find_package(Protobuf CONFIG REQUIRED)

set(PROTO_FILES	
	majestic.proto
)

# Generate Protobuf- and gRPC-related files.
add_library(MyGrpc ${PROTO_FILES})
target_link_libraries(MyGrpc PUBLIC protobuf::libprotobuf gRPC::grpc++)
target_include_directories(MyGrpc PUBLIC ${CMAKE_CURRENT_BINARY_DIR})
get_target_property(GRPC_CPP_PLUGIN_LOCATION gRPC::grpc_cpp_plugin LOCATION)
protobuf_generate(TARGET MyGrpc LANGUAGE cpp)
protobuf_generate(
	TARGET MyGrpc
	LANGUAGE grpc
	GENERATE_EXTENSIONS .grpc.pb.h .grpc.pb.cc
	PLUGIN "protoc-gen-grpc=${GRPC_CPP_PLUGIN_LOCATION}"
)
