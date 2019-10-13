Formatting
==========

Some printable types support formatting.
Formatting is applied with the :cpp:class:`hippo::formatter <template\<typename T> hippo::formatter>` adapter, which itself is a printable type that applies a format to its contents.

Formatting numbers
------------------

The following example shows how numbers can be formatted for a user-defined type:

.. code-block:: cpp

   struct Foo {
     int bar;
     float baz;
   };

   static hippo::integer_format hex() {
     hippo::integer_format fmt;
     fmt.base = hippo::integer_format::base_type::hex;
     return fmt;
   }

   static hippo::float_format scientific() {
     hippo::float_format fmt;
     fmt.format = hippo::float_format::notation_type::scientific;
     return fmt;
   };

   HIPPO_CLASS_BEGIN(Foo)
     HIPPO_CLASS_MEMBER_EXPR(Foo, hippo::formatter(object.bar, hex()))
     HIPPO_CLASS_MEMBER_EXPR(Foo, hippo::formatter(object.baz, scientific()))
   HIPPO_CLASS_END()

Using formatting to print polymorphic types
-------------------------------------------

Polymorphic types can be printed by use of :cpp:class:`hippo::derived_type_printer <template\<typename Base, typename Derived> hippo::derived_type_printer>`:

.. code-block:: cpp

   #include "hippo/hippo.h"
   #include "hippo/std/memory.h"
   #include <iostream>

   struct Foo {
     virtual ~Foo() = default;
   };

   struct Bar : Foo {};
   struct Baz : Foo {};

   HIPPO_CLASS_BEGIN(Foo)
   HIPPO_CLASS_END()

   HIPPO_CLASS_BEGIN(Bar)
     HIPPO_BASE(Foo)
   HIPPO_CLASS_END()

   HIPPO_CLASS_BEGIN(Baz)
     HIPPO_BASE(Foo)
   HIPPO_CLASS_END()

   int main() {
     std::shared_ptr<Foo> foo = std::make_shared<Foo>();
     std::shared_ptr<Foo> bar = std::make_shared<Bar>();
     std::shared_ptr<Foo> baz = std::make_shared<Baz>();
     hippo::dynamic_type_format<Foo> dyn_fmt;
     dyn_fmt.printers.push_back(std::make_shared<hippo::derived_type_printer<Foo, Bar>>());
     dyn_fmt.printers.push_back(std::make_shared<hippo::derived_type_printer<Foo, Baz>>());
     hippo::pointer_format<Foo> fmt = std::move(dyn_fmt);
     hippo::print_to(std::cout, hippo::formatter(foo, fmt), hippo::configuration());
     hippo::print_to(std::cout, hippo::formatter(bar, fmt), hippo::configuration());
     hippo::print_to(std::cout, hippo::formatter(baz, fmt), hippo::configuration());
   }  

Once ``Bar`` and ``Baz`` are registered with the pointer format, the printer is able to use RTTI to determine which printer to use.
The following is printed:

.. code-block:: none

   std::shared_ptr containing [ Foo { } ]
   std::shared_ptr containing [ Bar { Base Foo { } } ]
   std::shared_ptr containing [ Baz { Base Foo { } } ]

Interface
---------

.. doxygenstruct:: hippo::formatter
   :members:
.. doxygenstruct:: hippo::formatter< T * >
   :members:
.. doxygenstruct:: hippo::no_format
   :members:

Number format configurations
^^^^^^^^^^^^^^^^^^^^^^^^^^^^
.. doxygenstruct:: hippo::integer_format
   :members:
.. doxygenstruct:: hippo::float_format
   :members:

Pointer configurations
^^^^^^^^^^^^^^^^^^^^^^
.. doxygentypedef:: hippo::pointer_format
.. doxygenstruct:: hippo::standard_pointer_format
   :members:
.. doxygenstruct:: hippo::address_format
   :members:
.. doxygenstruct:: hippo::dynamic_type_format
   :members:
.. doxygenstruct:: hippo::base_type_printer
   :members:
.. doxygenstruct:: hippo::derived_type_printer
   :members:
