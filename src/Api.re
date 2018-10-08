/* Must have ApiKey.re for this to work */
let endpoint =
  "https://www.alphavantage.co/query?apikey=" ++ ApiKey.key ++ "&";

type timeSeriesData = {hello: string};

let getTimeSeriesWeekly = (symbol: string) => {
  let uri = endpoint ++ "function=TIME_SERIES_WEEKLY&symbol=" ++ symbol;
  Js.Promise.(
    Fetch.fetch(uri)
    |> then_(Fetch.Response.text)
    |> then_(s => Js.Promise.resolve(Js_json.parseExn(s)))
  );
};