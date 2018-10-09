type state = {symbolInput: string};

type action =
  | SymbolChange(string);

let component = ReasonReact.reducerComponent("SymbolSearch");

let make = (~onSubmit, _children) => {
  ...component,
  initialState: () => {symbolInput: ""},
  reducer: (action, state) =>
    switch (action) {
    | SymbolChange(v) => ReasonReact.Update({symbolInput: v})
    },
  render: self =>
    <>
      <form
        onSubmit={
          event => {
            ReactEvent.Form.preventDefault(event);
            onSubmit(self.state.symbolInput);
          }
        }>
        <input
          type_="search"
          maxLength=60
          placeholder="Search stocks"
          onChange={
            event =>
              self.send(SymbolChange(ReactEvent.Form.target(event)##value))
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
    </>,
};