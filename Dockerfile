FROM ubuntu:latest

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y \
    g++ \
	make \
	gdb \
	valgrind \
    && rm -rf /var/lib/apt/lists/*


WORKDIR /app


COPY Makefile ./
COPY src/ ./src/


RUN make

ENTRYPOINT ["/bin/bash", "-c"]
CMD ["/bin/bash"]