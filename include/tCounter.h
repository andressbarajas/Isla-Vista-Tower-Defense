
#ifndef _NUMCOUNTER_H_
#define _NUMCOUNTER_H_
/**
* Template Class: Counter
* Purpose: Used to count, will be inherited/used by other objects
* Will be used to keep track of money or enemy life bars
*/
template <class T>
class Counter {
public:
    /**
    * Constructor
    * Pre-conditions: Nothing.
    * Post-conditions: m_count is set to 0.
    */
    Counter();
    ~Counter();
    /**
    * Function: GetCount
    * function getter for Count
    * Pre-conditions: nothing
    * Post-conditions: m_count returned.
    */
    T GetCount();
    /**
    * Function: SetCount
    * function setter for Count
    * Pre-conditions: none
    * Post-conditions: m_count was set to count
    */
    void SetCount(T count);
    /**
    * Function: IncreaseCount
    * function increases Count by an amount
    * Pre-conditions: none
    * Post-conditions: amount was added to m_count
    */
    void IncreaseCount(T amount);
    /**
    * Function: DecreaseCount
    * function decreases Count by an amount
    * Pre-conditions: none
    * Post-conditions: amount was subtraced from m_count and m_count is not negative
    */
    void DecreaseCount(T amount);
private:
    T m_count;
};

template <class T>
Counter<T>::Counter() {
    m_count = 0;
}

template <class T>
Counter<T>::~Counter() {}

template <class T>
T Counter<T>::GetCount() {
    return m_count;
}

template <class T>
void Counter<T>::SetCount(T count) {
    m_count = count;
}

template <class T>
void Counter<T>::IncreaseCount(T count) {
    m_count += count;
}

template <class T>
void Counter<T>:: DecreaseCount(T count) {
    if(count > m_count || m_count == 0) {
        m_count = 0;
        return;
    } else {
       m_count -= count;
    }
}


#endif
