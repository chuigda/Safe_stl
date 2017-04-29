#ifndef STRINGS_DEFS_H
#define STRINGS_DEFS_H

#define ELEM_COPY_CONSTRUCT_ERROR\
    "Element type T cannot be copy constructed"

#define ELEM_COPY_ASSIGN_ERROR\
    "Element type T cannot be copy assigned"

#define ELEM_DESTROY_ERROR\
    "Element type T cannot be destroyed"

#define TEMPLATE_ARG_NOT_ITERATOR\
    "Template argument Iterator is not an iterator type"

#define TEMPLATE_ARG_NOT_INPUT_ITERATOR\
    "Template argument Iterator is not an input iterator type"

#define TEMPLATE_ARG_NOT_OUTPUT_ITERATOR\
    "Template argument Iterator is not an output iterator type"

#define TEMPLATE_ARG_NOT_FORWARD_ITERATOR\
    "Template argument Iterator is not a forward iterator type"

#define TEMPLATE_ARG_NOT_BIDIRECTIONAL_ITERATOR\
    "Template argument Iterator is not a bidirectional iterator type"

#define TEMPLATE_ARG_NOT_RANDOM_ACCESS_ITERATOR\
    "Template argument Iterator is not a random-access iterator type"

#define TEMPLATE_ARG_NOT_COPY_ASSIGNABLE\
    "Template argument T is not copy-assignable"

#define TEMPLATE_ARG_NOT_MOVE_ASSIGNABLE\
    "Template argument T is not move-assignable"

#define UNINITIALIZED_ITERATOR\
    "This iterator did not get initialized"

#define OLD_ITERATOR\
    "A manipulating operation has been performed on container object"

#define CONTAINER_COPY\
    "Copying container"

#define ARRAY_OVERFLOW\
    "Accessing an invalid target"

#define ITERATOR_OVERFLOW\
    "This iterator is now pointing to an invalid position, for example, end()"

#define DELETED_CONTAINER\
    "Container has been destroyed but iterator left"

#define UNKNOWN_REGION_ITERATOR\
    "This iterator does not come from this container"

#define SPLICE_BETWEEN_UNEQUAL_ALLOC_CONTAINERS\
    "Splicing between two containers which have unequal allocators"

#endif // STRINGS_DEFS_H
