FROM emscripten/emsdk:3.1.73

WORKDIR /usr/src/app

COPY . .

RUN make wasm

CMD [ "bash" ]