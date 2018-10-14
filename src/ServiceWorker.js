/* Offline first, baby */

importScripts(
  "https://storage.googleapis.com/workbox-cdn/releases/3.6.1/workbox-sw.js"
);

if (workbox) {
  console.log(`Yay! Workbox is loaded 🎉`);
} else {
  console.log(`Boo! Workbox didn't load 😬`);
}

// how the heck do i do this reasonable for prod?
workbox.precaching.precacheAndRoute([]);

workbox.routing.registerRoute(
  // Cache assets
  /.*\.js|.*\.css|.*\.html/,
  // Use cache but update in the background ASAP
  workbox.strategies.cacheFirst({
    cacheName: "assets-cache",
    plugins: [
      new workbox.expiration.Plugin({
        // Cache for a maximum of a week
        maxAgeSeconds: 7 * 24 * 60 * 60
      })
    ]
  })
);

workbox.routing.registerRoute(
  // Cache CSS files
  /https:\/\/www.alphavantage.co\/query/,
  // Use cache but update in the background ASAP
  workbox.strategies.cacheFirst({
    cacheName: "api-cache",
    plugins: [
      new workbox.expiration.Plugin({
        // Cache for a maximum of a week
        maxAgeSeconds: 7 * 24 * 60 * 60
      })
    ] 
  })
);
