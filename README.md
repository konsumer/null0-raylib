This is null0 host, implemented with raylib.

> [!WARNING]  
> I am just experimenting with ideas here. It has a long way to go.

## building

```
# get build-tools and stuff
npm i

# build everything: native/emscripten host & carts
npm run build

# just carts
npm run build:carts

# just emscripten host
npm run build:web

# just native host
npm run build:native

# run a live-reloading server for web (carts and host)
npm start
```
