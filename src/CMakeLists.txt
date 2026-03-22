# Создание статической библиотеки
add_library(bst_lib STATIC bst.c)

# Указание заголовочного файла
target_include_directories(bst_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Создание исполняемого файла из main-файла
add_executable(bst main.c)

# Связка исполняемого файла с библиотекой
target_link_libraries(bst PRIVATE bst_lib)
