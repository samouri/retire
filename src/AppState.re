type symbolData = Belt.Map.String.t(array(Victory.victoryData));
type appState = {
  symbolData,
  selectedSymbol: option(string),
  upsertSymbolData: (string, array(Victory.victoryData)) => unit,
  selectSymbol: string => unit,
};

let defaultValue: appState = {
  symbolData: Belt.Map.String.empty,
  selectedSymbol: None,
  upsertSymbolData: (_, _) => (),
  selectSymbol: _ => (),
};

module AppStateContext =
  Context.MakePair({
    type t = appState;
    let defaultValue = defaultValue;
  });

module Provider = {
  type state = {
    symbolData,
    selectedSymbol: option(string),
  };

  type action =
    | SelectSymbol(string)
    | UpsertSymbolData(string, array(Victory.victoryData));

  let component = ReasonReact.reducerComponent("AppStateProvider");
  let make = children => {
    ...component,
    initialState: () => {
        selectedSymbol: None,
        symbolData: Belt.Map.String.empty,
    },
    reducer: (action: action, state: state) =>
      switch (action) {
      | UpsertSymbolData(symbol, symbolData) =>
        ReasonReact.Update({
          ...state,
          symbolData:
            Belt.Map.String.set(state.symbolData, symbol, symbolData),
        })
      | SelectSymbol(symbol) =>
        ReasonReact.UpdateWithSideEffects(
          {...state, selectedSymbol: Some(symbol)},
          (
            _self =>
              Api.getTimeSeriesWeeklyCloseValues(symbol)
              |> Js.Promise.then_(data => {
                   _self.send(UpsertSymbolData(symbol, data));
                   Js.Promise.resolve();
                 })
              |> ignore
          ),
        )
      },
    render: self =>
      <AppStateContext.Provider
        value={
          ...self.state,
          upsertSymbolData: (symbol, data) =>
            self.send(UpsertSymbolData(symbol, data)),
          selectSymbol: symbol => self.send(SelectSymbol(symbol)),
        }>
        children
      </AppStateContext.Provider>,
  };
};