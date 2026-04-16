add_library(ui_if)

target_sources(ui_if
        PUBLIC FILE_SET ui_if TYPE CXX_MODULES FILES
        UI.ixx
)

target_link_libraries(ui_if PRIVATE model)


add_library(ui)

target_sources(ui
        PUBLIC FILE_SET ui TYPE CXX_MODULES FILES
        impl/TUI.ixx
        impl/NetworkUI.ixx
)

target_link_libraries(ui PRIVATE core model)
