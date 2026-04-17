add_library(commands_if)

target_sources(commands_if
        PUBLIC FILE_SET commands_if TYPE CXX_MODULES FILES
        commands/Command.ixx
)


add_library(ui_if)

target_sources(ui_if
        PUBLIC FILE_SET ui_if TYPE CXX_MODULES FILES
        UI.ixx
)

target_link_libraries(ui_if PRIVATE model)


add_library(game_server_if)

target_sources(game_server_if
        PUBLIC FILE_SET game_server_if TYPE CXX_MODULES FILES
        IGameServer.ixx
)

target_link_libraries(game_server_if PRIVATE ui_if core commands_if)


add_library(commands)

target_sources(commands
        PUBLIC FILE_SET commands TYPE CXX_MODULES FILES
        commands/impl/RollDiceCommand.ixx
        commands/impl/SelectPawnCommand.ixx
        commands/impl/QuitCommand.ixx
        commands/impl/RegisterCommand.ixx
        commands/impl/StartGameCommand.ixx
)

target_link_libraries(commands PRIVATE commands_if game_server_if)


add_library(game_server)

target_sources(game_server
        PUBLIC impl/GameServer.cpp
        PUBLIC FILE_SET game_server TYPE CXX_MODULES FILES
        GameServer.ixx
)

target_link_libraries(game_server PRIVATE game_server_if commands)


add_library(tui)

target_sources(tui
        PUBLIC FILE_SET tui TYPE CXX_MODULES FILES
        impl/TUI.ixx
)

target_link_libraries(tui PRIVATE ui_if core model commands)
