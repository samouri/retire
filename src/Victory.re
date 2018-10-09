[@bs.deriving abstract]
type victoryData = {
  x: int,
  y: float,
};

module VictoryTheme = {
  type t;
  [@bs.module "victory-core/es/victory-theme/material"] [@bs.val]
  external material: t = "default";
  [@bs.module "victory-core/es/victory-theme/grayscale"] [@bs.val]
  external grayscale: t = "default";
};

module VictoryBar = {
  [@bs.module "victory"]
  external victoryBar: ReasonReact.reactClass = "VictoryBar";
  let make = (~data: option(array(victoryData))=?, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=victoryBar,
      ~props={"data": Js.Undefined.fromOption(data)},
      children,
    );
};

module VictoryCursorContainer = {
  [@bs.module "victory"]
  external victoryBar: ReasonReact.reactClass = "VictoryCursorContainer";
  let make = (~width=?, ~height=?, ~cursorLabel, ~cursorDimension=?,  children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=victoryBar,
      ~props={
        "height": Js.Undefined.fromOption(height),
        "width": Js.Undefined.fromOption(width),
        "cursorLabel": cursorLabel,
        "cursorDimension": cursorDimension,
      },
      children,
    );
};

module VictoryLine = {
  [@bs.module "victory"]
  external victoryLine: ReasonReact.reactClass = "VictoryLine";
  let make = (~data: option(array(victoryData))=?, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=victoryLine,
      ~props={"data": Js.Undefined.fromOption(data)},
      children,
    );
};

module VictoryStack = {
  [@bs.module "victory"]
  external victoryStack: ReasonReact.reactClass = "VictoryStack";
  let make = (~colorScale=?, children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=victoryStack,
      ~props={"colorScale": Js.Undefined.fromOption(colorScale)},
      children,
    );
};

module VictoryChart = {
  [@bs.module "victory"]
  external victoryChart: ReasonReact.reactClass = "VictoryChart";
  let make =
      (
        ~domainPadding=?,
        ~theme: option(VictoryTheme.t)=?,
        ~containerComponent=?,
        ~height=?,
        ~width=?,
        children,
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=victoryChart,
      ~props={
        "domainPadding": Js.Undefined.fromOption(domainPadding),
        "theme": Js.Undefined.fromOption(theme),
        "height": Js.Undefined.fromOption(height),
        "width": Js.Undefined.fromOption(width),
        "containerComponent": Js.Undefined.fromOption(containerComponent),
      },
      children,
    );
};

module VictoryAxis = {
  [@bs.module "victory"]
  external victoryAxis: ReasonReact.reactClass = "VictoryAxis";
  let make =
      (
        ~tickValues=?,
        ~tickFormat: option('a => string)=?,
        ~dependentAxis: option(bool)=?,
        children,
      ) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=victoryAxis,
      ~props={
        "tickValues": Js.Undefined.fromOption(tickValues),
        "tickFormat": Js.Undefined.fromOption(tickFormat),
        "dependentAxis": Js.Undefined.fromOption(dependentAxis),
      },
      children,
    );
};

module VictoryArea = {
  [@bs.module "victory"]
  external victoryArea: ReasonReact.reactClass = "VictoryArea";
  let make = (~animate=?, ~data=?, ~interpolation="linear", children) =>
    ReasonReact.wrapJsForReason(
      ~reactClass=victoryArea,
      ~props={
        "animate": Js.Undefined.fromOption(animate),
        "data": Js.Undefined.fromOption(data),
        "interpolation": interpolation,
      },
      children,
    );
};