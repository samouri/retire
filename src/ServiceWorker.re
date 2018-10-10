/* Offline first, baby */

/* module WebStorage = {
     open Dom.Storage;

     type storedData('a) = {
       data: 'a,
       lastUpdated: Js.Date.t,
     };

     let getStockData = symbol => {
       let item = getItem(symbol, localStorage);
         switch (item) {
         | None => None
         | Some(json) =>
           ignore(json);
           let parsed: storedData(array(Victory.victoryData)) = [%bs.raw {| JSON.parse(json)]) |}]);
         }
     };
   }; */

type caches;
type cache;
type response;

[@bs.val] external window: Dom.window = "";
[@bs.get] external getCaches: Dom.window => caches = "caches";

module CacheStorage = {
  [@bs.send.pipe: caches] external match: string => Js.Promise.t(option(cache)) = "";
  [@bs.send.pipe: caches] external has: string => Js.Promise.t(bool) = "";
  [@bs.send.pipe: caches] external access: string => Js.Promise.t(cache) = "open";
  [@bs.send.pipe: caches] external delete: string => Js.Promise.t(bool) = "";
  [@bs.send.pipe: caches] external keys: Js.Promise.t(Js.Array.t(string)) = "";
};

module Cache = {
  [@bs.send.pipe: cache] external match: string => Js.Promise.t(response) = "";
  [@bs.send.pipe: cache] external add: string => Js.Promise.t(unit) = "";
  [@bs.send.pipe: cache] external addAll: Js.Array.t(string) => Js.Promise.t(unit) = "";
  [@bs.send.pipe: cache] external delete: string => Js.Promise.t(bool) = "";
  [@bs.send.pipe: cache] external keys: Js.Promise.t(Js.Array.t(string)) = "";
};