add_library(ui)

target_sources(ui
        PUBLIC FILE_SET ui TYPE CXX_MODULES FILES
        TUI.ixx
        EventListener.ixx
        impl/TuiEventListener.cpp
)

target_link_libraries(ui PRIVATE core)
