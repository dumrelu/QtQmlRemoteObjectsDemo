
add_executable(server
    main.cpp
)

qt6_add_repc_sources(server
    ../common/rep/server.rep
)

target_link_libraries(server PRIVATE
    Qt${QT_VERSION_MAJOR}::Core 
    Qt${QT_VERSION_MAJOR}::RemoteObjects
)
