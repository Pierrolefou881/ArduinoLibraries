# Event
Defines the business logic for callbacks and event handlers. All 
classes of this library implement the same interface.

## Callable
Generic interface for all event based mechanics. **Callable** is a 
template class that needs to define the type for the caller 
(sender) and the calling context (args).

### call()
Calls the wrapped callback(s), which must all respect the same 
signature.
- Parameter **sender** instigator of the call.
- Parameter **args** context and reason for the call.

### equals()
Equality is based on type (represented by a unique character) and
equality of pointers. Equality is needed for using **UnorderedSet**
and removing callbacks from **EventHandler**s.

### operator == and !=
Shortcuts **equals()**.

## EventHandler
Concrete implementation of **Callable**. Holds a list of other **Callable**
to call when the **call()** method gets triggered. **EventHandler** thus
implements additional functionnalities related to managing a set of
**Callable**s.

### register_callback()
Adds a new **Callable** to the set of callbacks. This method exists in two
versions, one that registers a **FunctionCallback**, the other 
registering a **MethodCallback**.

#### **FunctionCallback** version
- Parameter **function** pointer to the function that sall be called.

#### **MethodCallback** version
- Parameter **instance** object of which method shall be called.
- Parameter **method** to be called upon instance.

### remove_callback()
Removes a **callback** from the set of callbacks. Like register_callback,
this method exists in two versions. It uses equality to find out
which callback to remove.

#### **FunctionCallback** version
- Parameter **function** pointer to the function that sall be called.

#### **MethodCallback** version
- Parameter **instance** object of which method shall be called.
- Parameter **method** to be called upon instance.

## FunctionCallback
Concrete implementation of **Callable** specialized with pointer to
functions.

## MethodCallback
Concrete implementation of **Callable** specialized with instance
methods.