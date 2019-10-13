Advanced usage
==============

Sometimes it is necessary to access the internal workings to create a more complicated printer.

Representing of lines of text
-----------------------------

Before we get into printing types, we must understand how outputs are represented.
In Hippo, a line of text is represented by :cpp:class:`hippo::line`, which tracks the indentation level of the line separately from the contents.

.. doxygenstruct:: hippo::line
   :members:

When an object is printed, the generated lines of text are then collected into a :cpp:type:`hippo::object`.
Any lines that are shorter than :cpp:member:`hippo::configuration::width` are condensed into a single line if possible.
Multiple :cpp:type:`hippo::object` may be condensed as well, but only if all of the objects are a single line.

.. doxygentypedef:: hippo::object
.. doxygenfunction:: hippo::condense(const std::list<hippo::line>&, const hippo::configuration&)
.. doxygenfunction:: hippo::condense(const std::list<hippo::object>&, const hippo::configuration&)

Defining a printer
------------------

Printers are added for a type by specializing the :cpp:class:`hippo::printer` struct.
This class is declared as follows:

.. doxygenstruct:: hippo::printer

Specializations must fulfill the following interface:

.. code-block:: cpp

   template<> hippo::printer<Foo> {
     using format_type = /* any default-constructible and copy-constructible type */
     static ::hippo::object print(const Foo &f,
                                  std::uint64_t current_indent,
                                  const ::hippo::configuration &config,
                                  const format_type &format = format_type());

   }

Convenient utilities
--------------------

The following operations are so common when creating printers that Hippo provides them.

Manipulating lines
^^^^^^^^^^^^^^^^^^

.. doxygenstruct:: hippo::prepend_visitor
   :members:
.. doxygenstruct:: hippo::append_visitor
   :members:

Formatting values
^^^^^^^^^^^^^^^^^

.. doxygenfunction:: hippo::apply_format(T, const float_format&)
.. doxygenfunction:: hippo::apply_format(T, const integer_format&)
.. doxygenfunction:: hippo::apply_format(const T *, std::uint64_t, const hippo::configuration&, const pointer_format<T>&)
