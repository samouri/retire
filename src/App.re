type state = {
  stockInput: string,
  selectedStock: option(string),
};

type action =
  | SetStockInput(string)
  | AddStock(string)
  | RemoveStock(string);

let component = ReasonReact.reducerComponent("App");

let xAxisFormatter = x => Js.Int.toString(x);

let yAxisFormatter = y => Js.Int.toString(y / 1000) ++ "k";

let data = [|
  {"x": 2015, "y": 13000},
  {"x": 2016, "y": 16500},
  {"x": 2017, "y": 14250},
  {"x": 2018, "y": 19000},
|];

let make = _children => {
  ...component,
  initialState: () => {selectedStock: None, stockInput: ""},
  reducer: (action, state) =>
    switch (action) {
    | SetStockInput(v) => ReasonReact.Update({...state, stockInput: v})
    | AddStock(stock) =>
      ReasonReact.UpdateWithSideEffects(
        {...state, selectedStock: Some(stock)},
        (
          _self => {
            Api.getTimeSeriesWeekly(stock)
            |> Js.Promise.then_(data => {
                 Js.log(data);
                 Js.Promise.resolve(data);
               })
            |> ignore;
            ();
          }
        ),
      )
    | RemoveStock(_) => ReasonReact.Update({...state, selectedStock: None})
    },
  render: self =>
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
          <form
            onSubmit={
              event => {
                ReactEvent.Form.preventDefault(event);
                Js.log(ReactEvent.Form.target(event));
                self.send(AddStock(self.state.stockInput));
              }
            }>
            <input
              type_="search"
              maxLength=60
              placeholder="Search stocks"
              onChange={
                event =>
                  self.send(
                    SetStockInput(ReactEvent.Form.target(event)##value),
                  )
              }
              style={
                ReactDOMRe.Style.make(
                  ~display="flex",
                  ~border="0",
                  ~margin="0",
                  ~padding="0",
                  ~paddingLeft="60px",
                  ~width="100%",
                  ~height="65px",
                  ~maxWidth="500px",
                  ~fontSize="30px",
                  ~fontWeight="300",
                  ~background="transparent",
                  ~outline="none",
                  ~color="#f0f0f0",
                  (),
                )
              }
            />
          </form>
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
              <VictoryChart domainPadding=20 theme=VictoryTheme.material>
                <VictoryAxis
                  tickValues=[|2015, 2016, 2017, 2018|]
                  tickFormat=xAxisFormatter
                />
                <VictoryAxis dependentAxis=true tickFormat=yAxisFormatter />
                <VictoryLine data />
              </VictoryChart>
            )
          </div>
        </div>
      </div>
    </>,
};