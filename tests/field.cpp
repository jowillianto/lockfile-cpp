#include "../deps/test-lib/test-lib.hpp"
#include "../src/lock-field.hpp"
#include "../src/lock-section.hpp"

int main(){
  Test::TestCase fieldTest("Test of Fields");
  fieldTest.addTest("initialization", [](){
    auto field  = Lock::CharField("Hello World");
    if(field.get() != "Hello World")
      throw "defaultValue setting error";
  });
  fieldTest.addTest("mutation", [](){
    auto field  = Lock::CharField("Hello World");
    if(field.get() != "Hello World")
      throw "defaultValue setting errror";
    // Mutate field
    field.set("A New Value");
    if(field.get() != "A New Value")
      throw "Mutation failed";
  });
  fieldTest.addTest("init mutate list field", [](){
    auto field  = Lock::ListField<std::string>({"a"});
    if(field.get().size() != 1) 
      throw "defaultValue setting error";
    auto cont   = field.get();
    cont.push_back("b");
    field.set(cont);
    if(field.get().size() != 2)
      throw "push_back() failed";
    cont        = field.get();
    cont.clear();
    field.set(cont);
    if(field.get().size() != 0)
      throw "clearing failed";
  });
  fieldTest.addTest("Polymorphism", [](){
    auto field  = Lock::ListField<std::string>({"a"});
    Lock::LockBaseWithType<std::vector<std::string> >& polyField  = field;
    if(polyField.get().size() != 1)
      throw "defaultValue setting error";
    auto cont   = polyField.get();
    cont.push_back("b");
    polyField.set(cont);
    if(field.get().size() != 2)
      throw "push_back failed";
  });
  fieldTest.runAll();
}
