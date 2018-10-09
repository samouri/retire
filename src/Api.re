/* Must have ApiKey.re for this to work */
let endpoint =
  "https://www.alphavantage.co/query?apikey=" ++ ApiKey.key ++ "&";

/* module WeeklyTimeSeriesData = {
     [@bs.deriving abstract]
     type metadata = {
       [@bs.as "1. Information"] information: string,
       [@bs.as "2. Digital Currency Code"] currencyCode: string,
       [@bs.as "3. Digital Currency Name"] currencyName: string,
       [@bs.as "4. Market Code"] marketCode: string,
       [@bs.as "5. Market Name"] marketName: string,
       [@bs.as "6. Last Refreshed"] lastRefreshed: string,
       [@bs.as "7. Time Zone"] timeZone: string,
     };

     [@bs.deriving abstract]
     type weekData = {
       [@bs.as "1. open"] _open: string,
       [@bs.as "2. high"] high: string,
       [@bs.as "3. low"] low: string,
       [@bs.as "4. close"] close: string,
       [@bs.as "5. volume"] marketName: string,
     };

     [@bs.deriving abstract]
     type t = {
       [@bs.as "Meta Data"] metadata: metadata,
       [@bs.as "Time Series (Digital Currency Weekly)"] timeSeries: weekData
     }
   }; */

let decodeObj = json =>
  switch (Js.Json.decodeObject(json)) {
  | None => Js.Dict.empty()
  | Some(d) => d
  };

let decodeStr = json =>
  switch (Js.Json.decodeString(json)) {
  | None => ""
  | Some(s) => s
  };

type timeSeriesWeeklyCloseValues = array((string, float));
external myShadyConversion:
  array((Js.Dict.key, float)) => timeSeriesWeeklyCloseValues =
  "%identity";
let getTimeSeriesWeeklyCloseValues =
    (symbol: string): Js.Promise.t(timeSeriesWeeklyCloseValues) => {
  let uri = endpoint ++ "function=TIME_SERIES_WEEKLY&symbol=" ++ symbol;
  Js.Promise.(
    Fetch.fetch(uri)
    |> then_(Fetch.Response.text)
    |> then_(s => Js.Promise.resolve(Js_json.parseExn(s)))
    |> then_((json: Js.Json.t) => {
         let obj = decodeObj(json);
         let timeSeries = Js.Dict.get(obj, "Weekly Time Series");
         let transformed: timeSeriesWeeklyCloseValues =
           switch (timeSeries) {
           | None => [||]
           | Some(ts) =>
             let intVer =
               Js.Dict.map(
                 (. x) => {
                   let _ = Js.log(x);
                   decodeObj(x)->Js.Dict.unsafeGet("4. close")
                   |> decodeStr
                   |> float_of_string
                 },
                 decodeObj(ts),
               );
             intVer |> Js.Dict.entries |> myShadyConversion;
           };
         Js.Promise.resolve(transformed);
       })
  );
};