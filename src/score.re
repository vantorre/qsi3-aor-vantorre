open Tennis;

type action =
  | ScorePlayerOne
  | ScorePlayerTwo
  | NewGame;

type state = {score: score};
let component = ReasonReact.reducerComponent("Score");

let make = (_children) => {
  ...component,
  initialState: () => {score : newGame}, 
  reducer: (action, state) =>
  switch (action) {
  | ScorePlayerOne => ReasonReact.Update({score:score(state.score, PlayerOne) })
  | ScorePlayerTwo => ReasonReact.Update({score:score(state.score, PlayerTwo) })
  | NewGame => ReasonReact.Update({score : newGame})
  },
  render: (self) => {
    let strScore = string_of_score(self.state.score);
    <div>
        <h1>{ReasonReact.stringToElement(strScore)}</h1>
        
       ( switch self.state.score {
        | Game(p) => <button onClick=((_)=>self.send(NewGame)) >{ReasonReact.stringToElement("New Game")}</button>
        | _ => (<div>{ReasonReact.stringToElement("Who scored ?")}
                <button onClick=((_)=>self.send(ScorePlayerOne)) >{ReasonReact.stringToElement(" Player 1 ")}</button>
                <button onClick=((_)=>self.send(ScorePlayerTwo)) >{ReasonReact.stringToElement(" Player 2 ")}</button>
                </div>)
        })
        
    </div>
  }
};