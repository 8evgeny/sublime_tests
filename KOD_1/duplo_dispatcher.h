#pragma once

#include <fstream>
#include <memory>
#include <vector>
#include "soapMessengerServiceSoapBindingProxy.h"

// library
#include "violation_order.h"

namespace sadko {

using ProxyPtrS = std::shared_ptr<MessengerServiceSoapBindingProxy>;

class DuploDispatcher {
 public:
  ~DuploDispatcher();

  explicit DuploDispatcher(const char* host);

  void SetMaxResendNumberOnError(int number) {
    _max_resend_number_on_error = number;
  }

  void SendMessage(const ViolationOrder& violation_order);

  void SetMessengerService(ProxyPtrS proxy);
  void SetDelay(int delay) { _delay = delay; }

 private:
  ProxyPtrS _proxy;
  int _max_resend_number_on_error = 0;
  int _delay = 0;
};
}  // namespace sadko
