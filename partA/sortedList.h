#include<iostream>
#include "examDetails.h"

#ifndef SORTEDLIST_H
#define SORTEDLIST_H
#include <stdexcept>
namespace mtm
{
    template<class T>
    class SortedList
    {
    private:
        class Node
        {
        private:
            const T data;
            SortedList<T>::Node *next= nullptr;

            friend class SortedList<T>;

            explicit Node(const T &data = NULL);

            ~Node();

            Node(const Node &node);

            Node &operator=(const Node &node);

            T &getData() const;

            void setData(const T &dataValue);

            Node *getNext();

//        void insertNode(SortedList& list);
            void setNext(Node *next);

            bool operator==(const Node &node) const;

            const T &operator*() const;
        };

        int size = 0;
        SortedList<T>::Node *head = nullptr;
        SortedList<T>::Node *tail = nullptr;
    public:
        class const_iterator
        {
        private:
            SortedList<T>::Node *element;// presents An element to which the iterator points to.
            friend class SortedList<T>;

           const  const_iterator operator+(int index) const;

            const_iterator(SortedList<T>::Node *element = nullptr);

        public:
            ~const_iterator()=default;

            const_iterator(const const_iterator &constIterator) = default;

            const_iterator &operator=(const const_iterator &constIterator) = default;

            const_iterator &operator++();
            const const_iterator operator++(int num);


            bool operator==(const const_iterator constIterator) const;

            const T &operator*() const;


            bool operator!=(const const_iterator &constIterator) const;

            Node *getElement() const;

            void setElement(Node *element);

        };

        explicit SortedList() = default;

        ~SortedList();

        SortedList(const SortedList &list);

        SortedList &operator=(const SortedList &list);

        void insert(const T &data);

        void remove(const SortedList<T>::const_iterator const_iterator);

        int length() const;

        SortedList<T>::const_iterator begin() const;

        SortedList<T>::const_iterator end() const;

        template<class condition>
        SortedList<T> filter(condition filter);//todo
        template<class operation>
        SortedList<T> apply(operation func);//todo
    };

    /*function - const T &SortedList<T>::Node::operator*() const
    *overload * : return the data of the element.
    */
    template<class T>
    const T &SortedList<T>::Node::operator*() const
    {
        return data;
    }

    /*function - typename SortedList<T>::Node &SortedList<T>::Node::operator=(const SortedList<T>::Node &node)
    *overloading = : copy node and his data to new node.
    */
    template<class T>
    typename SortedList<T>::Node &SortedList<T>::Node::operator=(const SortedList<T>::Node &node)
    {
        if(this==&node)
        {
            return *this;
        }
        T data_node=node.data;
        delete &data;
        data=data_node;
        return *this;
    }

    /*function - SortedList<T>::Node::~Node()
    *distructor for Node.
    */
    template<class T>
    SortedList<T>::Node::~Node()
    {
        delete next;
    }

    /*function - SortedList<T>::Node::Node(const T &data):data(data)
    * a copy constructor for class Node. copy data , set next to nullptr. 
    */
    template<class T>
    SortedList<T>::Node::Node(const T &data):data(data)
    {
        this->next = nullptr;
    }

    /*
    */
    template<class T>
    SortedList<T>::Node::Node(const SortedList<T>::Node &node): Node(node.data)
    {}

    /*function - T &SortedList<T>::Node::getData() const
    *function that return the data the Node has.
    *@return data- type of T.
    */
    template<class T>
    T &SortedList<T>::Node::getData() const
    {
        return data;
    }

    /*function - void SortedList<T>::Node::setData(const T &dataValue)
    *function to enter the data value to our Node. the type of the value is T.
    */
    template<class T>
    void SortedList<T>::Node::setData(const T &dataValue)
    {
        data = dataValue;
    }


    /*typename SortedList<T>::Node *SortedList<T>::Node::getNext()
    *function to return the next node.
    */
    template<class T>
    typename SortedList<T>::Node *SortedList<T>::Node::getNext()
    {
        return next;
    }

    /*function - void SortedList<T>::Node::setNext(SortedList<T>::Node *nextNode)
    *function to set a nextNode , connect a current node with the next node.
    @param - nextNode, the node to add.
    */
    template<class T>
    void SortedList<T>::Node::setNext(SortedList<T>::Node *nextNode)
    {
        next = nextNode;
    }

    /*function - bool SortedList<T>::Node::operator==(const SortedList<T>::Node &node) const
    *@param - node.
    *@return true if the left node is equal to the right node(parameter).
    *@return false - the nodes are not equal.
    */
    template<class T>
    bool SortedList<T>::Node::operator==(const SortedList<T>::Node &node) const
    {
        return (data == node.data);
    }


    /*~SortedList()- distructor to list.
    *delete the head.
    */
    template<class T>
    SortedList<T>::~SortedList()
    {
        delete head;
    }

    /*function : SortedList<T>::SortedList(const SortedList<T> &list)
    *CopyConstrctor, set a new list with the element of the parameter.
    */
    template<class T>
    SortedList<T>::SortedList(const SortedList<T> &list)
    {
        for (auto item = list.begin(); item != list.end(); ++item)
        {
            insert(*(item));
        }
    }

    /*function : SortedList<T> &SortedList<T>::operator=(const SortedList<T> &list)
    *Placement- copy a list to a new list.
    *@param const SortedList<T> &list - the list we want to copy the elements.
    @return the copied list.
    */
    template<class T>
    SortedList<T> &SortedList<T>::operator=(const SortedList<T> &list)
    {
        if (this == &list)
        {
            return *this;
        }
        delete this->head;
        this->head = nullptr;
        this->size = 0;
        for (auto item = list.begin(); item != list.end(); ++item)
        {
            this->insert(*item);
        }
        return *this;
    }


    /*function: void SortedList<T>::insert(const T& data) 
    *insert a new data , and keep it sorted.
    @param const T& data - the const data to insert
    @return void.
    */
    template<class T>
    void SortedList<T>::insert(const T& data)  {
        
            SortedList<T>::Node* to_insert=new SortedList<T>::Node(data);
        if(this->length()==0)
        {
            head=to_insert;
            to_insert->setNext(tail);
            size++;
            return;
        }
        if(data<**head)
        {
            to_insert->setNext(head);
            head=to_insert;
            size++;
            return;
        }

            SortedList<T>::const_iterator previous=begin();
            for (typename SortedList<T>::const_iterator item = begin(); item != end(); ++item) {
            if(data < (*(item)))
            {
                    to_insert->setNext(item.element);
                    previous.element->setNext(to_insert);
                    size++;
                    return;
            }
            previous=item;
    }
    //if we're here.means data is bigger compared to everyone else.
    // now we need to make the new tail be to_insert
    //lucky for us,we have previous..which will be now tail.
    previous.element->setNext(to_insert);
    to_insert->setNext(tail);
    size++;
    return;
}


    /* function operator+ - move the iterator to our requested index.
    @param int index- the index to set the iteartor
    @return the iterot that points to the requested index.
    */
    template<class T>
    const typename SortedList<T>::const_iterator  SortedList<T>::const_iterator::operator+(int index)  const
    {
        auto iterator=*this;
        for(int i=0;i<index;i++)
        {
            ++iterator;
        }
        return iterator;
    }

    /*setElement - add an element to the iterator.
    */
    template<class T>
    void SortedList<T>::const_iterator::setElement(SortedList::Node *element)
    {
        const_iterator::element = element;
    }

    /* function length()
    @return the length of the list.
    */
    template<class T>
    int SortedList<T>::length() const {

        return this->size;
    }


    /*function begin()
    @return a const iterator that points to the head of the list.
    */
    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::begin() const {
        return const_iterator(this->head);
    }


    /* function end()
    @return const_iterator that points to the end of the list.
    */
    template<class T>
    typename SortedList<T>::const_iterator SortedList<T>::end() const {
        return const_iterator(this->tail);
    }

    /* function const_iterator(SortedList<T>::Node *other) - copyConstructor.
    @param *other- an other iterator that point to elemnt.
    */
    template<class T>
    SortedList<T>::const_iterator ::const_iterator(SortedList<T>::Node *other)  {
        this->element=other;
    }

//    template<class T>
//    SortedList<T>::const_iterator:: ~const_iterator() {
//        delete element;
//    }

    /* operator== - check if 2 iteartors are equals.
    @param itertor - the iterator to compare with.
    @return true- iterators equal.
    @return false- iterators not equal.
    */
    template<class T>
    bool SortedList<T>::const_iterator::operator==(const SortedList<T>::const_iterator constIterator) const {
        return (element == (constIterator.element));
    }

    /* operator++ - move the iterator to the next element.
    @throw out_of_range - in case that the iterator reached the end.
    @return - the iterator. 
    */
    template<class T>
     typename SortedList<T>::const_iterator& SortedList<T>::const_iterator::operator++() {
        if(this->element == nullptr)
        {
            throw std::out_of_range("out of bounds iterator!");
        }
        this->element=this->element->getNext();
        return *this;
    }

    /* function -  T& SortedList<T>::const_iterator:: operator*
    *   return a const reference to the element that the iterator point to.
    */
    template<class T>
    const T& SortedList<T>::const_iterator:: operator*() const {
        return **element;
    }


    template<class T>
    bool SortedList<T>::const_iterator::operator!=(const SortedList<T>::const_iterator &constIterator) const {  //todo
        return (!(element==constIterator.element));
    }

    /* function :const_iterator SortedList<T>::const_iterator::operator++
    *  move the iterator to the next element.
    *@return iterator. 
    */
    template<class T>
   const typename SortedList<T>::const_iterator SortedList<T>::const_iterator::operator++(int num) {
        SortedList<T>::const_iterator current(*this);
        ++*this;
        return current;
    }


    /*function filter  - function to filter our current list and return the new list after filtered.
    @param condition - the boolean function with the condition.
    @return - the new list adter filters the elements.
    */
    template<class T>
    template<class condition>
    SortedList<T> SortedList<T>::filter(condition filter) {
        SortedList<T> new_list;
        for (typename SortedList<T>::const_iterator item = begin(); item != end(); ++item) {
            if (filter(*item) == true) {
                new_list.insert(*item);
            }
        }
        //because insert already  adds by sorting order,no need to sort again.
        return new_list;
    }

    /*function apply - Activate a function that change the elements, and sort them with the new element.
    @param operation func- the func with the condition and the changes.
    @return a new order list.
    */
    template<class T>
    template<class operation>
    SortedList<T> SortedList<T>::apply(operation func) {
        SortedList<T> appliedList;//create newlist
        for (auto item = begin(); item != end(); ++item) {
            appliedList.insert( func(*item));//insert all on new list,making it sorted

        }
        return appliedList;//return sortednewlist with applied items.
    }



    /* void remove- remove element from the List.
    @param const_iterator - a iterator the pointer to the element we want to remove.
    */
    template<class T>
    void SortedList<T>::remove(const SortedList<T>::const_iterator const_iterator)
    {
              if(this->length()==0)
              {
                  return;
              }
              if(const_iterator==nullptr)
              {
                  return ;
              }
              if(const_iterator==this->begin())
              {
                  //remove head
                  SortedList<T>::Node* remove=this->head;
                  this->head=head->next;
                  remove->setNext(nullptr);
                  delete remove;
                  this->size--;
                  return;
              }
              if((const_iterator+1)==end())
              {
                  //we're on last Node
                   SortedList<T>::Node* remove=(this->begin()+(this->length())).element;
                   this->tail=(this->begin()+(this->length()-1)).element;
                   delete remove;
                   this->size--;
                   return;
              }
              //if not head or tail..we will look up for him..
              SortedList<T>::const_iterator previous=this->begin();
              for(auto item =this->begin(); item != this->end(); ++item) {
                  if(item==const_iterator)
                  {
                      SortedList<T>::Node* to_remove=const_iterator.element;
                      previous.element->setNext(const_iterator.element->getNext());
                      to_remove->setNext(nullptr);
                      delete to_remove;
                   size--;
                   return;
                  }
                  previous=item;
              }

    }


}
#endif
