file(GLOB hdrs "*.h*")
file(GLOB srcs "*.cpp")

add_executable(Main ${srcs} ${hdrs} Queue.h Stack.h Lex.h)