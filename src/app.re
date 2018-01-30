module App = {
let component = ReasonReact.statelessComponent("App");

let make = _children => {
    ...component,
    render: (self) =>
      <Score/>
  };
};

ReactDOMRe.renderToElementWithId(<App/>,"index");