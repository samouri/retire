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

type timeSeriesWeeklyCloseValues = array(Victory.victoryData);
let getTimeSeriesWeeklyCloseValues =
    (symbol: string): Js.Promise.t(timeSeriesWeeklyCloseValues) => {
  let uri = endpoint ++ "function=TIME_SERIES_WEEKLY&symbol=" ++ symbol;
  Js.log(uri);
  let ret: Js.Promise.t(timeSeriesWeeklyCloseValues) = [%bs.raw
    {|
      fetch(uri)
        .then(res => res.json())
        .then(res => res["Weekly Time Series"])
        .then(ts =>
          Object.entries(ts).map(x => {
            const date = + new Date(x[0]);
            let closeValue = parseFloat(x[1]['4. close'], 10);
            return {x: date, y: closeValue};
          })
        )
    |}
  ];
  ret;
};