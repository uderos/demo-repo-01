
#include <iostream>
#include <fstream>
#include <sstream>
#include "NodeGenerator.hpp"

// 20150225-01 WS01

NodeGenerator::NodeGenerator()
{
  ;
}

NodeGenerator::~NodeGenerator()
{
  ;
}


bool NodeGenerator::LoadFile(const std::string & fname)
{
  m_nodes.clear();

  std::ifstream ifs(fname.c_str());
  
  bool result = ifs && 
                m_load_nodes(ifs) &&
                m_load_links(ifs);

  if (! result)
    m_nodes.clear();

  return result;
}


void NodeGenerator::Dump() const
{
  std::cout << "DUMP = NumNodes=" << m_nodes.size() << std::endl;
    
  for (node_map_t::const_iterator p = m_nodes.begin();
      p != m_nodes.end(); ++p) {
    (p->second)->Dump(std::cout);
    std::cout << std::endl;
  }
}


Node * NodeGenerator::m_get_node(const std::string & name)
{
  Node * node_ptr = 0;

  node_map_t::iterator p = m_nodes.find(name);

  if (p != m_nodes.end())
    node_ptr = p->second;

  return node_ptr;
}

bool NodeGenerator::m_add_link(const std::string & from_node_name, 
                               const std::string & to_node_name)
{
  Node * from_node_ptr = m_get_node(from_node_name);
  Node * to_node_ptr   = m_get_node(to_node_name);

  if (from_node_ptr && to_node_ptr) {
    from_node_ptr->AddOutputNode(*to_node_ptr);
    to_node_ptr->AddInputNode(*from_node_ptr);
    return true;
  }

  return false;
}

bool NodeGenerator::m_load_nodes(std::ifstream & ifs)
{
  std::string fline;

  if (std::getline(ifs, fline)) {
    std::istringstream iss(fline);

    std::string node_name;
    while (iss >> node_name)
      m_nodes[node_name] = new Node(node_name);
  }

  return (! m_nodes.empty());
}

bool NodeGenerator::m_load_links(std::ifstream & ifs)
{
  std::string fline;

  while (std::getline(ifs, fline)) {
    std::istringstream iss(fline);

    std::string from_node, to_node;
    if (iss >> from_node >> to_node)
      m_add_link(from_node, to_node);
  }

  return true;
}

Node::node_set_t NodeGenerator::GetNodes() const
{
  Node::node_set_t node_list;
  
  for (node_map_t::const_iterator p = m_nodes.begin();
      p != m_nodes.end(); ++p)
    node_list.insert(p->second);

  return node_list;
}


