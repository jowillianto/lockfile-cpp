#pragma once
#include "./lock-base.hpp"
#include <sstream>
#include <vector>

namespace Lock{
  /*
    LockField is the base class for any other classes used.
  */
  template<typename T>
  class LockField : public LockBaseWithType<T>{
    public:
      LockField(const T& defaultValue){
        super::_value  = defaultValue;
      }
      LockField(){}

      const T& get()const{
        return super::_value;
      }
      void set(const T& value){
        _setValue(value, true);
      }
    protected:
      typedef LockBaseWithType<T> super;
      void _setValue(const T& value, const bool& changed = true){
        super::_value  = value;
        if(changed) LockBaseWithType<T>::markChanged();
      }
  };

  /*
    Additional Fields class
  */
  class IntegerField : public LockField<int>{
    public:
      IntegerField(const int& defaultValue) : 
        LockField<int>(defaultValue){}
      IntegerField() : 
        LockField<int>(){}
      std::string serialize() const{
        std::stringstream text;
        text<<_value;
        return text.str();
      }
      void deserialize(const std::string& value){
        _value  = atoi(value.c_str());
      }
  };
  class FloatField : public LockField<float>{
    public:
      FloatField(const float& defaultValue) : 
        LockField<float>(defaultValue){}
      FloatField() : 
        LockField<float>(){}
      std::string serialize() const{
        std::stringstream text;
        text << _value;
        return text.str();
      }
      void deserialize(const std::string& value){
        _value  = atof(value.c_str());
      }
  };
  class CharField : public LockField<std::string>{
    public:
      CharField(const std::string& defaultValue) : 
        LockField<std::string>(defaultValue){}
      CharField() : 
        LockField<std::string>(){}
      std::string serialize() const{
        return _value;
      }
      void deserialize(const std::string& value){
        _value  = value;
      }
  };
  class BoolField : public LockField<bool>{
    public:
      BoolField(const bool& defaultValue) : 
        LockField<bool>(defaultValue){}
      BoolField() : LockField<bool>(){}
      std::string serialize()const{
        if(_value) return "true";
        else return "false";
      }
      void deserialize(const std::string& value){
        if(value == "true") _value = true;
        else _value = false;
      }
  };
  template<typename T>
  class ListField : public LockField<std::vector<T> >{
    public:
      ListField(const std::vector<T>& defaultValue) : super(defaultValue){}
      ListField() : super(){}
      std::string serialize() const{
        std::stringstream s;
        for (auto& entry : super::_value){
          s<<entry<<std::endl;
        }
        return s.str();
      }
      void deserialize(const std::string& value){

      }
    private:
      typedef LockField<std::vector<T> > super;
  };
}