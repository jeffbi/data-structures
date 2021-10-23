
add_executable(linked_list_sample_c linked_list_sample.c)

#target_link_libraries(linked_list_sample_c -L../ single_linked_list double_linked_list)
target_link_libraries(linked_list_sample_c -L../ linked_list)
