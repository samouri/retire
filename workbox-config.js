module.exports = {
  "globDirectory": "build/",
  "globPatterns": [
    "**/*.{html,js}"
  ],
  "swDest": "build/ServiceWorker.js",
  "swSrc": "./src/ServiceWorker.js",
  "maximumFileSizeToCacheInBytes": 5000000
};