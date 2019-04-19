# Find Protobuf installation
set (protobuf_MODULE_COMPATABLE TRUE)
list (APPEND CMAKE_PREFIX_PATH "/usr/local/include/grpc++" "/usr/local/include/google/protobuf/")
find_package(Protobuf REQUIRED)
echo ("Using protobuf ${Protobuf_VERSION}")

set(PROTOBUF_LIBPROTOBUF protobuf::libprotobuf)
set(PROTOBUF_PROTOC $<TARGET_FILE:protobuf::protoc>)

# Find gRPC instalation
find_package(GRPC REQUIRED)
echo ("Using GRPC ${gRPC_VERSION}")

# set(GRPC_GRPCPP_UNSECURE grpc++_unsecure)
set(GRPC_GRPCPP_UNSECURE "-L/usr/local/lib -lgrpc++ -lgrpc -lgrpc++_reflection -ldl")
set(GRPC_CPP_PLUGIN_EXECUTABLE $<TARGET_FILE:gRPC::grpc_cpp_plugin>)
# get_target_property(GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin IMPORTED_LOCATION_RELEASE)

# Proto file, for example, pubsub is what I used in my last project. Checkout grpcpp pubsub system for details https://yiakwy.github.io
get_filename_component(hw_proto "
../proto/pubsub.proto
" ABSOLUTE)
get_filename_component(hw_proto_path "${hw_proto}" PATH)

# Generate sources, or you can use GRPC_GENERATE_CPP micro instead. See Modules/FindGRPC.cmake. Basically they are doing the exactly same things.
set (hw_proto_srcs 
	"${PROTOC}/pubsub.pb.cc"
	)
set (hw_proto_hdrs 
	"${PROTOC}/pubsub.pb.h"
	)
set (hw_grpc__srcs 
	"${PROTOC}/pubsub.grpc.pb.cc"
	)
set (hw_grpc__hdrs 
	"${PROTOC}/pubsub.grpc.pb.h"
	)

# PROTOBUF_GENERATE_CPP(hw_proto_srcs hw_proto_hdrs ${hw_proto})
