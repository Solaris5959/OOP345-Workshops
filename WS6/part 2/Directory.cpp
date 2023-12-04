#include <string>
#include <vector>
#include <iostream>
#include <iomanip>
#include "Directory.h"
#include "Resource.h"
#include "Flags.h"

namespace sdds {
    // [part 1]
    Directory::Directory(std::string dName) {
        m_name = dName;
        m_contents = {};
    }
    
    void Directory::update_parent_path(const std::string &newPath) {
        m_parent_path = newPath;

        for (Resource* resource : m_contents)
            if (resource)
                resource->update_parent_path(path());
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
        if (find(newResource->name()))
            throw std::string("Already in Directory");
        else {
            newResource->update_parent_path(path());
            m_contents.push_back(newResource);
        }

        return *this;
    }
    
    Resource *Directory::find(const std::string &name, const std::vector<OpFlags> &operationFlag) {
        if (!(operationFlag.empty()) && (operationFlag.front() == OpFlags::RECURSIVE)) {
            Resource * ret = nullptr;
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
            if (!m_contents.empty())
                for (auto it = m_contents.begin(); it != m_contents.end(); it++)
                    if ((*it)->name() == name)
                        return (*it);

            return nullptr;
        }
    }
    
    Directory::~Directory() {
        for (auto it = m_contents.begin(); it != m_contents.end(); it++) 
                delete *it; // delete file or recursively call destructor on subdirectory
        m_contents.clear();
    }

    // [part 2]
    void Directory::remove(const std::string& name, const std::vector<OpFlags>& flags) {
        bool isRecursive = false;

        for (const OpFlags& f : flags)
            if (f == OpFlags::RECURSIVE)
                isRecursive = true;

        Resource* toDelete = find(name);

        if (toDelete) {
            size_t indexOfResult{}, i = 0;
            for (auto element : m_contents) {
                if (element == toDelete)
                    indexOfResult = i;
                i++;
            }

            if (toDelete->type() == NodeType::FILE) {
                delete toDelete;
                m_contents.erase(m_contents.begin() + indexOfResult);
            }
            else if (toDelete->type() == NodeType::DIR) {
                if (isRecursive) {
                    delete toDelete;
                    m_contents.erase(m_contents.begin() + indexOfResult);
                }
                else
                    throw std::invalid_argument(name + " is a directory. Pass the recursive flag to delete directories.");
            }
        }
        else
            throw std::string(name + " does not exist in " + m_parent_path);
    }
    
    void Directory::display(std::ostream& out, const std::vector<FormatFlags>& formatFlag) const {
        out << "Total size: " << size() << " bytes" << std::endl;
        for (size_t i = 0; i < m_contents.size(); i++) {
            out << ((m_contents.at(i)->type() == NodeType::DIR) ? "D | " : "F | ") // part 1 ("F | FILE_NAME |" or "D | DIR_NAME |")
                << std::left << std::setw(15) << m_contents.at(i)->name() << " |";
            
            if (!formatFlag.empty() && formatFlag.front() == FormatFlags::LONG) {
                out << " ";
                if (m_contents.at(i)->type() == NodeType::DIR)
                    out << std::right << std::setw(2) 
                        << m_contents.at(i)->count();
                else 
                    out << "  ";
                out << " | " << std::right << std::setw(10) 
                    << std::string(std::to_string(m_contents.at(i)->size()) + " bytes") << " | ";
            }
            out << std::endl;
        }
    }
}