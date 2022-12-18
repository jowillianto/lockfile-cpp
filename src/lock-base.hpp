#pragma once
#include <string>
#include <map>

#define LOCK_TYPE_FIELD 0
#define LOCK_TYPE_SECTION 1 

namespace Lock{
  /*
    LockBase
    Provides the base for all lock fields used. All Lock Fields should subclass
    this. 
  */
  class LockBase{
    public:
      LockBase(const int& lockType){
        _type = lockType;
      }
      /*
        Changes API
      */
      const bool& changed()const{
        return _changed;
      }
      void markChanged(){
        _changed  = true;
      }
      virtual void flush(){
        _changed  = false;
      }
      /*
        Serializing API
      */
      virtual std::string serialize() const = 0;
      virtual void deserialize(const std::string& value) = 0;
      /*
        Field Typing
      */
      const size_t& lockType() const{
        return _type;
      }

    private:
      bool _changed;
      size_t _type;
  };
  /*
    LockBaseWithType<FieldType>
    Bases for the creation of LockFields with types
  */
  template<typename T>
  class LockBaseWithType : public LockBase{
    public:
      LockBaseWithType() : LockBase(LOCK_TYPE_FIELD){}
      /*
        Setters and Getters
      */
      virtual const T& get()const = 0;
      virtual void set(const T& value) = 0;
    protected:  
      T _value;
      virtual void _setValue(const T& value, const bool& changed = true) = 0;
  };
}