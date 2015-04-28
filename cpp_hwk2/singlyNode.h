/**
    Templated header file for implementation of a node that stores 2 entries and a pointer to the next node.
*/

#ifndef SINGLY_NODE_H
#define SINGLY_NODE_H

template <class keyT, class itemT>
class singlyNode
{
private:
    keyT _key;
    itemT _item;
    singlyNode* _fwd;

public:
    singlyNode(): _fwd(nullptr) {};
    singlyNode(keyT key, itemT item): _key(key), _item(item),_fwd(nullptr) {};
    ~singlyNode() {};
    void setItem(const itemT& item)
    {
        _item = item;
    }
    void setKey(const keyT& key)
    {
        _key=key;
    }
    void setFwd(singlyNode<keyT, itemT>* nextNode)
    {
        _fwd = nextNode;
    }
    itemT getItem() const
    {
        return _item;
    }
    keyT getKey() const
    {
        return _key;
    }
    singlyNode<keyT,itemT>* getFwd() const
    {
        return _fwd;
    }
    bool operator==(const singlyNode<keyT, itemT>& rhs) const
    {
        return (_key == rhs.getKey());
    }

    bool operator>(const singlyNode<keyT, itemT>& rhs) const
    {
        return (_key > rhs.getKey());
    }
};
#endif // SINGLY_NODE_H
