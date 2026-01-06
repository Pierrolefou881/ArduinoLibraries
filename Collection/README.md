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

### ProcessingCollection
Unordered collections used as waiting list or for stocking commands and
data to be treated. Base abstraction for stacks and queues. **ProcessingCollection**
implements **Iterable** to create **ProcessingCollectionIterator** instances.

#### push()
Adds the provided item to the collection.
- Parameter **item** to add.

#### pop()
Removes the head item from the collection. On stacks, that would be the
last inserted element, the first on queues.
- Return type: S_ptr<T>.

#### peek()
Access the head element without removing it. On stack, the last inserted
element, the first on queues.
- Return type: T&.

#### clear()
Removes all elements from the collection.

#### is_empty()
- Return type: bool, true if the collection has no elements, false otherwise.

#### size()
- Retunr type: unsigned int, the number of elements in the collection.

### Map
Defines collections of items indexed by a unique key. Such
an association is contained in a **KeyValue**, alhtough those 
objects are not *stricto sensu* required in the algorithms. Maps
should tolerate duplicates as far as values are concerned.

#### add()
Adds a specfied item with the specified key. Should fail if key
already in use.
- Parameter **key** must be unique
- Parameter **value** can be anything defined by the template type.
- Return value: bool, true if insertion successful, false otherwise.

#### remove()
Removes an item out of the Map. If the item is not found, does nothing.
- Parameter **key** of the item to remove.

#### remove_all()
Removes all the instances of the provided value and frees all
the keys associated with them. Does nothing if the item is not
present.
-Parameter **item** value to wipe off the Map.

#### try_get()
Tries to fetch an item by its key.
- Parameter **key** of the item to find.
- Parameter **out_value** the item, if found. Out parameter.
- Return type: bool, true if item found, false otherwise.

#### Size()
- Return type: unsigned integer, the number of KeyValues in the Map.

#### contains_key()
Checks whether a specific key is in use within the Map.
- Parameter **key** to check the presence of.
- Return type: bool, true if **key** is used within the Map,
false otherwise.

#### contains()
Check if a specific item is present within the Map.
- Parameter **value** to check the presence of.
- Return type: bool, true if **value** contained in the Map, false otherwise.

#### clear()
Removes all elements and frees all keys.

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
As a linked collection, acces through index costs more in terms
of computation times than array based collections.

### ArraySet
**UnorderedCollection** implementation that uses data array as
dynamic memory allocation. As a set, **ArraySet** does not
allow duplicates.
**ArraySet** offers good performance if one needs to access data
via indices and allows only one occurrence per value.

### OrderedSet
**OrderedCollection** implementation that uses data array as
dynamic memory allocation. As a set, **OrderedSet** does not
allow duplicates.
**OrderedSet** offers excellent access performance since it relies on array indexing and its data is sorted.

### Stack
**Stack** inherits from **ProcessingCollection** as a last in,
first out collection. The head is therefore set as the last
element to be inserted.

### Queue
**Queue** inherits from **ProcessingCollection** as a
first in, first out collection. The head is therefore set
as the first element to be inserted.

### ArrayMap
**Map** implementation using double data arrays for dynamic
memory allocation. Since **ArrayMap** uses arrays, it also
offers access via index to its elements.

#### at()
Accesses the KeyValue at the specified index. CAUTION: Ensure index is always within bounds, i.e. strictly inferior to size().
- Parameter **index** must be within bounds.
- Return type: KeyValue<TK, TV>, the pair at the given index.

#### operator[]
See **at()**.