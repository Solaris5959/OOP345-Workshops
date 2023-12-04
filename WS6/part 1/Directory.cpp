#include <string>
#include <vector>
#include "Directory.h"
#include "Resource.h"
#include "Flags.h"

namespace sdds {
    Directory::Directory(std::string dName) {
        m_name = dName;
    }
    
    void Directory::update_parent_path(const std::string &newPath) {
        m_parent_path = newPath;
    }
    
    NodeType Directory::type() const {
        return NodeType::DIR;
    }
    
    std::string Directory::path() const {
        return m_parent_path + m_name;
    }
    
    std::string Directory::name() const {
        return m_name;
    }
    
    int Directory::count() const {
        return m_contents.size();
    }
    
    size_t Directory::size() const {
        size_t totalSize = 0u;
        for (auto it = m_contents.begin(); it != m_contents.end(); it++)
            totalSize += (**it).size();

        return totalSize;
    }
    
    Directory &Directory::operator+=(Resource *newResource) {
        if (this->find(newResource->name()))
            throw "Already in Directory";
        else {
            newResource->update_parent_path(path());
            m_contents.push_back(newResource);
        }

        return *this;
    }
    
    Resource *Directory::find(const std::string &name, const std::vector<OpFlags> &operationFlag) {
        if (!(operationFlag.empty()) && (operationFlag.front() == OpFlags::RECURSIVE)) {
            Resource * ret;
            for (size_t i = 0; i < m_contents.size(); i++) {
                if (m_contents.at(i)->type() == NodeType::DIR) {
                    Directory* dir = dynamic_cast<Directory*>(m_contents.at(i));
                    ret = dir->find(name, operationFlag);
                }
                else 
                    if (m_contents.at(i)->name() == name)
                        return m_contents.at(i);
            }

            if (ret)
                return ret;
            return nullptr;
        }
        else {
            for (auto it = m_contents.begin(); it != m_contents.end(); it++)
                if ((*it)->name() == name)
                    return (*it);

            return nullptr;
        }
    }
    
    Directory::~Directory() {
        for (auto it = m_contents.begin(); it != m_contents.end(); it++)
                delete *it; // delete file
    }
}