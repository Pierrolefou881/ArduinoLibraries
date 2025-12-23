# Collection
Dynamic collections to be used on Arduino boards. All collections are generic types
and offer a specific hierarchy according to one's needs. Functionnalities are defined
through interfaces

## Interfaces

### BaseCollection
This is the base interface for most indexed collections. It defines
the following methods:

#### add()
Tries to add an item in the collection at
the provided index. If no index is provided, the insertion shall occur at
the beginning (first element).
- Parameter **item** to add.
- paramater **index** of the insertion (0 by default).
- Return type : bool. True if insertion successful, false otherwise.

One common failure of insertion comes from index being out of bounds.

#### remove()
Removes the first occurrence of the provided item from the 
collection. If the
item is not present, does nothing.
- Parameter **item** to remove.

#### remove_at()
Removes the item at the specified index. If index is out of 
bounds, does nothing.
- Parameter **index** of the removal. Must be within bounds.

#### clear()
Removes all elements from the collection.

#### at()
Accesses the element at the specified index.
**CAUTION**: the provided index must be within bounds, for Arduino 
does not offer exception support. If out of bounds,
undefined behavior shall occur.
- Parameter **index** of the item to access. Must be within bounds.
- Return type: T&, the object at the specified index.

#### contains()
Determines whether at least one occurrence of the provided item is
present within the collection.
- Parameter **item** to look for.
- Return type: bool, true if item is present at least once, false 
otherwise.

#### size
- Return type: uint16_t, the number of elements within the 
collection.

#### operator []
See **at()**.

#### operator += or -=
Shortcuts for **append()** and **remove()**

### BaseIterator
This is the base interface for all iterators. Iterators are useful 
for stacks and linked collections for instance and avoid accessing 
repetitively to indices, which can prove costly in terms of 
performance. BaseIterator defines the followng methods:

#### has_next()
Determines whether ther is a next element in the collection.
- Return type : bool

#### get()
Access the element currently iterated over.
- Return type : T&

#### next()
Move to the next element.

### OrderedCollection
Inherits from **BaseCollection**. Introduces a sorting order for 
all its elements. This sorting order is
expressed through an enumerated type. Because there is a sorting 
order, insertion index shall not be taken into
account when adding items.

#### SortingOrder
- ASCENDING
- DESCENDING

### UnorderedCollection
Inherits from **BaseCollection** and defines a collection without 
any sorting order. Adds therefore the possibility to
append an item.

#### append()
Adds the provided item at the end of the colection.
- Parameter **item** to add.

### BaseList
Defines lists, collections that can hold
multiple instances of the same object. As such, they also have the 
possibility to remove all instances of a given object.

#### remove_all()
Removes all the instances of the provided
item, if any.
- Parameter **item** to remove entirely from the list.

### UnorderedList
Merges the UnorderedCollection and BaseList interfaces.

### Iterable
Defines iterable collections, i.e. the possibility to create an
instance of **BaseIterator**

#### create_iterator()
Creates a single use iterator for the collection.
- Return type: U_ptr, unique pointer to the generated iterator.

## Implementations

### ArrayList
**UnorderedList** implementation that uses an ArrayContainer to 
manage its memory. **ArrayList** is best used when regular access
to indexed data items is needed.

### LinkedList
**UnorderedList** implementation that uses dynamic memory 
allocation to manage its size. **LinkedList** is better suited when
memory occupation is at a premium and access through index can be
sacrificed. **LinkedList** also implements **Iterable** and can
therefore generate **LinkedListIterator**s

### LinkedSet
**UnorderedCollection** implementation that uses dynamic memory
allocation to manage its size. As a set, **LinkedSet** does not
allow duplicates. It also implements **Iterable** an can
therefore generate **LinkedSetIterator**s.
**LinkedSet**s are useful for collections that need only one
occurrence per item and require strict memory allocation policies.
As a linked collection, acces through inex is costs more in terms
of computation times than array based collections.