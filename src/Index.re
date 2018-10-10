ReactDOMRe.renderToElementWithId(
  <AppState.Provider> <App /> </AppState.Provider>,
  "app",
);

[%%bs.raw {|
  if ('serviceWorker' in navigator) {
      navigator.serviceWorker.register('./ServiceWorker.bs.js')
        .then(reg => console.log('Service worker succesfully registered', reg))
        .catch(err => console.error('Error registering service worker', err));
  }
|}];