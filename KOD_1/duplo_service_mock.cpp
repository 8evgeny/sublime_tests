#include <atomic>
#include <boost/program_options.hpp>
#include <iostream>

#include "MessengerServiceSoapBinding.nsmap"
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wredundant-decls"
#include "soapMessengerServiceSoapBindingService.h"
#pragma GCC diagnostic pop

using namespace boost::program_options;

int main(int argc, const char* argv[]) {
  int port = 8092;
  options_description desc{"Options"};
  desc.add_options()("help,h", "Help screen")(
      "port,p", value<int>(&port)->default_value(8093),
      "The port number on which the server will be started.");

  MessengerServiceSoapBindingService dublo2_mock(SOAP_XML_INDENT);
  variables_map vm;
  store(parse_command_line(argc, argv, desc), vm);
  notify(vm);

  if (vm.count("help")) {
    std::cout << desc << '\n';
  } else {
    std::cout << "The mock of duplo service is starting on the port " << port
              << ".\n";

    if (dublo2_mock.run(port) != SOAP_OK) {
      dublo2_mock.soap_stream_fault(std::cerr);
    }

    dublo2_mock.destroy();
  }
  return 0;
}

/// <summary>
/// Mock implementation of the Duplo2 processGetInfo method.
/// </summary>
/// <paramref name="request"></paramref>
/// <paramref name="response"></paramref>
/// <returns></returns>
int MessengerServiceSoapBindingService::processGetInfo(
    ns1__processGetInfo* /*request*/,
    ns1__processGetInfoResponse& /*response*/) {
  return SOAP_OK;
}

/// <summary>
/// Mock implementation of the Duplo2 process method.
/// </summary>
/// <paramref name="request"></paramref>
/// <paramref name="response"></paramref>
/// <returns></returns>
int MessengerServiceSoapBindingService::process(
    ns1__process* request, ns1__processResponse& /*response*/) {
  static std::atomic_uint64_t calls_num = 0;
  std::cout << ++calls_num << " camera score "
            << request->message->tr_USCOREcheckIn->v_USCOREcamera
            << "-> Speed= "
            << *request->message->tr_USCOREcheckIn->v_USCOREspeed << '\n';
  //  auto photo_grz =
  //      request->message->tr_USCOREcheckIn->v_USCOREphoto_USCOREgrz->__ptr;
  //  auto photo_grz_length =
  //      request->message->tr_USCOREcheckIn->v_USCOREphoto_USCOREgrz->__size;

  //  std::string s(photo_grz, photo_grz + photo_grz_length);
  //  // auto result = base64_decode(s);
  //  std::ofstream file("/home/vladimir/regno.jpg", std::ios::binary);
  //  if (!file) {
  //    std::cout << "Cannot create file\n";
  //  }
  //  file.write(s.c_str(), static_cast<long>(s.size()));
  //  std::cout << "photo_USCOREextra.  "
  //            <<
  //            *request->message->photo_USCOREextra[0]->v_USCOREtype_USCOREphoto
  //            << std::endl;
  //  auto photo_extra =
  //      request->message->photo_USCOREextra[0]->v_USCOREphoto_USCOREextra->__ptr;
  //  auto photo_extra_size =
  //      request->message->photo_USCOREextra[0]->v_USCOREphoto_USCOREextra->__size;
  //  std::string extrafoto(photo_extra, photo_extra + photo_extra_size);
  //  std::ofstream file2("/home/vladimir/extrafoto.jpg", std::ios::binary);
  //  if (!file2) {
  //    std::cout << "Cannot create file\n";
  //  }
  //  file2.write(extrafoto.c_str(), static_cast<long>(extrafoto.size()));

  return SOAP_OK;
}

/// <summary>
/// Mock implementation of the Duplo2 getVersion method.
/// </summary>
/// <paramref name="request"></paramref>
/// <paramref name="response"></paramref>
/// <returns></returns>
int MessengerServiceSoapBindingService::getVersion(
    ns1__getVersion* /*request*/, ns1__getVersionResponse& /*response*/) {
  return SOAP_OK;
}
