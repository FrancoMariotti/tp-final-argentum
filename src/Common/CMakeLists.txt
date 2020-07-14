project(argentum)

add_library(commonLib
            common_proxy_socket.h
            common_proxy_socket.cpp
            Utils.h
            Utils.cpp
            BlockingQueue.h
            ClosedQueueException.h
            ClosedQueueException.cpp
            Message.h
            Message.cpp
            OsException.h
            OsException.cpp
            Socket.h
            Socket.cpp
            Thread.h
            Thread.cpp)