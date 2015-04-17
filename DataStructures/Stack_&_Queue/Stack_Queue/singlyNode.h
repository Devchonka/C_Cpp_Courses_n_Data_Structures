/**
    Template class for a singly linking node.
*/
#ifndef SINGLYNODE_H
#define SINGLYNODE_H

template<class T>
class singlyNode
{
private:
    T _data;
    singlyNode<T>* _fwd;
public:
    singlyNode<T>(): _fwd(nullptr){};
    singlyNode<T>(T data): _data(data) {};
    ~singlyNode(){};

    T getNodeData() const;
    singlyNode<T>* getNodeF() const;
    void setNodeData(const T&);
    void setNodeF(singlyNode<T>*);
};

template <class T>
T singlyNode<T>::getNodeData() const
{
    return _data;
}


template <class T>
singlyNode<T>* singlyNode<T>::getNodeF() const
{
    return _fwd;
}

template<class T>
void singlyNode<T>::setNodeData(const T& data)
{
    _data = data;
}

template<class T>
void singlyNode<T>::setNodeF(singlyNode<T>* nodeF)
{
    _fwd = nodeF;
}

#endif // SINGLYNODE_H

