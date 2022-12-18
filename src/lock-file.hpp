#pragma once
#include <filesystem>
#include <vector>
#include "./lock-section.hpp"

namespace Lock{
  class LockFileBase{
    public:
      LockFileBase(
        const std::filesystem::path& filePath,  LockSection* section
      ){
        _filePath   = filePath;
        _fileSection= section;
      }
      /*
        returns the file path to the lock file
      */
      const std::filesystem::path& filePath()const{
        return _filePath;
      }
      /*
        returns the internal data stored in the file. LockSection type
      */
      LockSection& data(){
        return *_fileSection;
      }
      const LockSection& data()const{
        return *_fileSection;
      }
      
      // Override the functions over here to use as file.
    private:
      std::filesystem::path _filePath;
      LockSection* _fileSection;
  };
}