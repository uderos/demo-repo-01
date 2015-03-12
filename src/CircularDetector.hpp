/////////////////////////////////////////////////////////////////////////
// FILE HEADER
// #DATE#:Thu Mar 12 09:56:10 EDT 2015
/////////////////////////////////////////////////////////////////////////
#ifndef CIRCULAR_DETECTOR_HPP
#define CIRCULAR_DETECTOR_HPP

#include <string>
#include <vector>
#include <iosfwd>
#include <map>
#include <queue>
#include "Node.hpp"

class CircularDetector
{
  public:
    CircularDetector(const Node::node_set_t & nodes);
    virtual ~CircularDetector();

    bool HasCircularDependency();

  private:

    typedef std::queue<Node *> node_queue_t;
    
    Node::node_set_t m_nodes;

    void m_initialize_nodes();

    node_queue_t m_get_root_nodes();

    bool m_all_inputs_processed(const Node & node) const;

    void m_set_to_processed(Node & node, 
                            node_queue_t & readyToProcess,
                            Node::node_set_t & visitedSet);

    void m_set_to_visited(Node & node,
                          node_queue_t & readyToProcess,
                          Node::node_set_t & visitedSet);
};



#endif // CIRCULAR_DETECTOR_HPP
