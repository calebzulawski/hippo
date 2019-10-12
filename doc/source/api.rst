API reference
=============

Printing values
---------------

.. doxygenstruct:: hippo::configuration
   :members:

.. doxygenfunction:: hippo::print
.. doxygenfunction:: hippo::print_to

Making user-defined types printable
-----------------------------------

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
