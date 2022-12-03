#!/bin/bash
tmux splitw -h -p 50 "gdbserver :5555 ./test"
tmux selectp -t 0
gdb -x debug.gdb
