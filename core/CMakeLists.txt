add_library(core)

target_sources(core
        PUBLIC FILE_SET core TYPE CXX_MODULES FILES
        Game.ixx
        EventListener.ixx
        impl/DefaultGame.ixx
)

target_link_libraries(core PRIVATE model)
