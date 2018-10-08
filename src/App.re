let component = ReasonReact.statelessComponent("App");

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
  render: _self =>
    <>
      <style>
        (
          ReasonReact.string(
            {|
        body {
          background-color: rgb(40, 40, 40);
        }
      |},
          )
        )
      </style>
      <Header />
      <div style=(ReactDOMRe.Style.make(~display="flex", ()))>
        <Sidebar />
        <div
          style=(
            ReactDOMRe.Style.make(
              ~display="flex",
              ~flexDirection="column",
              (),
            )
          )>
          <input
            type_="search"
            maxLength=60
            placeholder="Search stocks"
            style=(
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
            )
          />
          <div
            style=(
              ReactDOMRe.Style.make(
                ~display="flex",
                ~height="500px",
                ~paddingLeft="20px",
                (),
              )
            )>
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