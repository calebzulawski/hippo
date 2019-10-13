Out-of-the-box type support
===========================

As discussed in :ref:`reflection`, ``struct``, ``class``, ``enum``, and ``enum class`` are all supported via macros.

In addition to user defined types, most types provided by the language are automatically supported.
All builtin types are supported, as well as many from the standard library.

Supported standard library types
--------------------------------

Strings
^^^^^^^

In addition to ``const char *``, Hippo supports ``std::string`` via ``"hippo/std/string.h"``.

Containers
^^^^^^^^^^

Support for all containers is available:

* ``std::array`` via ``"hippo/std/array.h"``
* ``std::vector`` via ``"hippo/std/vector.h"``
* ``std::list`` via ``"hippo/std/list.h"``
* ``std::forward_list`` via ``"hippo/std/forward_list.h"``
* ``std::deque`` via ``"hippo/std/deque.h"``
* ``std::set`` and ``std::multiset`` via ``"hippo/std/set.h"``
* ``std::unordered_set`` and ``std::unordered_multiset`` via ``"hippo/std/unordered_set.h"``
* ``std::map`` and ``std::multimap`` via ``"hippo/std/map.h"``
* ``std::unordered_map`` and ``std::unordered_multimap`` via ``"hippo/std/unordered_map.h"``

All containers can be formatted with the format configuration of the inner type(s).
Map types can be formatted with:

.. doxygentypedef:: hippo::map_format

Tuples
^^^^^^

Both ``std::pair`` and ``std::tuple`` are supported, by ``"hippo/std/utility.h"`` and ``"hippo/std/tuple.h"``, respectively.

They can be formatted with:

.. doxygentypedef:: hippo::pair_format
.. doxygentypedef:: hippo::tuple_format

Smart pointers
^^^^^^^^^^^^^^

In addition to plain pointers, ``std::unique_ptr``, ``std::shared_ptr``, and ``std::weak_ptr`` are supported via ``"hippo/std/memory.h"``.
These types are all formattable by :cpp:type:`hippo::pointer_format`.

Sum types
^^^^^^^^^

``std::optional`` is supported via ``"hippo/std/optional.h"`` and is formattable with the inner type's format configuration.
``std::variant`` is supported via ``"hippo/std/variant.h"`` and is formattable with:

.. doxygentypedef:: hippo::variant_format

Chrono
^^^^^^
``std::chrono::duration`` is supported via ``"hippo/std/chrono.h"`` and is formattable with the inner type's format configuration.

Complex
^^^^^^^

``std::complex`` is supported via ``"hippo/std/complex.h"`` and is formattable with the inner type's format configuration.

Atomic
^^^^^^

``std::atomic`` is supported via ``"hippo/std/atomic.h"`` and is formattable with the inner type's format configuration.

Bitset
^^^^^^

``std::bitset`` is supported via ``"hippo/std/bitset.h"`` and is not formattable.
