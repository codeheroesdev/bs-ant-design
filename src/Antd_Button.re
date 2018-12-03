module IconName = Antd_IconName;

[@bs.module] external reactClass: ReasonReact.reactClass = "antd/lib/button";

[%bs.raw {|require("antd/lib/button/style")|}];

[@bs.deriving jsConverter]
type buttonType = [ | `primary | `ghost | `dashed | `danger];

[@bs.deriving jsConverter]
type buttonShape = [ | `circle' | [@bs.as "circle-outline"] `circleOutline];

[@bs.deriving jsConverter]
type buttonSize = [ | `small | `default | `large];

module LoadingProps = {
  type delay = {. "delay": int};
  type t =
    | Bool(bool)
    | Delay(delay);
  type js;
  external ofBool: bool => js = "%identity";
  external ofDelay: delay => js = "%identity";
  let toJs: t => js =
    fun
    | Bool(a) => a |> ofBool
    | Delay(a) => a |> ofDelay;
};

[@bs.deriving abstract]
type jsProps = {
  [@bs.optional] [@bs.as "type"]
  _type: string,
  [@bs.optional]
  htmlType: string,
  [@bs.optional]
  icon: IconName.t,
  [@bs.optional]
  shape: string,
  [@bs.optional]
  size: string,
  [@bs.optional]
  onClick: ReactEvent.Mouse.t => unit,
  [@bs.optional]
  onMouseUp: ReactEvent.Mouse.t => unit,
  [@bs.optional]
  onMouseDown: ReactEvent.Mouse.t => unit,
  [@bs.optional]
  tabIndex: int,
  [@bs.optional]
  loading: LoadingProps.js,
  [@bs.optional]
  disabled: bool,
  [@bs.optional]
  ghost: bool,
  [@bs.optional]
  target: string,
  [@bs.optional]
  href: string,
  [@bs.optional]
  download: string,
  [@bs.optional]
  id: string,
  [@bs.optional]
  className: string,
  [@bs.optional]
  style: ReactDOMRe.Style.t,
  [@bs.optional] [@bs.as "data-testid"]
  testID: string,
};

let make =
    (
      ~_type=?,
      ~htmlType=?,
      ~icon=?,
      ~shape=?,
      ~size=?,
      ~onClick=?,
      ~onMouseUp=?,
      ~onMouseDown=?,
      ~tabIndex=?,
      ~loading: option(LoadingProps.t)=?,
      ~disabled=?,
      ~ghost=?,
      ~target=?,
      ~href=?,
      ~download=?,
      ~id=?,
      ~className=?,
      ~style=?,
      ~testID=?,
      children,
    ) =>
  ReasonReact.wrapJsForReason(
    ~reactClass,
    ~props=
      jsProps(
        ~_type=?Js.Option.map((. b) => buttonTypeToJs(b), _type),
        ~htmlType?,
        ~icon?,
        ~shape=?Js.Option.map((. b) => buttonShapeToJs(b), shape),
        ~size=?Js.Option.map((. b) => buttonSizeToJs(b), size),
        ~onClick?,
        ~onMouseUp?,
        ~onMouseDown?,
        ~tabIndex?,
        ~loading=?Js.Option.map((. b) => LoadingProps.toJs(b), loading),
        ~disabled?,
        ~ghost?,
        ~target?,
        ~href?,
        ~download?,
        ~id?,
        ~className?,
        ~style?,
        ~testID?,
        (),
      ),
    children,
  );