namespace mafCore
{

  ////////////////////////////////////////////////////////////////////////////////
  // body class implements the aliasing behaviour

  template<typename O, typename N>
  class mafSafeIterator_body
  {
  private:
    const O* m_owner;
    N* m_node;
    unsigned m_count;

  public:

    mafSafeIterator_body(const O* owner, N* node) throw() :
      m_owner(owner), m_node(node), m_count(1)
      {
//         std::cerr << "constructing " 
//                   << std::hex << ((unsigned long)this) 
//                   << " => " << ((unsigned long)m_owner) << ":" << ((unsigned long)m_node)
//                   << ":" << std::dec << m_count << std::endl;
      }

    ~mafSafeIterator_body(void) throw()
      {
//         std::cerr << "destroying " 
//                   << std::hex << ((unsigned long)this) 
//                   << " => " << ((unsigned long)m_owner) << ":" << ((unsigned long)m_node)
//                   << ":" << std::dec << m_count << std::endl;
        m_owner = 0;
        m_node = 0;
      }

    unsigned count(void) const
      {
        return m_count;
      }

    void increment(void)
      {
        ++m_count;
//         std::cerr << "incremented " 
//                   << std::hex << ((unsigned long)this) 
//                   << " => " << ((unsigned long)m_owner) << ":" << ((unsigned long)m_node)
//                   << ":" << std::dec << m_count << std::endl;
      }

    bool decrement(void)
      {
        --m_count;
//         std::cerr << "decremented " 
//                   << std::hex << ((unsigned long)this) 
//                   << " => " << ((unsigned long)m_owner) << ":" << ((unsigned long)m_node)
//                   << ":" << std::dec << m_count << std::endl;
        return m_count == 0;
      }

    N* node(void) const throw()
      {
        return m_node;
      }

    const O* owner(void) const throw()
      {
        return m_owner;
      }

    void change_owner(const O* owner)
      {
        m_owner = owner;
      }

    bool equal(const mafSafeIterator_body<O,N>* right) const throw()
      {
//        return m_node == right->m_node;
        return compare(right) == 0;
      }

    int compare(const mafSafeIterator_body<O,N>* right) const throw()
      {
        return ((long)m_node) - ((long)right->m_node);
      }

    bool null(void) const throw()
      {
        return m_owner == 0;
      }

    bool end(void) const throw()
      {
        return m_owner != 0 && m_node == 0;
      }

    bool valid(void) const throw()
      {
        return m_owner != 0 && m_node != 0;
      }

    void set_end(void) throw()
      {
        m_node = 0;
      }

    void set_null(void) throw()
      {
        m_owner = 0;
        m_node = 0;
      }

    void assert_valid(void) const throw(mafNullDereference,mafEndDereference)
      {
        if (null())
          throw mafNullDereference("mafCore::mafSafeIterator");
        if (end())
          throw mafEndDereference("mafCore::mafSafeIterator");
      }

    void assert_non_null(void) const throw(mafNullDereference)
      {
        if (null())
          throw mafNullDereference("mafCore::mafSafeIterator");
      }

    void assert_owner(const O* owner) const throw(mafWrongObject)
      {
        if (owner != m_owner)
          throw mafWrongObject("mafCore::mafSafeIterator");
      }
  };


  ////////////////////////////////////////////////////////////////////////////////
  // Master Iterator
  ////////////////////////////////////////////////////////////////////////////////

  // construct a valid iterator
  template<typename O, typename N>
  master_iterator<O,N>::master_iterator(const O* owner, N* node) throw() :
    m_body(new mafSafeIterator_body<O,N>(owner,node))
  {
  }

  // destructor - disconnect all iterators from the node
  // this usually happens when the node is deleted and must invalidate all aliases
  template<typename O, typename N>
  master_iterator<O,N>::~master_iterator(void) throw()
  {
    m_body->set_end();
    if(m_body->decrement())
    {
      delete m_body;
      m_body = 0;
    }
  }

  // dereference
  template<typename O, typename N>
  N* master_iterator<O,N>::node(void) const throw()
  {
    return m_body->node();
  }

  template<typename O, typename N>
  const O* master_iterator<O,N>::owner(void) const throw()
  {
    return m_body->owner();
  }

  // when you move a node from one owner to another, call this on the node's iterator
  // this effectively moves all iterators to the node so that they are owned by the new owner too
  template<typename O, typename N>
  void master_iterator<O,N>::change_owner(const O* owner) throw()
  {
    m_body->change_owner(owner);
  }

  ////////////////////////////////////////////////////////////////////////////////
  // Safe Iterator
  ////////////////////////////////////////////////////////////////////////////////

  // construct a null iterator
  // later assignment of a valid iterator to this is done by using step
  template<typename O, typename N>
  mafSafeIterator<O,N>::mafSafeIterator(void) throw() :
    m_body(new mafSafeIterator_body<O,N>(0,0))
  {
  }

  // construct a valid iterator by aliasing from the owner node's master iterator
  template<typename O, typename N>
  mafSafeIterator<O,N>::mafSafeIterator(const master_iterator<O,N>& r) throw() :
    m_body(0)
  {
    m_body = r.m_body;
    m_body->increment();
  }

  // construct a valid iterator by aliasing from the owner node's master iterator
  template<typename O, typename N>
  mafSafeIterator<O,N>::mafSafeIterator(const mafSafeIterator<O,N>& r) throw() :
    m_body(0)
  {
    m_body = r.m_body;
    m_body->increment();
  }

  // assignment implements dealiasing followed by aliasing
  template<typename O, typename N>
  mafSafeIterator<O,N>& mafSafeIterator<O,N>::operator=(const mafSafeIterator<O,N>& r) throw()
  {
    if (m_body != r.m_body)
    {
      if (m_body->decrement())
        delete m_body;
      m_body = r.m_body;
      m_body->increment();
    }
    return *this;
  }

  // destructor - implements dealiasing
  template<typename O, typename N>
  mafSafeIterator<O,N>::~mafSafeIterator(void) throw()
  {
    if(m_body->decrement())
    {
      delete m_body;
      m_body = 0;
    }
  }


  // increment/decrement operation
  // implements dealiasing followed by aliasing
  template<typename O, typename N>
  void mafSafeIterator<O,N>::set(const master_iterator<O,N>& r) throw()
  {
    if (m_body != r.m_body)
    {
      if (m_body->decrement())
        delete m_body;
      m_body = r.m_body;
      m_body->increment();
    }
  }

  // dereference
  template<typename O, typename N>
  N* mafSafeIterator<O,N>::node(void) const throw()
  {
    return m_body->node();
  }

  template<typename O, typename N>
  const O* mafSafeIterator<O,N>::owner(void) const throw()
  {
    return m_body->owner();
  }

  // change to a null iterator - i.e. one that doees not belong to any object
  // this does not affect any other iterators pointing to the same node
  template<typename O, typename N>
  void mafSafeIterator<O,N>::set_null(void) throw()
  {
    if (m_body->count() == 1)
    {
      // no aliases, so just make this null
      m_body->set_null();
    }
    else
    {
      // create a new body which is null so as not to affect any other aliases
      m_body->decrement();
      m_body = new mafSafeIterator_body<O,N>(0,0);
    }
  }

  ////////////////////////////////////////////////////////////////////////////////
  // operations for clients that do not have a master end iterator
  // alternatively, have a master end iterator as part of the container
  // and call constructor(master_end) or step(master_end)

  // construct an end iterator
  template<typename O, typename N>
  mafSafeIterator<O,N>::mafSafeIterator(const O* owner) throw() :
    m_body(new mafSafeIterator_body<O,N>(owner,0))
  {
  }

  // change to an end iterator - e.g. as a result of incrementing off the end
  template<typename O, typename N>
  void mafSafeIterator<O,N>::set_end(void) throw()
  {
    if (m_body->count() == 1)
    {
      // no aliases, so just make this an end iterator
      m_body->set_end();
    }
    else
    {
      // create a new body which is null so as not to affect any other aliases
      m_body->decrement();
      m_body = new mafSafeIterator_body<O,N>(owner(),0);
    }
  }

  ////////////////////////////////////////////////////////////////////////////////
  // tests

  // comparison
  template<typename O, typename N>
  bool mafSafeIterator<O,N>::equal(const mafSafeIterator<O,N>& right) const throw()
  {
    return compare(right) == 0;
  }

  template<typename O, typename N>
  int mafSafeIterator<O,N>::compare(const mafSafeIterator<O,N>& right) const throw()
  {
    if (m_body == right.m_body) return 0;
    return m_body->compare(right.m_body);
  }

  // a null iterator is one that has not been initialised with a value yet
  template<typename O, typename N>
  bool mafSafeIterator<O,N>::null(void) const throw()
  {
    return m_body->null();
  }

  // an end iterator is one that points to the end element of the list of nodes
  template<typename O, typename N>
  bool mafSafeIterator<O,N>::end(void) const throw()
  {
    return m_body->end();
  }

  // a valid iterator is one that can be dereferenced
  template<typename O, typename N>
  bool mafSafeIterator<O,N>::valid(void) const throw()
  {
    return m_body->valid();
  }

  // check the rules for a valid iterator that can be dereferenced
  template<typename O, typename N>
  void mafSafeIterator<O,N>::assert_valid(void) const throw(mafNullDereference,mafEndDereference)
  {
    m_body->assert_valid();
  }

  template<typename O, typename N>
  void mafSafeIterator<O,N>::assert_valid(const O* owner) const throw(mafWrongObject,mafNullDereference,mafEndDereference)
  {
    m_body->assert_valid();
    m_body->assert_owner(owner);
  }

  template<typename O, typename N>
  void mafSafeIterator<O,N>::assert_non_null(void) const throw(mafNullDereference)
  {
    m_body->assert_non_null();
  }

  template<typename O, typename N>
  void mafSafeIterator<O,N>::assert_owner(const O* owner) const throw(mafWrongObject)
  {
    m_body->assert_owner(owner);
  }

} // end namespace mafCore
