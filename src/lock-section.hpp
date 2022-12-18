#pragma once
#include "./lock-base.hpp"
#include "./exceptions.hpp"
#include <vector>

namespace Lock{
  class LockSection : public LockBase{
    public:
      LockSection() : LockBase(LOCK_TYPE_SECTION){}
      /*
        Add a field into the LockSection. Somehow requires a pointer.
        fieldName   -> the name of the field
        lockField   -> the lock base we are supposed to add to the section
        deleteAfter -> if the field should be deleted later
      */
      void addField(const std::string& fieldName, LockBase* lockField){
        if(_value.count(fieldName) == 0){
          _value[fieldName]   = lockField;
          _fields.push_back(fieldName);
        }
        else
          throw FieldAlreadyExists(fieldName);
      }
      /*
        returns a LockBase reference of the corresponding field. The field can 
        then be type casted or just used for serialization and deserialization.
        fieldName   -> the name of the field
      */
      LockBase& getRaw(const std::string& fieldName){
        if(_value.count(fieldName) != 0)
          return *(_value.at(fieldName));
        else
          throw FieldNotFound(fieldName);
      }
      const LockBase& getRaw(const std::string& fieldName)const{
        if(_value.count(fieldName) != 0)
          return *(_value.at(fieldName));
        else
          throw FieldNotFound(fieldName);
      }
      /*
        returns a type casted reference of the field. LockBaseWithType<T> is 
        expected as the return value.
        fieldName   -> the name of the field
      */
      template<typename T>
      LockBaseWithType<T>& getField(const std::string& fieldName){
        auto& field     = getRaw(fieldName);
        if(field.lockType() == LOCK_TYPE_FIELD)
          return static_cast<LockBaseWithType<T>& >(field);
        else
          throw FieldIsNotAField(fieldName);
        
      }
      template<typename T>
      const LockBaseWithType<T>& getField(const std::string& fieldName) const{
        auto& field     = getRaw(fieldName);
        if(field.lockType() == LOCK_TYPE_FIELD)
          return static_cast<const LockBaseWithType<T>& >(field);
        else
          throw FieldIsNotAField(fieldName);
      }
      /*
        returns a type casted reference of the field. LockSection is the return 
        type
        fieldName   -> the name of the field
      */
      LockSection& getSection(const std::string& fieldName){
        auto& field     = getRaw(fieldName);
        if(field.lockType() == LOCK_TYPE_SECTION)
          return static_cast<LockSection& >(field);
        else
          throw FieldIsNotASection(fieldName);
      }
      const LockSection& getSection(const std::string& fieldName)const{
        auto& field     = getRaw(fieldName);
        if(field.lockType() == LOCK_TYPE_SECTION)
          return static_cast<const LockSection& >(field);
        else
          throw FieldIsNotASection(fieldName);
      }
      /*
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
    protected:
      std::map<std::string, LockBase*> _value;
      std::vector<std::string> _fields;
  };
}