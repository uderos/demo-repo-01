/////////////////////////////////////////////////////////////////////////
// FILE HEADER
// CIRCULAR DETECTOR
// #DATE#:Thu Mar 12 09:57:05 EDT 2015
/////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <fstream>
#include <sstream>
#include "CircularDetector.hpp"

// #define DBGOUT std::cout
#define DBGOUT if(0)std::cout


CircularDetector::CircularDetector(const Node::node_set_t & nodes) : 
  m_nodes(nodes)
{
  ;
}

CircularDetector::~CircularDetector()
{
  ;
}

bool CircularDetector::HasCircularDependency()
{
  m_initialize_nodes();

  node_queue_t readyToProcess = m_get_root_nodes();
  Node::node_set_t visitedSet;

  while (! readyToProcess.empty()) {

    Node & node = *(readyToProcess.front());
    DBGOUT << "\nLooking at node " << node.GetName() 
           << " rqs=" << readyToProcess.size()
           << " vs=" << visitedSet.size()
           << std::endl;
  
    const Node::node_set_t & output_nodes = node.GetOutputNodes();
    for (Node::node_set_t::const_iterator q = output_nodes.begin();
          q != output_nodes.end(); ++q) {

      if (m_all_inputs_processed(*(*q))) 
        m_set_to_processed(*(*q), readyToProcess, visitedSet);
      else 
        m_set_to_visited(*(*q), readyToProcess, visitedSet);
    }
    
    readyToProcess.pop();
  }

  DBGOUT << "Out of loop"
         << " rqs=" << readyToProcess.size()
         << " vs=" << visitedSet.size()
         << std::endl;

  return (! visitedSet.empty());
}

void CircularDetector::m_initialize_nodes()
{
  for (Node::node_set_t::const_iterator p = m_nodes.begin();
        p != m_nodes.end(); ++p) {

    (*p)->ClearFlag(Node::NUM_FLAGS);
  }
}


CircularDetector::node_queue_t CircularDetector::m_get_root_nodes()
{
  node_queue_t root_nodes;

  for (Node::node_set_t::const_iterator p = m_nodes.begin();
        p != m_nodes.end(); ++p) 
  {
    if ((*p)->GetInputNodes().size() == 0)
    {
    
      (*p)->SetFlag(Node::PROCESSED);
      root_nodes.push(*p);
    }
  }

  return root_nodes;
}

bool Node::m_all_inputs_processed(const Node & node) const;
{
  const Node::node_set_t & input_nodes = node.GetInputNodes();

  for (Node::node_set_t::const_iterator p = input_nodes.begin();
        p != input_nodes.end(); ++p) 
  {
      if ( ! (*p)->HasFlag(Node::PROCESSED)) 
      {
        DBGOUT << "Node " << node.GetName()
               << " - input node " << (*p)->GetName()
               << " is NOT processed\n";

        return false;
      }
  }

  return true;
}

void CircularDetector::m_set_to_processed(Node & node, 
                                          node_queue_t & readyToProcess,
                                          Node::node_set_t & visitedSet)
{
  // Add to the ready to process queue and flag as 'processed'
  if (! node.HasFlag(Node::PROCESSED)) 
  {
    DBGOUT << "Adding " << node.GetName() << " to readyToProcess queue" << std::endl;
    node.SetFlag(Node::PROCESSED);
    readyToProcess.push(&node);
  }

  // Remove from the visited queue
  if (visitedSet.find(&node) != visitedSet.end()) 
  {
    DBGOUT << "Removing " << node.GetName() << " from visited queue" << std::endl;
    node.ClearFlag(Node::VISITED);
    visitedSet.erase(&node);
  }
}

void CircularDetector::m_set_to_visited(Node & node,
                            node_queue_t & readyToProcess,
                            Node::node_set_t & visitedSet)
{
  DBGOUT << "Adding " << node.GetName() << " to visited queue" << std::endl;
  node.SetFlag(Node::VISITED);
  visitedSet.insert(&node);
}

// END OF FILE ///////////////////////////////////////////////////////////////
