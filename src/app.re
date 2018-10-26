module App = {
  let component = ReasonReact.statelessComponent("App");
  let make = _children => {...component, render: (_) => <Score />};
};

ReactDOMRe.renderToElementWithId(<App />, "index");

Dummy.test();