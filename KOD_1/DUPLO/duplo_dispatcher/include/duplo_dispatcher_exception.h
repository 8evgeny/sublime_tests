#pragma once
#include <exception>
#include <string>
class DuploDispatcherException : public std::exception {
 public:
  explicit DuploDispatcherException(unsigned short err_code)
      : _err_code(err_code) {}
  unsigned short get_err_code() { return _err_code; }

 protected:
  unsigned short _err_code;
};

class SOAPConnectionException : public DuploDispatcherException {
 public:
  explicit SOAPConnectionException(unsigned short err_num)
      : DuploDispatcherException(err_num) {}
};

class SOAPDuploException : public DuploDispatcherException {
 public:
  explicit SOAPDuploException(unsigned short err_num)

      : DuploDispatcherException(err_num) {}
};

class SOAPDuploFault : public DuploDispatcherException {
 public:
  explicit SOAPDuploFault(unsigned short err_num, const std::string& fault_code,
                          const std::string& fault_message)
      : DuploDispatcherException(err_num),
        _fault_code(fault_code),
        _fault_message(fault_message) {}
  std::string get_fault_code() { return _fault_code; }
  std::string get_fault_message() { return _fault_message; }

 protected:
  std::string _fault_code;
  std::string _fault_message;
};

class SOAPDuploFaultSql : public DuploDispatcherException {
 public:
  explicit SOAPDuploFaultSql(unsigned short err_num)
      : DuploDispatcherException(err_num) {}
};
