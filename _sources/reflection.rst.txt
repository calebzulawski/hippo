Printing user-defined types via reflection
==========================================

.. code-block::

   #include "hippo/hippo.h"

Classes
-------
Hippo provides utilities for printing user-defined types. Consider the following types:

.. code-block:: cpp

   struct Foo {
     int a;
     float b;
   };

   struct Bar {
     std::vector<Foo> foos;
   };

To print these types, we reflect the type using :c:macro:`HIPPO_CLASS_BEGIN`, :c:macro:`HIPPO_MEMBER`, and :c:macro:`HIPPO_CLASS_END`:

.. code-block:: cpp

   #include "hippo/hippo.h"       // reflection macros
   #include "hippo/std/vector.h"  // std::vector printer
   
   HIPPO_CLASS_BEGIN(Foo)
     HIPPO_MEMBER(a)
     HIPPO_MEMBER(b)
   HIPPO_CLASS_END()
   
   HIPPO_CLASS_BEGIN(Bar)
     HIPPO_MEMBER(foos)
   HIPPO_CLASS_END()

The printers for ``int``, ``float``, and ``std::vector`` are all provided by Hippo.
Once we've provided the printer for ``Foo``, we are able to use it to print ``Bar``.
A printed instance of ``Bar`` might look something like this:

.. code-block:: none

   Bar {
     foos: std::vector [
       Foo { a: 1, b: 0.5 },
       Foo { a: 2, b: -3.1 }
     ]
   }

Enums
-----
Like classes, enums can be reflected wish :c:macro:`HIPPO_ENUM_BEGIN`, :c:macro:`HIPPO_ENUM_VALUE`, and :c:macro:`HIPPO_ENUM_END`:

.. code-block:: cpp

   enum Foo {
       Bar,
       Baz
   };

   HIPPO_ENUM_BEGIN(Foo)
     HIPPO_ENUM_VALUE(Bar)
     HIPPO_ENUM_VALUE(Baz)
   HIPPO_ENUM_END()

Base classes
------------
Hippo can also reflect base classes with :c:macro:`HIPPO_BASE`:

.. code-block:: cpp

   struct Foo : Bar {
       /* members */
   };
   
   HIPPO_CLASS_BEGIN(Foo)
     HIPPO_BASE(Bar)
     /* members */
   HIPPO_CLASS_END()

Custom member access expressions
--------------------------------
In some cases, it's useful to use another expression to access a member.
This is accomplished by using the :c:macro:`HIPPO_MEMBER_EXPR` macro, which allows a custom expression to be provided, operating on the input ``object``:

.. code-block:: cpp

   class Foo {
       int bar;
   public:
       Foo(int bar) : bar(bar) {}
       int get_bar() const { return bar; }
   };

   HIPPO_CLASS_BEGIN(Foo)
     HIPPO_MEMBER_EXPR(bar, object.get_bar())
   HIPPO_CLASS_END()

Interface
---------
Class reflection
^^^^^^^^^^^^^^^^
.. doxygendefine:: HIPPO_CLASS_BEGIN
.. doxygendefine:: HIPPO_CLASS_END
.. doxygendefine:: HIPPO_BASE
.. doxygendefine:: HIPPO_MEMBER
.. doxygendefine:: HIPPO_MEMBER_EXPR

Enum reflection
^^^^^^^^^^^^^^^
.. doxygendefine:: HIPPO_ENUM_BEGIN
.. doxygendefine:: HIPPO_ENUM_END
.. doxygendefine:: HIPPO_ENUM_VALUE
