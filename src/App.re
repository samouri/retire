let deoptStr = str =>
  switch (str) {
  | None => ""
  | Some(s) => s
  };

let component = ReasonReact.statelessComponent("App");

let xAxisFormatter = (x: float) =>
  Js.Date.fromFloat(x) |> Js.Date.toLocaleDateString;
let yAxisFormatter = y => Js.Int.toString(y);

let make = _children => {
  ...component,
  render: _self =>
    <AppState.AppStateContext.Consumer>
      ...{
           ({selectedSymbol, symbolData, selectSymbol}) => {
             let selectedStock = deoptStr(selectedSymbol);
             let data: array(Victory.victoryData) =
               switch (Belt.Map.String.get(symbolData, selectedStock)) {
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
                   <SymbolSearch onSubmit=selectSymbol />
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
                                 x->Victory.xGet
                                 |> float_of_int
                                 |> xAxisFormatter
                             }
                             cursorDimension="x"
                           />
                         }
                         domainPadding=20
                         theme=VictoryTheme.material
                         width=1000>
                         <VictoryAxis tickFormat=xAxisFormatter />
                         <VictoryAxis
                           dependentAxis=true
                           tickFormat=yAxisFormatter
                         />
                         <VictoryLine data />
                       </VictoryChart>
                     )
                   </div>
                 </div>
               </div>
             </>;
           }
         }
    </AppState.AppStateContext.Consumer>,
};