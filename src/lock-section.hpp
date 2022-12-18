#pragma once
#include "./lock-base.hpp"
#include <vector>

namespace Lock{
  class LockSection : public LockBase{
    public:
      LockSection() : LockBase(LOCK_TYPE_SECTION){

      }
      void addField(
        const std::string& fieldName, LockBase* lockField, 
        const bool& deleteAfter = true
      ){
        if(_value.count(fieldName) == 0){
          _value[fieldName]   = lockField;
          _boolMap[fieldName] = deleteAfter;
          _typeMap[fieldName] = lockField -> lockType();
          _fields.push_back(fieldName);
        }
        else{
          // Throw exception if field already exists
        }
      }
      /*
        getRaw()
        returns a LockBase reference of the corresponding field. The field can 
        then be type casted or just used for serialization and deserialization.
      */
      LockBase& getRaw(const std::string& fieldName){
        if(_value.count(fieldName) != 0)
          return *(_value.at(fieldName));
          // Throw exception
      }
      const LockBase& getRaw(const std::string& fieldName)const{
        if(_value.count(fieldName) != 0)
          return *(_value.at(fieldName));
      }
      /*
        getField()
        returns a type casted reference of the field. LockBaseWithType<T> is 
        expected as the return value.
      */
      template<typename T>
      LockBaseWithType<T>& getField(const std::string& fieldName){
        auto& field     = getRaw(fieldName);
        auto& fieldType = _typeMap[fieldName];
        if(fieldType == LOCK_TYPE_FIELD){
          return static_cast<LockBaseWithType<T>& >(field);
        }
        else{
          // Throw error
        }
      }
      template<typename T>
      const LockBaseWithType<T>& getField(const std::string& fieldName) const{
        auto& field     = getRaw(fieldName);
        auto& fieldType = _typeMap.at(fieldName);
        if(fieldType == LOCK_TYPE_FIELD){
          return static_cast<const LockBaseWithType<T>& >(field);
        }
      }
      /*
        getSection()
        returns a type casted reference of the field. LockSection is the return 
        type
      */
      LockSection& getSection(const std::string& fieldName){
        auto& field     = getRaw(fieldName);
        auto& fieldType = _typeMap.at(fieldName);
        if(fieldType == LOCK_TYPE_SECTION){
          return static_cast<LockSection& >(field);
        }
      }
      const LockSection& getSection(const std::string& fieldName)const{
        auto& field     = getRaw(fieldName);
        auto& fieldType = _typeMap.at(fieldName);
        if(fieldType == LOCK_TYPE_SECTION){
          return static_cast<const LockSection& >(field);
        }
      }
      /*
        fields()
        Get a list of fields in the section
      */
      const std::vector<std::string>& fields()const{
        return _fields;
      }

      
      std::string serialize() const{
        return "";
      }
      void deserialize(const std::string& value){

      }
      ~LockSection(){
        for(auto& [key, value] : _value){
          if(_boolMap[key]) delete value;
        }
      }


      static LockSection& create(){
        return *(new LockSection);
      }
    protected:
      std::map<std::string, LockBase*> _value;
      std::map<std::string, bool> _boolMap;
      std::map<std::string, std::size_t> _typeMap;
      std::vector<std::string> _fields;
  };
}