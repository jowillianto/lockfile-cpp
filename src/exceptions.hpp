#pragma once
#include <exception>
#include <string>

namespace Lock{
  class BaseException : public std::exception{
    public:
      const char* what() const noexcept{
        return _msg.c_str();
      }
    protected:  
      std::string _msg;
  };
  class FieldNotFound : public BaseException{
    public:
      FieldNotFound(const std::string& field){
        _msg  = field + " is not found";
      }
  };
  class FieldAlreadyExists : public BaseException{
    public:
      FieldAlreadyExists(const std::string& field){
        _msg  = field + " already exists";
      }
  };
  class FieldIsNotASection : public BaseException{
    public:
      FieldIsNotASection(const std::string& field){
        _msg  = field + " is not a section";
      }
  };
  class FieldIsNotAField : public BaseException{
    public:
      FieldIsNotAField(const std::string& field){
        _msg  = field + " is not a field";
      }
  };
}