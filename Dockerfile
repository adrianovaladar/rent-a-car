# Stage 1: Build
FROM ubuntu:latest AS builder

LABEL authors="adrianovaladar"

RUN apt-get update && \
    apt-get install -y \
        cmake \
        build-essential \
        git \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /build

COPY . .

RUN cmake . && \
    make

# Stage 2: Run
FROM ubuntu:latest

LABEL authors="adrianovaladar"

WORKDIR /usr/src/app

COPY --from=builder /build/rent_a_car .

RUN mkdir -p /usr/src/app/files

CMD ["./rent_a_car"]
