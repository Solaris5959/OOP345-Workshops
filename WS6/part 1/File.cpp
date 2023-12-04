#include <string>
#include "File.h"
#include "Resource.h"
#include "Flags.h"

namespace sdds {
    File::File(std::string fName, std::string fContents) {
        m_name = fName;
        m_contents = fContents;
    }
    
    void File::update_parent_path(const std::string& newPath) {
        m_parent_path = newPath;
    }
    
    NodeType File::type() const {
        return NodeType::FILE;
    }
    
    std::string File::path() const {
        return m_parent_path + m_name;
    }
    
     std::string File::name() const {
        return m_name;
     }
    
    int File::count() const {
        return -1;
    }
    
    size_t File::size() const {
        return m_contents.size();
    }
}