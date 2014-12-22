#ifndef NODE_HPP
#define NODE_HPP

#include <iosfwd>
#include <string>
#include <set>
#include <bitset>

// CHANGE FROM WS02
class Node
{
  public:

    enum eFlags
    {
      PROCESSED,
      VISITED,

      NUM_FLAGS
    };

    typedef std::set<Node *>node_set_t;

    Node(const std::string & name);
    virtual ~Node();

    const std::string & GetName() const;
    const node_set_t & GetInputNodes() const;
    const node_set_t & GetOutputNodes() const;

    void AddInputNode(Node & input_node);
    void AddOutputNode(Node & output_node);

    void SetFlag(const eFlags flag);
    void ClearFlag(const eFlags flag);
    bool HasFlag(const eFlags flag) const;
    
    void Dump(std::ostream & oss) const;

  private:
    std::string m_name;

    node_set_t m_input_nodes;
    node_set_t m_output_nodes;

    std::bitset<NUM_FLAGS> m_flags;

};


#endif // NODE_HPP
