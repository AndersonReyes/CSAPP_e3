FROM debian:bookworm

RUN apt-get update && apt-get install build-essential -y valgrind binutils gcc-multilib
