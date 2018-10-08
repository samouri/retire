let component = ReasonReact.statelessComponent("Header");

let make = _children => {
  ...component,
  render: _self =>
    <div
      style=(
        ReactDOMRe.Style.make(
          ~paddingTop="10px",
          ~borderBottom="1px solid " ++ Constants.lightYellowColor,
          ~color=Constants.redColor,
          ~height="50px",
          ~paddingLeft="5px",
          (),
        )
      )>
      <h1 style=(ReactDOMRe.Style.make(~margin="0", ()))>
        (ReasonReact.string("Retire"))
      </h1>
    </div>,
};