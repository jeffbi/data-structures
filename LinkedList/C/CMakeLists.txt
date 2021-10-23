add_library("linked_list" ${LIB_TYPE}
            single_linked_list.h single_linked_list.c
            double_linked_list.h double_linked_list.c
           )

add_subdirectory(sample)
