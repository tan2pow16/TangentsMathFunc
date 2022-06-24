/*
 * Tangent's Math Function V1.02
 *  Copyright (c) 2018-2022, tangent65536. All rights reserved.
 *
 * The code may be found on my GitHub repository:
 *  https://github.com/tan2pow16/TangentsMathFunc
 */

#ifndef __TANGENT_MATH_FUNC__LINKED_NODE
#define __TANGENT_MATH_FUNC__LINKED_NODE 65536

template <typename T>
class Node
{
    private:
        /*
         * Value, or the content of this node. Late-binding compatible.
         */
        T* value;
        
        /*
         * Whether the value should be deleted when being replaced/removed.
         */
        bool del;
        
        /*
         * Next node.
         */
        Node<T>* next;
        
        /*
         * :P (Banned constructor.)
         */
        Node(const Node<T>&);
        
        /*
         * Nah. (Banned operator.)
         */
        void operator=(const Node<T>&);
        
    public:
        /*
         * Creates a node with its content only.
         *
         * Param(s):
         *    _val    -> Content of the new node which WILL NOT be copied.
         */
        Node(T* _val, bool _del);
        
        /*
         * Creates a node with both its content and the next node it links to.
         *
         * Param(s):
         *    _val     -> Content of the new node which WILL NOT be copied.
         *    _next    -> The next node this node should link to.
         */
        Node(T* _val, Node<T>* _next, bool _del);
        
        ~Node();
        
        /*
         * Get the content of this node as a pointer.
         *
         * Return:
         *    _ret    -> The content of this node as a pointer.
         */
        T* getValue() const;
        
        /*
         * Replace the content with a new one.
         *
         * Param(s):
         *    newValue    -> New content of the new node which WILL NOT be copied.
         *    del         -> Whether the old content should be deleted.
         */
        void setValue(T* newValue, bool del);
        
        /*
         * Get the next node this node links to.
         *
         * Return:
         *    _ret    -> The next node as a pointer.
         */
        Node<T>* getNext() const;
        
        /*
         * Set the next node of this node.
         *
         * Param(s):
         *    _next    -> Next node.
         */
        void setNext(Node<T>* _next);
};

#endif
