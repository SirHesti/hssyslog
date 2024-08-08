# 08.08.2024 12:16:17 Genrated by cbp2cmake V2.5.0 Finale X86 
project(hssyslog LANGUAGES C)
cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
set (CMAKE_INSTALL_PREFIX /usr )
add_executable(hssyslog tools.c hssyslog.c)
install(TARGETS hssyslog RUNTIME DESTINATION bin)
