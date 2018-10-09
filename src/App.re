type stockData = Belt.Map.String.t(array(Victory.victoryData));
type state = {
  stockData,
  selectedStock: option(string),
};

let deoptStr = str =>
  switch (str) {
  | None => ""
  | Some(s) => s
  };

type action =
  | AddStock(string)
  | RemoveStock(string)
  | AddStockData(string, array(Victory.victoryData));

let component = ReasonReact.reducerComponent("App");

let xAxisFormatter = (x: float) =>
  Js.Date.fromFloat(x) |> Js.Date.toLocaleDateString;
let yAxisFormatter = y => Js.Int.toString(y);

let make = _children => {
  ...component,
  initialState: () => {selectedStock: None, stockData: Belt.Map.String.empty},
  reducer: (action, state) =>
    switch (action) {
    | AddStockData(symbol, stockData) =>
      ReasonReact.Update({
        ...state,
        stockData: Belt.Map.String.set(state.stockData, symbol, stockData),
      })
    | AddStock(symbol) =>
      ReasonReact.UpdateWithSideEffects(
        {...state, selectedStock: Some(symbol)},
        (
          _self =>
            Api.getTimeSeriesWeeklyCloseValues(symbol)
            |> Js.Promise.then_(data => {
                 _self.send(AddStockData(symbol, data));
                 Js.Promise.resolve();
               })
            |> ignore
        ),
      )
    | RemoveStock(_) => ReasonReact.Update({...state, selectedStock: None})
    },
  render: self => {
    let selectedStock = deoptStr(self.state.selectedStock);
    let data: array(Victory.victoryData) =
      switch (Belt.Map.String.get(self.state.stockData, selectedStock)) {
      | None => [||]
      | Some(s) => s
      };
    <>
      <style>
        {
          ReasonReact.string(
            {|
        body {
          background-color: rgb(40, 40, 40);
        }
      |},
          )
        }
      </style>
      <Header />
      <div style={ReactDOMRe.Style.make(~display="flex", ())}>
        <Sidebar />
        <div
          style={
            ReactDOMRe.Style.make(
              ~display="flex",
              ~flexDirection="column",
              (),
            )
          }>
          <SymbolSearch onSubmit={symbol => self.send(AddStock(symbol))} />
          <div
            style={
              ReactDOMRe.Style.make(
                ~display="flex",
                ~height="500px",
                ~paddingLeft="20px",
                (),
              )
            }>
            Victory.(
              <VictoryChart
                containerComponent={
                  <VictoryCursorContainer
                    cursorLabel={
                      (x: Victory.victoryData) =>
                        x->Victory.xGet |> float_of_int |> xAxisFormatter
                    }
                    cursorDimension="x"
                  />
                }
                domainPadding=20
                theme=VictoryTheme.material
                width=1000>
                <VictoryAxis tickFormat=xAxisFormatter />
                <VictoryAxis dependentAxis=true tickFormat=yAxisFormatter />
                <VictoryLine data />
              </VictoryChart>
            )
          </div>
        </div>
      </div>
    </>;
  },
};