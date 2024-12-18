

```bash
docker build -t easygal-build . 
docker create --name extract-container easygal-build
docker cp extract-container:/usr/src/app/easy_gal.js .
docker cp extract-container:/usr/src/app/easy_gal.wasm .
docker rm extract-container
```