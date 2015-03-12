/////////////////////////////////////////////////////////////////////////
// FILE HEADER
// #DATE#:  
/////////////////////////////////////////////////////////////////////////

#ifndef NODE_GENERATOR_HPP
#define NODE_GENERATOR_HPP

#include <string>
#include <vector>
#include <iosfwd>
#include <map>
#include "Node.hpp"

class NodeGenerator
{
  public:
    NodeGenerator();
    virtual ~NodeGenerator();

    bool LoadFile(const std::string & fname);

    Node::node_set_t GetNodes() const;

    void Dump() const;


  private:

    typedef std::map<std::string, Node *> node_map_t;
    node_map_t m_nodes;

    Node * m_get_node(const std::string & name);
    bool m_add_link(const std::string & from_node_name, 
                    const std::string & to_node_name);
                
    bool m_load_nodes(std::ifstream & ifs);
    bool m_load_links(std::ifstream & ifs);
};


#endif // NODE_GENERATOR_HPP
