add_library(bit_input_stream ./input/BitInputStream.cpp)
target_include_directories(bit_input_stream PUBLIC ./input)
#target_link_libraries(bit_input_stream PUBLIC huffman_encoder)

add_library(bit_output_stream ./output/BitOutputStream.cpp)
target_include_directories(bit_output_stream PUBLIC ./output)
#target_link_libraries(bit_output_stream PUBLIC huffman_encoder)