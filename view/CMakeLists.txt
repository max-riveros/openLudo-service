add_library(view)

target_sources(view
        PUBLIC FILE_SET view TYPE CXX_MODULES FILES
)

target_link_libraries(view PRIVATE controller)
