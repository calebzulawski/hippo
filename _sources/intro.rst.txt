Introduction
============

Using Hippo
-----------

Hippo is a header-only library, so install the headers however you'd like.

To begin using Hippo, include the following:

.. code-block:: cpp

   #include "hippo/hippo.h"

Printing a value
----------------

Printing values is performed by the :cpp:func:`hippo::print` or :cpp:func:`hippo::print_to` functions.
Both functions take a value and a :cpp:class:`hippo::configuration` and produce a pretty-printed output.

A simple example of printing a vector:

.. code-block:: cpp
   
   #include "hippo/hippo.h"
   #include "hippo/std/vector.h"
   #include <iostream>

   int main() {
     std::vector<int> v {0, 1, 2};
     hippo::print_to(std::cout, v, hippo::configuration());
   }

This example will print:

.. code-block:: none

   std::vector [0, 1, 2]

Interface
---------

.. doxygenstruct:: hippo::configuration
   :members:

.. doxygenfunction:: hippo::print
.. doxygenfunction:: hippo::print_to
