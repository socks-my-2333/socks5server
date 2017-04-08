SOURCES := main.c client.c defs.h s5.c s5.h server.c util.c sutil.c \
b64/b64.c \
uv/fs-poll.c uv/heap-inl.h uv/inet.c \
uv/queue.h uv/threadpool.c uv/uv-common.c uv/uv-common.h \
uv/version.c uv/unix/async.c uv/unix/atomic-ops.h \
uv/unix/core.c uv/unix/dl.c uv/unix/fs.c \
uv/unix/getaddrinfo.c uv/unix/getnameinfo.c \
uv/unix/internal.h uv/unix/loop-watcher.c uv/unix/loop.c \
uv/unix/pipe.c uv/unix/poll.c uv/unix/process.c \
uv/unix/signal.c uv/unix/spinlock.h uv/unix/stream.c \
uv/unix/tcp.c uv/unix/thread.c uv/unix/timer.c \
uv/unix/tty.c uv/unix/udp.c \
uv/unix/proctitle.c \
uv/unix/linux-core.c \
uv/unix/linux-inotify.c uv/unix/linux-syscalls.c \
uv/unix/linux-syscalls.h

.PHONY: all clean

s5-proxy:
	gcc $(SOURCES) -o s5 -Iinclude -Iuv -lpthread -ldl -lrt -Lb64 -lb64 -rdynamic -std=gnu99 -DNDEBUG

clean:
	find . -name "*.o" -exec rm {} \;

#getopt.c 
