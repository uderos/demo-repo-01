/////////////////////////////////////////////////////////////////////////
// FILE HEADER
// #DATE#:Thu Mar 12 09:56:10 EDT 2015
/////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include "Node.hpp"


Node::Node(const std::string & name) : m_name(name)
{
  ;
}

Node::~Node()
{
  ;
}

const std::string & Node::GetName() const
{
  return m_name;
}

const Node::node_set_t & Node::GetInputNodes() const
{
  return m_input_nodes;
}

const Node::node_set_t & Node::GetOutputNodes() const
{
  return m_output_nodes;
}


void Node::AddInputNode(Node & input_node)
{
  m_input_nodes.insert(&input_node);
}

void Node::AddOutputNode(Node & output_node)
{
  m_output_nodes.insert(&output_node);
}

void Node::Dump(std::ostream & oss) const
{
  const std::string none("(none)");
  oss << m_name;

  oss << " IN: ";
  if (m_input_nodes.empty()) {
    oss << none
  } else {
    for (Node::node_set_t::const_iterator p = m_input_nodes.begin();
          p != m_input_nodes.end(); ++p)
      oss << (*p)->GetName() << " ";
  }

  oss << " OUT: ";
  if (m_output_nodes.empty()) {
    oss << none
  } else {
    for (Node::node_set_t::const_iterator p = m_output_nodes.begin();
          p != m_output_nodes.end(); ++p)
      oss << (*p)->GetName() << " ";
  }
}

void Node::SetFlag(const eFlags flag)
{
  if (flag < NUM_FLAGS)
    m_flags[flag] = true;
}

void Node::ClearFlag(const eFlags flag)
{
  if (flag == NUM_FLAGS) {
    for (int i = 0; i < NUM_FLAGS; ++i)
    	m_flags[i] = false;
  } else {
    	m_flags[flag] = false;
  }
}

bool Node::HasFlag(const eFlags flag) const
{
	return m_flags.test(flag);
}

