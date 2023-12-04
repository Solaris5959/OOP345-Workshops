#ifndef SDDS_DIRECTORY_H
#define SDDS_DIRECTORY_H
#include <vector>
#include "Resource.h"
#include "Flags.h"

namespace sdds
{
    class Directory : public Resource {
        std::vector<Resource*> m_contents;
      public:
      // [part 1]
        Directory(std::string dName);
        void update_parent_path(const std::string &);
        NodeType type() const;
        std::string path() const;
        std::string name() const;
        int count() const;
        size_t size() const;
        Directory& operator+=(Resource *);
        Resource* find(const std::string&, const std::vector<OpFlags>& = std::vector<OpFlags>());
        ~Directory();
        // disallow copy/move
        Directory(const Directory&) = delete;
        Directory& operator=(const Directory&) = delete;

      // [part 2]
        void remove(const std::string&, const std::vector<OpFlags>& = std::vector<OpFlags>());
        void display(std::ostream&, const std::vector<FormatFlags>& = std::vector<FormatFlags>()) const;
    };
}

#endif